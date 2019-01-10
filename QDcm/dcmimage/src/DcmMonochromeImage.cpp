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

#include "DcmTagPixelData.h"
#include "DcmMonochromeImage.h"

DcmMonochromeImage::DcmMonochromeImage(int width,
                                       int height,
                                       int frames,
                                       int bitsAllocated,
                                       int bitsStored,
                                       int highBit,
                                       const DcmPhotometricInterpretation &pi)
    : DcmImage(width, height, frames, bitsAllocated, bitsStored, highBit, 1 /* samples per pixel */, pi)
{
}

DcmMonochromeImage::DcmMonochromeImage(DcmDataset &dataset)
    : DcmImage(dataset)
{
}

DcmMonochromeImage::DcmMonochromeImage(const DcmMonochromeImage &monoImage)
    : DcmImage(monoImage)
{
}

DcmMonochromeImage& DcmMonochromeImage::operator =(const DcmMonochromeImage &monoImage)
{
    if (this != &monoImage) {
        DcmImage::operator =(monoImage);
    }
    return *this;
}

DcmMonochromeImage::~DcmMonochromeImage()
{
}

bool DcmMonochromeImage::isValid() const
{
    if (!DcmImage::isValid()) {
        return false;
    }

    // Check photometric interpretation
    DcmPhotometricInterpretation pi = photometricInterpretation();
    return (pi == DcmPhotometricInterpretation::Monochrome1) || (pi == DcmPhotometricInterpretation::Monochrome2);
}

DcmUnsignedShort DcmMonochromeImage::rawPixel(int x, int y, int frame) const
{
    Q_ASSERT(x >= 0 && x < width());
    Q_ASSERT(y >= 0 && y < height());
    Q_ASSERT(frame >= 0 && frame < frames());
    Q_ASSERT(isValid());

    DcmTagPixelData *tagPixelDataPtr = tagPixelData();
    Q_ASSERT(tagPixelDataPtr);

    quint32 idx = pixelByteArrayIndex(x, y, frame);
    const char *rawBytePtr = &(tagPixelDataPtr->constData()[idx]);

    DcmUnsignedShort pixel = 0;

    if (bitsAllocated() > 8) {
        // One 16-bits word per pixel
        pixel = *((const DcmUnsignedShort*)rawBytePtr);
    } else {
        // One byte per pixel
        pixel = (DcmUnsignedShort)*((const unsigned char*)rawBytePtr);
    }

    return pixel;
}

double DcmMonochromeImage::rescaledPixel(int x, int y, int frame) const
{
    DcmUnsignedShort rawValue = rawPixel(x, y, frame);
    double slope = rescaleSlope();
    double offset = rescaleIntercept();

    return ((double)rawValue) * slope + offset;
}

void DcmMonochromeImage::setRawPixel(DcmUnsignedShort p, int x, int y, int frame)
{
    Q_ASSERT(x >= 0 && x < width());
    Q_ASSERT(y >= 0 && y < height());
    Q_ASSERT(frame >= 0 && frame < frames());
    Q_ASSERT(isValid());

    DcmTagPixelData *tagPixelDataPtr = tagPixelData();
    Q_ASSERT(tagPixelDataPtr);

    quint32 idx = pixelByteArrayIndex(x, y, frame);
    char *rawBytePtr = &(tagPixelDataPtr->data().data()[idx]);

    if (bitsAllocated() > 8) {
        DcmUnsignedShort *usPtr = (DcmUnsignedShort*)rawBytePtr;
        *usPtr = p;
    } else {
        // One byte per pixel
        DcmUnsignedByte *ubPtr = (DcmUnsignedByte*)rawBytePtr;
        if (p > 0x00FF) {
            *ubPtr = 0xFF;
        } else {
            *ubPtr = p & 0x00FF;
        }
    }
}

void DcmMonochromeImage::setRescaledPixel(double p, int x, int y, int frame)
{
    double slope = rescaleSlope();
    double offset = rescaleIntercept();
    DcmUnsignedShort rawValue = (DcmUnsignedShort)((p - offset) / slope);
    setRawPixel(rawValue, x, y, frame);
}

QImage DcmMonochromeImage::toQImage(const DcmImageTransferFunction &tf, int frame) const
{
    QImage qImage(width(), height(), QImage::Format_ARGB32);

    double slope = rescaleSlope();
    double offset = rescaleIntercept();

    DcmTagPixelData *tagPixelDataPtr = tagPixelData();
    Q_ASSERT(tagPixelDataPtr);

    const DcmUnsignedByte *rawBytePtr = (const DcmUnsignedByte*) tagPixelDataPtr->constData();
    const DcmUnsignedShort *rawShortPtr = (DcmUnsignedShort*)rawBytePtr;

    int idx = frame * width() * height();

    int colorTableSize = bitsAllocated() > 8 ? 65536 : 256;

    QColor *colorTable = new QColor[colorTableSize];
    for (int v = 0; v < colorTableSize; v++) {
        colorTable[v] = tf.colorForPixelValue(((double)v) * slope + offset);
    }

    // Somehow optimized, but still rather slow

    if (bitsAllocated() > 8) {
        for (int y = 0; y < height(); y++) {
            QRgb *scanLine = (QRgb*)qImage.scanLine(y);
            for (int x = 0; x < width(); x++) {
                DcmUnsignedShort raw = rawShortPtr[idx++];
                scanLine[x] = colorTable[raw].rgba();
            }
        }
    } else {
        for (int y = 0; y < height(); y++) {
            QRgb *scanLine = (QRgb*)qImage.scanLine(y);
            for (int x = 0; x < width(); x++) {
                DcmUnsignedShort raw = rawBytePtr[idx++];
                scanLine[x] = colorTable[raw].rgba();
            }
        }
    }

    delete[] colorTable;

    return qImage;
}

DcmMonochromeImage* DcmMonochromeImage::fromDcmImage(DcmImage *imagePtr)
{
    Q_ASSERT(imagePtr);
    if (!imagePtr) {
        return 0;
    }

    DcmPhotometricInterpretation phi = imagePtr->photometricInterpretation();
    if (!phi.isGrayscale()) {
        return 0;   // Not a monochrome image
    }

    DcmMonochromeImage *monoImage = new DcmMonochromeImage(imagePtr->dataset());
    return monoImage;
}
