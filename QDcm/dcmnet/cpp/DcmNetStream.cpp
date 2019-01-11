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

#include <QDebug>
#include "DcmAbstractSyntax.h"
#include "DcmTransferSyntax.h"
#include "DcmApplicationContext.h"
#include "DcmPresentationContext.h"
#include "DcmAcceptedPresentationContext.h"
#include "DcmPDUUserInfo.h"
#include "DcmPDUMaxLength.h"
#include "DcmPDUImplementationClassUID.h"
#include "DcmPDUImplementationVersionName.h"
#include "DcmAAssociateRequest.h"
#include "DcmAAssociateAccept.h"
#include "DcmAAssociateReject.h"
#include "DcmAReleaseRequest.h"
#include "DcmAReleaseResponse.h"
#include "DcmAAbort.h"
#include "DcmPDataTf.h"
#include "DcmNetStream.h"

DcmNetStream::DcmNetStream(DcmStream &stream)
{
    m_streamPtr = &stream;
}

void DcmNetStream::writePDUItem(const DcmPDUItem &item)
{
    DcmPDUType type = item.type();

#define CASE(t,c)   \
    case t: {   \
        const c pdu = dynamic_cast<const c&>(item); \
        *m_streamPtr << pdu;    \
        break;  \
    }

    switch(type) {
    CASE(DcmPDUType_AbstractSyntax, DcmAbstractSyntax);
    CASE(DcmPDUType_TransferSyntax, DcmTransferSyntax);
    CASE(DcmPDUType_ApplicationContext, DcmApplicationContext);
    CASE(DcmPDUType_PresentationContext, DcmPresentationContext);
    CASE(DcmPDUType_AcceptedPresentationContext, DcmAcceptedPresentationContext);
    CASE(DcmPDUType_UserInfo, DcmPDUUserInfo);
    CASE(DcmPDUType_PDUMaxLength, DcmPDUMaxLength);
    CASE(DcmPDUType_ImplementationClassUID, DcmPDUImplementationClassUID);
    CASE(DcmPDUType_ImplementationVersionName, DcmPDUImplementationVersionName);
    CASE(DcmPDUType_AAssociateRq, DcmAAssociateRequest);
    CASE(DcmPDUType_AAssociateAc, DcmAAssociateAccept);
    CASE(DcmPDUType_AAssociateRj, DcmAAssociateReject);
    CASE(DcmPDUType_AReleaseRq, DcmAReleaseRequest);
    CASE(DcmPDUType_AReleaseRp, DcmAReleaseResponse);
    CASE(DcmPDUType_AAbort, DcmAAbort);
    CASE(DcmPDUType_PData, DcmPDataTf);
    default:
        qWarning() << "Unknown PDU type" << type;
        break;
    }

#undef CASE
}

DcmPDUItem* DcmNetStream::readPDUItem()
{
    DcmPDUType type = DcmPDUType_Invalid;

    // Peek one byte
    if (m_streamPtr->dataStream().device()->peek((char*)&type, 1) != 1) {
        return 0;
    }

    DcmPDUItem *item = 0;

#define CASE(t,c)   \
    case t: {   \
        c pdu;  \
        *m_streamPtr >> pdu;    \
        item = pdu.clone(); \
    }

    switch (type) {
    CASE(DcmPDUType_AbstractSyntax, DcmAbstractSyntax);
    CASE(DcmPDUType_TransferSyntax, DcmTransferSyntax);
    CASE(DcmPDUType_ApplicationContext, DcmApplicationContext);
    CASE(DcmPDUType_PresentationContext, DcmPresentationContext);
    CASE(DcmPDUType_AcceptedPresentationContext, DcmAcceptedPresentationContext);
    CASE(DcmPDUType_UserInfo, DcmPDUUserInfo);
    CASE(DcmPDUType_PDUMaxLength, DcmPDUMaxLength);
    CASE(DcmPDUType_ImplementationClassUID, DcmPDUImplementationClassUID);
    CASE(DcmPDUType_ImplementationVersionName, DcmPDUImplementationVersionName);
    CASE(DcmPDUType_AAssociateRq, DcmAAssociateRequest);
    CASE(DcmPDUType_AAssociateAc, DcmAAssociateAccept);
    CASE(DcmPDUType_AAssociateRj, DcmAAssociateReject);
    CASE(DcmPDUType_AReleaseRq, DcmAReleaseRequest);
    CASE(DcmPDUType_AReleaseRp, DcmAReleaseResponse);
    CASE(DcmPDUType_AAbort, DcmAAbort);
    CASE(DcmPDUType_PData, DcmPDataTf);
    default:
        qWarning() << "Unknown PDU type" << type;
        break;
    }

#undef CASE

    return item;
}
