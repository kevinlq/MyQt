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

#ifndef DCMTAG_H
#define DCMTAG_H

#include <QVariant>

#include "DcmCoreApi.h"
#include "DcmTagKey.h"
#include "DcmVr.h"
#include "DcmTransferSyntax.h"

/*! DICOM tag base class.
 *
 * This is a base abstract class for DICOM tags.
 * It does not hold any value but provides a basis for
 * all other tag classed to be constructed.
 */
class DCM_CORE_API DcmTag
{
public:

    /**
     * Default constructor.
     */
    DcmTag();

    /**
     * Construct a tag by its key and value representation.
     * \param tagKey Tag key.
     * \param vr Tag value representation.
     */
    DcmTag(const DcmTagKey &tagKey, const DcmVr &vr);

    /**
     * Copy constructor.
     * \param tag Tag to be copied.
     */
    DcmTag(const DcmTag &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag object.
     */
    DcmTag& operator =(const DcmTag &tag);

    /**
     * Clone this tag.
     * This method allocates a new tag and performs a deep copy
     * of all the tag data.
     * This method is pure virtual and has to be implemented by derived class.
     * \return Pointer to a new cloned tag.
     */
    virtual DcmTag* clone() const;

    /**
     * Destructor.
     */
    virtual ~DcmTag();

    /**
     * Returns tag key.
     * \return Tag key.
     */
    DcmTagKey tagKey() const;

    /**
     * Returns tag's value representation.
     * \return Tag VR.
     */
    DcmVr vr() const;

    /**
     * Tells whether this tag is a group of tags.
     * \return true If this tag represents a tags group.
     */
    virtual bool isGroup() const;

    /**
     * Tells whether this tag is binary.
     * \return true if tag is binary.
     */
    virtual bool isBinary() const;

    /**
     * Tells whether this tag is valid.
     * A valid tag has a valid VR.
     * \return true if tag is valid (it's VR is valid).
     */
    bool isValid() const;

    /**
     * Returns tag value.
     * This method returns tag value encoded in a variant type.
     * Not all values can be encoded precisely with QVariant.
     * For spacific cases one should call a corresponding method
     * to get a correct value.
     * This method is pure virtual and must be implemented by derived class.
     * \return Tag value as QVariant.
     */
    virtual QVariant value() const;

    /**
     * Returns a list of tag's values.
     * \return Tag's values list.
     */
    virtual QVariantList values() const;

    /**
     * Assign a value expressed in variant type.
     * Not all tag values can be encoded as QVariant type
     * (e.g. DICOM time (TM) value is more precise than QTime).
     * One have use corresponding methods of derived classes to assign
     * such values.
     * This method is pure virtual and must be implemented by derived class.
     * \param v Value to be assigned.
     */
    virtual void setValue(const QVariant &v);

    /**
     * Append value to existing ones.
     * This will increate multiplicity by one.
     * \param v Value to be added.
     */
    virtual void appendValue(const QVariant &v);

    /**
     * Assignment operator to set tag value.
     * \param v Tag value to be set.
     * \return This tag.
     */
    DcmTag& operator =(const QVariant &v);

    /**
     * Operator to append a value.
     * \param v Value to be added.
     * \return This tag.
     */
    DcmTag& operator <<(const QVariant &v);

    /**
     * Returns tag value.
     * \return Tag value.
     */
    QVariant operator ()() const;

    /**
     * Returns tag value for specified index.
     * \param index Value index.
     * \return Tag value.
     */
    QVariant operator [](int index) const;

    /**
     * Returns multiplicity of this tag's value.
     * This method is pure virtual and has to be implemented by derived class.
     */
    virtual int multiplicity() const;

    /**
     * Returns tag raw content size in bytes.
     * The content size depends on transfer syntax used to encode the tag.
     * \param transferSyntax Transfer syntax to encode the tag.
     * \return Tag's raw content size in bytes.
     */
    virtual DcmSize contentSize(const DcmTransferSyntax &transferSyntax) const;

    /**
     * Returns tag's raw size in bytes including content
     * and tag descriptor.
     * \param transferSyntax Transfer syntax to encode the tag.
     * \return Tag's raw size in bytes.
     */
    virtual DcmSize size(const DcmTransferSyntax &transferSyntax) const;

    /**
     * Create tag with specified key and representation.
     * \param tagKey Tag key to be used.
     * \param vr Value representation.
     * \return Pointer to create tag or null if cannot create.
     */
    static DcmTag* create(const DcmTagKey &tagKey, const DcmVr &vr);

    /**
     * Create tag by key.
     * This method querries DICOM dictionary for tag value representation.
     * \param tagKey Tag key to be used.
     * \return Pointer to created tag or null if failed.
     */
    static DcmTag* create(const DcmTagKey &tagKey);

    /**
     * Create tag by name.
     * This method querries DICOM dictionary for tag value representation.
     * \param tagName Tag name (case insensitive).
     * \return Pointer to create tag or null if failed.
     */
    static DcmTag* create(const QString &tagName);

protected:

    /**
     * Assign the VR of this tag.
     * Normally the VR a tag cannot be changed, but in some
     * cases some internal implementation may need to change the VR
     * (e.g. switching it to Invalid).
     */
    void setVr(const DcmVr &vr);

private:

    DcmTagKey m_tagKey; ///< Tag key.
    DcmVr m_vr;         ///< Tag VR.

};

#endif // DCMTAG_H
