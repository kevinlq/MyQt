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

#include "DcmTagString.h"
#include "DcmTagBinary.h"
#include "DcmTagItem.h"
#include "DcmTagPixelData.h"
#include "DcmTagSQ.h"
#include "DcmTagUI.h"
#include "DcmTagSS.h"
#include "DcmTagUS.h"
#include "DcmTagSL.h"
#include "DcmTagUL.h"
#include "DcmTagAT.h"
#include "DcmTagFL.h"
#include "DcmTagFD.h"
#include "DcmWriter.h"

DcmWriter::DcmWriter(DcmStream *streamPtr)
    : m_streamPtr(streamPtr),
      m_ignoreMetaInfoTransferSyntax(false),
      m_charSet()
{
    Q_ASSERT(streamPtr);
}

bool DcmWriter::isIgnoreMetaInfoHeader() const
{
    return m_ignoreMetaInfoTransferSyntax;
}

void DcmWriter::setIgnoreMetaInfoHeader(bool v)
{
    m_ignoreMetaInfoTransferSyntax = v;
}

void DcmWriter::writeDataset(DcmDataset &dataset)
{
    // Check whether there is a character set in the dataset
    DcmTag *tagPtr = dataset.findTag(DcmTagKey::SpecificCharacterSet);
    if (tagPtr) {
        DcmCharSet cs = DcmCharSet::forName(tagPtr->value().toString());
        if (cs.isValid()) {
            m_charSet = cs;
        }
    }

    DcmTransferSyntax streamTransferSyntax = m_streamPtr->transferSyntax();
    DcmTransferSyntax metaTransferSyntax = streamTransferSyntax;

    DcmTag *tagTransferSyntax = dataset.findTag(DcmTagKey::TransferSyntaxUID);
    if (tagTransferSyntax && !isIgnoreMetaInfoHeader()) {
        // Meta info header exists, it must be written using explicit little endian syntax
        metaTransferSyntax = DcmTransferSyntax::fromUid(tagTransferSyntax->value().toString());
        if (!metaTransferSyntax.isValid()) {
            metaTransferSyntax = streamTransferSyntax;
        }

        // Set transfer syntax to write meta info header
        m_streamPtr->setTransferSyntax(DcmTransferSyntax::ExplicitLittleEndian);
    }

    DcmUnsignedShort prevGroup = 0x0000;

    QLinkedList<DcmTag*> groupsList = dataset.tagGroups().list();
    foreach (DcmTag *tag, groupsList) {
        DcmTagGroup *tagGroup = dynamic_cast<DcmTagGroup*>(tag);
        Q_ASSERT(tagGroup);
        DcmUnsignedShort currentGroup = tagGroup->group();
        if (currentGroup != prevGroup) {
            if (prevGroup == 0x0002) {
                // Switch transfer syntax accoring to the meta info header
                m_streamPtr->setTransferSyntax(metaTransferSyntax);
            }
            prevGroup = currentGroup;
        }

        if (currentGroup == 0x0002 && isIgnoreMetaInfoHeader()) {
            // Skip writing meta info header
        } else {
            writeTagGroup(tagGroup);
        }
    }

}

void DcmWriter::writeTagGroup(DcmTagGroup *tagGroupPtr)
{
    if (!tagGroupPtr) {
        return;
    }

    DcmSize size = tagGroupPtr->contentSize(m_streamPtr->transferSyntax());

    *m_streamPtr << tagGroupPtr->tagKey();
    if (m_streamPtr->transferSyntax().encoding() == DcmEncoding_Explicit) {
        DcmUnsignedShort us = sizeof(DcmUnsignedLong);
        *m_streamPtr << DcmVr::UL;
        *m_streamPtr << us;
    } else {
        DcmUnsignedLong ul = sizeof(DcmUnsignedLong);
        *m_streamPtr << ul;
    }
    *m_streamPtr << size;

    writeTagList(&tagGroupPtr->tags());
}

void DcmWriter::writeTagList(DcmTagList *tagListPtr)
{
    QLinkedList<DcmTag*> tags = tagListPtr->list();
    foreach (DcmTag *tag, tags) {
        writeTag(tag);
    }
}

void DcmWriter::writeTag(DcmTag *tagPtr)
{
    if (!tagPtr) {
        return;
    }

    if (tagPtr->tagKey().isGroupSize()) {
        DcmTagGroup *tagGroup = dynamic_cast<DcmTagGroup*>(tagPtr);
        writeTagGroup(tagGroup);
    } else if (tagPtr->tagKey() == DcmTagKey::Item) {
        DcmTagItem *tagItem = dynamic_cast<DcmTagItem*>(tagPtr);
        writeTagAsItem(tagItem);
    } else if (tagPtr->vr() == DcmVr::SQ) {
        DcmTagSQ *tagSQ = dynamic_cast<DcmTagSQ*>(tagPtr);
        writeTagAsSQ(tagSQ);
    } else if (tagPtr->vr().isString()) {
        DcmTagString *tagString = dynamic_cast<DcmTagString*>(tagPtr);
        writeTagAsString(tagString);
    } else if (tagPtr->vr().isBinary()) {
        DcmTagBinary *tagBinary = dynamic_cast<DcmTagBinary*>(tagPtr);
        writeTagAsBinary(tagBinary);
    } else if (tagPtr->vr() == DcmVr::SS) {
        DcmTagSS *tagSS = dynamic_cast<DcmTagSS*>(tagPtr);
        writeTagAsSS(tagSS);
    } else if (tagPtr->vr() == DcmVr::US) {
        DcmTagUS *tagUS = dynamic_cast<DcmTagUS*>(tagPtr);
        writeTagAsUS(tagUS);
    } else if (tagPtr->vr() == DcmVr::SL) {
        DcmTagSL *tagSL = dynamic_cast<DcmTagSL*>(tagPtr);
        writeTagAsSL(tagSL);
    } else if (tagPtr->vr() == DcmVr::UL) {
        DcmTagUL *tagUL = dynamic_cast<DcmTagUL*>(tagPtr);
        writeTagAsUL(tagUL);
    } else if (tagPtr->vr() == DcmVr::AT) {
        DcmTagAT *tagAT = dynamic_cast<DcmTagAT*>(tagPtr);
        writeTagAsAT(tagAT);
    } else if (tagPtr->vr() == DcmVr::FL) {
        DcmTagFL *tagFL = dynamic_cast<DcmTagFL*>(tagPtr);
        writeTagAsFL(tagFL);
    } else if (tagPtr->vr() == DcmVr::FD) {
        DcmTagFD *tagFD = dynamic_cast<DcmTagFD*>(tagPtr);
        writeTagAsFD(tagFD);
    } else {
        Q_ASSERT(!"Missing tag writer");
    }
}

void DcmWriter::writeTagAsString(DcmTagString *tagPtr)
{
    if (!tagPtr) {
        return;
    }

    writeTagPrefix(tagPtr);
    QByteArray byteArray;

    if (tagPtr->vr().isText()) {
        // Encode textual data using current character set
        byteArray = m_charSet.encode(tagPtr->asString());
    } else {
        byteArray = tagPtr->asString().toLatin1();
    }

    // Padding according to the length;
    while (byteArray.size() & 1) {
        if (tagPtr->vr() == DcmVr::UI) {
            byteArray.append('\0');
        } else {
            byteArray.append(' ');
        }
    }

    DcmSize length = byteArray.length();
    m_streamPtr->dataStream().writeRawData(byteArray.constData(), length);
}

void DcmWriter::writeTagAsBinary(DcmTagBinary *tagPtr)
{
    if (!tagPtr) {
        return;
    }

    DcmSize contentSize = tagPtr->contentSize(m_streamPtr->transferSyntax());

    *m_streamPtr << tagPtr->tagKey();
    if (m_streamPtr->transferSyntax().encoding() == DcmEncoding_Explicit) {
        DcmUnsignedShort us = 0;
        *m_streamPtr << tagPtr->vr();
        *m_streamPtr << us;
    }

    *m_streamPtr << contentSize;

    QByteArray byteArray = tagPtr->asByteArray();
    m_streamPtr->dataStream().writeRawData(byteArray.data(), contentSize);
}

void DcmWriter::writeTagAsItem(DcmTagItem *tagPtr)
{
    if (!tagPtr) {
        return;
    }

    DcmSize contentSize = tagPtr->contentSize(m_streamPtr->transferSyntax());

    *m_streamPtr << tagPtr->tagKey();
    *m_streamPtr << contentSize;

    writeTagList(&tagPtr->tagGroups());

    if (contentSize == DcmSize_Undefined) {
        DcmUnsignedLong s = 0;
        *m_streamPtr << DcmTagKey::ItemDeliminationItem;
        *m_streamPtr << s;
    }
}

void DcmWriter::writeTagAsSQ(DcmTagSQ *tagPtr)
{
    if (!tagPtr) {
        return;
    }

    DcmSize contentSize = tagPtr->contentSize(m_streamPtr->transferSyntax());
    *m_streamPtr << tagPtr->tagKey();
    if (m_streamPtr->transferSyntax().encoding() == DcmEncoding_Explicit) {
        DcmUnsignedShort us = 0;
        *m_streamPtr << tagPtr->vr();
        *m_streamPtr << us;
    }

    *m_streamPtr << contentSize;

    writeTagList(&tagPtr->items());

    if (contentSize == DcmSize_Undefined) {
        DcmUnsignedLong s = 0;
        *m_streamPtr << DcmTagKey::SequenceDeliminationItem;
        *m_streamPtr << s;
    }
}

void DcmWriter::writeTagAsPixelData(DcmTagPixelData *tagPtr)
{
    if (!tagPtr) {
        return;
    }

    *m_streamPtr << tagPtr->tagKey();
    if (m_streamPtr->transferSyntax().encoding() == DcmEncoding_Explicit) {
        DcmUnsignedShort us = 0;
        *m_streamPtr << tagPtr->vr();
        *m_streamPtr << us;
    }

    DcmSize contentSize = tagPtr->contentSize(m_streamPtr->transferSyntax());

    if (tagPtr->format() == DcmTagPixelData::Format_Native) {
        // Native (uncompressed) format
        *m_streamPtr << contentSize;
        QByteArray byteArray = tagPtr->asByteArray();
        m_streamPtr->dataStream().writeRawData(byteArray.data(), contentSize);
    } else {
        // Encapsulated (compressed) format
        contentSize = DcmSize_Undefined;
        *m_streamPtr << contentSize;

        QLinkedList<DcmTag*> tagList = tagPtr->items().list();
        foreach (DcmTag *tag, tagList) {
            DcmTagPixelDataItem *pixelDataItem = dynamic_cast<DcmTagPixelDataItem*>(tag);
            writeTagAsPixelDataItem(pixelDataItem);
        }
    }
}

void DcmWriter::writeTagAsPixelDataItem(DcmTagPixelDataItem *tagPtr)
{
    if (!tagPtr) {
        return;
    }

    DcmSize contentSize = tagPtr->contentSize(m_streamPtr->transferSyntax());
    *m_streamPtr << tagPtr->tagKey();
    *m_streamPtr << contentSize;

    QByteArray byteArray = tagPtr->asByteArray();
    m_streamPtr->dataStream().writeRawData(byteArray.data(), contentSize);
}

void DcmWriter::writeTagAsSS(DcmTagSS *tagPtr)
{
    if (!tagPtr) {
        return;
    }

    writeTagPrefix(tagPtr);

    foreach(DcmSignedShort value, tagPtr->asSignedShortList()) {
        *m_streamPtr << value;
    }
}

void DcmWriter::writeTagAsUS(DcmTagUS *tagPtr)
{
    if (!tagPtr) {
        return;
    }

    writeTagPrefix(tagPtr);

    foreach(DcmUnsignedShort value, tagPtr->asUnsignedShortList()) {
        *m_streamPtr << value;
    }
}

void DcmWriter::writeTagAsSL(DcmTagSL *tagPtr)
{
    if (!tagPtr) {
        return;
    }

    writeTagPrefix(tagPtr);

    foreach(DcmSignedLong value, tagPtr->asSignedLongList()) {
        *m_streamPtr << value;
    }
}

void DcmWriter::writeTagAsUL(DcmTagUL *tagPtr)
{
    if (!tagPtr) {
        return;
    }

    writeTagPrefix(tagPtr);

    foreach(DcmUnsignedLong value, tagPtr->asUnsignedLongList()) {
        *m_streamPtr << value;
    }
}

void DcmWriter::writeTagAsAT(DcmTagAT *tagPtr)
{
    if (!tagPtr) {
        return;
    }

    writeTagPrefix(tagPtr);

    foreach (DcmTagKey attr, tagPtr->asDcmTagKeyList()) {
        *m_streamPtr << attr;
    }
}

void DcmWriter::writeTagAsFL(DcmTagFL *tagPtr)
{
    if (!tagPtr) {
        return;
    }

    writeTagPrefix(tagPtr);

    foreach(DcmFloat value, tagPtr->asFloatList()) {
        *m_streamPtr << value;
    }
}

void DcmWriter::writeTagAsFD(DcmTagFD *tagPtr)
{
    if (!tagPtr) {
        return;
    }

    writeTagPrefix(tagPtr);

    foreach(DcmDouble value, tagPtr->asDoubleList()) {
        *m_streamPtr << value;
    }
}

void DcmWriter::writeTagPrefix(DcmTag *tagPtr)
{
    if (!tagPtr) {
        return;
    }

    *m_streamPtr << tagPtr->tagKey();
    DcmSize length = tagPtr->contentSize(m_streamPtr->transferSyntax());
    if (m_streamPtr->transferSyntax().encoding() == DcmEncoding_Explicit) {
        *m_streamPtr << tagPtr->vr();
        if (tagPtr->vr().isBinary() || tagPtr->vr() == DcmVr::SQ || tagPtr->vr() == DcmVr::UT) {
            DcmUnsignedShort usZeros = 0;
            *m_streamPtr << usZeros;
            *m_streamPtr << length;
        } else {
            DcmUnsignedShort usLength = (DcmUnsignedShort)length;
            *m_streamPtr << usLength;
        }
    } else {
        *m_streamPtr << length;
    }

}
