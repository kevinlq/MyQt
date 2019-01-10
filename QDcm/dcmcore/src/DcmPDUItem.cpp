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

#include "DcmPDUItem.h"

DcmPDUItem::DcmPDUItem(DcmPDUType pduItemType)
    : m_type(pduItemType)
{
}

DcmPDUItem::DcmPDUItem(const DcmPDUItem &item)
    : m_type(item.m_type)
{
}

DcmPDUItem& DcmPDUItem::operator =(const DcmPDUItem &item)
{
    if (this != &item) {
        m_type = item.m_type;
    }
    return *this;
}

DcmPDUItem* DcmPDUItem::clone() const
{
    return new DcmPDUItem(*this);
}

DcmPDUItem::~DcmPDUItem()
{
}

DcmPDUType DcmPDUItem::type() const
{
    return m_type;
}

bool DcmPDUItem::isAssociationLevel() const
{
    return m_type == DcmPDUType_AAssociateRq
            || m_type == DcmPDUType_AAssociateAc
            || m_type == DcmPDUType_AAssociateRj
            || m_type == DcmPDUType_AReleaseRq
            || m_type == DcmPDUType_AReleaseRp
            || m_type == DcmPDUType_AAbort
            || m_type == DcmPDUType_PData;
}

DcmSize DcmPDUItem::size() const
{
    // DcmPDUType, 00, content length (2 bytes), ...content...
    return 4 + contentSize();
}

DcmSize DcmPDUItem::contentSize() const
{
    return 0;
}

bool DcmPDUItem::isValid() const
{
    return m_type != DcmPDUType_Invalid;
}
