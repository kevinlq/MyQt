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

#ifndef DCMVR_H
#define DCMVR_H

#include <QString>
#include "DcmCoreApi.h"
#include "DcmTypes.h"

/*! DICOM Value Representation (VR).
 *
 * This class is used to define differebt VRs used in DICOM.
 * It provides method to track min/max of particular VR,
 * as well as convertion to string signature and vice versa.
 * Normally no instances of this class should be constructed,
 * instead a set of predefined instances for each VR type
 * have to be used.
 */
class DCM_CORE_API DcmVr
{
public:

    static const DcmVr CS;
    static const DcmVr SH;
    static const DcmVr LO;
    static const DcmVr ST;
    static const DcmVr LT;
    static const DcmVr UT;
    static const DcmVr AE;
    static const DcmVr PN;
    static const DcmVr UI;
    static const DcmVr DA;
    static const DcmVr TM;
    static const DcmVr DT;
    static const DcmVr AS;
    static const DcmVr IS;
    static const DcmVr DS;
    static const DcmVr SS;
    static const DcmVr US;
    static const DcmVr SL;
    static const DcmVr UL;
    static const DcmVr AT;
    static const DcmVr FL;
    static const DcmVr FD;
    static const DcmVr OB;
    static const DcmVr OW;
    static const DcmVr OF;
    static const DcmVr SQ;
    static const DcmVr UN;

    static const DcmVr None;
    static const DcmVr Invalid;

    /**
     * Default constructor.
     * Contructs Invalid value representation.
     */
    DcmVr();

    /**
     * Construct value representation.
     * \param key VR key.
     * \param min VR minimal size.
     * \param max VR maximal size.
     */
    DcmVr(DcmVrKey key, DcmSize min, DcmSize max);

    /**
     * Copy constructor.
     * \param vr VR to be copied.
     */
    DcmVr(const DcmVr &vr);

    /**
     * Assignment operator.
     * \param vr VR to be assigned.
     * \return This VR object.
     */
    DcmVr& operator =(const DcmVr &vr);

    /**
     * Compare with another VR.
     * Only keys are compared.
     * \param vr Another VR to compare with.
     * \return true if VRs are equal.
     */
    bool operator ==(const DcmVr &vr) const;

    /**
     * Compare with another VR.
     * Only keys are compared.
     * \param vr Another VR to compare with.
     * \return true if VRs are different.
     */
    bool operator !=(const DcmVr &vr) const;

    /**
     * Returns VR key of this VR object.
     * \return VR key.
     */
    DcmVrKey vrKey() const;

    /**
     * Returns VR minimal possible size.
     * \return VR minimal size.
     */
    DcmSize minSize() const;

    /**
     * Returns VR maximal possible size.
     * \return VR maximal size.
     */
    DcmSize maxSize() const;

    /**
     * Returns two-letters signature of this VR.
     * This signature may be used to encode the VR when
     * using explicit encoding.
     * \return Two letters signatrure.
     */
    const char *signature() const;

    /**
     * Tells whether this VR is a string-based one.
     * \return true if this VR is string based.
     */
    bool isString() const;

    /**
     * Tells whether this VR is a text.
     * Text strings normally have to be passed via character set encoder.
     * \return true is this VR is a text.
     */
    bool isText() const;

    /**
     * Tells whether this VR is a binary.
     * The Unknown (UN) VR is also considered being binary.
     * \return true if this VR is binary.
     */
    bool isBinary() const;

    /**
     * Tells whether this VR is unknown.
     * The unknown VR value cannot be presented and normally is
     * kept in raw format.
     * \return true if the VR is unknown.
     */
    bool isUnknown() const;

    /**
     * Tells whether this VR has to be padded to an even length.
     * All string based values have to be padded except UI values.
     * \return true if this VR value has to be padded.
     */
    bool isPadded() const;

    /**
     * Returns string representation of this VR object.
     * For DICOM VRs this method returns VR signature.
     * For Invalid or None VRs, 'Invalid' or 'None' is returned.
     * This method should be used only for displaying DICOM data
     * structures but never for encoding of those data.
     * \return Textual representation of this VR.
     */
    QString toString() const;

    /**
     * Returns VR object by its signature.
     * For invalid or void signature the Invalid VR is returned.
     * \param s Two-characters signature.
     * \return VR object.
     */
    static DcmVr bySignatrure(const char *s);

    /**
     * Returns VR object by its string representation.
     * String representation is basically the signature in QString
     * format.
     * \param str VR string.
     * \return VR object or Invalid VR if input string is not correct.
     */
    static DcmVr fromString(const QString &str);

private:
    DcmVrKey m_vrKey;   ///< Value Representation key.
    DcmSize m_minSize;  ///< Minimal size of the VR.
    DcmSize m_maxSize;  ///< Maximal size of the VR.
};

#endif // DCMVR_H
