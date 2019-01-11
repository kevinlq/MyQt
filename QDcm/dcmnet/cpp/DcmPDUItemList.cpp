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

#include "DcmPDUItemList.h"

DcmPDUItemList::DcmPDUItemList()
    : m_pduItems()
{
}

DcmPDUItemList::DcmPDUItemList(const DcmPDUItemList &list)
    : m_pduItems()
{
    foreach (DcmPDUItem *item, list.m_pduItems) {
        m_pduItems.append(item->clone());
    }
}

DcmPDUItemList& DcmPDUItemList::operator =(const DcmPDUItemList &list)
{
    if (this != &list) {
        clear();
        foreach (DcmPDUItem *item, list.m_pduItems) {
            m_pduItems.append(item->clone());
        }
    }
    return *this;
}

DcmPDUItemList::~DcmPDUItemList()
{
    clear();
}

int DcmPDUItemList::count() const
{
    return m_pduItems.count();
}

DcmPDUItem* DcmPDUItemList::at(int index) const
{
    return m_pduItems.at(index);
}

void DcmPDUItemList::append(const DcmPDUItem &pdu)
{
    m_pduItems.append(pdu.clone());
}

void DcmPDUItemList::appendAndRetain(DcmPDUItem *pduPtr)
{
    Q_ASSERT(pduPtr);
    if (pduPtr) {
        m_pduItems.append(pduPtr);
    }
}

void DcmPDUItemList::clear()
{
    QMutableListIterator<DcmPDUItem*> iterator(m_pduItems);
    while (iterator.hasNext()) {
        DcmPDUItem *item = iterator.next();
        iterator.remove();
        delete item;
    }
}

DcmSize DcmPDUItemList::size() const
{
    DcmSize s = 0;
    foreach (DcmPDUItem *item, m_pduItems) {
        s += item->size();
    }
    return s;
}
