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
#include "DcmCEchoResponse.h"

DcmCEchoResponse::DcmCEchoResponse()
    : DcmDimseResponse()
{
    setServiceClassUID(DcmAbstractSyntax::Verification.uid());
    setCommand(DcmCommandType_CEchoResponse);
    setMessageId(0);
    setStatus(DcmDimseResponse::Status_Success);
}

DcmCEchoResponse::DcmCEchoResponse(const DcmDataset &dataset)
    : DcmDimseResponse(dataset)
{
}

DcmCEchoResponse::DcmCEchoResponse(const DcmCEchoRequest &request)
    : DcmDimseResponse(request)
{
}

DcmCEchoResponse::DcmCEchoResponse(const DcmCEchoResponse &message)
    : DcmDimseResponse(message)
{
}

DcmCEchoResponse& DcmCEchoResponse::operator =(const DcmCEchoResponse &message)
{
    if (this != &message) {
        DcmDimseResponse::operator =(message);
    }
    return *this;
}

DcmDimseMessage* DcmCEchoResponse::clone() const
{
    return new DcmCEchoResponse(*this);
}
