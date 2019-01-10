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

#include "DcmTagUT.h"

DcmTagUT::DcmTagUT()
    : DcmTagString(DcmTagKey(), DcmVr::UT)
{
}

DcmTagUT::DcmTagUT(const DcmTagKey &tagKey)
    : DcmTagString(tagKey, DcmVr::UT)
{
}

DcmTagUT::DcmTagUT(const DcmTagUT &tag)
    : DcmTagString(tag)
{
}

DcmTagUT& DcmTagUT::operator =(const DcmTagUT &tag)
{
    if (this != &tag) {
        DcmTagString::operator =(tag);
    }
    return *this;
}

DcmTag* DcmTagUT::clone() const
{
    return new DcmTagUT(*this);
}

DcmTagUT::~DcmTagUT()
{
}

DcmTagUT& DcmTagUT::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}

DcmSize DcmTagUT::size(const DcmTransferSyntax &transferSyntax) const
{
    if (transferSyntax.encoding() == DcmEncoding_Explicit) {
        return contentSize(transferSyntax) + 12;
    }
    return contentSize(transferSyntax) + 8; // Implicit encoding.
}
