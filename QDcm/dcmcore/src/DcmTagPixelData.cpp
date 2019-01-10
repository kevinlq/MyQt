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

#include "DcmTagPixelData.h"

DcmTagPixelData::DcmTagPixelData(const Format format, const DcmVr &vr)
    : DcmTagBinary(DcmTagKey::PixelData, vr),
      m_format(format),
      m_items()
{
    Q_ASSERT(vr.isBinary());
}

DcmTagPixelData::DcmTagPixelData(const DcmTagPixelData &pixelData)
    : DcmTagBinary(pixelData),
      m_format(pixelData.m_format),
      m_items(pixelData.m_items)
{
}

DcmTagPixelData& DcmTagPixelData::operator =(const DcmTagPixelData &pixelData)
{
    if (this != &pixelData) {
        DcmTagBinary::operator =(pixelData);
        m_format = pixelData.m_format;
        m_items = pixelData.m_items;
    }
    return *this;
}

DcmTag* DcmTagPixelData::clone() const
{
    return new DcmTagPixelData(*this);
}

DcmTagPixelData::~DcmTagPixelData()
{
}

DcmTagPixelData::Format DcmTagPixelData::format() const
{
    return m_format;
}

bool DcmTagPixelData::isNative() const
{
    return m_format == DcmTagPixelData::Format_Native;
}

bool DcmTagPixelData::isEncapsulated() const
{
    return m_format == DcmTagPixelData::Format_Encapsulated;
}

DcmTagList& DcmTagPixelData::items()
{
    return m_items;
}

void DcmTagPixelData::clearItems()
{
    m_items.clear();
}

void DcmTagPixelData::insertItem(const DcmTagPixelDataItem &item)
{
    m_items.insert(item);
}

DcmSize DcmTagPixelData::contentSize(const DcmTransferSyntax &transferSyntax) const
{
    if (m_format == Format_Encapsulated) {
        return m_items.size(transferSyntax);
    }

    return DcmTagBinary::contentSize(transferSyntax);
}

DcmSize DcmTagPixelData::size(const DcmTransferSyntax &transferSyntax) const
{
    if (m_format == Format_Encapsulated) {
        DcmSize s = m_items.size(transferSyntax);
        if (s ==  DcmSize_Undefined) {
            return DcmSize_Undefined;
        }

        if (transferSyntax.encoding() == DcmEncoding_Explicit) {
            // 7F E0 00 10 O B 00 00 FF FF FF FF (12)
            // ... items ... (s)
            // FF FE E0 DD 00 00 00 00 (8)
            return s + 20;
        } else {
            // 7F E0 00 10 FF FF FF FF (8)
            // ... items ... (s)
            // FF FE E0 DD 00 00 00 00 (8)
            return s + 16;
        }
    } else {
        if (transferSyntax.encoding() == DcmEncoding_Explicit) {
            // 7F E0 00 10 O B 00 00 <size, 4 bytes> (12)
            // ... binary data ...
            return contentSize(transferSyntax) + 12;
        } else {
            // 7F E0 00 10 <size, 4 bytes> (8)
            // ... binary data ...
            return contentSize(transferSyntax) + 8;
        }
    }

    return DcmSize_Undefined;
}
