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

DcmTagGroup::DcmTagGroup(DcmUnsignedShort group)
    : DcmTag(DcmTagKey(group, 0x0000), DcmVr::UL),
      m_tags()
{
}

DcmTagGroup::DcmTagGroup(const DcmTagGroup &group)
    : DcmTag(group),
      m_tags(group.m_tags)
{
}

DcmTagGroup& DcmTagGroup::operator =(const DcmTagGroup &group)
{
    if (this != &group) {
        DcmTag::operator =(group);
        m_tags = group.m_tags;
    }
    return *this;
}

DcmTag* DcmTagGroup::clone() const
{
    return new DcmTagGroup(*this);
}

DcmTagGroup::~DcmTagGroup()
{
}

bool DcmTagGroup::isGroup() const
{
    return true;
}

DcmSize DcmTagGroup::contentSize(const DcmTransferSyntax &transferSyntax) const
{
    return m_tags.size(transferSyntax);
}

DcmSize DcmTagGroup::size(const DcmTransferSyntax &transferSyntax) const
{
    // GG GG EE EE UL UL 04 00 SS SS SS SS  (explicit)
    // GG GG EE EE 04 00 00 00 SS SS SS SS  (implicit)
    DcmSize content = contentSize(transferSyntax);
    if (content == DcmSize_Undefined) {
        // This group has undefined size
        return DcmSize_Undefined;
    }
    return contentSize(transferSyntax) + 12;
}

DcmUnsignedShort DcmTagGroup::group() const
{
    return tagKey().group();
}

DcmTagList& DcmTagGroup::tags()
{
    return m_tags;
}

void DcmTagGroup::insert(const DcmTag &tag)
{
    if (tag.tagKey().group() == group() && (!tag.tagKey().isGroupSize())) {
        m_tags.insertOrReplace(tag);
    }
}

void DcmTagGroup::insertAndRetain(DcmTag *tagPtr)
{
    if (!tagPtr) {
        return;
    }

    if (tagPtr->tagKey().group() == group() && (!tagPtr->tagKey().isGroupSize())) {
        m_tags.insertOrReplaceAndRetain(tagPtr);
    }
}

DcmTag* DcmTagGroup::findTag(const DcmTagKey &tagKey)
{
    if (tagKey.group() != group()) {
        return 0;
    }

    return m_tags.findFirst(tagKey);
}

void DcmTagGroup::clear()
{
    m_tags.clear();
}
