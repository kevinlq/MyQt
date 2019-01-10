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

#include "DcmTagCS.h"

DcmTagCS::DcmTagCS()
    : DcmTagString(DcmTagKey(), DcmVr::CS)
{
}

DcmTagCS::DcmTagCS(const DcmTagKey &tagKey)
    : DcmTagString(tagKey, DcmVr::CS)
{
}

DcmTagCS::DcmTagCS(const DcmTagCS &tag)
    : DcmTagString(tag)
{
}

DcmTagCS& DcmTagCS::operator =(const DcmTagCS &tag)
{
    if (this != &tag) {
        DcmTagString::operator =(tag);
    }
    return *this;
}

DcmTag* DcmTagCS::clone() const
{
    return new DcmTagCS(*this);
}

DcmTagCS::~DcmTagCS()
{
}

void DcmTagCS::setValue(const QVariant &v)
{
    setString(v.toString().toUpper());
}

void DcmTagCS::appendValue(const QVariant &v)
{
    appendString(v.toString().toUpper());
}

DcmTagCS& DcmTagCS::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}
