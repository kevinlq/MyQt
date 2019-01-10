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

#ifndef DCMTRANSFERSYNTAX_H
#define DCMTRANSFERSYNTAX_H

#include <QString>
#include "DcmCoreApi.h"
#include "DcmTypes.h"
#include "DcmPDUItem.h"

/*! DICOM transfer syntax.
 *
 * This class defines a transfer syntax used to encode DICOM
 * data when storing or communicating.
 * The transfer syntax is identified by its UID. It also
 * defines endianess and encoding (implicit/explicit) to be
 * used when transforming DICOM data into binary and vice versa.
 */
class DCM_CORE_API DcmTransferSyntax: public DcmPDUItem
{
public:

    // Predefined transfer syntaxes
    static const DcmTransferSyntax Invalid;                     ///< Invalid transfer syntax.
    static const DcmTransferSyntax ImplicitLittleEndian;        ///< 1.2.840.10008.1.2, default DICOM transfer syntax.
    static const DcmTransferSyntax ExplicitLittleEndian;        ///< 1.2.840.10008.1.2.1
    static const DcmTransferSyntax DeflatedExplicitBigEndian;   ///< 1.2.840.10008.1.2.1.99
    static const DcmTransferSyntax ExplicitBigEndian;           ///< 1.2.840.10008.1.2.2

    static const DcmTransferSyntax JPEGBaselineProcess1;        ///< 1.2.840.10008.1.2.4.50 (limited to 8 bits per sample)
    static const DcmTransferSyntax JPEGExtendedProcess2_4;      ///< 1.2.840.10008.1.2.4.51 (limited to 12 bits per sample)
    static const DcmTransferSyntax JPEGExtendedProcess3_5;      ///< 1.2.840.10008.1.2.4.52
    static const DcmTransferSyntax JPEGSpectralProcess6_8;      ///< 1.2.840.10008.1.2.4.53
    static const DcmTransferSyntax JPEGSpectralProcess7_9;      ///< 1.2.840.10008.1.2.4.54
    static const DcmTransferSyntax JPEGFullProgressionProcess10_12; ///< 1.2.840.10008.1.2.4.55
    static const DcmTransferSyntax JPEGFullProgressionProcess11_13; ///< 1.2.840.10008.1.2.4.56
    static const DcmTransferSyntax JPEGLosslessProcess14;       ///< 1.2.840.10008.1.2.4.57
    static const DcmTransferSyntax JPEGLosslessProcess15;       ///< 1.2.840.10008.1.2.4.58
    static const DcmTransferSyntax JPEGExtendedProcess16_18;    ///< 1.2.840.10008.1.2.4.59
    static const DcmTransferSyntax JPEGExtendedProcess17_19;    ///< 1.2.840.10008.1.2.4.60
    static const DcmTransferSyntax JPEGSpectralProcess20_22;    ///< 1.2.840.10008.1.2.4.61
    static const DcmTransferSyntax JPEGSpectralProcess21_23;    ///< 1.2.840.10008.1.2.4.62
    static const DcmTransferSyntax JPEGFullProgressionProcess24_26; ///< 1.2.840.10008.1.2.4.63
    static const DcmTransferSyntax JPEGFullProgressionProcess25_27; ///< 1.2.840.10008.1.2.4.64
    static const DcmTransferSyntax JPEGLosslessProcess28;       ///< 1.2.840.10008.1.2.4.65
    static const DcmTransferSyntax JPEGLosslessProcess29;       ///< 1.2.840.10008.1.2.4.66
    static const DcmTransferSyntax JPEGLosslessProcess14SV1;    ///< 1.2.840.10008.1.2.4.70
    static const DcmTransferSyntax JPEGLossless;                ///< 1.2.840.10008.1.2.4.80
    static const DcmTransferSyntax JPEGNearLossless;            ///< 1.2.840.10008.1.2.4.81
    static const DcmTransferSyntax JPEG2000Lossless;            ///< 1.2.840.10008.1.2.4.90
    static const DcmTransferSyntax JPEG2000Lossy;               ///< 1.2.840.10008.1.2.4.91
    static const DcmTransferSyntax JPEG2000Part2Lossless;       ///< 1.2.840.10008.1.2.4.92
    static const DcmTransferSyntax JPEG2000Part2Lossy;          ///< 1.2.840.10008.1.2.4.93

    static const DcmTransferSyntax JPIPReferenced;              ///< 1.2.840.10008.1.2.4.94
    static const DcmTransferSyntax JPIPReferencedDeflate;       ///< 1.2.840.10008.1.2.4.95
    static const DcmTransferSyntax RLELossless;                 ///< 1.2.840.10008.1.2.5
    static const DcmTransferSyntax RFC2557MIMEEncapsulation;    ///< 1.2.840.10008.1.2.6.1

    static const DcmTransferSyntax MPEG2MainProfile;            ///< 1.2.840.10008.1.2.4.100
    static const DcmTransferSyntax MPEG4HighProfile;            ///< 1.2.840.10008.1.2.4.102
    static const DcmTransferSyntax MPEG4BDCompatibleHighProfile;    ///< 1.2.840.10008.1.2.4.103

    /**
     * Default constructor.
     * Constructs invalid transfer syntax.
     */
    DcmTransferSyntax();

    /**
     * Construct transfer syntax.
     * With just an UID given, it default to little endian explicit transfer syntax.
     * \param uid UID.
     * \param endianess Endianess: little or big endian.
     * \param encoding Encoding: implicit or explicit.
     */
    DcmTransferSyntax(const QString &uid,
                      DcmEndianess endianess = DcmEndianess_LittleEndian,
                      DcmEncoding encoding = DcmEncoding_Explicit);

    /**
     * Copy constructor.
     * \param transferSyntax Transfer syntax to be copied.
     */
    DcmTransferSyntax(const DcmTransferSyntax &transferSyntax);

    /**
     * Assignment operator.
     * \param transferSyntax Transfer syntax to be assigned.
     * \return This transfer syntax object.
     */
    DcmTransferSyntax& operator =(const DcmTransferSyntax &transferSyntax);

    /**
     * Clone this transfer syntax object.
     * \return Pointer to this object's clone.
     */
    DcmPDUItem* clone() const;

    /**
     * Destructor.
     */
    ~DcmTransferSyntax();

    /**
     * Returns UID of this transfer syntax.
     * \return UID of this transfer syntax.
     */
    QString uid() const;

    /**
     * Returns endianess of this transfer syntax.
     * \return Transfer syntax endianess.
     */
    DcmEndianess endianess() const;

    /**
     * Returns encoding of this transfer syntax.
     * \return Transfer syntax encoding.
     */
    DcmEncoding encoding() const;

    /**
     * Return content size of this PDU item.
     * This actually returns the length of the UID of
     * this transfer syntax.
     * \return Transfer syntax PDU content size in bytes.
     */
    DcmSize contentSize() const;

    /**
     * Compare with another transfer syntax.
     * \return true if both syntaxes have same UID, endianess and encoding.
     */
    bool operator ==(const DcmTransferSyntax &transferSyntax) const;

    /**
     * Compare with another transfer syntax.
     * \return true if syntaxes have different UID, endianess, or encoding.
     */
    bool operator !=(const DcmTransferSyntax &transferSyntax) const;

    /**
     * Tells whether this transfer syntax object is valid.
     * \return true if this transfer syntax has non-empty UID.
     */
    bool isValid() const;

    /**
     * Return transfer syntax by its UID.
     * If UID is unknown, transfer syntax with explicit little endian
     * encoding will be returned.
     * \param uid Transfer syntax UID.
     * \return Transfer syntax for the UID specified.
     */
    static DcmTransferSyntax fromUid(const QString &uid);

private:

    QString m_uid;              ///< Transfer syntax UID.
    DcmEndianess m_endianess;   ///< Endianess: big or little.
    DcmEncoding m_encoding;     ///< Encoding: implicit or explicit.
};

#endif // DCMTRANSFERSYNTAX_H
