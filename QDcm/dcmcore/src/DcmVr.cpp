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

#include "DcmVr.h"

const DcmVr DcmVr::CS(DcmVrKey_CS, 0, 16);
const DcmVr DcmVr::SH(DcmVrKey_SH, 0, 16);
const DcmVr DcmVr::LO(DcmVrKey_LO, 0, 64);
const DcmVr DcmVr::ST(DcmVrKey_ST, 0, 1024);
const DcmVr DcmVr::LT(DcmVrKey_LT, 0, 10240);
const DcmVr DcmVr::UT(DcmVrKey_UT, 0, 0xFFFFFFFE);
const DcmVr DcmVr::AE(DcmVrKey_AE, 0, 16);
const DcmVr DcmVr::PN(DcmVrKey_PN, 0, 64);
const DcmVr DcmVr::UI(DcmVrKey_UI, 0, 64);
const DcmVr DcmVr::DA(DcmVrKey_DA, 0, 8);
const DcmVr DcmVr::TM(DcmVrKey_TM, 0, 16);
const DcmVr DcmVr::DT(DcmVrKey_DT, 0, 26);
const DcmVr DcmVr::AS(DcmVrKey_AS, 0, 4);
const DcmVr DcmVr::IS(DcmVrKey_IS, 0, 12);
const DcmVr DcmVr::DS(DcmVrKey_DS, 0, 16);
const DcmVr DcmVr::SS(DcmVrKey_SS, 2, 2);
const DcmVr DcmVr::US(DcmVrKey_US, 2, 2);
const DcmVr DcmVr::SL(DcmVrKey_SL, 4, 4);
const DcmVr DcmVr::UL(DcmVrKey_UL, 4, 4);
const DcmVr DcmVr::AT(DcmVrKey_AT, 4, 4);
const DcmVr DcmVr::FL(DcmVrKey_FL, 4, 4);
const DcmVr DcmVr::FD(DcmVrKey_FD, 8, 8);
const DcmVr DcmVr::OB(DcmVrKey_OB, 0, DcmSize_Undefined);
const DcmVr DcmVr::OW(DcmVrKey_OW, 0, DcmSize_Undefined);
const DcmVr DcmVr::OF(DcmVrKey_OF, 0, DcmSize_Undefined);
const DcmVr DcmVr::SQ(DcmVrKey_SQ, 0, DcmSize_Undefined);
const DcmVr DcmVr::UN(DcmVrKey_UN, 0, DcmSize_Undefined);

const DcmVr DcmVr::None(DcmVrKey_None, 0, DcmSize_Undefined);
const DcmVr DcmVr::Invalid(DcmVrKey_Invalid, 0, DcmSize_Undefined);

/// Signatures of all VRs.
const int DcmVrTableSize = 27;
const char dcmVrToSignTable[DcmVrTableSize][2] = {
    {'C', 'S'},
    {'S', 'H'},
    {'L', 'O'},
    {'S', 'T'},
    {'L', 'T'},
    {'U', 'T'},
    {'A', 'E'},
    {'P', 'N'},
    {'U', 'I'},
    {'D', 'A'},
    {'T', 'M'},
    {'D', 'T'},
    {'A', 'S'},
    {'I', 'S'},
    {'D', 'S'},
    {'S', 'S'},
    {'U', 'S'},
    {'S', 'L'},
    {'U', 'L'},
    {'A', 'T'},
    {'F', 'L'},
    {'F', 'D'},
    {'O', 'B'},
    {'O', 'W'},
    {'O', 'F'},
    {'S', 'Q'},
    {'U', 'N'}
};

/// Table of all VRs for rapid indexing.
const DcmVr dcmVrTable[DcmVrTableSize] = {
    DcmVr::CS, DcmVr::SH, DcmVr::LO, DcmVr::ST,
    DcmVr::LT, DcmVr::UT, DcmVr::AE, DcmVr::PN,
    DcmVr::UI, DcmVr::DA, DcmVr::TM, DcmVr::DT,
    DcmVr::AS, DcmVr::IS, DcmVr::DS, DcmVr::SS,
    DcmVr::US, DcmVr::SL, DcmVr::UL, DcmVr::AT,
    DcmVr::FL, DcmVr::FD, DcmVr::OB, DcmVr::OW,
    DcmVr::OF, DcmVr::SQ, DcmVr::UN
};

/* Implementation */

DcmVr::DcmVr()
    : m_vrKey(DcmVrKey_Invalid),
      m_minSize(0),
      m_maxSize(0)
{
}

DcmVr::DcmVr(DcmVrKey key, DcmSize min, DcmSize max)
    : m_vrKey(key),
      m_minSize(min),
      m_maxSize(max)
{
}

DcmVr::DcmVr(const DcmVr &vr)
    : m_vrKey(vr.m_vrKey),
      m_minSize(vr.m_minSize),
      m_maxSize(vr.m_maxSize)
{
}

DcmVr& DcmVr::operator =(const DcmVr &vr)
{
    if (this != &vr) {
        m_vrKey = vr.m_vrKey;
        m_minSize = vr.m_minSize;
        m_maxSize = vr.m_maxSize;
    }
    return *this;
}

bool DcmVr::operator ==(const DcmVr &vr) const
{
    return m_vrKey == vr.m_vrKey;
}

bool DcmVr::operator !=(const DcmVr &vr) const
{
    return m_vrKey != vr.m_vrKey;
}

DcmVrKey DcmVr::vrKey() const
{
    return m_vrKey;
}

DcmSize DcmVr::minSize() const
{
    return m_minSize;
}

DcmSize DcmVr::maxSize() const
{
    return m_maxSize;
}

const char *DcmVr::signature() const
{
    int i;
    if (m_vrKey == DcmVrKey_Invalid || m_vrKey == DcmVrKey_None) {
        i = static_cast<int>(DcmVrKey_UN);
    } else {
        i = static_cast<int>(m_vrKey);
    }

    return dcmVrToSignTable[i];
}

bool DcmVr::isString() const
{
    switch (m_vrKey) {
    case DcmVrKey_CS:
    case DcmVrKey_SH:
    case DcmVrKey_LO:
    case DcmVrKey_ST:
    case DcmVrKey_LT:
    case DcmVrKey_UT:
    case DcmVrKey_AE:
    case DcmVrKey_PN:
    case DcmVrKey_UI:
    case DcmVrKey_DA:
    case DcmVrKey_TM:
    case DcmVrKey_DT:
    case DcmVrKey_AS:
    case DcmVrKey_IS:
    case DcmVrKey_DS:
        return true;
    default:
        return false;
    }
}

bool DcmVr::isText() const
{
    switch (m_vrKey) {
    case DcmVrKey_CS:
    case DcmVrKey_SH:
    case DcmVrKey_LO:
    case DcmVrKey_ST:
    case DcmVrKey_LT:
    case DcmVrKey_UT:
    case DcmVrKey_AE:
    case DcmVrKey_PN:
        return true;
    default:
        return false;
    }
}

bool DcmVr::isBinary() const
{
    switch (m_vrKey) {
    case DcmVrKey_OB:
    case DcmVrKey_OW:
    case DcmVrKey_OF:
    case DcmVrKey_UN:
        return true;
    default:
        return false;
    }
}

bool DcmVr::isUnknown() const
{
    return m_vrKey == DcmVrKey_UN;
}

bool DcmVr::isPadded() const
{
    return isString() && (m_vrKey != DcmVrKey_UI);
}

QString DcmVr::toString() const
{
    if (m_vrKey == DcmVrKey_None) {
        return QString("");
    } else if (m_vrKey == DcmVrKey_Invalid) {
        return QString("Invalid");
    }

    int i = static_cast<int>(m_vrKey);

    return QString("%1%2").arg(dcmVrToSignTable[i][0]).arg(dcmVrToSignTable[i][1]);
}

DcmVr DcmVr::bySignatrure(const char *s)
{
    if (!s) {
        return DcmVr::Invalid;
    }

    for (int i = 0; i < DcmVrTableSize; i++) {
        char c[2];
        c[0] = dcmVrToSignTable[i][0];
        c[1] = dcmVrToSignTable[i][1];
        if ((s[0] == c[0]) && (s[1] == c[1])) {
            return dcmVrTable[i];
        }
    }

    return DcmVr::Invalid;
}

DcmVr DcmVr::fromString(const QString &str)
{
    if (str.length() != 2) {
        return DcmVr::Invalid;
    }

    char s[2];
    s[0] = str.at(0).toLatin1();
    s[1] = str.at(1).toLatin1();

    return DcmVr::bySignatrure(s);
}
