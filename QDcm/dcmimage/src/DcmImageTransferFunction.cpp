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

#include "DcmImageTransferFunction.h"

DcmImageTransferFunction::DcmImageTransferFunction()
    : m_referencePoints()
{
}

DcmImageTransferFunction::DcmImageTransferFunction(const DcmImageTransferFunction &tf)
    : m_referencePoints(tf.m_referencePoints)
{
}

DcmImageTransferFunction& DcmImageTransferFunction::operator =(const DcmImageTransferFunction &tf)
{
    if (this != &tf) {
        m_referencePoints = tf.m_referencePoints;
    }
    return *this;
}

void DcmImageTransferFunction::addReferencePoint(double pixelValue, const QColor &color)
{
    DcmImageTransferFunction::ReferencePoint refPoint;
    refPoint.pixelValue = pixelValue;
    refPoint.color = color;
    addReferencePoint(refPoint);
}

void DcmImageTransferFunction::addReferencePoint(const ReferencePoint &refPoint)
{
    if (m_referencePoints.count() == 0) {
        m_referencePoints.append(refPoint);
    } else {
        for (int i = 0; i < m_referencePoints.count(); i++) {
            if (m_referencePoints.at(i).pixelValue > refPoint.pixelValue) {
                m_referencePoints.insert(i, refPoint);
                return;
            }
        }
        m_referencePoints.append(refPoint);
    }
}

int DcmImageTransferFunction::numberOfReferencePoints() const
{
    return m_referencePoints.count();
}

DcmImageTransferFunction::ReferencePoint DcmImageTransferFunction::referencePointAt(int index) const
{
    return m_referencePoints.at(index);
}

void DcmImageTransferFunction::setReferencePoint(int index, const QColor &color)
{
    ReferencePoint rp;
    rp.pixelValue = m_referencePoints.at(index).pixelValue;
    rp.color = color;
    m_referencePoints.replace(index, rp);
}

QColor DcmImageTransferFunction::colorForPixelValue(double value) const
{
    QColor color(0, 0, 0);
    if (m_referencePoints.count() < 2) {
        return color;
    }

    if (value <= m_referencePoints.first().pixelValue) {
        return m_referencePoints.first().color;
    }

    if (value >= m_referencePoints.last().pixelValue) {
        return m_referencePoints.last().color;
    }

    int i = 0;
    while (m_referencePoints.at(i).pixelValue < value) {
        i++;
    }

    if (i == 0) {
        return m_referencePoints.at(0).color;
    }

    ReferencePoint rpA = m_referencePoints.at(i - 1);
    ReferencePoint rpB = m_referencePoints.at(i);

    double length = rpB.pixelValue - rpA.pixelValue;
    Q_ASSERT(length > 0.0);

    if (length <= 0.0) {
        return color;
    }

    return DcmImageTransferFunction::intermediateColor(rpA.color, rpB.color, (value - rpA.pixelValue) / length);
}

QColor DcmImageTransferFunction::intermediateColor(const QColor &colorA, const QColor &colorB, double fraction)
{
    if (fraction <= 0.0) {
        return colorA;
    }
    if (fraction >= 1.0) {
        return colorB;
    }

    return QColor((colorA.red() + colorB.red()) * fraction,
                  (colorA.green() + colorB.green()) * fraction,
                  (colorA.blue() + colorB.blue()) * fraction);
}
