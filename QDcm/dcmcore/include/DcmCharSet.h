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
#ifndef DCMCHARSET_H
#define DCMCHARSET_H

#include <QString>
#include <QByteArray>
#include "DcmCoreApi.h"

class QTextCodec;
class QTextEncoder;
class QTextDecoder;

/*! DICOM character set.
 * This class defines DICOM text data character set to
 * encode and decode strings to Qt string type.
 */
class DCM_CORE_API DcmCharSet
{
public:

    /**
     * Character set encodings.
     */
    typedef enum {
        Encoding_GB18030,
        Encoding_ISO_IR_6,          ///< Latin 1
        Encoding_ISO_IR_13,
        Encoding_ISO_IR_100,        ///< Latin 1
        Encoding_ISO_IR_101,
        Encoding_ISO_IR_109,
        Encoding_ISO_IR_110,
        Encoding_ISO_IR_126,        ///< Greek
        Encoding_ISO_IR_127,        ///< Arab
        Encoding_ISO_IR_138,        ///< Hebrew
        Encoding_ISO_IR_144,        ///< Russian
        Encoding_ISO_IR_148,
        Encoding_ISO_IR_166,
        Encoding_ISO_IR_192,        ///< Utf8
        Encoding_ISO_2022_IR_13,    ///< Shift-JIS
        Encoding_ISO_2022_IR_87,    ///< ISO-2022-JP

        Encoding_Invalid            ///< Invalid unknown encoding
    } Encoding;

    /**
     * Construct default character set.
     * Latin1 i.e. ISO_IR 100.
     */
    DcmCharSet();

    /**
     * Construct character set for specified encoding.
     * \param enc Encoding.
     */
    DcmCharSet(DcmCharSet::Encoding enc);

    /**
     * Copy constructor.
     * \param charSet Character set to be copied.
     */
    DcmCharSet(const DcmCharSet &charSet);

    /**
     * Assignment operator.
     * \param charSet Character set to be assigned.
     * \return This character set object.
     */
    DcmCharSet& operator =(const DcmCharSet &charSet);

    /**
     * Destructor.
     */
    ~DcmCharSet();

    /**
     * Compare with another character set.
     * \param charSet Character set to compare with.
     * \return true if both character sets have the same encoding.
     */
    bool operator ==(const DcmCharSet &charSet) const;

    /**
     * Compare with another character set.
     * \param charSet Character set to compare with.
     * \return true if character sets have different encodings.
     */
    bool operator !=(const DcmCharSet &charSet) const;

    /**
     * Returns encoding of this character set.
     * \return Character set encoding.
     */
    DcmCharSet::Encoding encoding() const;

    /**
     * Tells whether this character set is valid.
     * A valid character set has valid Qt text codecs instantiated.
     * \return true if this character set is valid.
     */
    bool isValid() const;

    /**
     * Decode data to Unicode string.
     * If character set is invalid, the data is interpreted as Latin-1 encoding.
     * \param byteArray Data to be decoded.
     * \return Decoded string.
     */
    QString decode(const QByteArray &byteArray) const;

    /**
     * Encode Unicode string.
     * If character set is invalid, the string is encoded as Latin-1.
     * \param str String to be encoded.
     * \return Encoded data.
     */
    QByteArray encode(const QString &str) const;

    /**
     * Find character set for given name.
     * If not found, an invalid character set is returned.
     * \param name Name of the encoding (e.g. 'ISO IR 100').
     * \return Character set for given encoding name.
     */
    static DcmCharSet forName(const QString &name);

private:

    /**
     * Returns corresponding text codec for specified encoding.
     * If cannot be found, null is returned.
     * \param enc Encoding.
     * \return Text coded or null.
     */
    static QTextCodec* findCodecByEncoding(DcmCharSet::Encoding enc);

    DcmCharSet::Encoding m_encoding;    ///< Encoding
    QTextEncoder *m_encoderPtr;         ///< Text encoder.
    QTextDecoder *m_decoderPtr;         ///< Text decoder.
};

#endif // DCMCHARSET_H
