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

#include "DcmTagString.h"
#include "DcmTagBinary.h"
#include "DcmTagPixelData.h"
#include "DcmTagGroup.h"
#include "DcmTagItem.h"
#include "DcmTagSQ.h"
#include "DcmTagSS.h"
#include "DcmTagUS.h"
#include "DcmTagSL.h"
#include "DcmTagUL.h"
#include "DcmTagAT.h"
#include "DcmTagFL.h"
#include "DcmTagFD.h"
#include "DcmDictionary.h"
#include "DcmTag.h"

DcmTag::DcmTag()
    : m_tagKey(),
      m_vr()
{
}

DcmTag::DcmTag(const DcmTagKey &tagKey, const DcmVr &vr)
    : m_tagKey(tagKey),
      m_vr(vr)
{

}

DcmTag::DcmTag(const DcmTag &tag)
    : m_tagKey(tag.m_tagKey),
      m_vr(tag.m_vr)
{
}

DcmTag& DcmTag::operator =(const DcmTag &tag)
{
    if (this != &tag) {
        m_tagKey = tag.m_tagKey;
        m_vr = tag.m_vr;
    }
    return *this;
}

DcmTag* DcmTag::clone() const
{
    return new DcmTag(*this);
}

DcmTag::~DcmTag()
{
}

DcmTagKey DcmTag::tagKey() const
{
    return m_tagKey;
}

DcmVr DcmTag::vr() const
{
    return m_vr;
}

bool DcmTag::isGroup() const
{
    return m_tagKey.isGroupSize();
}

bool DcmTag::isBinary() const
{
    return m_vr.isBinary();
}

bool DcmTag::isValid() const
{
    // Tags with None VR are allowed
    return m_vr != DcmVr::Invalid;
}

void DcmTag::setVr(const DcmVr &vr)
{
    m_vr = vr;
}

QVariant DcmTag::value() const
{
    return QVariant();
}

QVariantList DcmTag::values() const
{
    return QVariantList();
}

void DcmTag::setValue(const QVariant &v)
{
    Q_UNUSED(v);
}

void DcmTag::appendValue(const QVariant &v)
{
    Q_UNUSED(v);
}

DcmTag& DcmTag::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}

DcmTag& DcmTag::operator <<(const QVariant &v)
{
    appendValue(v);
    return *this;
}

QVariant DcmTag::operator ()() const
{
    return value();
}

QVariant DcmTag::operator [](int index) const
{
    if (index >= multiplicity()) {
        return QVariant();
    }

    return values().at(index);
}

int DcmTag::multiplicity() const
{
    return 0;
}

DcmSize DcmTag::size(const DcmTransferSyntax &transferSyntax) const
{
    DcmSize content = contentSize(transferSyntax);
    if (vr().isBinary() && transferSyntax.encoding() == DcmEncoding_Explicit) {
        // GG GG EE EE VR VR 00 00 SS SS SS SS
        // <group> <element> <vr> <00 00 reserved> <4-bytes size>
        return content + 12;
    }

    // GG GG EE EE VR VR SS SS  (explicit)
    // GG GG EE EE SS SS SS SS  (implicit)
    return content + 8;
}

DcmSize DcmTag::contentSize(const DcmTransferSyntax &transferSyntax) const
{
    Q_UNUSED(transferSyntax)
    return 0;
}

DcmTag* DcmTag::create(const DcmTagKey &tagKey, const DcmVr &vr)
{
    DcmTag *tag = 0;

    if (vr.isString()) {
        tag = DcmTagString::create(tagKey, vr);
    } else if (vr.isBinary()) {
        tag = new DcmTagBinary(tagKey, vr);
    } else if (vr == DcmVr::SQ) {
        tag = new DcmTagSQ(tagKey);
    } else if (tagKey == DcmTagKey::PixelData) {
        tag = new DcmTagPixelData(DcmTagPixelData::Format_Native, vr);
    } else if (tagKey == DcmTagKey::Item) {
        tag = new DcmTagItem();
    } else if (tagKey.isGroupSize()) {
        tag = new DcmTagGroup(tagKey.group());
    } else if (tagKey == DcmTagKey::ItemDeliminationItem || tagKey == DcmTagKey::SequenceDeliminationItem) {
        tag = new DcmTag(tagKey, DcmVr::None);
    } else if (vr == DcmVr::SS) {
        tag = new DcmTagSS(tagKey);
    } else if (vr == DcmVr::US) {
        tag = new DcmTagUS(tagKey);
    } else if (vr == DcmVr::SL) {
        tag = new DcmTagSL(tagKey);
    } else if (vr == DcmVr::UL) {
        tag = new DcmTagUL(tagKey);
    } else if (vr == DcmVr::AT) {
        tag = new DcmTagAT(tagKey);
    } else if (vr == DcmVr::FL) {
        tag = new DcmTagFL(tagKey);
    } else if (vr == DcmVr::FD) {
        tag = new DcmTagFD(tagKey);
    }

    return tag;
}

DcmTag* DcmTag::create(const DcmTagKey &tagKey)
{
    DcmDictionary *dict = DcmDictionary::getInstancePtr();
    if (!dict) {
        return 0;
    }
    DcmTagDescription desc = dict->findByTagKey(tagKey);
    DcmVr vr = desc.vr();

    return DcmTag::create(tagKey, vr);
}

DcmTag* DcmTag::create(const QString &tagName)
{
    DcmDictionary *dict = DcmDictionary::getInstancePtr();
    if (!dict) {
        return 0;
    }
    DcmTagDescription desc = dict->findByName(tagName);
    DcmTagKey key = desc.tagKey();
    DcmVr vr = desc.vr();

    return DcmTag::create(key, vr);
}
