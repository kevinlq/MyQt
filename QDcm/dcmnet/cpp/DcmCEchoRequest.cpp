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

#include "DcmAbstractSyntax.h"
#include "DcmCEchoRequest.h"

DcmCEchoRequest::DcmCEchoRequest()
    : DcmDimseRequest(DcmAbstractSyntax::Verification.uid(), DcmCommandType_CEchoRequest)
{
}

DcmCEchoRequest::DcmCEchoRequest(const DcmDataset &dataset)
    : DcmDimseRequest(dataset)
{
}

DcmCEchoRequest::DcmCEchoRequest(int id)
    : DcmDimseRequest(DcmAbstractSyntax::Verification.uid(), DcmCommandType_CEchoRequest, id)
{

}

DcmCEchoRequest::DcmCEchoRequest(const DcmCEchoRequest &message)
    : DcmDimseRequest(message)
{
}

DcmCEchoRequest& DcmCEchoRequest::operator =(const DcmCEchoRequest &message)
{
    if (this != &message) {
        DcmDimseRequest::operator =(message);
    }
    return *this;
}

DcmDimseMessage* DcmCEchoRequest::clone() const
{
    return new DcmCEchoRequest(*this);
}
