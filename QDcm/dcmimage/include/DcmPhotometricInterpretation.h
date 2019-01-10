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

#ifndef DCMPHOTOMETRICINTERPRETATION_H
#define DCMPHOTOMETRICINTERPRETATION_H

#include <QString>
#include "DcmImageApi.h"

/*! Image photometric interpretation.
 * Photometric interpretation tells how the image pixel data
 * should be interpreted in order to visualize it.
 */
class DCM_IMAGE_API DcmPhotometricInterpretation
{
public:

    /*
        Predefined photometric interpretations.
     */
    static const DcmPhotometricInterpretation Monochrome1;
    static const DcmPhotometricInterpretation Monochrome2;
    static const DcmPhotometricInterpretation PaletteColor;
    static const DcmPhotometricInterpretation RGB;
    static const DcmPhotometricInterpretation HSV;
    static const DcmPhotometricInterpretation ARGB;
    static const DcmPhotometricInterpretation CMYK;
    static const DcmPhotometricInterpretation YBRFull;
    static const DcmPhotometricInterpretation YBRFull422;
    static const DcmPhotometricInterpretation YBRPartial422;
    static const DcmPhotometricInterpretation Unknown;

    /**
     * Construct an invalid photometric interpretation.
     */
    DcmPhotometricInterpretation();

    /**
     * Construct photometric interpretation.
     * \param sign Signature string.
     */
    DcmPhotometricInterpretation(const QString &sign);

    /**
     * Copy constructor.
     * \param ph Photometric interpretation to be copied.
     */
    DcmPhotometricInterpretation(const DcmPhotometricInterpretation &ph);

    /**
     * Assignment operator.
     * \param ph Photometrix interpretation to be assigned.
     * \return This photometric interpretation.
     */
    DcmPhotometricInterpretation& operator =(const DcmPhotometricInterpretation &ph);

    /**
     * Returns photometric interpretation DICOM signature.
     * \return Signature.
     */
    QString signature() const;

    /**
     * Returns string corresponding to this photometric interpretation.
     * Actually, the same as signature.
     * \return String representation.
     */
    QString toString() const;

    /**
     * Tells whether this photometric representation is valid.
     * \return true if this photometric interpretation is valid.
     */
    bool isValid() const;

    /**
     * Tells whether this photometric interpretation corresponds to
     * grayscale images. These are 'MONOCHROME1' and 'MONOCHROME2' signatures.
     * \return true if photometric interpretation is for grayscale images.
     */
    bool isGrayscale() const;

    /**
     * Compare with another photometric interpretation.
     * \param ph Photomeric interpretation to compare with.
     * \return true if interpretations have same siganture.
     */
    bool operator ==(const DcmPhotometricInterpretation &ph) const;

    /**
     * Compare with another photometric interpretation.
     * \param ph Photomeric interpretation to compare with.
     * \return true if interpretations have different sigantures.
     */
    bool operator !=(const DcmPhotometricInterpretation &ph) const;

    /**
     * Returns photometric interpretation by its string signatrure.
     * If cannot find, unknown interpretation is returned.
     * \param sign Signatrure.
     * \return Photometric interpretation.
     */
    static DcmPhotometricInterpretation bySignature(const QString &sign);

private:

    QString m_signature;    ///< Textual signature (as in DICOM).
};

#endif // DCMPHOTOMETRICINTERPRETATION_H
