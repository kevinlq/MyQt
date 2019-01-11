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

#include "DcmPDVItem.h"

DcmPDVItem::DcmPDVItem(int contextId, bool command, bool terminating)
    : m_presentationContextId(contextId),
      m_command(command),
      m_terminating(terminating),
      m_byteArray()
{
}

DcmPDVItem::DcmPDVItem(const DcmPDVItem &pdv)
    : m_presentationContextId(pdv.m_presentationContextId),
      m_command(pdv.m_command),
      m_terminating(pdv.m_terminating),
      m_byteArray(pdv.m_byteArray)
{
}

DcmPDVItem& DcmPDVItem::operator =(const DcmPDVItem &pdv)
{
    if (this != &pdv) {
        m_presentationContextId = pdv.m_presentationContextId;
        m_command = pdv.m_command;
        m_terminating = pdv.m_terminating;
        m_byteArray = pdv.m_byteArray;
    }
    return *this;
}

int DcmPDVItem::presentationContextId() const
{
    return m_presentationContextId;
}

void DcmPDVItem::setPresentationContextId(int id)
{
    m_presentationContextId = id;
}

bool DcmPDVItem::isCommand() const
{
    return m_command;
}

void DcmPDVItem::setCommand(bool flag)
{
    m_command = flag;
}

bool DcmPDVItem::isTerminating() const
{
    return m_terminating;
}

void DcmPDVItem::setTerminating(bool flag)
{
    m_terminating = flag;
}

DcmSize DcmPDVItem::dataSize() const
{
    return m_byteArray.size();
}

const char* DcmPDVItem::constData() const
{
    return m_byteArray.constData();
}

char* DcmPDVItem::data()
{
    return m_byteArray.data();
}

QByteArray& DcmPDVItem::byteArray()
{
    return m_byteArray;
}

void DcmPDVItem::setByteArray(const QByteArray &data)
{
    m_byteArray = data;
}

void DcmPDVItem::clear()
{
    m_byteArray.clear();
}
