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

#include "DcmTagUS.h"
#include "DcmDimsePriorityRequest.h"

DcmDimsePriorityRequest::DcmDimsePriorityRequest()
    : DcmDimseRequest()
{
    setPriority(DcmPriorityType_Medium);
}

DcmDimsePriorityRequest::DcmDimsePriorityRequest(const DcmDataset &dataset)
    : DcmDimseRequest(dataset)
{
}

DcmDimsePriorityRequest::DcmDimsePriorityRequest(const QString &serviceClassUID, DcmCommandType command, int id)
    : DcmDimseRequest(serviceClassUID, command, id)
{
    setPriority(DcmPriorityType_Medium);
}

DcmDimsePriorityRequest::DcmDimsePriorityRequest(const DcmDimsePriorityRequest &message)
    : DcmDimseRequest(message)
{
}

DcmDimsePriorityRequest& DcmDimsePriorityRequest::operator =(const DcmDimsePriorityRequest &message)
{
    if (this != &message) {
        DcmDimseRequest::operator =(message);
    }
    return *this;
}

DcmDimseMessage* DcmDimsePriorityRequest::clone() const
{
    return new DcmDimsePriorityRequest(*this);
}

DcmPriorityType DcmDimsePriorityRequest::priority() const
{
    DcmPriorityType p = DcmPriorityType_Medium;

    DcmTag *tag = constCommandDataset().findTag(DcmTagKey::CommandPriority);
    if (tag) {
        p = (DcmPriorityType)tag->value().toInt();
    }

    return p;
}

void DcmDimsePriorityRequest::setPriority(DcmPriorityType priority)
{
    DcmTagUS tag(DcmTagKey::CommandPriority);
    tag.setUnsignedShort((DcmUnsignedShort)priority);
    commandDataset().insert(tag);
}
