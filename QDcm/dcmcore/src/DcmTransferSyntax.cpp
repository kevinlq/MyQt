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

#include "DcmGlobal.h"
#include "DcmTransferSyntax.h"

const DcmTransferSyntax DcmTransferSyntax::Invalid;
const DcmTransferSyntax DcmTransferSyntax::ImplicitLittleEndian("1.2.840.10008.1.2", DcmEndianess_LittleEndian, DcmEncoding_Implicit);
const DcmTransferSyntax DcmTransferSyntax::ExplicitLittleEndian("1.2.840.10008.1.2.1", DcmEndianess_LittleEndian, DcmEncoding_Explicit);
const DcmTransferSyntax DcmTransferSyntax::DeflatedExplicitBigEndian("1.2.840.10008.1.2.1.99", DcmEndianess_BigEndian, DcmEncoding_Explicit);
const DcmTransferSyntax DcmTransferSyntax::ExplicitBigEndian("1.2.840.10008.1.2.2", DcmEndianess_BigEndian, DcmEncoding_Explicit);

const DcmTransferSyntax DcmTransferSyntax::JPEGBaselineProcess1("1.2.840.10008.1.2.4.50");
const DcmTransferSyntax DcmTransferSyntax::JPEGExtendedProcess2_4("1.2.840.10008.1.2.4.51");
const DcmTransferSyntax DcmTransferSyntax::JPEGExtendedProcess3_5("1.2.840.10008.1.2.4.52");
const DcmTransferSyntax DcmTransferSyntax::JPEGSpectralProcess6_8("1.2.840.10008.1.2.4.53");
const DcmTransferSyntax DcmTransferSyntax::JPEGSpectralProcess7_9("1.2.840.10008.1.2.4.54");
const DcmTransferSyntax DcmTransferSyntax::JPEGFullProgressionProcess10_12("1.2.840.10008.1.2.4.55");
const DcmTransferSyntax DcmTransferSyntax::JPEGFullProgressionProcess11_13("1.2.840.10008.1.2.4.56");
const DcmTransferSyntax DcmTransferSyntax::JPEGLosslessProcess14("1.2.840.10008.1.2.4.57");
const DcmTransferSyntax DcmTransferSyntax::JPEGLosslessProcess15("1.2.840.10008.1.2.4.58");
const DcmTransferSyntax DcmTransferSyntax::JPEGExtendedProcess16_18("1.2.840.10008.1.2.4.59");
const DcmTransferSyntax DcmTransferSyntax::JPEGExtendedProcess17_19("1.2.840.10008.1.2.4.60");
const DcmTransferSyntax DcmTransferSyntax::JPEGSpectralProcess20_22("1.2.840.10008.1.2.4.61");
const DcmTransferSyntax DcmTransferSyntax::JPEGSpectralProcess21_23("1.2.840.10008.1.2.4.62");
const DcmTransferSyntax DcmTransferSyntax::JPEGFullProgressionProcess24_26("1.2.840.10008.1.2.4.63");
const DcmTransferSyntax DcmTransferSyntax::JPEGFullProgressionProcess25_27("1.2.840.10008.1.2.4.64");
const DcmTransferSyntax DcmTransferSyntax::JPEGLosslessProcess28("1.2.840.10008.1.2.4.65");
const DcmTransferSyntax DcmTransferSyntax::JPEGLosslessProcess29("1.2.840.10008.1.2.4.66");
const DcmTransferSyntax DcmTransferSyntax::JPEGLosslessProcess14SV1("1.2.840.10008.1.2.4.70");
const DcmTransferSyntax DcmTransferSyntax::JPEGLossless("1.2.840.10008.1.2.4.80");
const DcmTransferSyntax DcmTransferSyntax::JPEGNearLossless("1.2.840.10008.1.2.4.81");
const DcmTransferSyntax DcmTransferSyntax::JPEG2000Lossless("1.2.840.10008.1.2.4.90");
const DcmTransferSyntax DcmTransferSyntax::JPEG2000Lossy("1.2.840.10008.1.2.4.91");
const DcmTransferSyntax DcmTransferSyntax::JPEG2000Part2Lossless("1.2.840.10008.1.2.4.92");
const DcmTransferSyntax DcmTransferSyntax::JPEG2000Part2Lossy("1.2.840.10008.1.2.4.93");

const DcmTransferSyntax DcmTransferSyntax::JPIPReferenced("1.2.840.10008.1.2.4.94");
const DcmTransferSyntax DcmTransferSyntax::JPIPReferencedDeflate("1.2.840.10008.1.2.4.95");
const DcmTransferSyntax DcmTransferSyntax::RLELossless("1.2.840.10008.1.2.5");
const DcmTransferSyntax DcmTransferSyntax::RFC2557MIMEEncapsulation("1.2.840.10008.1.2.6.1");
const DcmTransferSyntax DcmTransferSyntax::MPEG2MainProfile("1.2.840.10008.1.2.4.100");
const DcmTransferSyntax DcmTransferSyntax::MPEG4HighProfile("1.2.840.10008.1.2.4.102");
const DcmTransferSyntax DcmTransferSyntax::MPEG4BDCompatibleHighProfile("1.2.840.10008.1.2.4.103");

DcmTransferSyntax::DcmTransferSyntax()
    : DcmPDUItem(DcmPDUType_TransferSyntax),
      m_uid(),
      m_endianess(DcmEndianess_LittleEndian),
      m_encoding(DcmEncoding_Implicit)
{
}

DcmTransferSyntax::DcmTransferSyntax(const QString &uid, DcmEndianess endianess, DcmEncoding encoding)
    : DcmPDUItem(DcmPDUType_TransferSyntax),
      m_uid(),
      m_endianess(endianess),
      m_encoding(encoding)
{
    if (dcmIsValidUID(uid)) {
        m_uid = uid;
    }
    // UID is invalid, this transfer syntax will be invalid.
}

DcmTransferSyntax::DcmTransferSyntax(const DcmTransferSyntax &transferSyntax)
    : DcmPDUItem(transferSyntax),
      m_uid(transferSyntax.m_uid),
      m_endianess(transferSyntax.m_endianess),
      m_encoding(transferSyntax.m_encoding)
{
}

DcmTransferSyntax& DcmTransferSyntax::operator =(const DcmTransferSyntax &transferSyntax)
{
    if (this != &transferSyntax) {
        DcmPDUItem::operator =(transferSyntax);
        m_uid = transferSyntax.m_uid;
        m_endianess = transferSyntax.m_endianess;
        m_encoding = transferSyntax.m_encoding;
    }
    return *this;
}

DcmPDUItem* DcmTransferSyntax::clone() const
{
    return new DcmTransferSyntax(*this);
}

DcmTransferSyntax::~DcmTransferSyntax()
{
}

QString DcmTransferSyntax::uid() const
{
    return m_uid;
}

DcmEndianess DcmTransferSyntax::endianess() const
{
    return m_endianess;
}

DcmEncoding DcmTransferSyntax::encoding() const
{
    return m_encoding;
}

DcmSize DcmTransferSyntax::contentSize() const
{
    return m_uid.length();
}

bool DcmTransferSyntax::operator ==(const DcmTransferSyntax &transferSyntax) const
{
    return (m_uid == transferSyntax.m_uid)
            && (m_endianess == transferSyntax.m_endianess)
            && (m_encoding == transferSyntax.m_encoding);
}

bool DcmTransferSyntax::operator !=(const DcmTransferSyntax &transferSyntax) const
{
    return (m_uid != transferSyntax.m_uid)
            || (m_endianess != transferSyntax.m_endianess)
            || (m_encoding != transferSyntax.m_encoding);
}

bool DcmTransferSyntax::isValid() const
{
    return (!m_uid.isEmpty()) && DcmPDUItem::isValid();
}

DcmTransferSyntax DcmTransferSyntax::fromUid(const QString &uid)
{
    DcmTransferSyntax ts = DcmTransferSyntax::ExplicitLittleEndian;
    if (uid == DcmTransferSyntax::ImplicitLittleEndian.uid()) {
        ts = DcmTransferSyntax::ImplicitLittleEndian;
    } else if (uid == DcmTransferSyntax::ExplicitBigEndian.uid()) {
        ts = DcmTransferSyntax::ExplicitBigEndian;
    } else {
        ts = DcmTransferSyntax(uid);
    }

    return ts;
}
