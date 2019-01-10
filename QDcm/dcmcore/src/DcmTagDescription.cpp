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

#include "DcmTagDescription.h"

DcmTagDescription::DcmTagDescription()
    : m_name(),
      m_tagKey(),
      m_vr(DcmVr::Invalid),
      m_vmMin(0),
      m_vmMax(DcmMultiplicity_Unknown),
      m_vmMod(1)
{
}

DcmTagDescription::DcmTagDescription(const QString &name,
                                     const DcmTagKey &tagKey,
                                     const DcmVr &vr,
                                     int min,
                                     int max,
                                     int mod)
    : m_name(name.trimmed()),
      m_tagKey(tagKey),
      m_vr(vr),
      m_vmMin(min),
      m_vmMax(max),
      m_vmMod(mod)
{
    Q_ASSERT(!name.isEmpty());
    Q_ASSERT(min >= 0);
    Q_ASSERT(mod >= 1);
}

DcmTagDescription::DcmTagDescription(const DcmTagDescription &tagDescription)
    : m_name(tagDescription.m_name),
      m_tagKey(tagDescription.m_tagKey),
      m_vr(tagDescription.m_vr),
      m_vmMin(tagDescription.m_vmMin),
      m_vmMax(tagDescription.m_vmMax),
      m_vmMod(tagDescription.m_vmMod)
{
}

DcmTagDescription& DcmTagDescription::operator =(const DcmTagDescription &tagDescription)
{
    if (this != &tagDescription) {
        m_name = tagDescription.m_name;
        m_tagKey = tagDescription.m_tagKey;
        m_vr = tagDescription.m_vr;
        m_vmMin = tagDescription.m_vmMin;
        m_vmMax = tagDescription.m_vmMax;
        m_vmMod = tagDescription.m_vmMod;
    }
    return *this;
}

bool DcmTagDescription::isValid() const
{
    return (!m_name.isEmpty()) && (m_vr != DcmVr::Invalid);
}

QString DcmTagDescription::name() const
{
    return m_name;
}

DcmTagKey DcmTagDescription::tagKey() const
{
    return m_tagKey;
}

DcmVr DcmTagDescription::vr() const
{
    return m_vr;
}

int DcmTagDescription::vmMin() const
{
    return m_vmMin;
}

int DcmTagDescription::vmMax() const
{
    return m_vmMax;
}

int DcmTagDescription::vmMod() const
{
    return m_vmMod;
}

bool DcmTagDescription::isValidMultiplicity(int multiplicity) const
{
    if (multiplicity < m_vmMin) {
        return false;
    }

    if (m_vmMax != DcmMultiplicity_Unknown && multiplicity > m_vmMax) {
        return false;
    }

    if (multiplicity % m_vmMod != 0) {
        return false;
    }

    return true;
}
