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

#ifndef DCMARELEASERESPONSE_H
#define DCMARELEASERESPONSE_H

#include "DcmPDUItem.h"
#include "DcmStream.h"
#include "DcmNetApi.h"

/*! DICOM association release response PDU.
 * This class defines an association release response PDU.
 * The release response does not have any particular paremeters.
 */
class DCM_NET_API DcmAReleaseResponse: public DcmPDUItem
{
public:

    /**
     * Construct association release response PDU.
     */
    DcmAReleaseResponse();

    /**
     * Copy constructor.
     * \param pdu PDU item to be copied.
     */
    DcmAReleaseResponse(const DcmAReleaseResponse &pdu);

    /**
     * Assignment operator.
     * \param pdu PDU item to be set.
     * \return This PDU item.
     */
    DcmAReleaseResponse& operator =(const DcmAReleaseResponse &pdu);

    /**
     * Clone this PDU item.
     * \return Pointer to cloned PDU item.
     */
    DcmPDUItem* clone() const;

    /**
     * Destructor.
     */
    ~DcmAReleaseResponse();

    /**
     * Returns this PDU item size in bytes.
     * \return This PDU item size.
     */
    DcmSize size() const;

    /**
     * Returns this PSU item content size in bytes.
     * \return This PDU item content size.
     */
    DcmSize contentSize() const;

    /**
     * Tells whether this PDU item is valid.
     * The association release response PDU item is always valid.
     * \return true.
     */
    bool isValid() const;

    // I/O operations
    DCM_NET_API friend DcmStream& operator <<(DcmStream &stream, const DcmAReleaseResponse &pdu);
    DCM_NET_API friend DcmStream& operator >>(DcmStream &stream, DcmAReleaseResponse &pdu);
};

DCM_NET_API DcmStream& operator <<(DcmStream &stream, const DcmAReleaseResponse &pdu);
DCM_NET_API DcmStream& operator >>(DcmStream &stream, DcmAReleaseResponse &pdu);

#endif // DCMARELEASERESPONSE_H
