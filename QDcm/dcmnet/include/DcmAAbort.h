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

#ifndef DCMAABORT_H
#define DCMAABORT_H

#include "DcmNetApi.h"
#include "DcmPDUItem.h"
#include "DcmStream.h"

/*! Association abort PDU item.
 * This PDU item represents association abortion.
 */
class DCM_NET_API DcmAAbort: public DcmPDUItem
{
public:

    /**
     * Construct AAbort PDU.
     */
    DcmAAbort();

    /**
     * Construct AAbort PDU.
     * \param source Abortion source.
     * \param reason Abortion reason.
     */
    DcmAAbort(DcmAssociationSourceType source,
              DcmAssociationReasonType reason = DcmAssociationReasonType_NoReason);

    /**
     * Copy constructor.
     * \param pdu AAbort PDU to be copied.
     */
    DcmAAbort(const DcmAAbort &pdu);

    /**
     * Assignment operator.
     * \param pdu AAbort PDU to ne set.
     * \return This PDU.
     */
    DcmAAbort& operator =(const DcmAAbort &pdu);

    /**
     * Clone this PDU.
     * \return Pointer to cloned PDU.
     */
    DcmPDUItem* clone() const;

    /**
     * Destructor.
     */
    ~DcmAAbort();

    /**
     * Returns abortion source.
     * \return Abortion source.
     */
    DcmAssociationSourceType source() const;

    /**
     * Assign abortion source.
     * \param src Abortion source to be set.
     */
    void setSource(DcmAssociationSourceType src);

    /**
     * Returns abortion reason.
     * \return Abort reason.
     */
    DcmAssociationReasonType reason() const;

    /**
     * Assign abortion reason.
     * \param r Reason to be set.
     */
    void setReason(DcmAssociationReasonType r);

    /**
     * Returns this PDU size in bytes.
     * \return PDU size in bytes.
     */
    DcmSize size() const;

    /**
     * Returns this PDU content size in bytes.
     * \return PDU content size in bytes.
     */
    DcmSize contentSize() const;

    /**
     * Tells whether this PDU object is valid.
     * \return True if this PDU is valid.
     */
    bool isValid() const;

    // I/O operations
    DCM_NET_API friend DcmStream& operator <<(DcmStream &stream, const DcmAAbort &pdu);
    DCM_NET_API friend DcmStream& operator >>(DcmStream &stream, DcmAAbort &pdu);

private:

    DcmAssociationSourceType m_source;  ///< Association abort source.
    DcmAssociationReasonType m_reason;  ///< Association abort reason.
};

/**
 * Write AAbort PDU to stream.
 * \param stream DICOM stream.
 * \param pdu AAbort PDU to be written.
 * \return Stream.
 */
DCM_NET_API DcmStream& operator <<(DcmStream &stream, const DcmAAbort &pdu);

/**
 * Read AAbort PDU from stream.
 * \param stream DICOM stream.
 * \param pdu AAbort PDU to be altered by reading.
 * \return Stream.
 */
DCM_NET_API DcmStream& operator >>(DcmStream &stream, DcmAAbort &pdu);

#endif // DCMAABORT_H
