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
#include "DcmGlobal.h"
#include "DcmTagUS.h"
#include "DcmTagUI.h"
#include "DcmDataset.h"
#include "DcmDimseMessage.h"

DcmDimseMessage::DcmDimseMessage()
    : m_commandDataset()
{
    setHasData(false);
}

DcmDimseMessage::DcmDimseMessage(const DcmDataset &dataset)
    : m_commandDataset(dataset)
{
}

DcmDimseMessage::DcmDimseMessage(const QString &serviceClassUID, DcmCommandType command, int id)
    : m_commandDataset()
{
    Q_ASSERT(!serviceClassUID.isEmpty());
    setServiceClassUID(serviceClassUID);
    setCommand(command);
    setMessageId(id);
    setHasData(false);
}

DcmDimseMessage::DcmDimseMessage(const DcmDimseMessage &message)
    : m_commandDataset(message.m_commandDataset)
{
}

DcmDimseMessage& DcmDimseMessage::operator =(const DcmDimseMessage &message)
{
    if (this != &message) {
        m_commandDataset = message.m_commandDataset;
    }
    return *this;
}

DcmDimseMessage* DcmDimseMessage::clone() const
{
    return new DcmDimseMessage(*this);
}

DcmDimseMessage::~DcmDimseMessage()
{
}

QString DcmDimseMessage::serviceClassUID() const
{
    DcmTag *tagPtr = m_commandDataset.findTag(DcmTagKey::CommandServiceClassUID);
    if (tagPtr) {
        return tagPtr->value().toString();
    }
    return QString();
}

void DcmDimseMessage::setServiceClassUID(const QString &uid)
{
    if (dcmIsValidUID(uid)) {
        qWarning() << "UID" << uid << "is invalid";
    }
    DcmTagUI tag(DcmTagKey::CommandServiceClassUID);
    tag.setString(uid);
    m_commandDataset.insert(tag);
}

int DcmDimseMessage::messageId() const
{
    DcmTag *tagPtr = m_commandDataset.findTag(DcmTagKey::CommandMessageId);
    if (tagPtr) {
        return tagPtr->value().toInt();
    }
    return 0;
}

void DcmDimseMessage::setMessageId(int id)
{
    DcmTagUS tag(DcmTagKey::CommandMessageId);
    tag.setUnsignedShort((DcmUnsignedShort)id);
    m_commandDataset.insert(tag);
}

DcmCommandType DcmDimseMessage::command() const
{
    DcmTag *tagPtr = m_commandDataset.findTag(DcmTagKey::CommandField);
    if (tagPtr) {
        return (DcmCommandType)tagPtr->value().toInt();
    }
    return DcmCommandType_None;
}

void DcmDimseMessage::setCommand(DcmCommandType cmd)
{
    DcmTagUS tag(DcmTagKey::CommandField);
    tag.setUnsignedShort((DcmUnsignedShort)cmd);
    m_commandDataset.insert(tag);
}

bool DcmDimseMessage::hasData() const
{
    DcmTag *tagPtr = m_commandDataset.findTag(DcmTagKey::CommandDataSetType);
    Q_ASSERT(tagPtr);
    if (tagPtr) {
        return tagPtr->value().toInt() == DcmDimseMessage::Data_Present;
    }
    return false;   // No data by default
}

void DcmDimseMessage::setHasData(bool flag)
{
    DcmTagUS tagDataSetType(DcmTagKey::CommandDataSetType);
    tagDataSetType.setUnsignedShort(flag ? DcmDimseMessage::Data_Present : DcmDimseMessage::Data_NotPresent);
    m_commandDataset.insert(tagDataSetType);
}

DcmDataset& DcmDimseMessage::commandDataset()
{
    return m_commandDataset;
}

DcmDataset DcmDimseMessage::constCommandDataset() const
{
    return m_commandDataset;
}

void DcmDimseMessage::setCommandDataset(const DcmDataset &dataset)
{
    m_commandDataset = dataset;
}
