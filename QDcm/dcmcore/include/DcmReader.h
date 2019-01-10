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

#ifndef DCMREADER_H
#define DCMREADER_H

#include "DcmCoreApi.h"
#include "DcmStream.h"
#include "DcmDictionary.h"
#include "DcmDataset.h"
#include "DcmTagSQ.h"
#include "DcmTagItem.h"
#include "DcmCharSet.h"

/*! Parse DICOM tags read from stream.
 *
 * This class is a parser that reads tags one by one
 * from DICOM stream and constructs DICOM dataset.
 */
class DCM_CORE_API DcmReader
{
public:

    /**
     * Construct DICOM reader.
     * \param streamPtr Pointer to DICOM stream.
     * \param dictionaryPtr Pointer to DICOM dictionary or null for default dictionary.
     */
    DcmReader(DcmStream *streamPtr, DcmDictionary *dictionaryPtr = 0);

    /**
     * Read DICOM dataset.
     * Caller is responsible to delete the dataset returned.
     * If failed to read for some reason, null pointer it returned.
     * However one must always check error flag after calling this method
     * since returned dataset may be inconsistent because of an error.
     * \return Read dataset.
     */
    DcmDataset readDataset();

    /**
     * Reads a single DICOM tag from a stream.
     * Returns null if unable to read. If error flag is set
     * the read tag is invalid has te be deleted by a caller.
     * \return Pointer to a read tag.
     */
    DcmTag* readTag();

    /**
     * Tells whether the meta information header transfer
     * syntax will be ignored when parsing the stream.
     * \return True if meta info transfer syntax will be ignored.
     */
    bool isIgnoreMetaInfoHeaderTransferSyntax() const;

    /**
     * Assign meta info header transfer syntax ignore flag.
     * Normally transfer syntax specified in meta header (tag 0002, 0010)
     * should be used to decore the rest of the stream, however in some
     * cases (e.g. reading from network stream) this syntax is not valid
     * and the one negociated has to be always used.
     * \param v Flag value to be set.
     */
    void setIgnoreMetaInfoHeaderTransferSyntax(bool v);

    /**
     * Tells whether an error has been detected while parsing
     * DICOM stream.
     * \return True if error has been detected.
     */
    bool isError() const;

    /**
     * Returns text string explaining the nature of an error detected.
     * The string returned is valid only in case the error flag has been set.
     * \return Error text message.
     */
    QString errorText() const;

private:

    /// No copying allowed.
    Q_DISABLE_COPY(DcmReader)

    /**
     * Enable error flag and assign error text message.
     * \param text Error message to be set.
     */
    void setError(const QString &text);

    /**
     * Read tag as pixel data.
     * This method reads tag raw data and iterprets
     * it as pixel data with native or encapsulated encoding.
     * \return Pointer to pixel data tag read or null if error.
     */
    DcmTag* readTagAsPixelData();

    /**
     * Read string-based tags.
     * \return Pointer to a tag or null if error.
     */
    DcmTag* readTagAsString();

    /**
     * Read tag as binary OB, OW, OF, or UN tag.
     * \return Read binary tag or null if error.
     */
    DcmTag* readTagAsBinary();

    /**
     * Read tag as a sequence SQ tag.
     * \return Sequence tag read or null if error.
     */
    DcmTagSQ* readTagAsSequence();

    /**
     * Read tag as item tag.
     * \return Item tag read or null if error.
     */
    DcmTagItem* readTagAsItem();

    /**
     * Read tag as signed short.
     * \return Signed short tag.
     */
    DcmTag* readTagAsSS();

    /**
     * Read tag as unsigned short.
     * \return Unsigned short tag.
     */
    DcmTag* readTagAsUS();

    /**
     * Read tag as signed long.
     * \return Signed long tag.
     */
    DcmTag* readTagAsSL();

    /**
     * Read tag as unsigned long.
     * \return Unsigned long tag.
     */
    DcmTag* readTagAsUL();

    /**
     * Read tag as attribute.
     * \return AT tag.
     */
    DcmTag* readTagAsAT();

    /**
     * Read tag as float.
     * \return Float tag.
     */
    DcmTag* readTagAsFL();

    /**
     * Read tag as double.
     * \return Double tag.
     */
    DcmTag* readTagAsFD();


    DcmStream *m_streamPtr;     ///< I/O stream.
    DcmDictionary *m_dictPtr;   ///< DICOM dictionary.
    bool m_error;               ///< Error flag.
    QString m_errorText;        ///< Error text.
    DcmTagKey m_tagKey;         ///< Tag key of the tag currently being read.
    DcmUnsignedShort m_group;   ///< Current tag group.
    int m_sequenceLevel;        ///< Sequence level.
    DcmTransferSyntax m_transferSyntax; ///< Transfer syntax used to decode the stream.
    bool m_ignoreMetaInfoTransferSyntax;    ///< Flag telling that meta header syntax to be ignored.
    DcmVr m_dictVr;             ///< Value representation as defined in the dictionary.
    int m_dictMinVm;            ///< Minimal multiplicity from the dictionary.
    int m_dictMaxVm;            ///< Maximal multiplicity from the dictionary.
    int m_dictModVm;            ///< Multiplicity module from the dictionary.
    DcmSize m_size;             ///< Tag's size.
    DcmVr m_vr;                 ///< Value representation read form stream (explicit encoding).
    DcmUnsignedShort m_vrSize;  ///< VR size (2 bytes, explicit encoding).
    DcmSize m_itemRealSize;     ///< Real size of item tag read.
    DcmSize m_sequenceRealSize; ///< Real size of sequence tag read.
    DcmCharSet m_charSet;       ///< Character set to decode textual data.
    DcmSize m_metaHeaderSize;   ///< Size of the meta-hader (in bytes).
    DcmSize m_metaHeaderRead;   ///< Meta-hader read bytes so far.
};

#endif // DCMREADER_H
