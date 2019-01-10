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

#ifndef DCMTAGFL_H
#define DCMTAGFL_H

#include "DcmCoreApi.h"
#include "DcmTag.h"

/*! DICOM Floating Point (FL) tag.
 *
 * Single precision (32 bits) floating point number.
 */
class DCM_CORE_API DcmTagFL: public DcmTag
{
public:

    /**
     * Default constructor.
     */
    DcmTagFL();

    /**
     * Construct FL tag.
     * \param tagKey Tag key.
     */
    DcmTagFL(const DcmTagKey &tagKey);

    /**
     * Copy constructor.
     * \param tag Tag to be copied.
     */
    DcmTagFL(const DcmTagFL &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag.
     */
    DcmTagFL& operator =(const DcmTagFL &tag);

    /**
     * Clone this tag.
     * \return Clone of this tag.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagFL();

    /**
     * Return tag's first value.
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
     * Append tag's value.
     * \param v Value to be added.
     */
    void appendValue(const QVariant &v);

    /**
     * Assign tag value.
     * \param v Value to be set.
     * \return This tag.
     */
    DcmTagFL& operator =(const QVariant &v);

    /**
     * Returns tag's multiplicity.
     * \return Tag's multiplicity.
     */
    int multiplicity() const;

    /**
     * Returns tag's value as float.
     * \return Tag value.
     */
    DcmFloat asFloat() const;

    /**
     * Returns tag's values as list of floats.
     * \return List of tag's values.
     */
    QList<DcmFloat> asFloatList() const;

    /**
     * Assign tag's value.
     * \param v Value to be assigned.
     */
    void setFloat(DcmFloat v);

    /**
     * Append value to the list of tag's values.
     * \param v Value to be added.
     */
    void appendFloat(DcmFloat v);

    /**
     * Returns tag's raw content size in bytes.
     * This will return 4 * multiplicity (FL tag single value takes 4 bytes).
     * \param transferSyntax Transfer syntax to encode the tag.
     * \return Content size in bytes.
     */
    DcmSize contentSize(const DcmTransferSyntax &transferSyntax) const;

private:

    QList<DcmFloat> m_values;   ///< List of values.
};

#endif // DCMTAGFL_H
