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

#ifndef DCMDIMSEPRIORITYREQUEST_H
#define DCMDIMSEPRIORITYREQUEST_H

#include "DcmDimseRequest.h"
#include "DcmNetApi.h"

/*! DIMSE message with priority.
 * This class defines a DIMSE request message with priority field.
 */
class DCM_NET_API DcmDimsePriorityRequest: public DcmDimseRequest
{
public:

    /**
     * Default constructor.
     */
    DcmDimsePriorityRequest();

    /**
     * Construct DIMSE priority request from a command dataset.
     * \param dataset Command dataset.
     */
    DcmDimsePriorityRequest(const DcmDataset &dataset);

    /**
     * Construct DIMSE priority request.
     * \param serviceClassUID service class UID.
     * \param command DIMSE command code.
     * \param id Message id.
     */
    DcmDimsePriorityRequest(const QString &serviceClassUID, DcmCommandType command, int id = 0);

    /**
     * Copy constructor.
     * \param message DIMSE message to be copied.
     */
    DcmDimsePriorityRequest(const DcmDimsePriorityRequest &message);

    /**
     * Assignment operator.
     * \param message Message to be assigned.
     * \return This DIMSE message.
     */
    DcmDimsePriorityRequest& operator =(const DcmDimsePriorityRequest &message);

    /**
     * Clone this DIMSE message.
     */
    DcmDimseMessage* clone() const;

    /**
     * Returns DIMSE request message priority.
     * \return DIMSE request priority.
     */
    DcmPriorityType priority() const;

    /**
     * Assign DIMSE request message priority.
     * \param priority DIMSE message priority to be set.
     */
    void setPriority(DcmPriorityType priority);
};

#endif // DCMDIMSEPRIORITYREQUEST_H
