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
#include "DcmTagUI.h"

DcmTagUI::DcmTagUI()
    : DcmTagString(DcmTagKey(), DcmVr::UI)
{
}

DcmTagUI::DcmTagUI(const DcmTagKey &tagKey)
    : DcmTagString(tagKey, DcmVr::UI)
{
}

DcmTagUI::DcmTagUI(const DcmTagUI &tag)
    : DcmTagString(tag)
{
}

DcmTagUI& DcmTagUI::operator =(const DcmTagUI &tag)
{
    if (this != &tag) {
        DcmTagString::operator =(tag);
    }
    return *this;
}

DcmTag* DcmTagUI::clone() const
{
    return new DcmTagUI(*this);
}

DcmTagUI::~DcmTagUI()
{
}

void DcmTagUI::setValue(const QVariant &v)
{
    QString str = v.toString().trimmed();

    if (!dcmIsValidUID(str)) {
        qCritical() << "The UID value" << str << "is invalid.";
    }

    setString(str);
}

void DcmTagUI::appendValue(const QVariant &v)
{
    QString str = v.toString().trimmed();

    if (!dcmIsValidUID(str)) {
        qCritical() << "The UID value" << str << "is invalid.";
    }
    appendString(str);
}

DcmTagUI& DcmTagUI::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}
