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

#include "DcmTagLT.h"

DcmTagLT::DcmTagLT()
    : DcmTagString(DcmTagKey(), DcmVr::LT)
{
}

DcmTagLT::DcmTagLT(const DcmTagKey &tagKey)
    : DcmTagString(tagKey, DcmVr::LT)
{
}

DcmTagLT::DcmTagLT(const DcmTagLT &tag)
    : DcmTagString(tag)
{
}

DcmTagLT& DcmTagLT::operator =(const DcmTagLT &tag)
{
    if (this != &tag) {
        DcmTagString::operator =(tag);
    }
    return *this;
}

DcmTag* DcmTagLT::clone() const
{
    return new DcmTagLT(*this);
}

DcmTagLT::~DcmTagLT()
{
}

DcmTagLT& DcmTagLT::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}
