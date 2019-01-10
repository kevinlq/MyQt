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

#ifndef DCMTAGPIXELDATA_H
#define DCMTAGPIXELDATA_H

#include "DcmCoreApi.h"
#include "DcmTagBinary.h"
#include "DcmTagList.h"
#include "DcmTagPixelDataItem.h"

/*! Special tag to handle pixel data.
 * The pixel data tag (7fe0, 0010) is a binary tag
 * that stores DICOM image pixels.
 * Pixel data can be stored in native (uncompressed) and
 * encapsulated (compressed) formats. In case of native format
 * the raw data stored in this tag represents pixel buffer of the image.
 * In case of encapsulated format, the pixel data is stored as a sequence
 * of item tags.
 * \sa DcmTagPixelDataItem
 */
class DCM_CORE_API DcmTagPixelData: public DcmTagBinary
{
public:

    /**
     * Pixel data format.
     */
    typedef enum {
        Format_Native,          ///< Uncompressed format
        Format_Encapsulated     ///< Compressed format
    } Format;

    /**
     * Construct pixel data tag.
     * \param format Pixel data format.
     * \param vr Value representation (OB or OW).
     */
    DcmTagPixelData(const Format format = Format_Native, const DcmVr &vr = DcmVr::OB);

    /**
     * Copy constructor.
     * \param pixelData Pixel data tag to be copied.
     */
    DcmTagPixelData(const DcmTagPixelData &pixelData);

    /**
     * Assignment operator.
     * \param pixelData Pixel data tag to be assigned.
     * \return This pixel data tag.
     */
    DcmTagPixelData& operator =(const DcmTagPixelData &pixelData);

    /**
     * Clone this pixel data tag.
     * \return Pointer to cloned tag.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagPixelData();

    /**
     * Returns pixel data format.
     * \return pixel data format.
     */
    Format format() const;

    /**
     * Tells whether the pixel data is stored in uncompressed raw format.
     * \return true if pixel data format is native.
     */
    bool isNative() const;

    /**
     * Tells whether the pixel data is stored in compressed format.
     * \return true if pixel data format is encapsulated.
     */
    bool isEncapsulated() const;

    /**
     * Returns pixel data items.
     * \return List of pixel data items.
     */
    DcmTagList& items();

    /**
     * Remove all items.
     */
    void clearItems();

    /**
     * Add another item to this pixel data tag.
     * \param item Pixel data item to be added.
     */
    void insertItem(const DcmTagPixelDataItem &item);

    /**
     * Returns raw content size in bytes.
     * For encapsulated data, content size should not be
     * used in pixel data tag size. Instead undefined size (0xFFFFFFFF)
     * should be used.
     * \param transferSyntax Transfer syntax to be used for encoding.
     * \return Content size in bytes.
     */
    DcmSize contentSize(const DcmTransferSyntax &transferSyntax) const;

    /**
     * Returns tag raw size in bytes.
     * \param transferSyntax Transfer syntax to be used for data encoding.
     * \return Tag size in bytes.
     */
    DcmSize size(const DcmTransferSyntax &transferSyntax) const;

private:

    Format m_format;    ///< Pixel data format.
    DcmTagList m_items; ///< Pixel data items (for encapsulated format).

};

#endif // DCMTAGPIXELDATA_H
