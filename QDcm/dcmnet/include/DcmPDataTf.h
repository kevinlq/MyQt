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

#ifndef DCMPDATATF_H
#define DCMPDATATF_H

#include <QList>
#include "DcmPDUItem.h"
#include "DcmPDVItem.h"
#include "DcmStream.h"
#include "DcmNetApi.h"

/*! DICOM data transfer PDU.
 * This class represents a raw data transfer PDU.
 * This PDataTF PDU holds a list of PDV items that encode
 * some raw data each.
 */
class DCM_NET_API DcmPDataTf: public DcmPDUItem
{
public:

    /**
     * Construct void P-Data-TF PDU.
     */
    DcmPDataTf();

    /**
     * Copy constructor.
     * \param pdu PDU item to be copied.
     */
    DcmPDataTf(const DcmPDataTf &pdu);

    /**
     * Assignment operator.
     * \param pdu PDU to be assigned.
     * \return This PDU item.
     */
    DcmPDataTf& operator =(const DcmPDataTf &pdu);

    /**
     * Clone this PDU item.
     * \return Pointer to cloned PDU item.
     */
    DcmPDUItem* clone() const;

    /**
     * Destructor.
     */
    ~DcmPDataTf();

    /**
     * Returns the number of PDVs in this P-Data-TF PDU.
     * \return Number of PDVs.
     */
    int count() const;

    /**
     * Returns pointer to PDV item at specified index.
     * If index is invalid, null pointer is returned.
     * \param i PDV item index.
     * \return Pointer to PDV item.
     */
    DcmPDVItem* at(int i) const;

    /**
     * Add a PDV item to this P-Data-TF PDU.
     * \param pdv PDV item to be added.
     */
    void addPDV(const DcmPDVItem &pdv);

    /**
     * Add a PDV item by pointer and retain it. The PDV item will be
     * deleted along with this PDU.
     * \param pdvPtr Pointer to PDV item to be added.
     */
    void addAndRetainPDV(DcmPDVItem *pdvPtr);

    /**
     * Remove all PDV items from this P-Data-TF PDU.
     */
    void clear();

    /**
     * Returns this PDU item size in bytes.
     * \return PDU item size.
     */
    DcmSize size() const;

    /**
     * Returns this PDU item raw content size in bytes.
     * \return PDU content size.
     */
    DcmSize contentSize() const;

    /**
     * Tells whether this P-Data-TF PDU is valid.
     * It is valid if there is at least one PDV attached.
     * \return true if this PDU item is valid.
     */
    bool isValid() const;

    // I/O operations
    DCM_NET_API friend DcmStream& operator <<(DcmStream &stream, const DcmPDataTf &pdu);
    DCM_NET_API friend DcmStream& operator >>(DcmStream &stream, DcmPDataTf &pdu);

private:

    QList<DcmPDVItem *> m_pdvItemsList; ///< List of attached PDV items.
};

DCM_NET_API DcmStream& operator <<(DcmStream &stream, const DcmPDataTf &pdu);
DCM_NET_API DcmStream& operator >>(DcmStream &stream, DcmPDataTf &pdu);

#endif // DCMPDATATF_H
