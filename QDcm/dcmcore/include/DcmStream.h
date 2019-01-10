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

#ifndef DCMSTREAM_H
#define DCMSTREAM_H

#include <QIODevice>
#include <QDataStream>

#include "DcmCoreApi.h"
#include "DcmTransferSyntax.h"
#include "DcmTagKey.h"
#include "DcmVr.h"

/*! DICOM IO stream.
 *
 * This class implements basic I/O methods for
 * DICOM-related data types. It is used by higher level
 * implementations such as DICOM parser or networking.
 *
 * DICOM stream object can be configured for different
 * transfer syntaxes. This will affect how the data will be written
 * or read in binary format.
 *
 * DICOM sream class uses '<<' and '>>' operators to
 * represent all I/O operations supported.
 */
class DCM_CORE_API DcmStream
{
public:

    /**
     * Construct DICOM stream.
     * \param transferSyntax Transfer syntax to be used.
     */
    DcmStream(const DcmTransferSyntax &transferSyntax = DcmTransferSyntax::ExplicitLittleEndian);

    /**
     * Construct DICOM stream.
     * \param ioDevice Pointer to I/O device.
     * \param transferSyntax Transfer syntax to be used.
     */
    DcmStream(QIODevice *ioDevice,
              const DcmTransferSyntax &transferSyntax = DcmTransferSyntax::ExplicitLittleEndian);

    /**
     * Construct DICOM stream.
     * \param byteArray Pointer to byte array that will be used to read/write data from/to.
     * \param openMode Read/write mode flag.
     * \param transferSyntax Transfer syntax to be used.
     */
    DcmStream(QByteArray *byteArray,
              QIODevice::OpenMode openMode,
              const DcmTransferSyntax &transferSyntax = DcmTransferSyntax::ExplicitLittleEndian);

    /**
     * Construct DICOM stream.
     * \param byteArray Byte array to be used to read data from.
     * \param transferSyntax Transfer syntax to be used.
     */
    DcmStream(const QByteArray &byteArray,
              const DcmTransferSyntax &transferSyntax = DcmTransferSyntax::ExplicitLittleEndian);

    /**
     * Returns currently set transfer syntax.
     * \return Current transfer syntax.
     */
    DcmTransferSyntax transferSyntax() const;

    /**
     * Assign current transfer syntax.
     * This will affect all further I/O operations according to the
     * transfer syntax set.
     * \param transferSyntax Transfer syntax to be set.
     */
    void setTransferSyntax(const DcmTransferSyntax &transferSyntax);

    /**
     * Returns reference to the internal data stream.
     * \return Reference to the internal data stream.
     */
    QDataStream& dataStream();

    /**
     * Tells whether the DICOM stream is over.
     * \return True if DICOM stream is at the end.
     */
    bool atEnd() const;

    /**
     * Write signed byte value to stream.
     * \param value Value to be written.
     * \return This stream.
     */
    DcmStream& operator <<(DcmSignedByte value);

    /**
     * Read signed byte from stream.
     * \param Reference to store the read byte.
     * \return This stream.
     */
    DcmStream& operator >>(DcmSignedByte &value);

    /**
     * Write unsigned byte to stream.
     * \param value Value to be written.
     * \return This stream.
     */
    DcmStream& operator <<(DcmUnsignedByte value);

    /**
     * Read unsigned byte from stream.
     * \param value Reference to store the read byte.
     * \return This stream.
     */
    DcmStream& operator >>(DcmUnsignedByte &value);

    /**
     * Write signed short value to stream.
     * \param value Value to be written.
     * \return This stream.
     */
    DcmStream& operator <<(DcmSignedShort value);

    /**
     * Read signed short from stream.
     * \param value Reference to store the read value.
     * \return This stream.
     */
    DcmStream& operator >>(DcmSignedShort &value);

    /**
     * Write unsigned short value to stream.
     * \param value Value to be written.
     * \return This stream.
     */
    DcmStream& operator <<(DcmUnsignedShort value);

    /**
     * Read unsigned short from stream.
     * \param value Reference to store the read value.
     * \return This stream.
     */
    DcmStream& operator >>(DcmUnsignedShort &value);

    /**
     * Write signed long value to stream.
     * \param value Value to be written.
     * \return This stream.
     */
    DcmStream& operator <<(DcmSignedLong value);

    /**
     * Read signed long value from stream.
     * \param value Reference to store the read value.
     * \return This stream.
     */
    DcmStream& operator >>(DcmSignedLong &value);

    /**
     * Write unsigned long value to stream.
     * \param value Value to be written.
     * \return This stream.
     */
    DcmStream& operator <<(DcmUnsignedLong value);

    /**
     * Read unsigned long value from stream.
     * \param value Reference to store the read value.
     * \return This stream.
     */
    DcmStream& operator >>(DcmUnsignedLong &value);

    /**
     * Write single precision float value to stream.
     * \param value Value to be written.
     * \return This stream.
     */
    DcmStream& operator <<(DcmFloat value);

    /**
     * Read single precision float value from stream.
     * \param value Reference to store the read value.
     * \return This stream.
     */
    DcmStream& operator >>(DcmFloat &value);

    /**
     * Write double precision float value to stream.
     * \param value Value to be written.
     * \return This stream.
     */
    DcmStream& operator <<(DcmDouble value);

    /**
     * Read double precision float value from stream.
     * \param value Reference to store the read value.
     * \return This stream.
     */
    DcmStream& operator >>(DcmDouble &value);

    /**
     * Write DICOM tag key to stream.
     * \param tagKey Tag key to be written.
     * \return This stream.
     */
    DcmStream& operator <<(const DcmTagKey &tagKey);

    /**
     * Read DICOM tag key from stream.
     * \param tagKey Reference to store the read tag key.
     * \return This stream.
     */
    DcmStream& operator >>(DcmTagKey &tagKey);

    /**
     * Write DICOM value representation to stream.
     * \param vr Value representation to be written.
     * \return This stream.
     */
    DcmStream& operator <<(const DcmVr &vr);

    /**
     * Read DICOM value representation from stream.
     * \param vr Reference to store the read VR.
     * \return This stream.
     */
    DcmStream& operator >>(DcmVr &vr);

    /**
     * Write DICOM transfer syntax PDU item.
     * \param ts Transfer syntax to write.
     * \return This stream.
     */
    DcmStream& operator <<(const DcmTransferSyntax &ts);

    /**
     * Read DICOM transfer syntax PDU item.
     * \param ts Transfer syntax to be read.
     * \return This stream.
     */
    DcmStream& operator >>(DcmTransferSyntax &ts);

    /**
     * Write PDU item size of 32 bytes.
     * \param s Size.
     */
    void writePDUSize32(DcmSize s);

    /**
     * Read PDU item size of 32 bytes.
     * \return PDU item size.
     */
    DcmSize readPDUSize32();

    /**
     * Write PDU item size of 16 bytes.
     * \param s Size.
     */
    void writePDUSize16(DcmUnsignedShort s);

    /**
     * Read PDU item size of 16 bytes.
     * \return PDU item size.
     */
    DcmUnsignedShort readPDUSize16();

private:

    /// No copy allowed.
    Q_DISABLE_COPY(DcmStream)

    QDataStream m_dataStream;   ///< Data stream used for I/O operations.
    DcmTransferSyntax m_transferSyntax; ///< DICOM transfer syntax.

};

#endif // DCMSTREAM_H
