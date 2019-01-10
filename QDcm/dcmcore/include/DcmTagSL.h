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

#ifndef DCMTAGSL_H
#define DCMTAGSL_H

#include "DcmCoreApi.h"
#include "DcmTag.h"

/*! DICOM Signed Long (SL) tag.
 *
 * Signed binary integer 32 bits long.
 */
class DCM_CORE_API DcmTagSL: public DcmTag
{
public:

    /**
     * Default constructor.
     */
    DcmTagSL();

    /**
     * Construct UL tag.
     * \param tagKey tag key.
     */
    DcmTagSL(const DcmTagKey &tagKey);

    /**
     * Copy constructor.
     * \param tag Tag to be copied.
     */
    DcmTagSL(const DcmTagSL &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag.
     */
    DcmTagSL& operator =(const DcmTagSL &tag);

    /**
     * Clone this tag.
     * \return Pointer to this tag's clone.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagSL();

    /**
     * Return tag's first value.
     * \return Tag's value.
     */
    QVariant value() const;

    /**
     * Return tag's values.
     * \return Tag's values.
     */
    QVariantList values() const;

    /**
     * Assign tag value.
     * \param v Value to be assigned.
     */
    void setValue(const QVariant &v);

    /**
     * Append tag value.
     * \param v Value to be added.
     */
    void appendValue(const QVariant &v);

    /**
     * Assign tag value.
     * \param v Value to be set.
     * \return This tag.
     */
    DcmTagSL& operator =(const QVariant &v);

    /**
     * Returns multiplicity of this tag's value.
     * \return Tag's value multiplicity.
     */
    int multiplicity() const;

    /**
     * Returns tag's value as signed long.
     * \return Tag's value.
     */
    DcmSignedLong asSignedLong() const;

    /**
     * Returns list of tag's values.
     * \return Tag's values.
     */
    QList<DcmSignedLong> asSignedLongList() const;

    /**
     * Assign tag's value.
     * \param v Value to be assigned.
     */
    void setSignedLong(DcmSignedLong v);

    /**
     * Append tag's value.
     * \param v Value to be added.
     */
    void appendSignedLong(DcmSignedLong v);

    /**
     * Returns tag's content size in bytes.
     * This will return 4 * multiplicity (SL tag single value takes 4 bytes).
     * \param transferSyntax Transfer syntax to encode the tag.
     * \return Content size in bytes.
     */
    DcmSize contentSize(const DcmTransferSyntax &transferSyntax) const;

private:

    QList<DcmSignedLong> m_values;  ///< List of values.
};

#endif // DCMTAGSL_H
