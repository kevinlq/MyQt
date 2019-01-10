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

#ifndef DCMTAGAS_H
#define DCMTAGAS_H

#include "DcmCoreApi.h"
#include "DcmTagString.h"

/*! DICOM Age String (AS) tag.
 *
 * A string of characters to represent an age.
 * It contains of three-digits number followed
 * by D, W, M, or Y symbol.
 */
class DCM_CORE_API DcmTagAS: public DcmTagString
{
public:

    /**
     * Default constructor.
     */
    DcmTagAS();

    /**
     * Construct AS tag.
     * \param tagKey Tag key.
     */
    DcmTagAS(const DcmTagKey &tagKey);

    /**
     * Copy constructor.
     * \param tag Tag to be copied.
     */
    DcmTagAS(const DcmTagAS &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag.
     */
    DcmTagAS& operator =(const DcmTagAS &tag);

    /**
     * Clone this tag.
     * \return Pointer to this tag's clone.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagAS();

    /**
     * Assign tag's value.
     * \param v Value to be assigned.
     */
    void setValue(const QVariant &v);

    /**
     * Append value to the list of values.
     * \param v Value to be added.
     */
    void appendValue(const QVariant &v);

    /**
     * Assign value.
     * \param v Value to be set.
     * \return This tag.
     */
    DcmTagAS& operator =(const QVariant &v);
};

#endif // DCMTAGAS_H
