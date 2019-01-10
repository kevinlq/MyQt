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

#include "DcmTagST.h"

DcmTagST::DcmTagST()
    : DcmTagString(DcmTagKey(), DcmVr::ST)
{
}

DcmTagST::DcmTagST(const DcmTagKey &tagKey)
    : DcmTagString(tagKey, DcmVr::ST)
{
}

DcmTagST::DcmTagST(const DcmTagST &tag)
    : DcmTagString(tag)
{
}

DcmTagST& DcmTagST::operator =(const DcmTagST &tag)
{
    if (this != &tag) {
        DcmTagString::operator =(tag);
    }
    return *this;
}

DcmTag* DcmTagST::clone() const
{
    return new DcmTagST(*this);
}

DcmTagST::~DcmTagST()
{
}

DcmTagST& DcmTagST::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}
