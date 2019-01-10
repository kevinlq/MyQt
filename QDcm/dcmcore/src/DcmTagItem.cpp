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

#include "DcmTagGroup.h"
#include "DcmTagItem.h"

DcmTagItem::DcmTagItem()
    : DcmTag(DcmTagKey::Item, DcmVr::None)
{
}

DcmTagItem::DcmTagItem(const DcmTagItem &item)
    : DcmTag(item),
      m_tagGroups(item.m_tagGroups)
{
}

DcmTagItem& DcmTagItem::operator =(const DcmTagItem &item)
{
    if (this != &item) {
        DcmTag::operator =(item);
        m_tagGroups = item.m_tagGroups;
    }
    return *this;
}

DcmTag* DcmTagItem::clone() const
{
    return new DcmTagItem(*this);
}

DcmTagItem::~DcmTagItem()
{
}

DcmSize DcmTagItem::contentSize(const DcmTransferSyntax &transferSyntax) const
{
    return m_tagGroups.size(transferSyntax);
}

DcmSize DcmTagItem::size(const DcmTransferSyntax &transferSyntax) const
{
    DcmSize content = contentSize(transferSyntax);
    if (content == DcmSize_Undefined) {
        return DcmSize_Undefined;
    }
    // fffe, e000, <content size, 4 bytes>
    // ...
    return contentSize(transferSyntax) + 8;
}

void DcmTagItem::insert(const DcmTag &tag)
{
    DcmTagGroup *group = findOrCreateGroup(tag.tagKey().group());

    Q_ASSERT(group);

    group->insert(tag);
}

void DcmTagItem::insertAndRetain(DcmTag *tagPtr)
{
    if (!tagPtr) {
        return;
    }

    DcmTagGroup *group = findOrCreateGroup(tagPtr->tagKey().group());

    Q_ASSERT(group);

    group->insertAndRetain(tagPtr);
}

DcmTagList& DcmTagItem::tagGroups()
{
    return m_tagGroups;
}

DcmTagGroup* DcmTagItem::findOrCreateGroup(DcmUnsignedShort g)
{
    DcmTag *groupTag = m_tagGroups.findFirst(DcmTagKey(g, 0x0000));
    DcmTagGroup *group = 0;
    if (groupTag) {
        group = dynamic_cast<DcmTagGroup*>(groupTag);
        Q_ASSERT(group);
    } else {
        group = new DcmTagGroup(g);
        m_tagGroups.insertAndRetain(group);
    }

    Q_ASSERT(group);
    return group;
}
