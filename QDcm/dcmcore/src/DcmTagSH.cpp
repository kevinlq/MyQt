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

#include "DcmTagSH.h"

DcmTagSH::DcmTagSH()
    : DcmTagString(DcmTagKey(), DcmVr::SH)
{
}

DcmTagSH::DcmTagSH(const DcmTagKey &tagKey)
    : DcmTagString(tagKey, DcmVr::SH)
{
}

DcmTagSH::DcmTagSH(const DcmTagSH &tag)
    : DcmTagString(tag)
{
}

DcmTagSH& DcmTagSH::operator =(const DcmTagSH &tag)
{
    if (this != &tag) {
        DcmTagString::operator =(tag);
    }
    return *this;
}

DcmTag* DcmTagSH::clone() const
{
    return new DcmTagSH(*this);
}

DcmTagSH::~DcmTagSH()
{
}

DcmTagSH& DcmTagSH::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}
