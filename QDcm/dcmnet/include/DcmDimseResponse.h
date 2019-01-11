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

#ifndef DCMDIMSERESPONSE_H
#define DCMDIMSERESPONSE_H

#include "DcmDimseMessage.h"
#include "DcmDimseRequest.h"
#include "DcmNetApi.h"

/*! DIMSE response message.
 * This is a base class for DIMSE response messages.
 */
class DCM_NET_API DcmDimseResponse: public DcmDimseMessage
{
public:

    /**
     * DIMSE message response status.
     * These are just known statuses. There may be other
     * values depending on particular application implementation.
     */
    typedef enum {
        Status_Success                          = 0x0000,
        Status_RefusedOutOfResources            = 0xA700,
        Status_UnablePerformSubOperations       = 0xA702,
        Status_RefusedMoveDestinationUnknown    = 0xA801,
        Status_ErrorCannotUnderstand            = 0xC000,
        Status_Cancel                           = 0xFE00,
        Status_Pending                          = 0xFF00,
        Status_PendingWithWarning               = 0xFF01,

        Status_Invalid                          = 0xFFFE    ///< Library private code.
    } Status;

    /**
     * Default constructor.
     */
    DcmDimseResponse();

    /**
     * Construct DIMSE response from command dataset.
     * \param dataset Command dataset.
     */
    DcmDimseResponse(const DcmDataset &dataset);

    /**
     * Construct DIMSE response from request message.
     * \param request DIMSE request message.
     */
    DcmDimseResponse(const DcmDimseRequest &request);

    /**
     * Copy constructor.
     * \param message Message to be copied.
     */
    DcmDimseResponse(const DcmDimseResponse &message);

    /**
     * Assignment operator.
     * \param message Message to be assigned.
     * \return This DIMSE response message.
     */
    DcmDimseResponse& operator =(const DcmDimseResponse &message);

    /**
     * Clone this DIMSE message.
     * \return Pointer to cloned DIMSE message.
     */
    DcmDimseMessage* clone() const;

    /**
     * Returns DIMSE response status code.
     * \return DIMSE response status code.
     */
    DcmDimseResponse::Status status() const;

    /**
     * Assign DIMSE response status code.
     * \param s Status code to be assigned.
     */
    void setStatus(DcmDimseResponse::Status s);

    /**
     * Returns response message id.
     * \return Response message id.
     */
    int responseMessageId() const;

    /**
     * Assign response message id.
     * \param id Response message id to be set.
     */
    void setResponseMessageId(int id);
};

#endif // DCMDIMSERESPONSE_H
