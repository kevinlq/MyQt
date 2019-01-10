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

#ifndef DCMTAGSH_H
#define DCMTAGSH_H

#include "DcmCoreApi.h"
#include "DcmTagString.h"

/*! DICOM short string tag.
 *
 * This class represents short string tag (16 symbols maximum).
 */
class DCM_CORE_API DcmTagSH: public DcmTagString
{
public:

    /**
     * Default constructor.
     */
    DcmTagSH();

    /**
     * Construct SH tag.
     * \param tagKey Tag key.
     */
    DcmTagSH(const DcmTagKey &tagKey);

    /**
     * Copy constrcutor.
     * \param tag Tag to be copied.
     */
    DcmTagSH(const DcmTagSH &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag.
     */
    DcmTagSH& operator =(const DcmTagSH &tag);

    /**
     * Clone this tag.
     * \return Cloned tag.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagSH();

    /**
     * Assign tag value.
     * \param v Value to be set.
     * \return This tag.
     */
    DcmTagSH& operator =(const QVariant &v);
};

#endif // DCMTAGSH_H
