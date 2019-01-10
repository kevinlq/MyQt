/* This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 */

#include <QDebug>
#include "DcmTagItem.h"
#include "DcmTagPixelData.h"
#include "DcmTagString.h"
#include "DcmTagSS.h"
#include "DcmTagUS.h"
#include "DcmTagSL.h"
#include "DcmTagUL.h"
#include "DcmTagAT.h"
#include "DcmTagFL.h"
#include "DcmTagFD.h"
#include "DcmTagSQ.h"
#include "DcmReader.h"

DcmReader::DcmReader(DcmStream *streamPtr, DcmDictionary *dictionaryPtr)
    : m_streamPtr(streamPtr),
      m_dictPtr(dictionaryPtr),
      m_error(false),
      m_errorText(),
      m_tagKey(),
      m_group(0),
      m_sequenceLevel(0),
      m_transferSyntax(),
      m_ignoreMetaInfoTransferSyntax(false),
      m_dictVr(DcmVr::Invalid),
      m_dictMinVm(0),
      m_dictMaxVm(DcmMultiplicity_Unknown),
      m_dictModVm(1),
      m_size(0),
      m_vr(),
      m_vrSize(),
      m_itemRealSize(0),
      m_sequenceRealSize(0),
      m_charSet()
{
    Q_ASSERT(streamPtr);

    if (0 == dictionaryPtr) {
        // Use default dictionary if not specified
        m_dictPtr = DcmDictionary::getInstancePtr();
    }
}

DcmDataset DcmReader::readDataset()
{
    DcmDataset dataset;

    // Take transfer syntax form currently set in streamer
    m_transferSyntax = m_streamPtr->transferSyntax();
    m_sequenceLevel = 0;

    // Read tags one by one to populate the dataset
    DcmTag *tagPtr = 0;
    while (0 != (tagPtr = readTag())) {
        if (isError()) {
            // Error detected when reading a tag
            delete tagPtr;
            return DcmDataset();
        }

        // Check for invalid tag keys
        DcmTagKey tagKey = tagPtr->tagKey();
        if ((tagKey == DcmTagKey::Item)
                || (tagKey == DcmTagKey::ItemDeliminationItem)
                || (tagKey == DcmTagKey::SequenceDeliminationItem)) {
            // These tags are a part of sequence, cannot have them here
            setError(QObject::tr("Invalid tag found while reading."));
            delete tagPtr;
            return DcmDataset();
        }

        if (tagKey.isGroupSize()) {
            // Ignore group size tags
            delete tagPtr;
        } else {
            dataset.insertAndRetain(tagPtr);
        }
    }

    if (m_sequenceLevel != 0) {
        QString prevError = errorText();
        setError(QObject::tr("Unbalanced %1 sequnce tag detected. %2")
                 .arg(m_sequenceLevel)
                 .arg(prevError));
        return DcmDataset();
    }

    return dataset;
}

DcmTag* DcmReader::readTag()
{
    DcmTag *tagPtr = 0;

    if (m_streamPtr->atEnd()) {
        // End of data stream detected
        return 0;
    }

    // Read tag key first
    *m_streamPtr >> m_tagKey;

    if (m_group != m_tagKey.group() && m_sequenceLevel == 0) {
        // Switching current group
        m_group = m_tagKey.group();
    }

    // Dictionary look-up
    m_dictMinVm = 1;
    m_dictMaxVm = 1;
    m_dictModVm = 1;
    if (m_tagKey.isGroupSize()) {
        // Group tags are not in the dictionary
        m_dictVr = DcmVr::UL;
    } else if (m_tagKey.isPrivate() && m_tagKey.element() == 0x0010) {
        // This tag is PrivateCreator
        m_dictVr = DcmVr::LO;
    } else {
        DcmTagDescription tagDescription = m_dictPtr->findByTagKey(m_tagKey);
        if (tagDescription.isValid()) {
            // Dictionary record found
            m_dictVr = tagDescription.vr();
            m_dictMinVm = tagDescription.vmMin();
            m_dictMaxVm = tagDescription.vmMax();
            m_dictModVm = tagDescription.vmMod();
        } else {
            // Tag key not found in the dictionary
            m_dictVr = DcmVr::Invalid;
            m_dictMinVm = 0;
            m_dictMaxVm = DcmMultiplicity_Unknown;
            m_dictModVm = 1;
        }
    }

    // Check item or sequence delimiters
    if ((m_tagKey == DcmTagKey::Item)
            || (m_tagKey == DcmTagKey::ItemDeliminationItem)
            || (m_tagKey == DcmTagKey::SequenceDeliminationItem)) {
        if (0 == m_sequenceLevel) {
            // We are not in a sequence
            setError(QObject::tr("Delimination tag outside sequence"));
            return 0;
        }

        *m_streamPtr >> m_size;

        if ((m_tagKey == DcmTagKey::ItemDeliminationItem) || (m_tagKey == DcmTagKey::SequenceDeliminationItem)) {
            // For delimiters size must be zero
            if (m_size != 0) {
                setError(QObject::tr("Delimiter tag must have zero length"));
                return 0;
            }
        }

        if (m_tagKey == DcmTagKey::Item) {
            tagPtr = new DcmTagItem();
        } else {
            // We use 'abstract' tag here just to report delimiter
            tagPtr = new DcmTag(m_tagKey, DcmVr::None);
        }

        return tagPtr;
    }

    if (m_streamPtr->transferSyntax().encoding() == DcmEncoding_Explicit) {
        *m_streamPtr >> m_vr;

        if (m_vr == DcmVr::Invalid) {
            setError(QObject::tr("Tag %1 has invalid value representation.").arg(m_tagKey.toString()));
            return 0;
        }

        *m_streamPtr >> m_vrSize;

        if (m_vr.isBinary() || m_vr == DcmVr::SQ || m_vr == DcmVr::UT) {
            // For binary, sequences, and unlimited text the VR size must be zero
            if (m_vrSize != 0) {
                setError(QObject::tr("Tag %1 must have zero VR size").arg(m_tagKey.toString()));
                return 0;
            }

            *m_streamPtr >> m_size;
        } else {
            // All other tags has 2-bytes encoded size (along with VR).
            m_size = m_vrSize;
        }

    } else {
        // Implicit encoding - take VR from the dictionary
        // Assume UN representation for tags not defined in dictionary
        m_vr = (m_dictVr == DcmVr::Invalid) ?  DcmVr::UN : m_dictVr;

        *m_streamPtr >> m_size;

        // For unknown size, assume sequence
        if (m_size == DcmSize_Undefined) {
            m_vr = DcmVr::SQ;
        }
    }

    // Preventive check: we still have data to read but stream is over
    if (m_streamPtr->atEnd() && m_size > 0) {
        setError(QObject::tr("Unexpected end of stream"));
        return 0;
    }

    // All tags, except binary, sequence and UI must have even length
    if (!m_vr.isBinary() && m_vr != DcmVr::SQ && m_vr != DcmVr::UI && (m_size & 1)) {
        setError(QObject::tr("Tag %1 %2 must have an even length, but % was read")
                 .arg(m_tagKey.toString())
                 .arg(m_vr.toString())
                 .arg(m_size));
        return 0;
    }

    // Parse tag according to its type
    if (m_tagKey == DcmTagKey::PixelData) {
        if (!m_vr.isBinary()) {
            setError(QObject::tr("Pixel data tag must have binary VR, but %1 read instead")
                     .arg(m_vr.toString()));
            return 0;
        }
        tagPtr = readTagAsPixelData();
    } else if (m_vr.isBinary()) {
        tagPtr = readTagAsBinary();
    } else if (m_vr.isString()) {
        tagPtr = readTagAsString();
        if (tagPtr && m_tagKey == DcmTagKey::TransferSyntaxUID) {
            // Save transfer syntax defined in meta info header for further use
            m_transferSyntax = DcmTransferSyntax::fromUid(tagPtr->value().toString());
        } else if (tagPtr && m_tagKey == DcmTagKey::SpecificCharacterSet) {
            // Save character set
            DcmCharSet cs = DcmCharSet::forName(tagPtr->value().toString());
            if (cs.isValid()) {
                m_charSet = cs;
            } else {
                qWarning() << "Unkown character set" << tagPtr->value().toString()
                           << "will be ignored";
            }
        }
    } else if (m_vr == DcmVr::SQ) {
        tagPtr = readTagAsSequence();
    } else if (m_vr == DcmVr::SS) {
        tagPtr = readTagAsSS();
    } else if (m_vr == DcmVr::US) {
        tagPtr = readTagAsUS();
    } else if (m_vr == DcmVr::SL) {
        tagPtr = readTagAsSL();
    } else if (m_vr == DcmVr::UL) {
        tagPtr = readTagAsUL();
    } else if (m_vr == DcmVr::AT) {
        tagPtr = readTagAsAT();
    } else if (m_vr == DcmVr::FL) {
        tagPtr = readTagAsFL();
    } else if (m_vr == DcmVr::FD) {
        tagPtr = readTagAsFD();
    } else {
        // Whatever else is terated as binary
        tagPtr = readTagAsBinary();
    }

    if (tagPtr) {
        // Check for the meta-header is over
        if (m_tagKey.group() == 0x0002) {
            if (m_tagKey.element() == 0x0000) {
                // Meta-header is just started
                m_metaHeaderSize = tagPtr->value().toUInt();
                m_metaHeaderRead = 0;
            } else {
                // Any other tag in the meta-hader
                m_metaHeaderRead += tagPtr->size(m_streamPtr->transferSyntax());
                if (m_metaHeaderRead > m_metaHeaderSize) {
                    delete tagPtr;
                    setError(QString("Meta-header group size is invalid. Encoded %1, but read %2")
                             .arg(m_metaHeaderSize).arg(m_metaHeaderRead));
                    return 0;
                }

                if (!m_ignoreMetaInfoTransferSyntax && m_metaHeaderRead == m_metaHeaderSize) {
                    // Meta-header is over, switching transfer syntax
                    m_streamPtr->setTransferSyntax(m_transferSyntax);
                }
            }
        }
    }

    return tagPtr;
}

bool DcmReader::isIgnoreMetaInfoHeaderTransferSyntax() const
{
    return m_ignoreMetaInfoTransferSyntax;
}

void DcmReader::setIgnoreMetaInfoHeaderTransferSyntax(bool v)
{
    m_ignoreMetaInfoTransferSyntax = v;
}

bool DcmReader::isError() const
{
    return m_error;
}

QString DcmReader::errorText() const
{
    return m_errorText;
}

void DcmReader::setError(const QString &text)
{
    m_error = true;
    m_errorText = text;
}

DcmTag *DcmReader::readTagAsPixelData()
{
    DcmTagPixelData::Format format = DcmTagPixelData::Format_Native;

    if (m_vr == DcmVr::OW && (m_size &1)) {
        setError(QObject::tr("Pixel data OW representation must have even size"));
        return 0;
    }

    // Check if encapsulated format
    if (m_size == DcmSize_Undefined) {
        format = DcmTagPixelData::Format_Encapsulated;
    }

    if (format == DcmTagPixelData::Format_Native) {
        char *buffer = new char[m_size];
        if (!buffer) {
            setError(QObject::tr("Unable to allocate pixel data of %1 bytes").arg(m_size));
            return 0;
        }

        DcmSize readSize = m_streamPtr->dataStream().readRawData(buffer, m_size);
        if (readSize != m_size) {
            delete[] buffer;
            setError(QObject::tr("Pixel data of %1 bytes expected, but %2 read")
                     .arg(m_size).arg(readSize));
            return 0;
        }

        // Swap bytes for big-endian
        if (m_streamPtr->transferSyntax().endianess() == DcmEndianess_BigEndian) {
            DcmSize i = 0;
            while (i < m_size) {
                char tmp = buffer[i];
                buffer[i] = buffer[i + 1];
                buffer[i + 1] = tmp;
                i += 2;
            }
        }

        QByteArray byteArray(buffer, m_size);
        delete[] buffer;
        DcmTagPixelData *tagPixelData = new DcmTagPixelData(format, m_vr);
        if (!tagPixelData) {
            setError(QObject::tr("Unable to allocate pixel data tag"));
            return 0;
        }

        tagPixelData->setByteArray(byteArray);
        return tagPixelData;
    }

    // Encapsulated encoding: parsing pixel data items
    DcmTagPixelData tagPixelData(format, m_vr);
    bool hasPixelDataItems = true;
    while (hasPixelDataItems) {

        if (m_streamPtr->atEnd()) {
            setError(QObject::tr("Unexpected end of stream when reading pixel data items"));
            return 0;
        }

        DcmTagKey tagKey;
        *m_streamPtr >> tagKey;

        if (tagKey == DcmTagKey::SequenceDeliminationItem) {
            DcmSize s;
            *m_streamPtr >> s;
            if (s != 0) {
                setError(QObject::tr("Pixel data items delimiter must have zero size"));
                return 0;
            }
            // We are done with pixel data
            hasPixelDataItems = false;
            break;
        } else if (tagKey == DcmTagKey::Item) {
            DcmSize itemSize;
            *m_streamPtr >> itemSize;
            if (itemSize == DcmSize_Undefined) {
                setError(QObject::tr("Pixel data item size is unknown"));
                return 0;
            }

            DcmTagPixelDataItem item;
            if (itemSize > 0) {
                // Read item binary data
                char *buffer = new char[itemSize];
                if (!buffer) {
                    setError(QObject::tr("Unable to allocate pixel data item of %1 bytes").arg(itemSize));
                    return 0;
                }
                DcmSize readSize = m_streamPtr->dataStream().readRawData(buffer, itemSize);
                if (readSize != itemSize) {
                    setError(QObject::tr("Pixel data item size is %1 bytes but %2 bytes read instead")
                             .arg(itemSize).arg(readSize));
                    delete[] buffer;
                    return 0;
                }
                QByteArray byteArray(buffer, itemSize);
                delete[] buffer;
                item.setByteArray(byteArray);
            }
            tagPixelData.insertItem(item);

        } else {
            // Unsupported tag here
            setError(QObject::tr("Pixel data item tag expected but %1 read instead").arg(tagKey.toString()));
            return 0;
        }

    }

    return tagPixelData.clone();
}

DcmTag* DcmReader::readTagAsBinary()
{
    char *buffer = new char[m_size];
    if (!buffer) {
        setError(QObject::tr("Unable allocate binary tag of %1 bytes").arg(m_size));
        return 0;
    }
    DcmSize readSize = m_streamPtr->dataStream().readRawData(buffer, m_size);
    if (readSize != m_size) {
        setError(QObject::tr("Binary tag %1 of %2 bytes size expected, but %3 bytes read instead")
                 .arg(m_vr.toString()).arg(m_size).arg(readSize));
        delete[] buffer;
        return 0;
    }

    // Swapping bytes for big endian
    if (m_streamPtr->transferSyntax().endianess() == DcmEndianess_BigEndian) {
        if (m_vr == DcmVr::OW) {
            for (int i = 0; i < (int)readSize; i += 2) {
                char tmp = buffer[i];
                buffer[i] = buffer[i + 1];
                buffer[i + 1] = tmp;
            }
        }
    }

    QByteArray byteArray(buffer, m_size);
    delete[] buffer;

    DcmTagBinary *tagBinary = new DcmTagBinary(m_tagKey, m_vr);
    if (!tagBinary) {
        setError(QObject::tr("Unable to allocate binary tag"));
        return 0;
    }
    tagBinary->setByteArray(byteArray);
    return tagBinary;
}

DcmTag* DcmReader::readTagAsString()
{
    QString sValue;

    if (m_size > 0) {
        char *buffer = new char[m_size];
        if (!buffer) {
            setError(QObject::tr("Unable allocate %1 bytes for %2 %3 tag")
                     .arg(m_size).arg(m_tagKey.toString().arg(m_vr.toString())));
            return 0;
        }

        DcmSize readSize = m_streamPtr->dataStream().readRawData(buffer, m_size);
        if (readSize != m_size) {
            setError(QObject::tr("When reading tag %1 %2, %3 bytes expected but %4 was read")
                     .arg(m_tagKey.toString()).arg(m_vr.toString()).arg(m_size).arg(readSize));
            delete[] buffer;
            return 0;
        }

        // Remove trailing zeros
        DcmSize s = m_size;
        while (s > 0 && buffer[s - 1] == 0)
            s--;
        if (m_vr.isText()) {
            QByteArray byteArray(buffer, s);
            sValue = m_charSet.decode(byteArray);
        } else {
            sValue = QString::fromLatin1(buffer, s);
        }
        delete[] buffer;
    }

    DcmTagString *tag = DcmTagString::create(m_tagKey, m_vr);
    if (!tag) {
        setError(QObject::tr("Unable to allocate %1 %2 tag").arg(m_tagKey.toString()).arg(m_vr.toString()));
        return 0;
    }

    tag->setString(sValue);

    return tag;
}

DcmTagSQ* DcmReader::readTagAsSequence()
{
    // Increment sequence level
    m_sequenceLevel++;
    DcmTagSQ *tag = new DcmTagSQ(m_tagKey);

    DcmSize sequenceExpectedSize = m_size;
    DcmSize sequenceSize = 0;

    bool inSequence = m_size > 0;   // Parse sequence only if it's no zero-size
    while (inSequence) {
        // Read item tag, but not its content
        DcmTag *itemHeadTag = readTag();

        if (!itemHeadTag) {
            // If we cannot read anything here, we suppose sequence is over
            inSequence = false;
            break;
        }

        if (itemHeadTag->tagKey() == DcmTagKey::SequenceDeliminationItem) {
            // Sequence is over
            delete itemHeadTag;
            inSequence = false;
            break;
        }

        delete itemHeadTag;

        DcmTagItem *itemTag = readTagAsItem();
        if (itemTag) {
            tag->insertAndRetain(itemTag);
            sequenceSize += m_itemRealSize;
            if (sequenceExpectedSize != DcmSize_Undefined) {
                if (sequenceSize == sequenceExpectedSize) {
                    inSequence = false;
                } else if (sequenceSize > sequenceExpectedSize) {
                    setError(QObject::tr("Sequence tag size overflow"));
                    delete tag;
                    return 0;
                }
            } else {
                // Sequence size is unspecified
                if (m_tagKey == DcmTagKey::SequenceDeliminationItem) {
                    inSequence = false;
                }
            }

        } else {
            // Failed to read item tag
            delete tag;
            return 0;
        }
    } // while (inSequence);

    // Decrement sequence level
    m_sequenceLevel--;

    m_sequenceRealSize = sequenceSize;
    // Account for the sequence tag itself
    if (m_streamPtr->transferSyntax().encoding() == DcmEncoding_Explicit) {
        m_sequenceRealSize += 12;
    } else {
        m_sequenceRealSize += 8;
    }

    return tag;
}

DcmTagItem* DcmReader::readTagAsItem()
{
    DcmSize itemExpectedSize = m_size;
    DcmSize itemSize = 0;

    DcmTagItem *item = new DcmTagItem();

    // It appears there are items of zero size
    bool inItem = (m_size > 0);
    while (inItem) {
        DcmTag *tag = readTag();
        if (tag) {
            if (tag->vr() == DcmVr::SQ) {
                itemSize += m_sequenceRealSize;
            } else {
                itemSize += tag->size(m_streamPtr->transferSyntax());
            }

            if (tag->tagKey() == DcmTagKey::SequenceDeliminationItem) {
                if (itemExpectedSize != DcmSize_Undefined) {
                    if (itemSize < itemExpectedSize) {
                        setError(QObject::tr("Unexpected sequence delimiter while reading item tag"));
                        delete tag;
                        delete item;
                        return 0;
                    }
                }

                inItem = false;
                break;
            } else  if (!tag->tagKey().isGroupSize()) {
                if (tag->tagKey() == DcmTagKey::ItemDeliminationItem) {
                    inItem = false;
                    break;
                } else if (tag->tagKey() == DcmTagKey::Item) {
                    qDebug() << "Item tag cannot contain another item";
                    qDebug() << "Current tag is" << m_tagKey.toString();
                    setError(QObject::tr("Item tag cannot contain another item"));
                    delete tag;
                    delete item;
                    return 0;
                }

                item->insertAndRetain(tag);
            } else  {
                delete tag;
            }

            // Check whether the item is over
            if (itemExpectedSize != DcmSize_Undefined) {
                if (itemSize == itemExpectedSize) {
                    inItem = false;
                } else if (itemSize > itemExpectedSize) {
                    setError(QObject::tr("Item tag size overflow: expected %1, read %2")
                             .arg(itemExpectedSize).arg(itemSize));
                    delete item;
                    return 0;
                }
            }

        } else {
            inItem = false;
            break;
        }
    }

    m_itemRealSize = itemSize + 8;  // Account for item tag itself

    return item;
}

DcmTag* DcmReader::readTagAsSS()
{
    int m = m_size / sizeof(DcmSignedShort);
    DcmTagSS *tag = new DcmTagSS(m_tagKey);
    while (m > 0) {
        DcmSignedShort value;
        *m_streamPtr >> value;
        tag->appendSignedShort(value);
        m--;
    }
    return tag;
}

DcmTag* DcmReader::readTagAsUS()
{
    int m = m_size / sizeof(DcmUnsignedShort);
    DcmTagUS *tag = new DcmTagUS(m_tagKey);
    while (m > 0) {
        DcmUnsignedShort value;
        *m_streamPtr >> value;
        tag->appendUnsignedShort(value);
        m--;
    }
    return tag;
}

DcmTag* DcmReader::readTagAsSL()
{
    int m = m_size / sizeof(DcmSignedLong);
    DcmTagSL *tag = new DcmTagSL(m_tagKey);
    while (m > 0) {
        DcmSignedLong value;
        *m_streamPtr >> value;
        tag->appendSignedLong(value);
        m--;
    }
    return tag;
}

DcmTag* DcmReader::readTagAsUL()
{
    int m = m_size / sizeof(DcmUnsignedLong);
    DcmTagUL *tag = new DcmTagUL(m_tagKey);
    while (m > 0) {
        DcmUnsignedLong value;
        *m_streamPtr >> value;
        tag->appendUnsignedLong(value);
        m--;
    }
    return tag;
}

DcmTag* DcmReader::readTagAsAT()
{
    int m = m_size / sizeof(DcmUnsignedLong);   // AT takes 4 bytes
    DcmTagAT *tag = new DcmTagAT(m_tagKey);
    while (m > 0) {
        DcmTagKey tagKey;
        *m_streamPtr >> tagKey;
        tag->appendDcmTagKey(tagKey);
        m--;
    }
    return tag;
}

DcmTag* DcmReader::readTagAsFL()
{
    int m = m_size / sizeof(DcmFloat);
    DcmTagFL *tag = new DcmTagFL(m_tagKey);
    while (m > 0) {
        DcmFloat value;
        *m_streamPtr >> value;
        tag->appendFloat(value);
        m--;
    }
    return tag;
}

DcmTag* DcmReader::readTagAsFD()
{
    int m = m_size / sizeof(DcmDouble);
    DcmTagFD *tag = new DcmTagFD(m_tagKey);
    while (m > 0) {
        DcmDouble value;
        *m_streamPtr >> value;
        tag->appendDouble(value);
        m--;
    }
    return tag;
}
