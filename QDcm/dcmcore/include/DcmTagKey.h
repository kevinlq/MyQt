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

#ifndef DCMTAGKEY_H
#define DCMTAGKEY_H

#include <qglobal.h>
#include <QString>

#include "DcmCoreApi.h"
#include "DcmTypes.h"

/*! DICOM tag (group, element) pair.
 *
 * This class represents DICOM tag group, element pair.
 * Group and element are encoded as 16 bits unsigned integers.
 * Tag key does not have any information of the data kind/type
 * stored. DICOM tag dictionary has to be used to find out
 * the tag meaning and data type.
 *
 * \author Arthur Benilov
 * \date March 2012
 */
class DCM_CORE_API DcmTagKey
{
public:

    /*
        Some frequently used tag keys.
    */
    static const DcmTagKey CommandServiceClassUID;
    static const DcmTagKey CommandField;
    static const DcmTagKey CommandMessageId;
    static const DcmTagKey CommandResponseMessageId;
    static const DcmTagKey CommandMoveDestinationAE;
    static const DcmTagKey CommandPriority;
    static const DcmTagKey CommandDataSetType;
    static const DcmTagKey CommandStatus;
    static const DcmTagKey CommandAffectedSOPInstanceUID;
    static const DcmTagKey CommandRequestedSOPInstanceUID;
    static const DcmTagKey CommandNumberOfRemainedSuboperations;
    static const DcmTagKey CommandNumberOfCompletedSuboperations;
    static const DcmTagKey CommandNumberOfFailedSuboperations;
    static const DcmTagKey CommandNumberOfWarningSuboperations;
    static const DcmTagKey CommandMoveOriginatorAE;
    static const DcmTagKey CommandMoveOriginatorMessageId;

    static const DcmTagKey TransferSyntaxUID;

    static const DcmTagKey SpecificCharacterSet;

    static const DcmTagKey PixelData;
    static const DcmTagKey Item;
    static const DcmTagKey ItemDeliminationItem;
    static const DcmTagKey SequenceDeliminationItem;

    /**
     * Default constructor. Create tag key (0000, 0000).
     */
    DcmTagKey();

    /**
     * Construct tag key from group and element pair.
     * \param group Group value.
     * \param element Element value.
     */
    DcmTagKey(DcmUnsignedShort group, DcmUnsignedShort element);

    /**
     * Construct tag key from hash value.
     * Hash value is a composition of 16-bits group, element pair
     * into single 32-bits unsigned integer.
     * \param hash Tag key hash value.
     */
    DcmTagKey(DcmHash hash);

    /**
     * Copy constructor.
     * \param tagKey Tag key to be copied.
     */
    DcmTagKey(const DcmTagKey &tagKey);

    /**
     * Assignment operator.
     * \param tagKey Tag key to be assigned.
     * \return This tag key object.
     */
    DcmTagKey& operator =(const DcmTagKey &tagKey);

    /**
     * Assign hash value.
     * As the tag key is entirely defined by its hash,
     * this operator allows direct assignment via hash value.
     * \param hash Hash value to be assigned.
     * \return This tag key object.
     */
    DcmTagKey& operator =(DcmHash hash);

    /**
     * Compare with another tag key.
     * \param tagKey Tag key to compare with.
     * \return true if keys are equal.
     */
    bool operator ==(const DcmTagKey &tagKey) const;

    /**
     * Compare with another tag key.
     * \param tagKey Tag key to compare with.
     * \return true if keys are different.
     */
    bool operator !=(const DcmTagKey &tagKey) const;

    /**
     * Compare with another tag key.
     * \param tagKey Tag key to compare with.
     * \return true if this key is higher than another one.
     */
    bool operator >(const DcmTagKey &tagKey) const;

    /**
     * Compare with another tag key.
     * \param tagKey Tag key to compare with.
     * \return true if this key is lower than another one.
     */
    bool operator <(const DcmTagKey &tagKey) const;

    /**
     * Compare with another tag key.
     * \param tagKey Tag key to compare with.
     * \return true if this key is higher or equal to another one.
     */
    bool operator >=(const DcmTagKey &tagKey) const;

    /**
     * Compare with another tag key.
     * \param tagKey Tag key to compare with.
     * \return true if this key is lower or equal to another one.
     */
    bool operator <=(const DcmTagKey &tagKey) const;

    /**
     * Returns group value of this tag key.
     * \return Tag key group.
     */
    DcmUnsignedShort group() const;

    /**
     * Returns element value of this tag key.
     * \return Tag key element.
     */
    DcmUnsignedShort element() const;

    /**
     * Returns tag key hash value.
     * Hash value is an unsigned 32-bits integers containing
     * group (at MSB position) and element (LSB position).
     * \return Hash value.
     */
    DcmHash hash() const;

    /**
     * Assign tag key group.
     * \param group Group to be assigned.
     */
    void setGroup(DcmUnsignedShort group);

    /**
     * Assign tag key element.
     * \param element Element to be assigned.
     */
    void setElement(DcmUnsignedShort element);

    /**
     * Assign tag key group and element via hash value.
     * \param hash Hash value to be assigned.
     */
    void setHash(DcmHash hash);

    /**
     * Tells whether this tag key is of a private tag.
     * Private tags have an odd group value.
     * \return true if this tag key is of a private tag.
     */
    bool isPrivate() const;

    /**
     * Tells whether this tag key is of a group size tag.
     * Group size tags has element value set to zero.
     * \return true if this tag key is of a group size tag.
     */
    bool isGroupSize() const;

    /**
     * Tells whether the tag of this key should be always
     * encoded using implicit encoding.
     * Some tags like sequence items or delimiters are always
     * encoded as implicit.
     * \return true if the tag of this key should be encoded as implicit.
     */
    bool isAlwaysImplicit() const;

    /**
     * Returns textual representation of this tag key.
     * The tag key is shown as '(gggg, eeee)' string with
     * gggg being a group value and eeee - element value.
     * Both are hexadecimals.
     * \return String representation of this tag key.
     */
    QString toString() const;

private:
    DcmUnsignedShort m_group;   ///< Tag key group.
    DcmUnsignedShort m_element; ///< Tag key element.
};

#endif // DCMTAGKEY_H
