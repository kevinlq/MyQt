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

#include <QDebug>
#include "DcmTagPixelData.h"
#include "DcmTagDS.h"
#include "DcmImage.h"

DcmImage::DcmImage(int width,
                   int height,
                   int frames,
                   int bitsAllocated,
                   int bitsStored,
                   int highBit,
                   int samplesPerPixel,
                   const DcmPhotometricInterpretation &pi)
    : m_dataset()
{
    Q_ASSERT(width > 0);
    Q_ASSERT(height > 0);
    Q_ASSERT(frames > 0);
    Q_ASSERT((bitsAllocated == 8)
             || (bitsAllocated == 16)
             || (bitsAllocated == 32));
    Q_ASSERT((bitsStored > 0)
             &&(bitsStored <= bitsAllocated));
    Q_ASSERT(highBit < bitsAllocated);
    Q_ASSERT(bitsStored <= highBit + 1);
    Q_ASSERT(samplesPerPixel > 0);

    m_dataset.setTagValue("Columns", width);
    m_dataset.setTagValue("Rows", height);
    m_dataset.setTagValue("Frames", frames);
    m_dataset.setTagValue("BitsAllocated", bitsAllocated);
    m_dataset.setTagValue("BitsStored", bitsStored);
    m_dataset.setTagValue("HighBit", highBit);
    m_dataset.setTagValue("SamplesPerPixel", samplesPerPixel);
    m_dataset.setTagValue("PhotometricInterpretation", pi.toString());

    allocatePixelData();

    m_tagPixelDataPtr = dynamic_cast<DcmTagPixelData*>(m_dataset.findTag(DcmTagKey::PixelData));
}

DcmImage::DcmImage(DcmDataset &dataset)
{
    m_dataset = dataset;
    DcmTag *tagPtr = m_dataset.findTag(DcmTagKey::PixelData);
    if (tagPtr) {
        m_tagPixelDataPtr = dynamic_cast<DcmTagPixelData*>(tagPtr);
    } else {
        // The dataset does not contain pixel data
        m_tagPixelDataPtr = 0;
    }
}

DcmImage::DcmImage(const DcmImage &image)
{
    m_dataset = image.m_dataset;
}

DcmImage& DcmImage::operator =(const DcmImage &image)
{
    if (this != &image) {
        m_dataset = image.m_dataset;
    }
    return *this;
}

DcmImage::~DcmImage()
{
}

int DcmImage::width() const
{
    return m_dataset.tagValue("Columns").toInt();
}

int DcmImage::height() const
{
    return m_dataset.tagValue("Rows").toInt();
}

int DcmImage::frames() const
{
    QVariant v = m_dataset.tagValue("Frames");
    if (v.isValid()) {
        return v.toInt();
    }
    return 1;
}

int DcmImage::bitsAllocated() const
{
    return m_dataset.tagValue("BitsAllocated").toInt();
}

int DcmImage::bitsStored() const
{
    return m_dataset.tagValue("BitsStored").toInt();
}

int DcmImage::highBit() const
{
    return m_dataset.tagValue("HighBit").toInt();
}

int DcmImage::samplesPerPixel() const
{
    return m_dataset.tagValue("SamplesPerPixel").toInt();
}

DcmPhotometricInterpretation DcmImage::photometricInterpretation() const
{
    return DcmPhotometricInterpretation::bySignature(m_dataset.tagValue("PhotometricInterpretation").toString());
}

double DcmImage::rescaleIntercept() const
{
    QVariant v = m_dataset.tagValue("RescaleIntercept");
    if (v.isValid()) {
        bool ok = true;
        double d = v.toDouble(&ok);
        if (ok) {
            return d;
        }
    }

    return 0.0;
}

void DcmImage::setRescaleIntercept(double ri)
{
    m_dataset.setTagValue("RescaleIntercept", QVariant(ri));
}

double DcmImage::rescaleSlope() const
{
    QVariant v = m_dataset.tagValue("RescaleSlope");
    if (v.isValid()) {
        bool ok = true;
        double d = v.toDouble(&ok);
        if (ok) {
            return d;
        }
    }

    return 1.0;
}

void DcmImage::setRescaleSlope(double rs)
{
    m_dataset.setTagValue("RescaleSlope", QVariant(rs));
}

double DcmImage::windowCenter() const
{
    DcmTag *tag = m_dataset.findTag("WindowCenter");
    if (tag) {
        DcmTagDS *tagDS = dynamic_cast<DcmTagDS *>(tag);
        if (tagDS) {
            return tagDS->asDouble();
        }
    }

    return ((double)(1 << bitsStored())) / 2;
}

void DcmImage::setWindowCenter(double c)
{
    m_dataset.setTagValue("WindowCenter", QVariant(c));
}

double DcmImage::windowWidth() const
{
    DcmTag *tag = m_dataset.findTag("WindowWidth");
    if (tag) {
        DcmTagDS *tagDS = dynamic_cast<DcmTagDS *>(tag);
        if (tagDS) {
            return tagDS->asDouble();
        }
    }

    return (double)(1 << bitsStored());
}

QString DcmImage::rescaleTypeString() const
{
    return m_dataset.tagValue("RescaleType").toString().trimmed();
}

void DcmImage::setRescaleTypeString(const QString &rt)
{
    m_dataset.setTagValue("RescaleType", QVariant(rt.trimmed()));
}

DcmDataset& DcmImage::dataset()
{
    return m_dataset;
}

DcmTagPixelData* DcmImage::tagPixelData() const
{
    return m_tagPixelDataPtr;
}

bool DcmImage::isValid() const
{
    // Check we have a pixel data present
    if (!m_tagPixelDataPtr) {
        return false;
    }

    // Check raw pixel data size is correct
    DcmSize size = width() * height() * frames() * bitsAllocated() * samplesPerPixel() / 8;
    if (size & 1) {
        size += 1;  // Correct for even size
    }

    // Check pixel data size for native (not compressed) image
    if (m_tagPixelDataPtr->isNative()) {
        // Transfer syntax does not affect pixel data tag content size (as it is a binary tag).
        if (size != m_tagPixelDataPtr->contentSize(DcmTransferSyntax::ImplicitLittleEndian)) {
            return false;
        }
    }

    return true;
}

quint32 DcmImage::pixelByteArrayIndex(int x, int y, int frame) const
{
    quint32 adj = bitsAllocated() * samplesPerPixel() / 8;
    quint32 idx = (x + y * width()) * adj;

    idx += frame * width() * height() * adj;
    return idx;
}

void DcmImage::allocatePixelData()
{
    int bytesToAllocate = width() * height() * frames() * bitsAllocated() * samplesPerPixel() / 8;
    QByteArray ba = QByteArray(bytesToAllocate, 0);
    // We always allocate pixel data as OW value representation.
    DcmTagPixelData tagPixelData(DcmTagPixelData::Format_Native, DcmVr::OW);
    tagPixelData.setByteArray(ba);
    m_dataset.insert(tagPixelData);
}
