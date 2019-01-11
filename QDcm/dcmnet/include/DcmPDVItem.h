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

#ifndef DCMPDVITEM_H
#define DCMPDVITEM_H

#include <QByteArray>
#include "DcmTypes.h"
#include "DcmNetApi.h"

/*! PDV data item.
 * This class represents a single data value encoded in
 * P-Data-TF PDU. PDV is actually a raw binary data chunk
 * with some additional flags added, telling
 * <li>Presentation context id used to decode the data
 * <li>Whether this data is a command
 * <li>Whether this chunk is the last one in a stream.
 */
class DCM_NET_API DcmPDVItem
{
public:

    /**
     * Construct PDV item.
     * \param contextId Presentation context id.
     * \param command Is it a command flag.
     * \param terminating Is this PDV termination one.
     */
    DcmPDVItem(int contextId, bool command, bool terminating);

    /**
     * Copy constructor.
     * \param pdv PDV item to be copied.
     */
    DcmPDVItem(const DcmPDVItem &pdv);

    /**
     * Assignment operator.
     * \param pdv PDV item to be assigned.
     */
    DcmPDVItem& operator =(const DcmPDVItem &pdv);

    /**
     * Returns presentation context id.
     * \return Presentation context id.
     */
    int presentationContextId() const;

    /**
     * Assign presentation context id.
     * \param id Presentation context id to be set.
     */
    void setPresentationContextId(int id);

    /**
     * Tells whether this PDV is a command.
     * \return true if this PDV encodes a command.
     */
    bool isCommand() const;

    /**
     * Assign command flag.
     * \param flag Command flag to be set.
     */
    void setCommand(bool flag);

    /**
     * Tells whether this PDV is terminating one.
     * \return true if this PDV is terminating.
     */
    bool isTerminating() const;

    /**
     * Assign terminating flag.
     * \param flag Terminating flag to be set.
     */
    void setTerminating(bool flag);

    /**
     * Returns enoded raw data size in bytes.
     * \return Encoded data size.
     */
    DcmSize dataSize() const;

    /**
     * Returns a constant pointer to the raw data.
     * \return Constant pointer to the raw data.
     */
    const char *constData() const;

    /**
     * Returns pointer to the raw data. The data can be
     * modified via the pointer returned.
     * \return Pointer to encoded raw data.
     */
    char *data();

    /**
     * Returns reference to PDV byte array.
     * \return PDV byte array reference.
     */
    QByteArray& byteArray();

    /**
     * Assign PDV data byte array.
     * \param data Data to be set.
     */
    void setByteArray(const QByteArray &data);

    /**
     * Clear all raw data.
     * This erases internal buffer discarding all the data.
     */
    void clear();

private:

    int m_presentationContextId;    ///< Id of the presentation context as negociated in association.
    bool m_command;     ///< Command flag.
    bool m_terminating; ///< Termination flag.
    QByteArray m_byteArray; ///< Encoded data.
};

#endif // DCMPDVITEM_H
