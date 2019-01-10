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
#include "DcmTagString.h"
#include "DcmTagCS.h"
#include "DcmTagSH.h"
#include "DcmTagLO.h"
#include "DcmTagST.h"
#include "DcmTagLT.h"
#include "DcmTagUT.h"
#include "DcmTagAE.h"
#include "DcmTagPN.h"
#include "DcmTagUI.h"
#include "DcmTagDA.h"
#include "DcmTagTM.h"
#include "DcmTagDT.h"
#include "DcmTagAS.h"
#include "DcmTagIS.h"
#include "DcmTagDS.h"

DcmTagString::DcmTagString()
    : DcmTag(),
      m_string()
{
}

DcmTagString::DcmTagString(const DcmTagKey &tagKey, const DcmVr &vr)
    : DcmTag(tagKey, vr),
      m_string()
{
    if (!vr.isString()) {
        qCritical() << "String-based tag created with non-string value representation" << vr.toString();
        setVr(DcmVr::Invalid);
    }
}

DcmTagString::DcmTagString(const DcmTagString &tag)
    : DcmTag(tag),
      m_string(tag.m_string)
{
}

DcmTagString& DcmTagString::operator =(const DcmTagString &tag)
{
    if (this != &tag) {
        DcmTag::operator =(tag);
        m_string = tag.m_string;
    }
    return *this;
}

DcmTag* DcmTagString::clone() const
{
    return new DcmTagString(*this);
}

DcmTagString::~DcmTagString()
{
}

QVariant DcmTagString::value() const
{
    return QVariant(m_string);
}

QVariantList DcmTagString::values() const
{
    QStringList sl = asStringList();
    QVariantList res;

    foreach (QString str, sl) {
        res.append(QVariant(str));
    }

    return res;
}

void DcmTagString::setValue(const QVariant &v)
{
    setString(v.toString());
}

void DcmTagString::appendValue(const QVariant &v)
{
    appendString(v.toString());
}

DcmTagString& DcmTagString::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}

int DcmTagString::multiplicity() const
{
    if (m_string.isEmpty()) {
        return 0;
    }
    return m_string.count('\\') + 1;
}

QString DcmTagString::asString() const
{
    return m_string;
}

void DcmTagString::setString(const QString &str)
{
    m_string = str.trimmed();
}

void DcmTagString::appendString(const QString &str)
{
    QString s = str.trimmed().left(vr().maxSize());

    if (!s.isEmpty()) {
        if (m_string.isEmpty()) {
            m_string = s;
        } else {
            m_string.append('\\').append(s);
        }
    }
}

QStringList DcmTagString::asStringList() const
{
    return m_string.split("\\", QString::KeepEmptyParts);
}

void DcmTagString::setStringList(const QStringList &strList)
{
    m_string = QString();

    QListIterator<QString> i(strList);
    while (i.hasNext()) {
        QString str = i.next().trimmed().left(vr().maxSize());
        m_string.append(str);
        if (i.hasNext()) {
            m_string.append('\\');
        }
    }
}

DcmSize DcmTagString::contentSize(const DcmTransferSyntax &transferSyntax) const
{
    Q_UNUSED(transferSyntax)

    DcmSize s = m_string.length();
    // Tag content must have an even length.
    if (s & 1) {
        s++;
    }
    return s;
}

DcmTagString* DcmTagString::create(const DcmTagKey &tagKey, const DcmVr &vr)
{
    DcmVrKey vrKey = vr.vrKey();
    DcmTagString *tag = 0;


    switch(vrKey) {
    case DcmVrKey_CS:
        tag = new DcmTagCS(tagKey);
        break;
    case DcmVrKey_SH:
        tag = new DcmTagSH(tagKey);
        break;
    case DcmVrKey_LO:
        tag = new DcmTagLO(tagKey);
        break;
    case DcmVrKey_ST:
        tag = new DcmTagST(tagKey);
        break;
    case DcmVrKey_LT:
        tag = new DcmTagLT(tagKey);
        break;
    case DcmVrKey_UT:
        tag = new DcmTagUT(tagKey);
        break;
    case DcmVrKey_AE:
        tag = new DcmTagAE(tagKey);
        break;
    case DcmVrKey_PN:
        tag = new DcmTagPN(tagKey);
        break;
    case DcmVrKey_UI:
        tag = new DcmTagUI(tagKey);
        break;
    case DcmVrKey_DA:
        tag = new DcmTagDA(tagKey);
        break;
    case DcmVrKey_TM:
        tag = new DcmTagTM(tagKey);
        break;
    case DcmVrKey_DT:
        tag = new DcmTagDT(tagKey);
        break;
    case DcmVrKey_AS:
        tag = new DcmTagAS(tagKey);
        break;
    case DcmVrKey_IS:
        tag = new DcmTagIS(tagKey);
        break;
    case DcmVrKey_DS:
        tag = new DcmTagDS(tagKey);
        break;
    default:
        return 0;
    }

    return tag;
}
