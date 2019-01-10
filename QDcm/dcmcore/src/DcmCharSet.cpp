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

#include <QTextCodec>
#include <QMap>
#include "DcmCharSet.h"

static QMap<QString, DcmCharSet> createCharSetMap()
{
    QMap<QString, DcmCharSet> map;
    map.insert("GB18030", DcmCharSet(DcmCharSet::Encoding_GB18030));
    map.insert("ISOIR6", DcmCharSet(DcmCharSet::Encoding_ISO_IR_6));
    map.insert("ISOIR13", DcmCharSet(DcmCharSet::Encoding_ISO_IR_13));
    map.insert("ISOIR100", DcmCharSet(DcmCharSet::Encoding_ISO_IR_100));
    map.insert("ISOIR101", DcmCharSet(DcmCharSet::Encoding_ISO_IR_101));
    map.insert("ISOIR109", DcmCharSet(DcmCharSet::Encoding_ISO_IR_109));
    map.insert("ISOIR110", DcmCharSet(DcmCharSet::Encoding_ISO_IR_110));
    map.insert("ISOIR126", DcmCharSet(DcmCharSet::Encoding_ISO_IR_126));
    map.insert("ISOIR127", DcmCharSet(DcmCharSet::Encoding_ISO_IR_127));
    map.insert("ISOIR138", DcmCharSet(DcmCharSet::Encoding_ISO_IR_138));
    map.insert("ISOIR144", DcmCharSet(DcmCharSet::Encoding_ISO_IR_144));
    map.insert("ISOIR148", DcmCharSet(DcmCharSet::Encoding_ISO_IR_148));
    map.insert("ISOIR166", DcmCharSet(DcmCharSet::Encoding_ISO_IR_166));
    map.insert("ISOIR192", DcmCharSet(DcmCharSet::Encoding_ISO_IR_192));
    map.insert("ISO2022IR13", DcmCharSet(DcmCharSet::Encoding_ISO_2022_IR_13));
    map.insert("ISO2022IR87", DcmCharSet(DcmCharSet::Encoding_ISO_2022_IR_87));
    return map;
}

static QMap<QString, DcmCharSet> charSetMap = createCharSetMap();

DcmCharSet::DcmCharSet()
    : m_encoding(DcmCharSet::Encoding_ISO_IR_100)
{
    QTextCodec *codec = DcmCharSet::findCodecByEncoding(m_encoding);
    m_encoderPtr = (codec) ? codec->makeEncoder() : 0;
    m_decoderPtr = (codec) ? codec->makeDecoder() : 0;
}

DcmCharSet::DcmCharSet(DcmCharSet::Encoding enc)
    : m_encoding(enc)
{
    QTextCodec *codec = DcmCharSet::findCodecByEncoding(m_encoding);
    m_encoderPtr = (codec) ? codec->makeEncoder() : 0;
    m_decoderPtr = (codec) ? codec->makeDecoder() : 0;
}

DcmCharSet::DcmCharSet(const DcmCharSet &charSet)
    : m_encoding(charSet.m_encoding)
{
    QTextCodec *codec = DcmCharSet::findCodecByEncoding(m_encoding);
    m_encoderPtr = (codec) ? codec->makeEncoder() : 0;
    m_decoderPtr = (codec) ? codec->makeDecoder() : 0;
}

DcmCharSet& DcmCharSet::operator =(const DcmCharSet &charSet)
{
    if (this != &charSet) {
        m_encoding = charSet.m_encoding;
        delete m_encoderPtr;
        delete m_decoderPtr;
        QTextCodec *codec = findCodecByEncoding(m_encoding);
        m_encoderPtr = (codec) ? codec->makeEncoder() : 0;
        m_decoderPtr = (codec) ? codec->makeDecoder() : 0;
    }
    return *this;
}

DcmCharSet::~DcmCharSet()
{
    delete m_encoderPtr;
    delete m_decoderPtr;
}

bool DcmCharSet::operator ==(const DcmCharSet &charSet) const
{
    return m_encoding == charSet.m_encoding;
}

bool DcmCharSet::operator !=(const DcmCharSet &charSet) const
{
    return m_encoding != charSet.m_encoding;
}

DcmCharSet::Encoding DcmCharSet::encoding() const
{
    return m_encoding;
}

bool DcmCharSet::isValid() const
{
    return (m_encoding != DcmCharSet::Encoding_Invalid)
            && (m_encoderPtr != 0)
            && (m_decoderPtr != 0);
}

QString DcmCharSet::decode(const QByteArray &byteArray) const
{
    QString str;
    if (m_decoderPtr) {
        str = m_decoderPtr->toUnicode(byteArray);
    } else {
        str = QString::fromLatin1(byteArray.constData());
    }
    return str;
}

QByteArray DcmCharSet::encode(const QString &str) const
{
    QByteArray ba;
    if (m_encoderPtr) {
        ba = m_encoderPtr->fromUnicode(str);
    } else {
        ba = str.toLatin1();
    }
    return ba;
}

DcmCharSet DcmCharSet::forName(const QString &name)
{
    QString key = name.trimmed().toUpper();
    key.remove(QChar(' '));
    key.remove(QChar('_'));
    key.remove(QChar('-'));

    if (charSetMap.contains(key)) {
        return charSetMap[key];
    }

    return DcmCharSet(DcmCharSet::Encoding_Invalid);
}

QTextCodec* DcmCharSet::findCodecByEncoding(DcmCharSet::Encoding enc)
{
    QTextCodec *codec = 0;
    switch (enc) {
    case Encoding_GB18030:
        codec = QTextCodec::codecForName("gb18030");
        break;
    case Encoding_ISO_IR_6:
    case Encoding_ISO_IR_100:
        codec = QTextCodec::codecForName("iso-ir-100");
        break;
    case Encoding_ISO_IR_13:
        codec = QTextCodec::codecForName("iso-ir-13");
        break;
    case Encoding_ISO_IR_101:
        codec = QTextCodec::codecForName("iso-ir-101");
        break;
    case Encoding_ISO_IR_109:
        codec = QTextCodec::codecForName("iso-ir-109");
        break;
    case Encoding_ISO_IR_110:
        codec = QTextCodec::codecForName("iso-ir-110");
        break;
    case Encoding_ISO_IR_126:
        codec = QTextCodec::codecForName("iso-ir-126");
        break;
    case Encoding_ISO_IR_127:
        codec = QTextCodec::codecForName("iso-ir-127");
        break;
    case Encoding_ISO_IR_138:
        codec = QTextCodec::codecForName("iso-ir-138");
        break;
    case Encoding_ISO_IR_144:
        codec = QTextCodec::codecForName("iso-ir-144");
        break;
    case Encoding_ISO_IR_148:
        codec = QTextCodec::codecForName("iso-ir-148");
        break;
    case Encoding_ISO_IR_166:
        codec = QTextCodec::codecForName("iso-ir-166");
        break;
    case Encoding_ISO_IR_192:
        codec = QTextCodec::codecForName("Utf8");
        break;
    case Encoding_ISO_2022_IR_13:
        codec = QTextCodec::codecForName("shift-jis");
        break;
    case Encoding_ISO_2022_IR_87:
        codec = QTextCodec::codecForName("iso-2022-jp");
        break;
    default:
        break;
    }

    return codec;
}
