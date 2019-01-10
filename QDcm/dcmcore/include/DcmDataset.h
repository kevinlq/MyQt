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

#ifndef DCMDATASET_H
#define DCMDATASET_H

#include "DcmCoreApi.h"
#include "DcmTagList.h"
#include "DcmTagGroup.h"
#include "DcmTag.h"
#include "DcmModule.h"

/*! A set of DICOM tags.
 *
 * This class represents a set of DICOM tags as
 * a single DICOM object. It also provides some method
 * to access the tags in the data set.
 *
 * All tags in the dataset are organized in groups.
 */
class DCM_CORE_API DcmDataset
{
public:

    /**
     * Construct an empty data set.
     */
    DcmDataset();

    /**
     * Copy constructor.
     * \param dataset Data set to be copied.
     */
    DcmDataset(const DcmDataset &dataset);

    /**
     * Assignment operator.
     * \param dataset Data set to be assigned.
     * \return This data set.
     */
    DcmDataset& operator =(const DcmDataset &dataset);

    /**
     * Insert a tag to the dataset.
     * If tag already exists it will be replaced.
     * \param tag Tag to be added.
     */
    void insert(const DcmTag &tag);

    /**
     * Insert and retain a tag.
     * The tag inserted will be delete along with this
     * dataset. If tag already exists it will be replaced.
     * \param tagPtr Pointer to a tag to be added.
     */
    void insertAndRetain(DcmTag *tagPtr);

    /**
     * Look for a tag in the dataset.
     * \param tagKey Tag key to look for.
     * \return Pointer to a tag or null if not found.
     */
    DcmTag* findTag(const DcmTagKey &tagKey) const;

    /**
     * Look for a tag in the dataset.
     * \param tagName Name of the tag to look for.
     * \return Pointer to a tag or null if not found.
     */
    DcmTag* findTag(const QString &tagName) const;

    /**
     * Returns tag value or empty variant if
     * tag does not exist.
     * \param tagKey Tag key to look for.
     * \return Tag value.
     */
    QVariant tagValue(const DcmTagKey &tagKey) const;

    /**
     * Returns tag value by its name.
     * \param tagName Tag name.
     * \return Tag value or empty if tag not found.
     */
    QVariant tagValue(const QString &tagName) const;

    /**
     * Returns tag value by its name.
     * @param tagName Tag name.
     * @return Tag value or empty if tag not found.
     */
    QVariant operator [](const QString &tagName) const;

    /**
     * Returns a list of tag values or empty list
     * if tag is not found.
     * \param tagKey Tag key to look for.
     * \return List of tag values.
     */
    QVariantList tagValues(const DcmTagKey &tagKey) const;

    /**
     * Returns a list of tag values or empty list
     * if tag is not found.
     * \param tagName Tag name.
     * \return List of tag values.
     */
    QVariantList tagValues(const QString &tagName) const;

    /**
     * Assign tag value.
     * If tag is not in the dataset it will be added.
     * \param tagKey Tag key.
     * \param value Value to be set.
     */
    void setTagValue(const DcmTagKey &tagKey, const QVariant &value);

    /**
     * Assign tag value.
     * If tag is not in the dataset it will be added.
     * \param tagName Tag name.
     * \param value Value to be set.
     */
    void setTagValue(const QString &tagName, const QVariant &value);

    /**
     * Returns a reference to tag groups list.
     * \return Reference to tags group list.
     */
    DcmTagList& tagGroups();

    /**
     * Attach module to the dataset.
     * \param module Module to be attached.
     */
    void attachModule(const DcmModule &module);

private:

    /**
     * Find or create a tags group.
     * \param g Group to look for or create.
     * \return Pointer to the tags group.
     */
    DcmTagGroup* findOrCreateGroup(DcmUnsignedShort g);

    DcmTagList m_tagGroups; ///< Tag groups holding corresponding tags.

};

Q_DECLARE_METATYPE(DcmDataset);

#endif // DCMDATASET_H
