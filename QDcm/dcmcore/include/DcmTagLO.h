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

#ifndef DCMTAGLO_H
#define DCMTAGLO_H

#include "DcmCoreApi.h"
#include "DcmTagString.h"

/*! DICOM long string (LO) tag.
 *
 * LO tag, 64 symbols maximum.
 */
class DCM_CORE_API DcmTagLO: public DcmTagString
{
public:

    /**
     * Default constructor.
     */
    DcmTagLO();

    /**
     * Construct LO tag.
     * \param tagKey Tag key.
     */
    DcmTagLO(const DcmTagKey &tagKey);

    /**
     * Copy constructor.
     * \param tag Tag to be copied.
     */
    DcmTagLO(const DcmTagLO &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag.
     */
    DcmTagLO& operator =(const DcmTagLO &tag);

    /**
     * Clone this tag.
     * \return Pointer to cloned tag.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagLO();

    /**
     * Assign tag value.
     * \param v Value to be set.
     * \return This tag.
     */
    DcmTagLO& operator =(const QVariant &v);

};

#endif // DCMTAGLO_H
