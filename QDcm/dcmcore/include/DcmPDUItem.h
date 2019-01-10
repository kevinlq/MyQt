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

#ifndef DCMPDUITEM_H
#define DCMPDUITEM_H

#include "DcmCoreApi.h"
#include "DcmTypes.h"

/*! Abstract PDU item.
 *
 * Abstract Protocol Data Unit (PDU) - element of
 * DICOM communication protocol. The PDU is defined by its
 * type that allows decode the PDU and fetch the corresponding
 * information.
 */
class DCM_CORE_API DcmPDUItem
{
public:

    /**
     * Construct a PDU item.
     * \param pduItemType Type of the PDU item to be costructed.
     */
    DcmPDUItem(DcmPDUType pduItemType);

    /**
     * Copy constructor.
     * \param item PDU item to be copied.
     */
    DcmPDUItem(const DcmPDUItem &item);

    /**
     * Assignment operator.
     * \param item PDU item to be assigned.
     * \return This PDU item.
     */
    DcmPDUItem& operator =(const DcmPDUItem &item);

    /**
     * Clone this PDU item.
     * \return Pointer to a cloned PDU item.
     */
    virtual DcmPDUItem* clone() const;

    /**
     * Destructor.
     */
    virtual ~DcmPDUItem();

    /**
     * Returns PDU item's type.
     * \return PDU item type.
     */
    DcmPDUType type() const;

    /**
     * Tells whether this PDU item is at the association level.
     * Such PDUs are AAssociateRq, AAssociareAc, AAssociateRj,
     * AAbort, AReleaseRq, AReleaseRp, and P-Data-TF.
     */
    bool isAssociationLevel() const;

    /**
     * Returns raw size of the PDU item in bytes.
     * This method accounts for the item content size
     * and add 4 bytes to encode item type and content size:
     * TT 00 LL LL (type, 00 - reserved, LLLL - content size).
     * \return PDU item raw size.
     */
    virtual DcmSize size() const;

    /**
     * Returns PDU item content size in bytes.
     * Default implementation returns 0.
     * \return PDU item context size.
     */
    virtual DcmSize contentSize() const;

    /**
     * Tells whether this PDU item is valid.
     * The items is valid if it has a valid type assigned.
     * \return true if this PDU item is valid.
     */
    virtual bool isValid() const;

private:

    DcmPDUType m_type;  ///< PDU item type.

};

#endif // DCMPDUITEM_H
