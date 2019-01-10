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

#ifndef DCMTAGUI_H
#define DCMTAGUI_H

#include "DcmCoreApi.h"
#include "DcmTagString.h"

/*! DICOM Unique Identifier (UI) tag.
 *
 * The UI tag holds UI value.
 * Note: Unlike all other string tags, UI tag must be padded with zeros,
 * not with spaces to acheive even length.
 */
class DCM_CORE_API DcmTagUI: public DcmTagString
{
public:

    /**
     * Default constructor.
     */
    DcmTagUI();

    /**
     * Construct UI tag.
     * \param tagKey Tag key.
     */
    DcmTagUI(const DcmTagKey &tagKey);

    /**
     * Copy constructor.
     * \param tag Tag to be copied.
     */
    DcmTagUI(const DcmTagUI &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag.
     */
    DcmTagUI& operator =(const DcmTagUI &tag);

    /**
     * Clone this tag.
     * Pointer to this tag's clone.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagUI();

    /**
     * Assign tag value.
     * \param v Value to be assigned.
     */
    void setValue(const QVariant &v);

    /**
     * Append a value to the list of values.
     * \param v Value to be added.
     */
    void appendValue(const QVariant &v);

    /**
     * Assign tag value.
     * \param v Value to be set.
     * \return This tag.
     */
    DcmTagUI& operator =(const QVariant &v);
};

#endif // DCMTAGUI_H
