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

#include "DcmTagAE.h"

DcmTagAE::DcmTagAE()
    : DcmTagString(DcmTagKey(), DcmVr::AE)
{
}

DcmTagAE::DcmTagAE(const DcmTagKey &tagKey)
    : DcmTagString(tagKey, DcmVr::AE)
{
}

DcmTagAE::DcmTagAE(const DcmTagAE &tag)
    : DcmTagString(tag)
{
}

DcmTagAE& DcmTagAE::operator =(const DcmTagAE &tag)
{
    if (this != &tag) {
        DcmTagString::operator =(tag);
    }
    return *this;
}

DcmTag* DcmTagAE::clone() const
{
    return new DcmTagAE(*this);
}

DcmTagAE::~DcmTagAE()
{
}

DcmTagAE& DcmTagAE::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}
