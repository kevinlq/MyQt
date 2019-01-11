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

#include "DcmDimseRequest.h"

DcmDimseRequest::DcmDimseRequest()
    : DcmDimseMessage()
{
}

DcmDimseRequest::DcmDimseRequest(const DcmDataset &dataset)
    : DcmDimseMessage(dataset)
{
}

DcmDimseRequest::DcmDimseRequest(const QString &serviceClassUID, DcmCommandType command, int id)
    : DcmDimseMessage(serviceClassUID, command, id)
{
}

DcmDimseRequest::DcmDimseRequest(const DcmDimseRequest &message)
    : DcmDimseMessage(message)
{
}

DcmDimseRequest& DcmDimseRequest::operator =(const DcmDimseRequest &message)
{
    if (this != &message) {
        DcmDimseMessage::operator =(message);
    }
    return *this;
}

DcmDimseMessage* DcmDimseRequest::clone() const
{
    return new DcmDimseRequest(*this);
}
