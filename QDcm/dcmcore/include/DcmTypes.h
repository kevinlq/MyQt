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

#ifndef DCMTYPES_H
#define DCMTYPES_H

#include <qglobal.h>

typedef qint8   DcmSignedByte;
typedef quint8  DcmUnsignedByte;
typedef qint16  DcmSignedShort;
typedef quint16 DcmUnsignedShort;
typedef qint32  DcmSignedLong;
typedef quint32 DcmUnsignedLong;
typedef float   DcmFloat;
typedef double  DcmDouble;

typedef DcmUnsignedLong DcmHash;

typedef quint32 DcmSize;
const DcmSize DcmSize_Undefined = 0xFFFFFFFF;   ///< Used for unknown size cases.

/**
 * DICOM value representations.
 */
typedef enum {
    DcmVrKey_CS,
    DcmVrKey_SH,
    DcmVrKey_LO,
    DcmVrKey_ST,
    DcmVrKey_LT,
    DcmVrKey_UT,
    DcmVrKey_AE,
    DcmVrKey_PN,
    DcmVrKey_UI,
    DcmVrKey_DA,
    DcmVrKey_TM,
    DcmVrKey_DT,
    DcmVrKey_AS,
    DcmVrKey_IS,
    DcmVrKey_DS,
    DcmVrKey_SS,
    DcmVrKey_US,
    DcmVrKey_SL,
    DcmVrKey_UL,
    DcmVrKey_AT,
    DcmVrKey_FL,
    DcmVrKey_FD,
    DcmVrKey_OB,
    DcmVrKey_OW,
    DcmVrKey_OF,
    DcmVrKey_SQ,
    DcmVrKey_UN,

    /* The following is not a part of DICOM specification */
    DcmVrKey_None,      ///< Some tags cannot have any VR. Those have NONE VR set.
    DcmVrKey_Invalid    ///< Custom VR key to identify invalid VRs.
} DcmVrKey;

/// The following is used to specify unknown multiplicity of a tag
const int DcmMultiplicity_Unknown = 0;

/**
 * Endianess.
 */
typedef enum {
    DcmEndianess_LittleEndian,
    DcmEndianess_BigEndian
} DcmEndianess;

/**
 * Encoding type.
 */
typedef enum {
    DcmEncoding_Explicit,
    DcmEncoding_Implicit
} DcmEncoding;

/**
 * Protocol data units.
 * These are constnts used to identify different elements
 * of the DICOM communication protocol.
 */
typedef enum {
    DcmPDUType_AAssociateRq                         = 0x01,
    DcmPDUType_AAssociateAc                         = 0x02,
    DcmPDUType_AAssociateRj                         = 0x03,
    DcmPDUType_PData                                = 0x04,
    DcmPDUType_AReleaseRq                           = 0x05,
    DcmPDUType_AReleaseRp                           = 0x06,
    DcmPDUType_AAbort                               = 0x07,
    DcmPDUType_ApplicationContext                   = 0x10,
    DcmPDUType_PresentationContext                  = 0x20,
    DcmPDUType_AcceptedPresentationContext          = 0x21,
    DcmPDUType_AbstractSyntax                       = 0x30,
    DcmPDUType_TransferSyntax                       = 0x40,
    DcmPDUType_UserInfo                             = 0x50,
    DcmPDUType_PDUMaxLength                         = 0x51,
    DcmPDUType_ImplementationClassUID               = 0x52,
    DcmPDUType_AsynchronousOperationsWindow         = 0x53,
    DcmPDUType_ScpScuRoleSelection                  = 0x54,
    DcmPDUType_ImplementationVersionName            = 0x55,
    DcmPDUType_SOPClassExtendedNegotiation          = 0x56,
    DcmPDUType_SOPClassCommonExtendedNegotiation    = 0x57,
    DcmPDUType_UserIdentityNegotiation              = 0x58,
    DcmPDUType_UserIdentityNegotiationAc            = 0x59,

    DcmPDUType_Invalid                              = 0xFF  ///< Non-DICOM PDU item, used internally only.
} DcmPDUType;

/**
 * DIMSE commands
 */
typedef enum {
    DcmCommandType_None                 = 0x0000,
    DcmCommandType_CStoreRequest        = 0x0001,
    DcmCommandType_CStoreResponse       = 0x8001,
    DcmCommandType_CGetRequest          = 0x0010,
    DcmCommandType_CGetResponse         = 0x8010,
    DcmCommandType_CFindRequest         = 0x0020,
    DcmCommandType_CFindResponse        = 0x8020,
    DcmCommandType_CMoveRequest         = 0x0021,
    DcmCommandType_CMoveResponse        = 0x8021,
    DcmCommandType_CEchoRequest         = 0x0030,
    DcmCommandType_CEchoResponse        = 0x8030,
    DcmCommandType_CCancelRequest       = 0x0FFF,

    DcmCommandType_NEventReportRequest  = 0x0100,
    DcmCommandType_NEventReportResponse = 0x8100,
    DcmCommandType_NGetRequest          = 0x0110,
    DcmCommandType_NGetResponse         = 0x8110,
    DcmCommandType_NActionRequest       = 0x0130,
    DcmCommandType_NActionResponse      = 0x8130,
    DcmCommandType_NCreateRequest       = 0x0140,
    DcmCommandType_NCreateResponse      = 0x8140,
    DcmCommandType_NDeleteRequest       = 0x0150,
    DcmCommandType_NDeleteResponse      = 0x8150
} DcmCommandType;

/**
 * DIMSE message priority.
 */
typedef enum {
    DcmPriorityType_Medium  = 0x0000,
    DcmPriorityType_High    = 0x0001,
    DcmPriorityType_Low     = 0x0002
} DcmPriorityType;

/**
 * Assiciation rejection result.
 */
typedef enum {
    DcmAssociationResultType_RejectPermanent = 1,
    DcmAssocuationResultType_RejectTransient = 2
} DcmAssociationResultType;

/**
 * Association source.
 */
typedef enum {
    DcmAssociationSourceType_ServiceUser = 0,
    DcmAssociationSourceType_ServiceProvider = 2
} DcmAssociationSourceType;

/**
 * Association rejection or abort reason.
 */
typedef enum {
    DcmAssociationReasonType_NoReason = 1,
    DcmAssociationReasonType_ApplicationContextNotSupported = 2,
    DcmAssociationReasonType_CallingAENotRecognized = 3,
    DcmAssociationReasonType_CalledAENotRecognized = 7
} DcmAssociationReasonType;

#endif // DCMTYPES_H
