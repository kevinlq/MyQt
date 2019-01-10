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

#ifndef DCMTAGUL_H
#define DCMTAGUL_H

#include "DcmCoreApi.h"
#include "DcmTag.h"

/*! DICOM Unsigned Long (UL) tag.
 *
 * Unsigned binary integer 32 bits long.
 */
class DCM_CORE_API DcmTagUL: public DcmTag
{
public:

    /**
     * Default constructor.
     */
    DcmTagUL();

    /**
     * Construct UL tag.
     * \param tagKey Tag key.
     */
    DcmTagUL(const DcmTagKey &tagKey);

    /**
     * Copy constructor.
     * \param tag Tag to be copied.
     */
    DcmTagUL(const DcmTagUL &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag.
     */
    DcmTagUL& operator =(const DcmTagUL &tag);

    /**
     * Clone this tag.
     * \return Pointer to this tag's clone.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagUL();

    /**
     * Returns tag's value.
     * \return Tag's value.
     */
    QVariant value() const;

    /**
     * Returns tag's values.
     * \return Tag's values.
     */
    QVariantList values() const;

    /**
     * Assign tag value.
     * This method takes unsigned integer value.
     * \param v Value to be assigned.
     */
    void setValue(const QVariant &v);

    /**
     * Append value.
     * This method takes unsigned integer value.
     * \param v Value to be added.
     */
    void appendValue(const QVariant &v);

    /**
     * Assign tag value.
     * \param v Value to be set.
     * \return This tag.
     */
    DcmTagUL& operator =(const QVariant &v);

    /**
     * Returns multiplicity of this tag.
     * \return Tag's multiplicity.
     */
    int multiplicity() const;

    /**
     * Returns tag value as unsigned long.
     * If tag is empty, zero is returned.
     * \return Tag's value.
     */
    DcmUnsignedLong asUnsignedLong() const;

    /**
     * Returns list of tag's values.
     * \return List of tag's values.
     */
    QList<DcmUnsignedLong> asUnsignedLongList() const;

    /**
     * Assign tag value.
     * \param v Value to be assigned.
     */
    void setUnsignedLong(DcmUnsignedLong v);

    /**
     * Append tag's value.
     * \param v Value to be added.
     */
    void appendUnsignedLong(DcmUnsignedLong v);

    /**
     * Returns tag's raw content size in bytes.
     * This will return 4 * multiplicity (UL tag single value takes 4 bytes).
     * \param transferSyntax Transfer syntax to encode the tag.
     * \return Content raw size in bytes.
     */
    DcmSize contentSize(const DcmTransferSyntax &transferSyntax) const;

private:

    QList<DcmUnsignedLong> m_values;    ///< List of values.
};

#endif // DCMTAGUL_H
