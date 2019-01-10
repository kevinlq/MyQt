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

#include "DcmTagLO.h"

DcmTagLO::DcmTagLO()
    : DcmTagString(DcmTagKey(), DcmVr::LO)
{
}

DcmTagLO::DcmTagLO(const DcmTagKey &tagKey)
    : DcmTagString(tagKey, DcmVr::LO)
{
}

DcmTagLO::DcmTagLO(const DcmTagLO &tag)
    : DcmTagString(tag)
{
}

DcmTagLO& DcmTagLO::operator =(const DcmTagLO &tag)
{
    if (this != &tag) {
        DcmTagString::operator =(tag);
    }
    return *this;
}

DcmTag* DcmTagLO::clone() const
{
    return new DcmTagLO(*this);
}

DcmTagLO::~DcmTagLO()
{
}

DcmTagLO& DcmTagLO::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}
