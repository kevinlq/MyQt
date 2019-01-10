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

#ifndef DCMIMAGETRANSFERFUNCTION_H
#define DCMIMAGETRANSFERFUNCTION_H

#include <QColor>
#include <QList>
#include "DcmImageApi.h"

/*! Transfer function class.
 * Transfer function class allows converting from DICOM image
 * pixel value to Qt color.
 * Transfer function is defined by a set of reference points that
 * map pixel value to a color. Given values are then interpolated
 * between the reference points.
 */
class DCM_IMAGE_API DcmImageTransferFunction
{
public:

    /*! Reference point that maps pixel value to a color.
     */
    typedef struct {
        double pixelValue;  ///< Pixel value.
        QColor color;       ///< Color.
    } ReferencePoint;

    /**
     * Construct a transfer function.
     */
    DcmImageTransferFunction();

    /**
     * Copy constructor.
     * \param tf Transfer function to be copied.
     */
    DcmImageTransferFunction(const DcmImageTransferFunction &tf);

    /**
     * Assignment operator.
     * \param tf Transfer function to be assigned.
     * \return Reference to this transfer function object.
     */
    DcmImageTransferFunction& operator =(const DcmImageTransferFunction &tf);

    /**
     * Add a reference point.
     * \param pixelValue Pixel value.
     * \param color Color associated with given value.
     */
    void addReferencePoint(double pixelValue, const QColor &color);

    /**
     * Add reference point.
     * \param refPoint Reference point to be added.
     */
    void addReferencePoint(const ReferencePoint &refPoint);

    /**
     * Returns a number of reference points in this transfer function.
     * \return Number of reference points.
     */
    int numberOfReferencePoints() const;

    /**
     * Returns reference point at given index position.
     * \param index reference point position.
     * \return Reference point.
     */
    ReferencePoint referencePointAt(int index) const;

    /**
     * Assign a reference point at given position.
     * \param index Reference point posititon.
     * \param color Reference point color to be assigned.
     */
    void setReferencePoint(int index, const QColor &color);

    /**
     * Returns interpolated color for given pixel value.
     * \param value Pixel value.
     * \return Interpolated color.
     */
    QColor colorForPixelValue(double value) const;

private:

    /**
     * Calculate intermediate color between given two colors.
     * The fraction value must be in a 0 .. 1 range. If not,
     * first or second color will be returned depending on which
     * end of the 0 .. 1 range the fraction is.
     * \param colorA First color.
     * \param colorB Second color.
     * \param fraction Fraction value between 0.0 and 1.0.
     * \return Intermediate color.
     */
    static QColor intermediateColor(const QColor &colorA, const QColor &colorB, double fraction);

    QList<ReferencePoint> m_referencePoints;    ///< List of reference points.
};

#endif // DCMIMAGETRANSFERFUNCTION_H
