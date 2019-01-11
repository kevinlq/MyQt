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

#ifndef DCMAASSOCIATEREJECT_H
#define DCMAASSOCIATEREJECT_H

#include <QString>
#include "DcmPDUItem.h"
#include "DcmStream.h"
#include "DcmNetApi.h"

/*! Association rejection PDU.
 * This class described a PDU used to reject an association.
 */
class DCM_NET_API DcmAAssociateReject: public DcmPDUItem
{
public:

    /**
     * Construct default association rejection with no reason.
     */
    DcmAAssociateReject();

    /**
     * Construct association rejection PDU.
     * \param result Rejection result (permanent or transient).
     * \param source Rejection source (user or service).
     * \param reason Rejection reason.
     */
    DcmAAssociateReject(DcmAssociationResultType result,
                        DcmAssociationSourceType source,
                        DcmAssociationReasonType reason);
    /**
     * Copy constructor.
     * \param pdu PDU item to be copied.
     */
    DcmAAssociateReject(const DcmAAssociateReject &pdu);

    /**
     * Assignment operator.
     * \param pdu PDU item to be assigned.
     * \return This PDU item.
     */
    DcmAAssociateReject& operator =(const DcmAAssociateReject &pdu);

    /**
     * Clone this PDU item.
     * \return Pointer to a cloned PDU item.
     */
    DcmPDUItem* clone() const;

    /**
     * Destructor.
     */
    ~DcmAAssociateReject();

    /**
     * Returns association rejection result.
     * \return Rejection result.
     */
    DcmAssociationResultType result() const;

    /**
     * Assign association result.
     * \param result Result to be assigned.
     */
    void setResult(DcmAssociationResultType result);

    /**
     * Returns association rejection source.
     * \return Rejection source.
     */
    DcmAssociationSourceType source() const;

    /**
     * Assign rejection source.
     * \param source Rejection source to be set.
     */
    void setSource(DcmAssociationSourceType source);

    /**
     * Returns association rejection reason.
     * \return Rejection reason.
     */
    DcmAssociationReasonType reason() const;

    /**
     * Assign association rejection reason.
     * \param reason Rejection reason to be set.
     */
    void setReason(DcmAssociationReasonType reason);

    /**
     * Returns textual description of association rejection.
     * The returned string can be used to report an error on association
     * rejection.
     * \return Association rejection reason text.
     */
    QString reasonAsString() const;

    /**
     * Returns this PDU item size in bytes.
     * \return This PDU size in bytes.
     */
    DcmSize size() const;

    /**
     * Returns this PDU item content size in bytes.
     * \return This PDU content size.
     */
    DcmSize contentSize() const;

    /**
     * Association rejection is always valid.
     * \returns true.
     */
    bool isValid() const;

    // I/O operations
    DCM_NET_API friend DcmStream& operator <<(DcmStream &stream, const DcmAAssociateReject &pdu);
    DCM_NET_API friend DcmStream& operator >>(DcmStream &stream, DcmAAssociateReject &pdu);

private:

    DcmAssociationResultType m_result;  ///< Association rejection result (permanent or transient).
    DcmAssociationSourceType m_source;  ///< Rejection source.
    DcmAssociationReasonType m_reason;  ///< Rejection reason.
};

DCM_NET_API DcmStream& operator <<(DcmStream &stream, const DcmAAssociateReject &pdu);
DCM_NET_API DcmStream& operator >>(DcmStream &stream, DcmAAssociateReject &pdu);

#endif // DCMAASSOCIATEREJECT_H
