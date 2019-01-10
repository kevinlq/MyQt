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

#include "DcmTagPixelDataItem.h"

DcmTagPixelDataItem::DcmTagPixelDataItem()
    : DcmTagBinary(DcmTagKey::Item, DcmVr::None)
{
}

DcmTagPixelDataItem::DcmTagPixelDataItem(const DcmTagPixelDataItem &item)
    : DcmTagBinary(item)
{
}

DcmTagPixelDataItem& DcmTagPixelDataItem::operator =(const DcmTagPixelDataItem &item)
{
    if (this != &item) {
        DcmTagBinary::operator =(item);
    }
    return *this;
}

DcmTag* DcmTagPixelDataItem::clone() const
{
    return new DcmTagPixelDataItem(*this);
}

DcmTagPixelDataItem::~DcmTagPixelDataItem()
{
}

DcmSize DcmTagPixelDataItem::size(const DcmTransferSyntax &transferSyntax) const
{
    // FF FE E0 00 <size, 4 bytes> = 8 bytes (always encoded as implicit)
    return contentSize(transferSyntax) + 8;
}
