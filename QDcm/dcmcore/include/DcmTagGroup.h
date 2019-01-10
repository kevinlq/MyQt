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

#ifndef DCMTAGGROUP_H
#define DCMTAGGROUP_H

#include "DcmCoreApi.h"
#include "DcmTag.h"
#include "DcmTagList.h"

/*! Group of tags.
 * DICOM tags are jointed by group. This class handles a list of tags
 * of the same group. When written group tag sets a global size of the group
 * that can be used to facilitate scanning and looking for tags.
 * Group tag key has 0000 as its element.
 * A group cannot contain two tags with the same key, so inserting
 * a tag will replace and existing one with the same key.
 */
class DCM_CORE_API DcmTagGroup: public DcmTag
{
public:

    /**
     * Construct group of tags.
     * \param group Group number.
     */
    DcmTagGroup(DcmUnsignedShort group);

    /**
     * Copy constructor.
     * \param group Group to be copied.
     */
    DcmTagGroup(const DcmTagGroup &group);

    /**
     * Assignment operator.
     * \param group Group to be assigned.
     * \param This object.
     */
    DcmTagGroup& operator =(const DcmTagGroup &group);

    /**
     * Clone this group of tags.
     * \return Pointer to cloned group.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagGroup();

    /**
     * Always returns true.
     * \return true.
     */
    bool isGroup() const;

    /**
     * Returns total size of all tags of the group.
     * \param transferSyntax Transfer syntax to encode the tags.
     * \return Group tags total size in bytes.
     */
    DcmSize contentSize(const DcmTransferSyntax &transferSyntax) const;

    /**
     * Returns total size of the group including group tag as well.
     * \param transferSyntax Transfer syntax to encode the tags.
     * \return Total size of the group in bytes.
     */
    DcmSize size(const DcmTransferSyntax &transferSyntax) const;

    /**
     * Returns the group number.
     * \return Group number.
     */
    DcmUnsignedShort group() const;

    /**
     * Returns reference to the list of tags containing in this group.
     * \return List of tags.
     */
    DcmTagList& tags();

    /**
     * Insert tag into the group.
     * If tag already exists, it will be replaced.
     * If tag is of another group, it will not be added.
     * \param tag Tag to be inserted.
     */
    void insert(const DcmTag &tag);

    /**
     * Insert the tag and retain the pointer.
     * The tag will be deleted along with the group.
     * However, if the tag is of another group, it will not be added nor retained
     * and has to be managed by a caller.
     */
    void insertAndRetain(DcmTag *tagPtr);

    /**
     * Look for a tag with specified key.
     * \param tagKey Tag key to look for.
     * \return Pointer to found tag or null if not found.
     */
    DcmTag* findTag(const DcmTagKey &tagKey);

    /**
     * Remove all tags from this group.
     */
    void clear();

private:

    DcmTagList m_tags;  ///< List of tags in this group.
};

#endif // DCMTAGGROUP_H
