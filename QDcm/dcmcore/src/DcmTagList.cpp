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

#include "DcmTagList.h"

DcmTagList::DcmTagList()
    : m_list()
{
}

DcmTagList::DcmTagList(const DcmTagList &tagList)
    : m_list()
{
    QLinkedListIterator<DcmTag*> i(tagList.m_list);
    while (i.hasNext()) {
        // Every tag has to be cloned to not retain
        // other's list pointers
        DcmTag *tag = i.next()->clone();
        m_list.append(tag);
    }
}

DcmTagList& DcmTagList::operator =(const DcmTagList &tagList)
{
    if (this != &tagList) {
        clear();
        QLinkedListIterator<DcmTag*> i(tagList.m_list);
        while (i.hasNext()) {
            DcmTag *tag = i.next()->clone();
            m_list.append(tag);
        }
    }
    return *this;
}

DcmTagList::~DcmTagList()
{
    clear();
}

void DcmTagList::insert(const DcmTag &tag)
{
    insertAndRetain(tag.clone());
}

void DcmTagList::insertAndRetain(DcmTag *tagPtr)
{
    if (!tagPtr) {
        return;
    }

    if (m_list.isEmpty()) {
        m_list.append(tagPtr);
    } else {
        QLinkedList<DcmTag*>::iterator iterator = m_list.begin();
        // Move along the list to keep it ordered by tag key
        while (iterator != m_list.end() && ((*iterator)->tagKey() <= tagPtr->tagKey())) {
            iterator++;
        }

        m_list.insert(iterator, tagPtr);
    }
}

void DcmTagList::insertOrReplace(const DcmTag &tag)
{
    insertOrReplaceAndRetain(tag.clone());
}

void DcmTagList::insertOrReplaceAndRetain(DcmTag *tagPtr)
{
    if (!tagPtr) {
        return;
    }

    if (m_list.isEmpty()) {
        m_list.append(tagPtr);
    } else {
        QLinkedList<DcmTag*>::iterator iterator = m_list.begin();
        while (iterator != m_list.end() && ((*iterator)->tagKey() < tagPtr->tagKey())) {
            iterator++;
        }

        if (iterator == m_list.end()) {
            m_list.append(tagPtr);
        } else {
            m_list.insert(iterator, tagPtr);
            // Remove old tag if replacing
            if ((*iterator)->tagKey() == tagPtr->tagKey()) {
                DcmTag *oldTagPtr = *iterator;
                m_list.erase(iterator);
                delete oldTagPtr;
            }
        }
    }
}

int DcmTagList::count() const
{
    return m_list.count();
}

DcmTag* DcmTagList::at(int index) const
{
    if (index < 0 || m_list.isEmpty()) {
        return 0;
    }

    QLinkedListIterator<DcmTag*> iterator(m_list);
    int i = 0;
    while (iterator.hasNext()) {
        DcmTag* tagPtr = iterator.next();
        if (i == index) {
            return tagPtr;
        }
        i++;
    }

    return 0;
}

DcmTag* DcmTagList::findFirst(const DcmTagKey &tagKey) const
{
    if (m_list.isEmpty()) {
        return 0;
    }

    QLinkedList<DcmTag*>::const_iterator iterator = m_list.begin();
    while (iterator != m_list.end() && (*iterator)->tagKey() < tagKey) {
        iterator++;
    }

    if (iterator != m_list.end()) {
        if ((*iterator)->tagKey() == tagKey) {
            return *iterator;
        }
    }

    return 0;
}

void DcmTagList::removeFirst(const DcmTagKey &tagKey)
{
    if (m_list.isEmpty()) {
        return;
    }

    QLinkedList<DcmTag*>::iterator iterator = m_list.begin();
    while (iterator != m_list.end()) {
        if ((*iterator)->tagKey() == tagKey) {
            DcmTag *tagPtr = *iterator;
            m_list.erase(iterator);
            delete tagPtr;
            return;
        }
        iterator++;
    }
}

void DcmTagList::removeAll(const DcmTagKey &tagKey)
{
    if (m_list.isEmpty()) {
        return;
    }

    QLinkedList<DcmTag*>::iterator iterator = m_list.begin();
    while (iterator != m_list.end() && (*iterator)->tagKey() <= tagKey) {
        if ((*iterator)->tagKey() == tagKey) {
            DcmTag* tagPtr = *iterator;
            iterator = m_list.erase(iterator);
            delete tagPtr;
        } else {
            iterator++;
        }
    }
}

void DcmTagList::clear()
{
    if (m_list.isEmpty()) {
        return;
    }

    QMutableLinkedListIterator<DcmTag*> iterator(m_list);
    while (iterator.hasNext()) {
        DcmTag* tagPtr = iterator.next();
        iterator.remove();
        delete tagPtr;
    }
}

DcmSize DcmTagList::size(const DcmTransferSyntax &transferSyntax) const
{
    DcmSize s = 0;

    foreach (DcmTag *tag, m_list) {
        DcmSize tagSize = tag->size(transferSyntax);
        if (tagSize == DcmSize_Undefined) {
            return DcmSize_Undefined;
        }
        s += tag->size(transferSyntax);
    }

    return s;
}

QLinkedList<DcmTag*>& DcmTagList::list()
{
    return m_list;
}
