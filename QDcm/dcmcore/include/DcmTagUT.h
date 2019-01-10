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

#ifndef DCMTAGUT_H
#define DCMTAGUT_H

#include "DcmCoreApi.h"
#include "DcmTagString.h"

/*! DICOM Unlimited Text (UT) tag.
 *
 * This tag holds a text of an unlimited length.
 */
class DCM_CORE_API DcmTagUT: public DcmTagString
{
public:

    /**
     * Default constructor.
     */
    DcmTagUT();

    /**
     * Construct an UT tag.
     * \param tagKey Tag key.
     */
    DcmTagUT(const DcmTagKey &tagKey);

    /**
     * Copy constructor.
     * \param tag Tag to be copied.
     */
    DcmTagUT(const DcmTagUT &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag.
     */
    DcmTagUT& operator =(const DcmTagUT &tag);

    /**
     * Clone this tag.
     * \return Pointer to this tag's clone.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagUT();

    /**
     * Assign tag value.
     * \param v Value to be set.
     * \return This tag.
     */
    DcmTagUT& operator =(const QVariant &v);

    /**
     * Returns tag size.
     * \param transferSyntax Transfer syntax used to encode the tag.
     * \return Tag size in bytes.
     */
    DcmSize size(const DcmTransferSyntax &transferSyntax) const;
};

#endif // DCMTAGUT_H
