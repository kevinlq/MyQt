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

#ifndef DCMDIMSEREQUEST_H
#define DCMDIMSEREQUEST_H

#include "DcmDimseMessage.h"
#include "DcmNetApi.h"

/*! DIMSE request message.
 * This class is derived from abstract DIMSE message implementation
 * in order to distinguish request messages.
 */
class DCM_NET_API DcmDimseRequest: public DcmDimseMessage
{
public:

    /**
     * Default constructor.
     */
    DcmDimseRequest();

    /**
     * Construct DIMSE request message from command dataset.
     * \param dataset Command dataset.
     */
    DcmDimseRequest(const DcmDataset &dataset);

    /**
     * Construct DIMSE request message.
     * \param serviceClassUID Service class UID.
     * \param command DIMSE command code.
     * \param id Message id.
     */
    DcmDimseRequest(const QString &serviceClassUID, DcmCommandType command, int id = 0);

    /**
     * Copy constructor.
     * \param message Message to be copied.
     */
    DcmDimseRequest(const DcmDimseRequest &message);

    /**
     * Assignment operator.
     * \param message Message to be assigned.
     * \return This DIMSE request message.
     */
    DcmDimseRequest& operator =(const DcmDimseRequest &message);

    /**
     * Clone this DIMSE message.
     * \return Pointer to cloned DIMSE message.
     */
    DcmDimseMessage* clone() const;
};

#endif // DCMDIMSEREQUEST_H
