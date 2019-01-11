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

#ifndef DCMACCEPTEDPRESENTATIONCONTEXT_H
#define DCMACCEPTEDPRESENTATIONCONTEXT_H

#include "DcmPDUItem.h"
#include "DcmTransferSyntax.h"
#include "DcmStream.h"
#include "DcmNetApi.h"

/*! DICOM accepted presentation context.
 * Accepted context contains only one transfer syntax to
 * be used for a given abstract syntax.
 */
class DCM_NET_API DcmAcceptedPresentationContext: public DcmPDUItem
{
public:

    static const DcmAcceptedPresentationContext Invalid;    ///< Invalid context.

    /**
     * Reason to accept or reject presentation context.
     */
    typedef enum {
        Reason_Acceptance = 0,
        Reason_UserRejection = 1,
        Reason_NoReason = 2,
        Reason_AbstractSyntaxNotSupported = 3,
        Reason_TransferSyntaxNotSupported = 4
    } Reason;


    /**
     * Construct invalid accepted presentation context.
     */
    DcmAcceptedPresentationContext();

    /**
     * Construct accepted presentation context.
     * If accepted transfer syntax is invalid, this means that
     * presentation context has not been accepted.
     * \param ts Accepted transfer syntax.
     * \param reason Acceptane or rejectance reason.
     * \param id Presentation context id.
     */
    DcmAcceptedPresentationContext(const DcmTransferSyntax &ts,
                                   DcmAcceptedPresentationContext::Reason reason,
                                   int id = 0);

    /**
     * Copy constructor.
     * \param pc Accepted presentation context to be copied.
     */
    DcmAcceptedPresentationContext(const DcmAcceptedPresentationContext &pc);

    /**
     * Assignment operator.
     * \param pc Accepted presentation context to be assigned.
     * \return This accepted presentation context.
     */
    DcmAcceptedPresentationContext& operator =(const DcmAcceptedPresentationContext &pc);

    /**
     * Clone this PDU item.
     * \return Pointer to cloned PDU item.
     */
    DcmPDUItem* clone() const;

    /**
     * Destructor.
     */
    ~DcmAcceptedPresentationContext();

    /**
     * Returns accepted transfer syntax.
     * \return Transfer syntax.
     */
    DcmTransferSyntax transferSyntax() const;

    /**
     * Returns acceptance or rejectance reason.
     * \return Accep/reject reason.
     */
    DcmAcceptedPresentationContext::Reason reason() const;

    /**
     * Returns presentation context id.
     * \return Presentation context id.
     */
    int id() const;

    /**
     * Returns this PDU item content size in bytes.
     * \return PDU content size.
     */
    DcmSize contentSize() const;

    /**
     * Tells whether this accepted presentation context is valid.
     * It is valid if transfer syntax is valid.
     * \return true if this accepted presentation context is valid.
     */
    bool isValid() const;

    /**
     * Tells whether this presentation context has been actually accepted.
     * This method check the 'reason' fiels of the accepted context.
     * \return true if presentation context has been accepted.
     */
    bool isAccepted() const;

    // I/O operations
    DCM_NET_API friend DcmStream& operator <<(DcmStream &stream, const DcmAcceptedPresentationContext &pdu);
    DCM_NET_API friend DcmStream& operator >>(DcmStream &stream, DcmAcceptedPresentationContext &pdu);

private:

    DcmUnsignedByte m_id;   ///< Presentation context id.
    DcmAcceptedPresentationContext::Reason m_reason;    ///< Acceptance/rejection reason.
    DcmTransferSyntax m_transferSyntax; ///< Accepted transfer syntax.
};

DCM_NET_API DcmStream& operator <<(DcmStream &stream, const DcmAcceptedPresentationContext &pdu);
DCM_NET_API DcmStream& operator >>(DcmStream &stream, DcmAcceptedPresentationContext &pdu);

#endif // DCMACCEPTEDPRESENTATIONCONTEXT_H
