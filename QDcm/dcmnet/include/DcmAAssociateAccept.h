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

#ifndef DCMAASSOCIATEACCEPT_H
#define DCMAASSOCIATEACCEPT_H

#include <QString>
#include "DcmPDUItem.h"
#include "DcmApplicationContext.h"
#include "DcmAcceptedPresentationContext.h"
#include "DcmPDUUserInfo.h"
#include "DcmPDUItemList.h"
#include "DcmStream.h"
#include "DcmNetApi.h"

/*! DICOM association acceptance PDU.
 * This class handles DICOM association acceptance.
 * It contains a list of accepted abstract syntaxes
 * along with chosen transfer syntaxes to be used in
 * DIMSE transactions.
 */
class DCM_NET_API DcmAAssociateAccept: public DcmPDUItem
{
public:

    /**
     * Construct association acception PDU.
     * Constructed object will be invalid and has to be populated
     * with corresponding information.
     */
    DcmAAssociateAccept();

    /**
     * Copy constructor.
     * \param pdu PDU item to be copied.
     */
    DcmAAssociateAccept(const DcmAAssociateAccept &pdu);

    /**
     * Assignment operator.
     * \param pdu PDU to be assigned.
     * \return This PDU item.
     */
    DcmAAssociateAccept& operator =(const DcmAAssociateAccept &pdu);

    /**
     * Returns a pointer to this PDU item cloned.
     * \return This PDU item clone pointer.
     */
    DcmPDUItem* clone() const;

    /**
     * Destructor.
     */
    ~DcmAAssociateAccept();

    /**
     * Returns communication protocol version.
     * \return Protocol version.
     */
    DcmUnsignedShort protocolVersion() const;

    /**
     * Assign protocol version.
     * \param version Protocol version to be set.
     */
    void setProtocolVersion(DcmUnsignedShort version);

    /**
     * Returns called application entity.
     * \return Called AE.
     */
    QString calledAE() const;

    /**
     * Assign called application entity.
     * \param ae AE to be set.
     */
    void setCalledAE(const QString &ae);

    /**
     * Returns calling application entry.
     * \return Calling AE.
     */
    QString callingAE() const;

    /**
     * Assign calling application entity.
     * \param ae Calling AE to be set.
     */
    void setCallingAE(const QString &ae);

    /**
     * Returns application context.
     * \return Application context.
     */
    DcmApplicationContext applicationContext() const;

    /**
     * Assign application context.
     * \param ac Application context to be set.
     */
    void setApplicationContext(const DcmApplicationContext &ac);

    /**
     * Returns the number of accepted presentation contexts encoded in
     * this association acceptance.
     * \return Number of accepted presentation contexts.
     */
    int numberOfAcceptedPresentationContexts() const;

    /**
     * Returns a pointer to accepted presentation context at specified index position.
     * \param index Accepted presentation context index.
     * \return Pointer to accepted presentation context or null if not found.
     */
    DcmAcceptedPresentationContext* acceptedPresentationContextAt(int index) const;

    /**
     * Add accepted presentation context.
     * \param apc Accepted presentation context to be added.
     */
    void addAcceptedPresentationContext(const DcmAcceptedPresentationContext &apc);

    /**
     * Add accepted presentation context and retain the pointer.
     * The context will be deleted along with this PDU.
     * \param apcPtr Pointer to accepted presentation context to be added.
     */
    void addAndRetainAcceptedPresentationContext(DcmAcceptedPresentationContext *apcPtr);

    /**
     * Returns user's info PDU.
     * \return User's info PDU.
     */
    DcmPDUUserInfo userInfoPDU() const;

    /**
     * Assign user's info PDU.
     * \param pdu User's info PDU to be set.
     */
    void setUserInfoPDU(const DcmPDUUserInfo &pdu);

    /**
     * Returns this PDU item size in bytes.
     * \return This PDU item size.
     */
    DcmSize size() const;

    /**
     * Returns this PDU item content size in bytes.
     * \return This PDU item content size.
     */
    DcmSize contentSize() const;

    /**
     * Tells whether this PDU item is valid.
     * The item is valid if all inset PDUs are valid and
     * called/calling AEs are not empty.
     * \return true if this PDU is valid.
     */
    bool isValid() const;

    // I/O operations
    DCM_NET_API friend DcmStream& operator <<(DcmStream &stream, const DcmAAssociateAccept &pdu);
    DCM_NET_API friend DcmStream& operator >>(DcmStream &stream, DcmAAssociateAccept &pdu);

private:

    DcmUnsignedShort m_protocolVersion; ///< Protocol version.
    QString m_calledAE;     ///< Called application entity.
    QString m_callingAE;    ///< Calling application entity.
    DcmApplicationContext m_applicationContext; ///< Application context.
    DcmPDUItemList m_acceptedPesentationContextsList;   ///< List of accepted presentation contexts.
    DcmPDUUserInfo m_userInfoPDU;   ///< User info PDU.
};

DCM_NET_API DcmStream& operator <<(DcmStream &stream, const DcmAAssociateAccept &pdu);
DCM_NET_API DcmStream& operator >>(DcmStream &stream, DcmAAssociateAccept &pdu);

#endif // DCMAASSOCIATEACCEPT_H
