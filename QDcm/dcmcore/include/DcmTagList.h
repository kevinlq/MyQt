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

#ifndef DCMTAGLIST_H
#define DCMTAGLIST_H

#include <QLinkedList>

#include "DcmCoreApi.h"
#include "DcmTag.h"

/*! List of DICOM tags.
 *
 * This class keeps an ordered list of DICOM tags.
 * It offers corresponding operations to find, insert,
 * or replace DICOM tags. The class DOES NOT guarantee that
 * all tags in the list have unique keys.
 * This is a base class for other tags containers,
 * like DICOM dataset, sequence tag, or sequence item.
 */
class DCM_CORE_API DcmTagList
{
public:

    /**
     * Default constructor.
     * Constructs an empty list of tags.
     */
    DcmTagList();

    /**
     * Copy constructor.
     * \param tagList Tags list to be copied.
     */
    DcmTagList(const DcmTagList &tagList);

    /**
     * Assignment operator.
     * \param tagList Tag list to be assigned.
     * \return This tag list object.
     */
    DcmTagList& operator =(const DcmTagList &tagList);

    /**
     * Destructor.
     */
    ~DcmTagList();

    /**
     * Puts a tag on the list.
     * The tag will be inserted even if another tag with
     * the same key is already on the list.
     */
    void insert(const DcmTag &tag);

    /**
     * Puts a tag on the list.
     * This method add a tag by its pointer and retain
     * the pointer. When the list is deleted, the tag
     * pointer will be freed as well.
     * If tag pointer is null, nothing is inserted.
     * \param Pointer to a tag to be inserted.
     */
    void insertAndRetain(DcmTag *tagPtr);

    /**
     * Adds tag or replaces existing tag with
     * the same key.
     * \param tag Tag to be inserted.
     */
    void insertOrReplace(const DcmTag &tag);

    /**
     * Adds tag or replaces existing one.
     * The posinted passed will be retained and freed
     * along with the list. If a tag exists altready,
     * the replaced tag will be freed immediately.
     * If passed tag pointer is null nothing is done.
     * \param tag Pointer to a tag to be inserted.
     */
    void insertOrReplaceAndRetain(DcmTag *tagPtr);

    /**
     * Returns number of tags in the list.
     * \return Number of tags.
     */
    int count() const;

    /**
     * Returns pointer to the tag at specified position
     * or null if position is invalid.
     * \param index Tag's position starting zero.
     * \return Pointer to a tag at requested position.
     */
    DcmTag* at(int index) const;

    /**
     * Find a first tag having the key specified.
     * \param tagKey Tag key to look for.
     * \return Pointer to a found tag or null if not found.
     */
    DcmTag* findFirst(const DcmTagKey &tagKey) const;

    /**
     * Remove the very first occurence of a tag with
     * specified key.
     * \param tagKey Tag key to be removed.
     */
    void removeFirst(const DcmTagKey &tagKey);

    /**
     * Remove all instances of tags with specified key.
     * \param tagKey Tag key to be removed.
     */
    void removeAll(const DcmTagKey &tagKey);

    /**
     * Remove all tags.
     */
    void clear();

    /**
     * Returns global size of all tags in this list for
     * given transfer syntax.
     * \param transferSyntax Transfer syntax to encode the list.
     * \return Global size of all tags.
     */
    DcmSize size(const DcmTransferSyntax &transferSyntax) const;

    /**
     * Returns a reference to tags list.
     * \return Reference to tags list.
     */
    QLinkedList<DcmTag*>& list();

private:

    QLinkedList<DcmTag*> m_list;    ///< List of tags.
};

#endif // DCMTAGLIST_H
