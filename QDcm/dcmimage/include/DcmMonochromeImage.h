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

#ifndef DCMMONOCHROMEIMAGE_H
#define DCMMONOCHROMEIMAGE_H

#include <QImage>
#include "DcmImageApi.h"
#include "DcmImage.h"
#include "DcmImageTransferFunction.h"

/*! DICOM monochrome image.
 * Monochrome image contains only one color channel
 * and is encoded using photometric representation MONOCHROME1 or
 * MONOCHROME2
 */
class DCM_IMAGE_API DcmMonochromeImage : public DcmImage
{
public:

    /**
     * Construct monochrome image with defined dimension.
     * \param width Image width in pixels.
     * \param height Image height in pixels.
     * \param frames Number of frame in the image.
     * \param bitsAllocated Number of bits allocated per single pixel (8 or 16).
     * \param bitsStored Number of bits used to encode pixel intensiti
     *      (less or equal to the number of allocated bits).
     * \param highBit High bit number.
     * \param pi Photometric interpretation Monochrome1 or Monochrome2 (if other is given
     *      the image is constructed as invalid).
     */
    DcmMonochromeImage(int width,
                       int height,
                       int frames = 1,
                       int bitsAllocated = 16,
                       int bitsStored = 16,
                       int highBit = 15,
                       const DcmPhotometricInterpretation &pi = DcmPhotometricInterpretation::Monochrome2);

    /**
     * Construct monochromatic image from DICOM dataset.
     * \param dataset A vaid DICOM dataset.
     */
    DcmMonochromeImage(DcmDataset &dataset);

    /**
     * Copy ocnstructor.
     * \param monoImage Image to be copied.
     */
    DcmMonochromeImage(const DcmMonochromeImage &monoImage);

    /**
     * Assignment operator.
     * \param monoImage Image to be assigned.
     * \return Reference to this image object.
     */
    DcmMonochromeImage& operator =(const DcmMonochromeImage &monoImage);

    /**
     * Destructor.
     */
    ~DcmMonochromeImage();

    /**
     * Tell whether this image is valid.
     * Additional to the checks performed by image base class, this method
     * also checks image phototetric representation to be Monochrome1 or Monochrome2.
     * \return true if image is valid.
     */
    bool isValid() const;

    /**
     * Returns raw pixel value at given position.
     * This method does not perform any correcting of the pixel value according
     * to clase/offset not to the photometric interpretation.
     * \param x Pixel x coordinate.
     * \param y Pixel y coordinate.
     * \param frame Frame number.
     * \return Pixel raw value.
     */
    DcmUnsignedShort rawPixel(int x, int y, int frame = 0) const;

    /**
     * Returns rescaled pixel value as defined by rescale DICOM tags.
     * \param x Pixel x coordinate.
     * \param y Pixel y coordinate.
     * \param frame Frame number.
     * \return Rescaled pixel value.
     */
    double rescaledPixel(int x, int y, int frame = 0) const;

    /**
     * Assign raw pixel value at given position.
     * \param p Pixel value to be assigned.
     * \param x Pixel x coordinate.
     * \param y Pixel y coordinate.
     * \param frame Frame number.
     */
    void setRawPixel(DcmUnsignedShort p, int x, int y, int frame = 0);

    /**
     * Assign rescaled pixel value. The pixel value must be provided
     * using rescale type units as specified by corresponding DICOM tag.
     * The given value will be rescaled back to pixel raw value.
     * Resulted pixel value will be clipped respecting the raw data type.
     * \param p Rescaled pixel value to be set.
     * \param x Pixel x coordinate.
     * \param y Pixel y coordinate.
     * \param frame Frame number.
     */
    void setRescaledPixel(double p, int x, int y, int frame = 0);

    /**
     * Convert this image to a QImage using specified transfer function.
     * \param tf Transfer function to be used in convertion.
     * \return Cobverted QImage.
     */
    QImage toQImage(const DcmImageTransferFunction &tf, int frame = 0) const;

    /**
     * Convert generic DICOM image to monochromatic image.
     * This method does not perform pixels convertion. It just reinterprets
     * the image as being monochromatic. The photometric interpretation of the
     * input image must be Grayscale. In other case a null pointer is returned
     * by this method.
     * This method makes a deep copy on an image. The original image can be
     * safely deleted afterwards.
     * \param imagePtr Pointer to an image to be converted.
     * \return Pointer to a newly allocated monochromatic image or null if unable to convert.
     */
    static DcmMonochromeImage *fromDcmImage(DcmImage *imagePtr);

};

#endif // DCMMONOCHROMEIMAGE_H
