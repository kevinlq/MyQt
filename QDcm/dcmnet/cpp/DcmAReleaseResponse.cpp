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

#include "DcmAReleaseResponse.h"

DcmAReleaseResponse::DcmAReleaseResponse()
    : DcmPDUItem(DcmPDUType_AReleaseRp)
{
}

DcmAReleaseResponse::DcmAReleaseResponse(const DcmAReleaseResponse &pdu)
    : DcmPDUItem(pdu)
{
}

DcmAReleaseResponse& DcmAReleaseResponse::operator =(const DcmAReleaseResponse &pdu)
{
    if (this != &pdu) {
        DcmPDUItem::operator =(pdu);
    }
    return *this;
}

DcmPDUItem* DcmAReleaseResponse::clone() const
{
    return new DcmAReleaseResponse(*this);
}

DcmAReleaseResponse::~DcmAReleaseResponse()
{
}

DcmSize DcmAReleaseResponse::size() const
{
    return 6 + contentSize();
}

DcmSize DcmAReleaseResponse::contentSize() const
{
    return 4;
}

bool DcmAReleaseResponse::isValid() const
{
    return true;
}

DcmStream& operator <<(DcmStream &stream, const DcmAReleaseResponse &pdu)
{
    char c[2] = {DcmPDUType_AReleaseRp, 0};
    DcmSize length = pdu.contentSize();

    stream.dataStream().writeRawData(c, 2);
    stream.writePDUSize32(length);
    length = 0;
    stream.writePDUSize32(length);

    return stream;
}

DcmStream& operator >>(DcmStream &stream, DcmAReleaseResponse &pdu)
{
    char c[2];

    stream.dataStream().readRawData(c, 2);
    if (c[0] == DcmPDUType_AReleaseRp && c[1] == 0) {
        DcmSize length = stream.readPDUSize32();
        stream.dataStream().skipRawData(length);
    }

    return stream;
}

