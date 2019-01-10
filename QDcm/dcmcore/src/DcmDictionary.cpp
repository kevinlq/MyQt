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

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QXmlStreamWriter>
#include <QDomDocument>
#include "DcmDictionary.h"

/* XML tags used to parse the dictionary file */
const static QString xmlTagDictionary("dictionary");
const static QString xmlTagTag("tag");
const static QString xmlTagKey("key");
const static QString xmlTagVr("vr");
const static QString xmlTagVm("vm");

DcmDictionary::DcmDictionary()
    : m_hashToDescriptionMap(),
      m_nameToHashMap()
{
}

void DcmDictionary::addTagDescription(const DcmTagDescription &tagDescription)
{
    if (!tagDescription.isValid()) {
        return;
    }

    DcmHash hash = tagDescription.tagKey().hash();

    m_hashToDescriptionMap[hash] = tagDescription;
    m_nameToHashMap[tagDescription.name().toLower()] = hash;
}

DcmTagDescription DcmDictionary::findByTagKey(const DcmTagKey &tagKey) const
{
    DcmHash hash = tagKey.hash();
    if (m_hashToDescriptionMap.contains(hash)) {
        return m_hashToDescriptionMap[hash];
    }
    return DcmTagDescription();
}

DcmTagDescription DcmDictionary::findByName(const QString &name) const
{
    QString sname = name.trimmed().toLower();
    if (m_nameToHashMap.contains(sname)) {
        DcmHash hash = m_nameToHashMap[sname];
        if (m_hashToDescriptionMap.contains(hash)) {
            return m_hashToDescriptionMap[hash];
        }
    }
    return DcmTagDescription();
}

void DcmDictionary::populateFromDCMTK(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        // Unable to open dictionary file
        qWarning() << "Unable to read file" << fileName;
        return;
    }

    QTextStream stream(&file);

    while (!stream.atEnd()) {
        QString line = stream.readLine();
        parseAndAddDCMTK(line);
    }

    file.close();
}

void DcmDictionary::parseAndAddDCMTK(const QString &line)
{
    if (line.isEmpty()) {
        return;
    }

    QString str = line.simplified();    // Remove extra spaces.

    if (str.left(1) == "#") {
        // Ignore comment
        return;
    }

    QStringList tokens = str.split(" ", QString::SkipEmptyParts);

    if (tokens.count() < 4) {
        // Four tokens expected: tag, VR, name, and multiplicity
        return;
    }

    /* Tag (group,element) token */
    QString strTag = tokens.at(0);
    if ((strTag.left(1) != "(") || (strTag.right(1) != ")")) {
        // Tag should be encoded as '(group,element)'
        return;
    }

    bool ok;    // String to number transformation flag

    DcmUnsignedShort group = strTag.mid(1, 4).toInt(&ok, 16);
    if (!ok) {
        return;
    }
    DcmUnsignedShort element = strTag.mid(6, 4).toInt(&ok, 16);
    if (!ok) {
        return;
    }

    /* Value Representation (VR) */
    QString strVr = tokens.at(1).toUpper();
    DcmVr vr = DcmVr::fromString(strVr);

    if (vr == DcmVr::Invalid) {
        // Invalid VR
        return;
    }

    /* Tag name */
    QString name = tokens.at(2);

    /* Multiplicity */
    QString strVm = tokens.at(3);

    int min = 0;
    int max = DcmMultiplicity_Unknown;
    int mod = 1;

    ok = parseMultiplicity(strVm, min, max, mod);
    if (!ok) {
        return;
    }

    DcmTagDescription tagDescription(name, DcmTagKey(group, element), vr, min, max, mod);
    addTagDescription(tagDescription);
}

bool DcmDictionary::dumpToXML(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        // Unable to write the file
        qWarning() << "Unable to write to file" << fileName;
        return false;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement(xmlTagDictionary);

    foreach (DcmTagDescription tagDescription, m_hashToDescriptionMap) {
        xmlWriter.writeStartElement(xmlTagTag);

        DcmTagKey tagKey = tagDescription.tagKey();
        QString strGroup = QString::number(tagKey.group(), 16).rightJustified(4, '0');
        QString strElement = QString::number(tagKey.element(), 16).rightJustified(4, '0');
        xmlWriter.writeAttribute(xmlTagKey, QString("%1,%2").arg(strGroup).arg(strElement));
        xmlWriter.writeAttribute(xmlTagVr, tagDescription.vr().toString());
        int min = tagDescription.vmMin();
        int max = tagDescription.vmMax();
        int mod = tagDescription.vmMod();

        QString strMin = (min != DcmMultiplicity_Unknown) ? QString::number(min) : QString("n");
        QString strMax = (max != DcmMultiplicity_Unknown) ? QString::number(max) : QString("n");
        QString strMod = (mod > 1) ? QString::number(mod) : QString("");

        if (min != max) {
            xmlWriter.writeAttribute(xmlTagVm, QString("%1-%2%3").arg(strMin).arg(strMod).arg(strMax));
        } else {
            xmlWriter.writeAttribute(xmlTagVm, strMin);
        }

        xmlWriter.writeCharacters(tagDescription.name());

        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndDocument();

    file.close();

    return true;
}

void DcmDictionary::populateFromXML(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qWarning() << "Unable to read file" << fileName;
        return;
    }

    QDomDocument doc;
    QString errText;
    int errLine;
    int errColumn;

    if (!doc.setContent(&file, &errText, &errLine, &errColumn)) {
        qWarning() << "Unable to load DICOM dictionary XML: line"
                   << errLine << ", column" << errColumn
                   << errText;
        file.close();
        return;
    }

    QDomElement root = doc.documentElement();
    if (root.tagName().toLower() != xmlTagDictionary) {
        qWarning() << "DICOM dictionary XML should contain" << xmlTagDictionary << "tag, but"
                   << root.tagName() << "found.";
        file.close();
        return;
    }

    QDomNode node = root.firstChild();
    bool ok = true;
    while (ok && (!node.isNull())) {
        QDomElement element = node.toElement();
        if (element.tagName().toLower() == xmlTagTag) {
            if (!element.hasAttribute(xmlTagKey)) {
                ok = false;
                qWarning() << "Failed to load DICOM dictionary XML:" << xmlTagKey
                           << "attribute is missing.";
            }
            if (!element.hasAttribute(xmlTagVr)) {
                ok = false;
                qWarning() << "Failed to load DICOM dictionary XML:" << xmlTagVr
                           << "attribute is missing.";
            }
            if (!element.hasAttribute(xmlTagVm)) {
                ok = false;
                qWarning() << "Failed to load DICOM dictionary XML:" << xmlTagVm
                           << "attribute is missing.";
            }

            QString strTagKey = element.attribute(xmlTagKey);
            QStringList tagKeyList = strTagKey.split(",", QString::SkipEmptyParts);
            if (tagKeyList.count() != 2) {
                ok = false;
                qWarning() << "Failed to load DICOM dictionary XML: tag key" << strTagKey
                           << "is invalid.";
            } else {
                DcmUnsignedShort tagGroup = tagKeyList.at(0).toInt(&ok, 16);
                if (!ok) {
                    qWarning() << "Failed to load DICOM dictionary XML: tag group" << tagKeyList.at(0)
                               << "is invalid.";
                } else {
                    DcmUnsignedShort tagElement = tagKeyList.at(1).toInt(&ok, 16);
                    if (!ok) {
                        qWarning() << "Failed to load DICOM dictionary XML: tag element" << tagKeyList.at(1)
                                   << "is invalid.";
                    } else {
                        DcmVr vr = DcmVr::fromString(element.attribute(xmlTagVr));
                        if (vr == DcmVr::Invalid) {
                            ok = false;
                            qWarning() << "Failed to load DICOM dictionary XML: Invalid VR" << element.attribute(xmlTagVr)
                                       << "for tag" << strTagKey;
                        } else {
                            QString strVm = element.attribute(xmlTagVm);
                            int min, max, mod;
                            ok = parseMultiplicity(strVm, min, max, mod);
                            if (!ok) {
                                qWarning() << "Failed to load DICOM dictionary XML: Invalid multiplicity" << strVm
                                           << "for tag" << strTagKey;
                            } else {
                                QString name = element.text();
                                name = name.trimmed();
                                if (name.isEmpty()) {
                                    ok = false;
                                    qWarning() << "Failed to load DICOM dictionary XML: tag name is missing for tag" << strTagKey;
                                } else {
                                    DcmTagDescription tagDescription(name, DcmTagKey(tagGroup, tagElement), vr, min, max, mod);
                                    addTagDescription(tagDescription);
                                }
                            }
                        }
                    }
                }
            }
        } else {
            ok = false;
            qWarning() << "Failed to load DICOM dictionary XML: tag" << element.tagName()
                       << "is unknown.";
        }

        node = node.nextSibling();
    }

    file.close();
}

bool DcmDictionary::parseMultiplicity(const QString &str, int &vmMin, int &vmMax, int &vmMod)
{
    int min = 0;
    int max = DcmMultiplicity_Unknown;
    int mod = 1;

    QStringList mult = str.split("-", QString::SkipEmptyParts);
    if (mult.count() < 1) {
        // Invalid multiplicity
        return false;
    }

    bool ok;
    min = mult.at(0).toInt(&ok);
    if (!ok) {
        return false;
    }

    if (mult.count() > 1) {
        // Multiplicity is defined as a range
        if (mult.at(1).right(1).toLower() == "n") {
            max = DcmMultiplicity_Unknown;
            QString strNum = mult.at(1).left(mult.at(1).length() - 1);
            if (strNum.isEmpty()) {
                mod = 1;
            } else {
                mod = strNum.toInt(&ok);
                if (!ok) {
                    // Module value is invalid
                    return false;
                }
            }
        } else {
            max = mult.at(1).toInt(&ok);
            if (!ok) {
                // Maximal value is invalid
                return false;
            }
        }
    } else {
        max = min;
    }

    vmMin = min;
    vmMax = max;
    vmMod = mod;

    return true;
}

DcmDictionary* DcmDictionary::getInstancePtr()
{
    static DcmDictionary dictionary;
    static bool initialized = false;

    if (!initialized) {
        dictionary.populateFromXML(":/dcmcore/dicom.xml");
        initialized = true;
    }
    return &dictionary;
}
