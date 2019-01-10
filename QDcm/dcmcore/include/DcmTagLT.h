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

#ifndef DCMTAGLT_H
#define DCMTAGLT_H

#include "DcmCoreApi.h"
#include "DcmTagString.h"

/*! DICOM Long Text (LT) tag.
 *
 * The tag holds a text of 10240 symbols maximum.
 */
class DCM_CORE_API DcmTagLT: public DcmTagString
{
public:

    /**
     * Default constructor.
     */
    DcmTagLT();

    /**
     * Construct an LT tag.
     * \param tagKey Tag key.
     */
    DcmTagLT(const DcmTagKey &tagKey);

    /**
     * Copy constructor.
     * \param tag Tag to be copied.
     */
    DcmTagLT(const DcmTagLT &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag.
     */
    DcmTagLT& operator =(const DcmTagLT &tag);

    /**
     * Clone this tag.
     * \return Pointer to this tag's clone.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagLT();

    /**
     * Assign tag value.
     * \param v Value to be set.
     * \return This tag.
     */
    DcmTagLT& operator =(const QVariant &v);
};

#endif // DCMTAGLT_H
