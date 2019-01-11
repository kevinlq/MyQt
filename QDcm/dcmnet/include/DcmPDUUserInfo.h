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

#ifndef DCMPDUUSERINFO_H
#define DCMPDUUSERINFO_H

#include "DcmPDUItem.h"
#include "DcmPDUItemList.h"
#include "DcmStream.h"
#include "DcmNetApi.h"

/*! User info PDU item.
 * This PDU item contains several other PDU items
 * giving additional information on DICOM association.
 */
class DCM_NET_API DcmPDUUserInfo: public DcmPDUItem
{
public:

    /**
     * Construct empty user info PDU.
     */
    DcmPDUUserInfo();

    /**
     * Copy constructor.
     * \param pdu PDU to be copied.
     */
    DcmPDUUserInfo(const DcmPDUUserInfo &pdu);

    /**
     * Assignment operator.
     * \param pdu PDU to be assigned.
     * \return This PDU.
     */
    DcmPDUUserInfo& operator =(const DcmPDUUserInfo &pdu);

    /**
     * Clone this PDU item.
     * \return Pointer to PDU clone.
     */
    DcmPDUItem* clone() const;

    /**
     * Destructor.
     */
    ~DcmPDUUserInfo();

    /**
     * Returns the number of inset PDUs in this user info PDU.
     * \return Number of contained PDUs.
     */
    int count() const;

    /**
     * Remove all inset PDUs.
     */
    void clear();

    /**
     * Returns a pointer to a PDU by its index.
     * For invalid index a null pointer is returned.
     */
    DcmPDUItem* at(int index) const;

    /**
     * Append PDU item.
     * \param pdu PDU item to be added.
     */
    void append(const DcmPDUItem &pdu);

    /**
     * Appent PDU item by pointer and retain it.
     * The item will be deleted along with this user info PDU.
     * \param pduPtr Pointer to a PDU to be added.
     */
    void appendAndRetain(DcmPDUItem *pduPtr);

    /**
     * Returns this PDU item content size in bytes.
     * \return This PDU item content size.
     */
    DcmSize contentSize() const;

    /**
     * Tells whether this PDU is valid.
     * User info PDU is valid if it contain at least one inset PDU.
     * \retur true if this PDU is valid.
     */
    bool isValid() const;

    /**
     * Returns PDU maximal length in bytes.
     * If no corresponding PDU item found, default length is returned.
     * \param defaultLength Default value to be returned if PDUMaxLength item not present.
     * \return PDU maximal length.
     */
    DcmSize pduMaxLength(DcmSize defaultLength = 16384) const;

    /**
     * Returns implementation class UID or empty string if not found.
     * \return Implementation class UID.
     */
    QString implementationClassUID() const;

    /**
     * Returns implementation version name or empty string if not found.
     * \return Implementation version name.
     */
    QString implementationVersionName() const;

    // I/O operations
    DCM_NET_API friend DcmStream& operator <<(DcmStream &stream, const DcmPDUUserInfo &pdu);
    DCM_NET_API friend DcmStream& operator >>(DcmStream &stream, DcmPDUUserInfo &pdu);

private:

    /**
     * Find contained PDU item by its type.
     * \param type PDU item type.
     * \return Pointer to found item or null if not found.
     */
    DcmPDUItem* findPDUItem(DcmPDUType type) const;

    DcmPDUItemList m_itemsList; ///< List of inset PDU items.
};

DCM_NET_API DcmStream& operator <<(DcmStream &stream, const DcmPDUUserInfo &pdu);
DCM_NET_API DcmStream& operator >>(DcmStream &stream, DcmPDUUserInfo &pdu);

#endif // DCMPDUUSERINFO_H
