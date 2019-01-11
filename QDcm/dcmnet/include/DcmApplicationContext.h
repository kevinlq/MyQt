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

#ifndef DCMAPPLICATIONCONTEXT_H
#define DCMAPPLICATIONCONTEXT_H

#include "DcmNetApi.h"
#include "DcmPDUItem.h"
#include "DcmStream.h"

/*! DICOM association application context.
 * There is only one applucation context currently defined -
 * the default one 1.2.840.10008.3.1.1.1
 */
class DCM_NET_API DcmApplicationContext: public DcmPDUItem
{
public:

    static const DcmApplicationContext Invalid; ///< Invalid application context.
    static const DcmApplicationContext Default; ///< 1.2.840.10008.3.1.1.1

    /**
     * Construct invalid application context.
     */
    DcmApplicationContext();

    /**
     * Construct application context.
     * \param uid Application context UID.
     */
    DcmApplicationContext(const QString &uid);

    /**
     * Copy constructor.
     * \param applicationContext Application context to be copied.
     */
    DcmApplicationContext(const DcmApplicationContext &applicationContext);

    /**
     * Assignment operator.
     * \param applicationContext Application context to be assigned.
     * \return This application context.
     */
    DcmApplicationContext& operator =(const DcmApplicationContext &applicationContext);

    /**
     * Clone this application context PDU.
     * \return Pointer to cloned PDU.
     */
    DcmPDUItem* clone() const;

    /**
     * Destructor.
     */
    ~DcmApplicationContext();

    /**
     * Returns application context UID.
     * \return UID.
     */
    QString uid() const;

    /**
     * Compare this application context with another one.
     * \param applicationContext Context to compare with.
     * \return true if contexts are equal.
     */
    bool operator ==(const DcmApplicationContext &applicationContext);

    /**
     * Compare this application context with another one.
     * \return true if contexts are different.
     */
    bool operator !=(const DcmApplicationContext &applicationContext);

    /**
     * Returns this PDU content size in bytes.
     * \return PDU content size.
     */
    DcmSize contentSize() const;

    /**
     * Tells whether this PDU is valid.
     * \return true if this PDU is valid.
     */
    bool isValid() const;

    // I/O operations
    DCM_NET_API friend DcmStream& operator <<(DcmStream &stream, const DcmApplicationContext &pdu);
    DCM_NET_API friend DcmStream& operator >>(DcmStream &stream, DcmApplicationContext &pdu);

private:

    QString m_uid;  ///< Application context UID.
};

DCM_NET_API DcmStream& operator <<(DcmStream &stream, const DcmApplicationContext &pdu);
DCM_NET_API DcmStream& operator >>(DcmStream &stream, DcmApplicationContext &pdu);

#endif // DCMAPPLICATIONCONTEXT_H
