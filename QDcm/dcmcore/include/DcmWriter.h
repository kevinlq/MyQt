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

#ifndef DCMWRITER_H
#define DCMWRITER_H

#include "DcmCoreApi.h"
#include "DcmStream.h"
#include "DcmDataset.h"
#include "DcmCharSet.h"

class DcmTagString;
class DcmTagBinary;
class DcmTagItem;
class DcmTagPixelData;
class DcmTagPixelDataItem;
class DcmTagSQ;
class DcmTagSS;
class DcmTagUS;
class DcmTagSL;
class DcmTagUL;
class DcmTagAT;
class DcmTagFL;
class DcmTagFD;

/*! DICOM data writer.
 * This class writes DICOM dataset to specified stream
 * The transfer syntax to be used must be previously set in the
 * I/O stream. If metaheader not to be ignored, the transfer
 * syntax defined in the I/O stream will be injected into the
 * dataset to be written.
 * This class does not perform reencoding of embedded images when
 * changing transfer syntax. The dataset must be prepared before according
 * to the transfer syntax chosen.
 */
class DCM_CORE_API DcmWriter
{

public:

    /**
     * Construct DICOM writer.
     * \param streamPtr Pointer to DICOM I/O stream.
     */
    DcmWriter(DcmStream *streamPtr);

    /**
     * Tells whether meta info header will be written
     * to the stream.
     * \return True if meta info header will be written.
     */
    bool isIgnoreMetaInfoHeader() const;

    /**
     * Set ignore meta header flag.
     * If enabled, the meta info header will not be
     * written. The rest of the dataset will be written as specified
     * in the I/O stream. If disabled, the meta info header will
     * be written using explicit little endian syntax, the rest
     * of the dataset will be written with a syntax specified in the header.
     * \param v Flag to be set.
     */
    void setIgnoreMetaInfoHeader(bool v);

    /**
     * Write dataset to the I/O stream.
     * \param dataset Dataset to be written.
     */
    void writeDataset(DcmDataset &dataset);

    /**
     * Write tag group.
     * \param tagGroupPtr Pointer to tags group to be written.
     */
    void writeTagGroup(DcmTagGroup *tagGroupPtr);

    /**
     * Write tags list.
     * \param tagListPtr Pointer to a list of tags to be written.
     */
    void writeTagList(DcmTagList *tagListPtr);

    /**
     * Write single tag.
     * \param tagPtr Pointer to a tag to be written.
     */
    void writeTag(DcmTag *tagPtr);

private:

    Q_DISABLE_COPY(DcmWriter)

    /**
     * Write tag as string tag.
     * \patam tagPtr String tag to be written.
     */
    void writeTagAsString(DcmTagString *tagPtr);

    /**
     * Write tag as binary tag.
     * \param tagPtr Poimter to binary tag to be written.
     */
    void writeTagAsBinary(DcmTagBinary *tagPtr);

    /**
     * Write tag as an item tag.
     * \param tagPtr Pointer to an item tag.
     */
    void writeTagAsItem(DcmTagItem *tagPtr);

    /**
     * Write tag as sequence tag.
     * \param tagPtr Pointer to a sequence tag.
     */
    void writeTagAsSQ(DcmTagSQ *tagPtr);

    /**
     * Write tag as pixel data tag.
     * \param tagPtr Pointer to a pixel data tag.
     */
    void writeTagAsPixelData(DcmTagPixelData *tagPtr);

    /**
     * Write tag as pixel data item.
     * \param tagPtr Pointer to a pixel data item.
     */
    void writeTagAsPixelDataItem(DcmTagPixelDataItem *tagPtr);

    /**
     * Write tag as signed short.
     * \param tagPtr Pointer to signed short tag.
     */
    void writeTagAsSS(DcmTagSS *tagPtr);

    /**
     * Write tag as unsigned short.
     * \param tagPtr Pointer to unsigned short tag.
     */
    void writeTagAsUS(DcmTagUS *tagPtr);

    /**
     * Write tag as signed long.
     * \param tagPtr Pointer to signed long tag.
     */
    void writeTagAsSL(DcmTagSL *tagPtr);

    /**
     * Write tag as unsigned long.
     * \param tagPtr Pointer to unsigned long tag.
     */
    void writeTagAsUL(DcmTagUL *tagPtr);

    /**
     * Write tas as attribute.
     * \param tagPtr Pointer to attribute tag.
     */
    void writeTagAsAT(DcmTagAT *tagPtr);

    /**
     * Write tag as float.
     * \param tagPtr Pointer to float tag.
     */
    void writeTagAsFL(DcmTagFL *tagPtr);

    /**
     * Write tag as double.
     * \param tagPtr Pointer to double tag.
     */
    void writeTagAsFD(DcmTagFD *tagPtr);

    /**
     * Writed tag's prefix (tag key and VR).
     * This should not be used for special tags, as binary
     * or items.
     * \param tagPtr Pointer to a tag to be written.
     */
    void writeTagPrefix(DcmTag *tagPtr);

    DcmStream *m_streamPtr; ///< Pointer to DICOM I/O stream.
    bool m_ignoreMetaInfoTransferSyntax;    ///< Flag telling whether the meta info syntax to be ignored.
    DcmCharSet m_charSet;   ///< Character set to encode textual data.

};

#endif // DCMWRITER_H
