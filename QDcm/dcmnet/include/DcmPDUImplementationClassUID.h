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

#ifndef DCMPDUIMPLEMENTATIONCLASSUID_H
#define DCMPDUIMPLEMENTATIONCLASSUID_H

#include "DcmPDUItem.h"
#include "DcmStream.h"
#include "DcmNetApi.h"

/*! Implementation class UID.
 * This PDU encoded an UID of DICOM communication implementation.
 */
class DCM_NET_API DcmPDUImplementationClassUID: public DcmPDUItem
{
public:

    /**
     * Construct an invalid PDU.
     */
    DcmPDUImplementationClassUID();

    /**
     * Construct implementation class UID.
     * \param uid Implementation class UID.
     */
    DcmPDUImplementationClassUID(const QString &uid);

    /**
     * Copy constructor.
     * \param pdu PDU to be copied.
     */
    DcmPDUImplementationClassUID(const DcmPDUImplementationClassUID &pdu);

    /**
     * Assignment operator.
     * \param pdu PDU to be assigned.
     * \return This PDU.
     */
    DcmPDUImplementationClassUID& operator =(const DcmPDUImplementationClassUID &pdu);

    /**
     * Clone this PDU item.
     * \return Pointer to cloned PDU.
     */
    DcmPDUItem* clone() const;

    /**
     * Destructor.
     */
    ~DcmPDUImplementationClassUID();

    /**
     * Returns implementation class UID.
     * \return UID.
     */
    QString uid() const;

    /**
     * Returns this PDU content size in bytes.
     * \return PDU context size.
     */
    DcmSize contentSize() const;

    /**
     * Tells whether this PDU is valid.
     * This PDU is valid if implementation class UID is not void.
     * \return true if this PDU is valid.
     */
    bool isValid() const;

    // I/O operations
    DCM_NET_API friend DcmStream& operator <<(DcmStream &stream, const DcmPDUImplementationClassUID &pdu);
    DCM_NET_API friend DcmStream& operator >>(DcmStream &stream, DcmPDUImplementationClassUID &pdu);

private:

    QString m_uid;
};

DCM_NET_API DcmStream& operator <<(DcmStream &stream, const DcmPDUImplementationClassUID &pdu);
DCM_NET_API DcmStream& operator >>(DcmStream &stream, DcmPDUImplementationClassUID &pdu);

#endif // DCMPDUIMPLEMENTATIONCLASSUID_H
