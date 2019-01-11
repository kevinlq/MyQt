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

#ifndef DCMAASSOCIATEREQUEST_H
#define DCMAASSOCIATEREQUEST_H

#include "DcmNetApi.h"
#include "DcmPDUItem.h"
#include "DcmStream.h"
#include "DcmApplicationContext.h"
#include "DcmPresentationContext.h"
#include "DcmPDUUserInfo.h"

/*! Association request PDU item.
 * This class represents a DICOM association request packet.
 * This packed contains some inset PDU items, like a list of
 * presentation contexts to negociate.
 */
class DCM_NET_API DcmAAssociateRequest: public DcmPDUItem
{
public:

    /**
     * Construct association request.
     * The constructed request object is invalid and has to be
     * populated with corresponding data.
     */
    DcmAAssociateRequest();

    /**
     * Copy constructor.
     * \param pdu PDU to be copied.
     */
    DcmAAssociateRequest(const DcmAAssociateRequest &pdu);

    /**
     * Assignment operator.
     * \param pdu PDU to be assigned.
     * \return This PDU.
     */
    DcmAAssociateRequest& operator =(const DcmAAssociateRequest &pdu);

    /**
     * Clone this PDU item.
     * \return Pointer to a cloned PDU.
     */
    DcmPDUItem* clone() const;

    /**
     * Destructor.
     */
    ~DcmAAssociateRequest();

    /**
     * Returns called applocation entity.
     * \return Called AE.
     */
    QString calledAE() const;

    /**
     * Assign called application entity.
     * \param ae Called AE to be set.
     */
    void setCalledAE(const QString &ae);

    /**
     * Returns calling application entity.
     * \return Calling AE.
     */
    QString callingAE() const;

    /**
     * Assign calling application entity.
     * \param ae Calling AE to be set.
     */
    void setCallingAE(const QString &ae);

    /**
     * Returns application context set in this
     * association request.
     * \return Application context.
     */
    DcmApplicationContext applicationContext() const;

    /**
     * Assign application context.
     * \param ac Application context to be set.
     */
    void setApplicationContext(const DcmApplicationContext &ac);

    /**
     * Returns number of presentation contexts present in
     * this association request.
     * \return Number of presentation contexts.
     */
    int numberOfPresentationContexts() const;

    /**
     * Returns a pointer to a presentation context
     * at specified index in the list.
     * \param index Presentation context index.
     * \return Pointer to the presentation context or null if invalid index.
     */
    DcmPresentationContext* presentationContextAt(int index) const;

    /**
     * Add presentation context to the list.
     * \param pc Presentation context to be added.
     */
    void addPresentationContext(const DcmPresentationContext &pc);

    /**
     * Add presentation context and retain the pointer.
     * The presentation context will be deleted along with this
     * association object.
     * \param pcPtr Pointer to a preentation context to be added.
     */
    void addAndRetainPresentationContext(DcmPresentationContext *pcPtr);

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
     * Returns protocol version number.
     * \return Protocol version number.
     */
    DcmUnsignedShort protocolVersion() const;

    /**
     * Assign protocol version number.
     * \param vesrion Protocol version to be set.
     */
    void setProtocolVersion(DcmUnsignedShort version);

    /**
     * Returns this PSU size in bytes.
     * \return This PDU size in bytes.
     */
    DcmSize size() const;

    /**
     * Returns this PDU content size in bytes.
     * \return This PDU content size.
     */
    DcmSize contentSize() const;

    /**
     * Tells whether this PDU is valid.
     * The association request is valid if all insed PDUs are valid,
     * and the application entities are not empty.
     */
    bool isValid() const;

    // I/O operations
    DCM_NET_API friend DcmStream& operator <<(DcmStream &stream, const DcmAAssociateRequest &pdu);
    DCM_NET_API friend DcmStream& operator >>(DcmStream &stream, DcmAAssociateRequest &pdu);

private:

    DcmUnsignedShort m_protocolVersion; ///< Protocol version, normally 0x0100.
    QString m_calledAE;     ///< Called application entity.
    QString m_callingAE;    ///< Calling application entity.
    DcmApplicationContext m_applicationContext; ///< Application context.
    DcmPDUItemList m_presentationContextList;   ///< List of presentation conexts.
    DcmPDUUserInfo m_userInfoPDU;   ///< User's info PDU.
};

DCM_NET_API DcmStream& operator <<(DcmStream &stream, const DcmAAssociateRequest &pdu);
DCM_NET_API DcmStream& operator >>(DcmStream &stream, DcmAAssociateRequest &pdu);

#endif // DCMAASSOCIATEREQUEST_H
