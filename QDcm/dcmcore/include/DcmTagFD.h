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

#ifndef DCMTAGFD_H
#define DCMTAGFD_H

#include "DcmCoreApi.h"
#include "DcmTag.h"

/*! DICOM Floating Double Precision (FD) tag.
 *
 * Double precision (64-bits) floating point numbers.
 */
class DCM_CORE_API DcmTagFD: public DcmTag
{
public:

    /**
     * Default constructor.
     */
    DcmTagFD();

    /**
     * Construct FD tag.
     * \param tagKey Tag key.
     */
    DcmTagFD(const DcmTagKey &tagKey);

    /**
     * Copy constructor.
     * \param tag Tag to be copied.
     */
    DcmTagFD(const DcmTagFD &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag.
     */
    DcmTagFD& operator =(const DcmTagFD &tag);

    /**
     * Clone this tag.
     * \return Pointer to this tag's clone.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagFD();

    /**
     * Returns tag's frist value.
     * \return Tag's value.
     */
    QVariant value() const;

    /**
     * Returns tag's values.
     * \return List of tag's values.
     */
    QVariantList values() const;

    /**
     * Assign tag's value.
     * \param v Value to be assigned.
     */
    void setValue(const QVariant &v);

    /**
     * Append value to the list of tag's values.
     * \param v Values to be added.
     */
    void appendValue(const QVariant &v);

    /**
     * Assign value.
     * \param v Value to be set.
     * \return This tag.
     */
    DcmTagFD& operator =(const QVariant &v);

    /**
     * Returns tag's multiplicity.
     * \return Tag's multiplicity.
     */
    int multiplicity() const;

    /**
     * Returns tag value as double.
     * \return Tag's value.
     */
    DcmDouble asDouble() const;

    /**
     * Returns list of tag's double values.
     * \return Tag's values list.
     */
    QList<DcmDouble> asDoubleList() const;

    /**
     * Assign tag's value.
     * \param v Value to be set.
     */
    void setDouble(DcmDouble v);

    /**
     * Append value to the tag's values list.
     * \param v Value to be added.
     */
    void appendDouble(DcmDouble v);

    /**
     * Returns tag raw content size in bytes.
     * This will return 8 * multiplicity (single value takes 8 bytes).
     * \param transferSyntax Transfer syntax to encode the tag.
     * \return Content size in bytes.
     */
    DcmSize contentSize(const DcmTransferSyntax &transferSyntax) const;

private:

    QList<DcmDouble> m_values;  ///< List of values.
};

#endif // DCMTAGFD_H
