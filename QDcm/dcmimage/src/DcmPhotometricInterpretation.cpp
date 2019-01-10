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

#include <QMap>
#include "DcmPhotometricInterpretation.h"

const DcmPhotometricInterpretation DcmPhotometricInterpretation::Monochrome1("MONOCHROME1");
const DcmPhotometricInterpretation DcmPhotometricInterpretation::Monochrome2("MONOCHROME2");
const DcmPhotometricInterpretation DcmPhotometricInterpretation::PaletteColor("PALETTE COLOR");
const DcmPhotometricInterpretation DcmPhotometricInterpretation::RGB("RGB");
const DcmPhotometricInterpretation DcmPhotometricInterpretation::HSV("HSV");
const DcmPhotometricInterpretation DcmPhotometricInterpretation::ARGB("ARGB");
const DcmPhotometricInterpretation DcmPhotometricInterpretation::CMYK("CMYK");
const DcmPhotometricInterpretation DcmPhotometricInterpretation::YBRFull("YBR_FULL");
const DcmPhotometricInterpretation DcmPhotometricInterpretation::YBRFull422("YBR_FULL_422");
const DcmPhotometricInterpretation DcmPhotometricInterpretation::YBRPartial422("YBR_PARTIAL_422");
const DcmPhotometricInterpretation DcmPhotometricInterpretation::Unknown;

static QMap<QString, DcmPhotometricInterpretation> generateSignatureToPIMap()
{
    QMap<QString, DcmPhotometricInterpretation> map;
    map.insert(DcmPhotometricInterpretation::Monochrome1.signature(), DcmPhotometricInterpretation::Monochrome1);
    map.insert(DcmPhotometricInterpretation::Monochrome2.signature(), DcmPhotometricInterpretation::Monochrome2);
    map.insert(DcmPhotometricInterpretation::PaletteColor.signature(), DcmPhotometricInterpretation::PaletteColor);
    map.insert(DcmPhotometricInterpretation::RGB.signature(), DcmPhotometricInterpretation::RGB);
    map.insert(DcmPhotometricInterpretation::HSV.signature(), DcmPhotometricInterpretation::HSV);
    map.insert(DcmPhotometricInterpretation::ARGB.signature(), DcmPhotometricInterpretation::ARGB);
    map.insert(DcmPhotometricInterpretation::CMYK.signature(), DcmPhotometricInterpretation::CMYK);
    map.insert(DcmPhotometricInterpretation::YBRFull.signature(), DcmPhotometricInterpretation::YBRFull);
    map.insert(DcmPhotometricInterpretation::YBRFull422.signature(), DcmPhotometricInterpretation::YBRFull422);
    map.insert(DcmPhotometricInterpretation::YBRPartial422.signature(), DcmPhotometricInterpretation::YBRPartial422);
    return map;
}

static const QMap<QString, DcmPhotometricInterpretation> signatureToPIMap
    = generateSignatureToPIMap();

DcmPhotometricInterpretation::DcmPhotometricInterpretation()
    : m_signature()
{
}

DcmPhotometricInterpretation::DcmPhotometricInterpretation(const QString &sign)
    : m_signature(sign)
{
}

DcmPhotometricInterpretation::DcmPhotometricInterpretation(const DcmPhotometricInterpretation &ph)
    : m_signature(ph.m_signature)
{
}

DcmPhotometricInterpretation& DcmPhotometricInterpretation::operator =(const DcmPhotometricInterpretation &ph)
{
    if (this != &ph) {
        m_signature = ph.m_signature;
    }
    return *this;
}

QString DcmPhotometricInterpretation::signature() const
{
    return m_signature;
}

QString DcmPhotometricInterpretation::toString() const
{
    return m_signature;
}

bool DcmPhotometricInterpretation::isValid() const
{
    return !m_signature.isEmpty();
}

bool DcmPhotometricInterpretation::isGrayscale() const
{
    return (*this == DcmPhotometricInterpretation::Monochrome1)
            || (*this == DcmPhotometricInterpretation::Monochrome2);
}

bool DcmPhotometricInterpretation::operator ==(const DcmPhotometricInterpretation &ph) const
{
    return m_signature == ph.m_signature;
}

bool DcmPhotometricInterpretation::operator !=(const DcmPhotometricInterpretation &ph) const
{
    return m_signature != ph.m_signature;
}

DcmPhotometricInterpretation DcmPhotometricInterpretation::bySignature(const QString &sign)
{
    if (signatureToPIMap.contains(sign)) {
        return signatureToPIMap[sign];
    }
    return DcmPhotometricInterpretation::Unknown;
}
