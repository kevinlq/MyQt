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

#ifndef DCMDIMSEMESSAGE_H
#define DCMDIMSEMESSAGE_H

#include <QString>
#include "DcmTypes.h"
#include "DcmDataset.h"
#include "DcmNetApi.h"

/*! Base class for DIMSE messages.
 * DIMSE message is composed of command set of DICOM tags,
 * plus it may have some additional data attached.
 */
class DCM_NET_API DcmDimseMessage
{
public:

    /**
     * Data presence flag.
     */
    typedef enum {
        Data_Present    = 0x0000,   ///< Some data is attached to this DIMSE message.
        Data_NotPresent = 0x0101    ///< No data in this DIMSE message.
    } Data;

    /**
     * Construct an empty DIMSE message with no data.
     */
    DcmDimseMessage();

    /**
     * Construct DIMSE message from provided command dataset.
     * \param dataset DICOM dataset.
     */
    DcmDimseMessage(const DcmDataset &dataset);

    /**
     * Construct DIMSE message.
     * The message constructed has its data flag disabled by default.
     * \param serviceClassUID Service class UID.
     * \param command DIMSE command.
     * \param Message id.
     */
    DcmDimseMessage(const QString &serviceClassUID, DcmCommandType command, int id);

    /**
     * Copy constructor.
     * \param message DIMSE message to be copied.
     */
    DcmDimseMessage(const DcmDimseMessage &message);

    /**
     * Assignment operator.
     * \param message DIMSE message to be assigned.
     * \return This DIMSE message.
     */
    DcmDimseMessage& operator =(const DcmDimseMessage &message);

    /**
     * Clone this DIMSE message.
     * \return Pointer to DIMSE message clone.
     */
    DcmDimseMessage* clone() const;

    /**
     * Destructor.
     */
    virtual ~DcmDimseMessage();

    /**
     * Returns service class UID encoded in this DIMSE message.
     * If no corresponding tag found, an empty string is returned.
     * \return Service class UID.
     */
    QString serviceClassUID() const;

    /**
     * Assign service class UID.
     * \param uid UID to be set.
     */
    void setServiceClassUID(const QString &uid);

    /**
     * Returns this DIMSE message id number.
     * \return Message id.
     */
    int messageId() const;

    /**
     * Assign this DIMSE message id number.
     * \param id Id to be set.
     */
    void setMessageId(int id);

    /**
     * Returns command encoded in this DIMSE message.
     * If no corresponding tag found, None command is returned.
     * \return DIMSE sommand.
     */
    DcmCommandType command() const;

    /**
     * Assign DIMSE command.
     * \param cmd Command to be set.
     */
    void setCommand(DcmCommandType cmd);

    /**
     * Tells whether this DIMSE message has data attached.
     * \return true if there are additional data attached.
     */
    bool hasData() const;

    /**
     * Assign the data presence flag.
     * \param flag Data presence flag.
     */
    void setHasData(bool flag);

    /**
     * Returns reference to command dataset.
     * \return Command dataset reference.
     */
    DcmDataset& commandDataset();

    /**
     * Returns constant copy of the command dataset.
     * \return Command dataset.
     */
    DcmDataset constCommandDataset() const;

    /**
     * Assign command dataset.
     * \param dataset Command dataset to be assigned.
     */
    void setCommandDataset(const DcmDataset &dataset);

private:

    DcmDataset m_commandDataset;    ///< DIMSE message command dataset.
};

#endif // DCMDIMSEMESSAGE_H
