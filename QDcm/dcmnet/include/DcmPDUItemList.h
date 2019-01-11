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

#ifndef DCMPDUITEMLIST_H
#define DCMPDUITEMLIST_H

#include <QList>
#include "DcmNetApi.h"
#include "DcmPDUItem.h"

/*! List of PDU items.
 * This class handles a list of PDU items.
 * An example of such a list is a set of presentation
 * contexts proposed in association.
 */
class DCM_NET_API DcmPDUItemList
{
public:

    /**
     * Construct an empty list of PDU items.
     */
    DcmPDUItemList();

    /**
     * Copy constructor.
     * \param list PDU items list to be copied.
     */
    DcmPDUItemList(const DcmPDUItemList &list);

    /**
     * Assignment operator.
     * \param list List to be assigned.
     * \return This list.
     */
    DcmPDUItemList& operator =(const DcmPDUItemList &list);

    /**
     * Destructor.
     */
    ~DcmPDUItemList();

    /**
     * Returns number of PDU items in this list.
     * \return Number of PDU items.
     */
    int count() const;

    /**
     * Returns PDU items at specified index.
     * \param index PDU item index.
     * \return Pointer to PDU item.
     */
    DcmPDUItem* at(int index) const;

    /**
     * Append PDU item to the list.
     * \param pdu PDU item to be added.
     */
    void append(const DcmPDUItem &pdu);

    /**
     * Append PDU item and retain the pointer.
     * The item will be deleted along with this list.
     * \param pduPtr PDU item pointer.
     */
    void appendAndRetain(DcmPDUItem *pduPtr);

    /**
     * Remove and delete all PDU items in this list.
     */
    void clear();

    /**
     * Returns total size of all PDU items in this list.
     * \return List size in bytes.
     */
    DcmSize size() const;

private:

    QList<DcmPDUItem*> m_pduItems;  ///< List of items.
};

#endif // DCMPDUITEMLIST_H
