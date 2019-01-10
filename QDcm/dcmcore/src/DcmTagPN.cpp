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

#include "DcmTagPN.h"

DcmTagPN::DcmTagPN()
    : DcmTagString(DcmTagKey(), DcmVr::PN)
{
}

DcmTagPN::DcmTagPN(const DcmTagKey &tagKey)
    : DcmTagString(tagKey, DcmVr::PN)
{
}

DcmTagPN::DcmTagPN(const DcmTagPN &tag)
    : DcmTagString(tag)
{
}

DcmTagPN& DcmTagPN::operator =(const DcmTagPN &tag)
{
    if (this != &tag) {
        DcmTagString::operator =(tag);
    }
    return *this;
}

DcmTag* DcmTagPN::clone() const
{
    return new DcmTagPN(*this);
}

DcmTagPN::~DcmTagPN()
{
}

DcmTagPN& DcmTagPN::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}
