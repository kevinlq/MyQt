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

#ifndef DCMTAGSQ_H
#define DCMTAGSQ_H

#include "DcmCoreApi.h"
#include "DcmTag.h"
#include "DcmTagList.h"
#include "DcmTagItem.h"

/*! DICOM sequence (SQ) tag.
 *
 * Sequence tag is a list of items.
 */
class DCM_CORE_API DcmTagSQ : public DcmTag
{
public:

    /**
     * Default constructor.
     */
    DcmTagSQ();

    /**
     * Construct sequence tag.
     * \param tagKey Tag key of the constructed sequence tag.
     */
    DcmTagSQ(const DcmTagKey &tagKey);

    /**
     * Copy constructor.
     * \param tagSq Tag to be copied.
     */
    DcmTagSQ(const DcmTagSQ &tagSq);

    /**
     * Assignment operator.
     * \param tagSq Sequence tag to be assigned.
     * \return This sequence tag.
     */
    DcmTagSQ& operator =(const DcmTagSQ &tagSq);

    /**
     * Clone this tag.
     * \return Pointer to a cloned tag.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagSQ();

    /**
     * Returns this tag content raw size in bytes.
     * \param transferSyntax Transfer syntax to be used when estimating size.
     * \return Content size in bytes.
     */
    DcmSize contentSize(const DcmTransferSyntax &transferSyntax) const;

    /**
     * Returns this tag raw size in bytes.
     * \param transferSyntax Transfer syntax to be used when estimating size.
     * \return Tag size in bytes.
     */
    DcmSize size(const DcmTransferSyntax &transferSyntax) const;

    /**
     * Returns reference to the list of items stored in this sequence.
     * \return Items list.
     */
    DcmTagList& items();

    /**
     * Insert item to this sequence.
     * \param item Items to be inserted.
     */
    void insert(const DcmTagItem &item);

    /**
     * Insert and retain the item.
     * \param itemPtr Pointer to an item to be inserted.
     */
    void insertAndRetain(DcmTagItem *itemPtr);

private:

    DcmTagList m_items; ///< List of sequence items.

};

#endif // DCMTAGSQ_H
