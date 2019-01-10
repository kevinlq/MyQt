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

#include "DcmTagKey.h"

const DcmTagKey DcmTagKey::CommandServiceClassUID                   (0x0000, 0x0002);
const DcmTagKey DcmTagKey::CommandField                             (0x0000, 0x0100);
const DcmTagKey DcmTagKey::CommandMessageId                         (0x0000, 0x0110);
const DcmTagKey DcmTagKey::CommandResponseMessageId                 (0x0000, 0x0120);
const DcmTagKey DcmTagKey::CommandMoveDestinationAE                 (0x0000, 0x0600);
const DcmTagKey DcmTagKey::CommandPriority                          (0x0000, 0x0700);
const DcmTagKey DcmTagKey::CommandDataSetType                       (0x0000, 0x0800);
const DcmTagKey DcmTagKey::CommandStatus                            (0x0000, 0x0900);
const DcmTagKey DcmTagKey::CommandAffectedSOPInstanceUID            (0x0000, 0x1000);
const DcmTagKey DcmTagKey::CommandRequestedSOPInstanceUID           (0x0000, 0x1001);
const DcmTagKey DcmTagKey::CommandNumberOfRemainedSuboperations     (0x0000, 0x1020);
const DcmTagKey DcmTagKey::CommandNumberOfCompletedSuboperations    (0x0000, 0x1021);
const DcmTagKey DcmTagKey::CommandNumberOfFailedSuboperations       (0x0000, 0x1022);
const DcmTagKey DcmTagKey::CommandNumberOfWarningSuboperations      (0x0000, 0x1023);
const DcmTagKey DcmTagKey::CommandMoveOriginatorAE                  (0x0000, 0x1030);
const DcmTagKey DcmTagKey::CommandMoveOriginatorMessageId           (0x0000, 0x1031);

const DcmTagKey DcmTagKey::TransferSyntaxUID                        (0x0002, 0x0010);

const DcmTagKey DcmTagKey::SpecificCharacterSet                     (0x0008, 0x0005);

const DcmTagKey DcmTagKey::PixelData                                (0x7FE0, 0x0010);
const DcmTagKey DcmTagKey::Item                                     (0xFFFE, 0xE000);
const DcmTagKey DcmTagKey::ItemDeliminationItem                     (0xFFFE, 0xE00D);
const DcmTagKey DcmTagKey::SequenceDeliminationItem                 (0xFFFE, 0xE0DD);

/* Implementation */

DcmTagKey::DcmTagKey()
    : m_group(0),
      m_element(0)
{
}

DcmTagKey::DcmTagKey(DcmUnsignedShort group, DcmUnsignedShort element)
    : m_group(group),
      m_element(element)
{
}

DcmTagKey::DcmTagKey(DcmHash hash)
    : m_group(hash >> 16),
      m_element(hash & 0xFFFF)
{
}

DcmTagKey::DcmTagKey(const DcmTagKey &tagKey)
    : m_group(tagKey.m_group),
      m_element(tagKey.m_element)
{
}

DcmTagKey& DcmTagKey::operator =(const DcmTagKey &tagKey)
{
    if (this != &tagKey) {
        m_group = tagKey.m_group;
        m_element = tagKey.m_element;
    }
    return *this;
}

DcmTagKey& DcmTagKey::operator =(DcmHash hash)
{
    m_group = hash >> 16;
    m_element = hash & 0xFFFF;
    return *this;
}

bool DcmTagKey::operator ==(const DcmTagKey &tagKey) const
{
    return (m_group == tagKey.m_group) && (m_element == tagKey.m_element);
}

bool DcmTagKey::operator !=(const DcmTagKey &tagKey) const
{
    return (m_group != tagKey.m_group) || (m_element != tagKey.m_element);
}

bool DcmTagKey::operator >(const DcmTagKey &tagKey) const
{
    if (m_group == tagKey.m_group) {
        return m_element > tagKey.m_element;
    }
    return m_group > tagKey.m_group;
}

bool DcmTagKey::operator <(const DcmTagKey &tagKey) const
{
    if (m_group == tagKey.m_group) {
        return m_element < tagKey.m_element;
    }
    return m_group < tagKey.m_group;
}

bool DcmTagKey::operator >=(const DcmTagKey &tagKey) const
{
    if (m_group == tagKey.m_group) {
        return(m_element >= tagKey.m_element);
    }
    return m_group > tagKey.m_group;
}

bool DcmTagKey::operator <=(const DcmTagKey &tagKey) const
{
    if (m_group == tagKey.m_group) {
        return m_element <= tagKey.m_element;
    }
    return m_group < tagKey.m_group;
}

DcmUnsignedShort DcmTagKey::group() const
{
    return m_group;
}

DcmUnsignedShort DcmTagKey::element() const
{
    return m_element;
}

DcmHash DcmTagKey::hash() const
{
    return (((DcmUnsignedLong)m_group)<< 16) | m_element;
}

void DcmTagKey::setGroup(DcmUnsignedShort group)
{
    m_group = group;
}

void DcmTagKey::setElement(DcmUnsignedShort element)
{
    m_element = element;
}

void DcmTagKey::setHash(DcmHash hash)
{
    m_group = hash >> 16;
    m_element = hash & 0xFFFF;
}

bool DcmTagKey::isPrivate() const
{
    return (m_group & 0x0001) != 0;
}

bool DcmTagKey::isGroupSize() const
{
    return m_element == 0;
}

bool DcmTagKey::isAlwaysImplicit() const
{
    return (*this == Item)
            || (*this == ItemDeliminationItem)
            || (*this == SequenceDeliminationItem);
}

QString DcmTagKey::toString() const
{
    return QString("(%1, %2)")
            .arg(QString::number(m_group, 16).rightJustified(4, '0'))
            .arg(QString::number(m_element, 16).rightJustified(4, '0'));
}
