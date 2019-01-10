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

#include <QDebug>
#include "DcmDictionary.h"
#include "DcmDataset.h"
#include "DcmModule.h"

DcmModule::DcmModule(const QString &name)
    : m_name(name),
      m_tagKeys(),
      m_tagsList()
{
}

DcmModule::DcmModule(const DcmModule &module)
    : m_name(module.m_name),
      m_tagKeys(module.m_tagKeys),
      m_tagsList(module.m_tagsList)
{
}

DcmModule& DcmModule::operator =(const DcmModule &module)
{
    if (this != &module) {
        m_name = module.m_name;
        m_tagKeys = module.m_tagKeys;
        m_tagsList = module.m_tagsList;
    }
    return *this;
}

DcmModule* DcmModule::clone() const
{
    return new DcmModule(*this);
}

DcmModule::~DcmModule()
{
}

QString DcmModule::name() const
{
    return m_name;
}

QList<DcmTagKey> DcmModule::tagKeys(TagType type) const
{
    return m_tagKeys.value(type);
}

void DcmModule::fetchFromDataset(const DcmDataset &dataset)
{
    fetchTags(dataset, m_tagKeys.value(TagType_1));
    fetchTags(dataset, m_tagKeys.value(TagType_1C));
    fetchTags(dataset, m_tagKeys.value(TagType_2));
    fetchTags(dataset, m_tagKeys.value(TagType_2C));
    fetchTags(dataset, m_tagKeys.value(TagType_3));
}

bool DcmModule::isValid() const
{
    bool valid = true;

    // Check that mandatory tags are present and are not null
    foreach (DcmTagKey tagKey, m_tagKeys.value(TagType_1)) {
        DcmTag *tag = m_tagsList.findFirst(tagKey);
        if (!tag) {
            valid = false;
            break;
        }
        if (!tag->value().isValid() || tag->value().isNull()) {
            valid = false;
            break;
        }
    }

    // Check the mandatory tags that can be null
    foreach (DcmTagKey tagKey, m_tagKeys.value(TagType_2)) {
        DcmTag *tag = m_tagsList.findFirst(tagKey);
        if (!tag) {
            valid = false;
            break;
        }
    }

    return valid;
}

DcmTag* DcmModule::tag(const DcmTagKey &tagKey) const
{
    return m_tagsList.findFirst(tagKey);
}

DcmTag* DcmModule::tag(const QString &name) const
{
    DcmTagDescription desc = DcmDictionary::getInstancePtr()->findByName(name);
    if (desc.isValid()) {
        return tag(desc.tagKey());
    }
    return 0;
}

QVariant DcmModule::tagValue(const DcmTagKey &tagKey) const
{
    DcmTag *tagPtr = tag(tagKey);
    if (tagPtr) {
        return tagPtr->value();
    }
    return QVariant();
}

QVariant DcmModule::tagValue(const QString &tagName) const
{
    DcmTag *tagPtr = tag(tagName);
    if (tagPtr) {
        return tagPtr->value();
    }
    return QVariant();
}

QVariantList DcmModule::tagValues(const DcmTagKey &tagKey) const
{
    DcmTag *tagPtr = tag(tagKey);
    if (tagPtr) {
        return tagPtr->values();
    }
    return QVariantList();
}

QVariantList DcmModule::tagValues(const QString &tagName) const
{
    DcmTag *tagPtr = tag(tagName);
    if (tagPtr) {
        return tagPtr->values();
    }
    return QVariantList();
}

void DcmModule::setTagValue(const DcmTagKey &tagKey, const QVariant &value)
{
    if (!isTagOfThisModule(tagKey)) {
        qWarning() << "Setting value of a tag " << tagKey.toString() << ": not a part of the module" << name();
        return;
    }

    DcmTag *tagPtr = DcmTag::create(tagKey);
    tagPtr->setValue(value);
    m_tagsList.insertOrReplaceAndRetain(tagPtr);
}

void DcmModule::setTagValues(const DcmTagKey &tagKey, const QVariantList &values)
{
    if (!isTagOfThisModule(tagKey)) {
        qWarning() << "Tag " << tagKey.toString() << "is not a part of the module.";
        return;
    }

    DcmTag *tagPtr = DcmTag::create(tagKey);
    foreach (QVariant v, values) {
        tagPtr->appendValue(v);
    }
    m_tagsList.insertOrReplaceAndRetain(tagPtr);
}

void DcmModule::setTagValue(const QString &tagName, const QVariant &value)
{
    DcmTagDescription desc = DcmDictionary::getInstancePtr()->findByName(tagName);
    if (desc.isValid()) {
        setTagValue(desc.tagKey(), value);
    } else {
        qWarning() << "Tag" << tagName << "is unknown";
    }
}

void DcmModule::setTagValues(const QString &tagName, const QVariantList &values)
{
    DcmTagDescription desc = DcmDictionary::getInstancePtr()->findByName(tagName);
    if (desc.isValid()) {
        if (!desc.isValidMultiplicity(values.count())) {
            qWarning() << "Tag" << tagName << desc.tagKey().toString()
                       << "multiplicity" << values.count() << "is invalid.";
        }
        setTagValues(desc.tagKey(), values);
    } else {
        qWarning() << "Tag" << tagName << "is unknown";
    }
}

void DcmModule::completeVoidTags()
{
    // Complete module with missing tags of type 2.
    // Void value will be assigned to these tags
    foreach (DcmTagKey key, m_tagKeys.value(TagType_2)) {
        if (m_tagsList.findFirst(key) == 0) {
            setTagValue(key, QVariant());
        }
    }
}

DcmTagList DcmModule::tagList() const
{
    return m_tagsList;
}

void DcmModule::addSupportedTag(const DcmTagKey &tagKey, TagType type)
{
    if (!m_tagKeys[type].contains(type)) {
        m_tagKeys[type].append(tagKey);
    }
}

void DcmModule::addSupportedTag(const QString &tagName, TagType type)
{
    DcmTagDescription desc = DcmDictionary::getInstancePtr()->findByName(tagName);
    if (desc.isValid()) {
        addSupportedTag(desc.tagKey(), type);
    }
}

bool DcmModule::isTagOfThisModule(const DcmTagKey &tagKey) const
{
    return m_tagKeys.value(TagType_1).contains(tagKey)
            || m_tagKeys.value(TagType_1C).contains(tagKey)
            || m_tagKeys.value(TagType_2).contains(tagKey)
            || m_tagKeys.value(TagType_2C).contains(tagKey)
            || m_tagKeys.value(TagType_3).contains(tagKey);
}

void DcmModule::fetchTags(const DcmDataset &dataset, const QList<DcmTagKey> &tagKeys)
{
    foreach (DcmTagKey tagKey, tagKeys) {
        DcmTag *tagPtr = dataset.findTag(tagKey);
        if (tagPtr) {
            m_tagsList.insertOrReplace(*tagPtr);
        }
    }
}
