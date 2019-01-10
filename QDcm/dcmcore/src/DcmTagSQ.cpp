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

#include "DcmTagSQ.h"

DcmTagSQ::DcmTagSQ()
    : DcmTag(DcmTagKey(), DcmVr::SQ),
      m_items()
{
}

DcmTagSQ::DcmTagSQ(const DcmTagKey &tagKey)
    : DcmTag(tagKey, DcmVr::SQ),
      m_items()
{
}

DcmTagSQ::DcmTagSQ(const DcmTagSQ &tagSq)
    : DcmTag(tagSq),
      m_items(tagSq.m_items)
{
}

DcmTagSQ& DcmTagSQ::operator =(const DcmTagSQ &tagSq)
{
    if (this != &tagSq) {
        DcmTag::operator =(tagSq);
        m_items = tagSq.m_items;
    }
    return *this;
}

DcmTag* DcmTagSQ::clone() const
{
    return new DcmTagSQ(*this);
}

DcmTagSQ::~DcmTagSQ()
{
}

DcmSize DcmTagSQ::contentSize(const DcmTransferSyntax &transferSyntax) const
{
    return m_items.size(transferSyntax);
}

DcmSize DcmTagSQ::size(const DcmTransferSyntax &transferSyntax) const
{
    DcmSize s = contentSize(transferSyntax);
    if (s != DcmSize_Undefined) {
        if (transferSyntax.encoding() == DcmEncoding_Explicit) {
            // Explicit: gg gg ee ee S Q 00 00 <content size, 4 bytes>
            s += 12;
        } else {
            // Implicit: gg gg ee ee <content size, 4 bytes>
            s += 8;
        }
    }
    return s;
}

DcmTagList& DcmTagSQ::items()
{
    return m_items;
}

void DcmTagSQ::insert(const DcmTagItem &item)
{
    m_items.insert(item);
}

void DcmTagSQ::insertAndRetain(DcmTagItem *itemPtr)
{
    Q_ASSERT(itemPtr);
    if (itemPtr) {
        m_items.insertAndRetain(itemPtr);
    }
}
