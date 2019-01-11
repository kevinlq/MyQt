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

#include <QMap>
#include "DcmGlobal.h"
#include "DcmAbstractSyntax.h"

const DcmAbstractSyntax DcmAbstractSyntax::Invalid;
const DcmAbstractSyntax DcmAbstractSyntax::Verification("1.2.840.10008.1.1");
const DcmAbstractSyntax DcmAbstractSyntax::DicomApplicationContextName("1.2.840.10008.3.1.1.1");
const DcmAbstractSyntax DcmAbstractSyntax::ModalityPerformedProcedureStep("1.2.840.10008.3.1.2.3.3");
const DcmAbstractSyntax DcmAbstractSyntax::ModalityPerformedProcedureStepRetreive("1.2.840.10008.3.1.2.3.4");
const DcmAbstractSyntax DcmAbstractSyntax::ModalityPerformedProcedureStepNotification("1.2.840.10008.3.1.2.3.5");
const DcmAbstractSyntax DcmAbstractSyntax::StudyFind("1.2.840.10008.5.1.4.1.2.2.1");
const DcmAbstractSyntax DcmAbstractSyntax::StudyGet("1.2.840.10008.5.1.4.1.2.2.3");
const DcmAbstractSyntax DcmAbstractSyntax::StudyMove("1.2.840.10008.5.1.4.1.2.2.2");
const DcmAbstractSyntax DcmAbstractSyntax::PatientFind("1.2.840.10008.5.1.4.1.2.1.1");
const DcmAbstractSyntax DcmAbstractSyntax::PatientGet("1.2.840.10008.5.1.4.1.2.1.3");
const DcmAbstractSyntax DcmAbstractSyntax::PatientMove("1.2.840.10008.5.1.4.1.2.1.2");
const DcmAbstractSyntax DcmAbstractSyntax::PatientStudyMove("1.2.840.10008.5.1.4.1.2.3.2");
const DcmAbstractSyntax DcmAbstractSyntax::ModalityWorklistFind("1.2.840.10008.5.1.4.31");
const DcmAbstractSyntax DcmAbstractSyntax::CRImageStorage("1.2.840.10008.5.1.4.1.1.1");
const DcmAbstractSyntax DcmAbstractSyntax::CTImageStorage("1.2.840.10008.5.1.4.1.1.2");
const DcmAbstractSyntax DcmAbstractSyntax::MRImageStorage("1.2.840.10008.5.1.4.1.1.4");
const DcmAbstractSyntax DcmAbstractSyntax::USImageStorage("1.2.840.10008.5.1.4.1.1.6.1");
const DcmAbstractSyntax DcmAbstractSyntax::NMImageStorage("1.2.840.10008.5.1.4.1.1.20");
const DcmAbstractSyntax DcmAbstractSyntax::PETImageStorage("1.2.840.10008.5.1.4.1.1.128");
const DcmAbstractSyntax DcmAbstractSyntax::RTImageStorage("1.2.840.10008.5.1.4.1.1.481.1");
const DcmAbstractSyntax DcmAbstractSyntax::RTDoseStorage("1.2.840.10008.5.1.4.1.1.481.2");
const DcmAbstractSyntax DcmAbstractSyntax::RTStructStorage("1.2.840.10008.5.1.4.1.1.481.3");
const DcmAbstractSyntax DcmAbstractSyntax::RTBeamsTreatmentRecordStorage("1.2.840.10008.5.1.4.1.1.481.4");
const DcmAbstractSyntax DcmAbstractSyntax::RTIonBeamsTreatmentRecordStorage("1.2.840.10008.5.1.4.1.1.481.9");
const DcmAbstractSyntax DcmAbstractSyntax::RTPlanStorage("1.2.840.10008.5.1.4.1.1.481.5");
const DcmAbstractSyntax DcmAbstractSyntax::RTBranchyTreatmentRecordStorage("1.2.840.10008.5.1.4.1.1.481.6");
const DcmAbstractSyntax DcmAbstractSyntax::RTTreatmentSummaryRecordStorage("1.2.840.10008.5.1.4.1.1.481.7");
const DcmAbstractSyntax DcmAbstractSyntax::RTIonPlanStorage("1.2.840.10008.5.1.4.1.1.481.8");
const DcmAbstractSyntax DcmAbstractSyntax::PrintBasicFilm("1.2.840.10008.5.1.1.1");
const DcmAbstractSyntax DcmAbstractSyntax::PrintBasicFilmBox("1.2.840.10008.5.1.1.2");
const DcmAbstractSyntax DcmAbstractSyntax::PrintBasicGrayscaleImageBox("1.2.840.10008.5.1.1.4");

DcmAbstractSyntax::DcmAbstractSyntax()
    : DcmPDUItem(DcmPDUType_AbstractSyntax),
      m_uid()
{
}

DcmAbstractSyntax::DcmAbstractSyntax(const QString &uid)
    : DcmPDUItem(DcmPDUType_AbstractSyntax),
      m_uid(uid)
{
    Q_ASSERT(dcmIsValidUID(uid));
}

DcmAbstractSyntax::DcmAbstractSyntax(const DcmAbstractSyntax &as)
    : DcmPDUItem(as),
      m_uid(as.m_uid)
{
}

DcmAbstractSyntax& DcmAbstractSyntax::operator =(const DcmAbstractSyntax &as)
{
    if (this != &as) {
        DcmPDUItem::operator =(as);
        m_uid =as.m_uid;
    }
    return *this;
}

DcmPDUItem* DcmAbstractSyntax::clone() const
{
    return new DcmAbstractSyntax(*this);
}

DcmAbstractSyntax::~DcmAbstractSyntax()
{
}

QString DcmAbstractSyntax::uid() const
{
    return m_uid;
}

bool DcmAbstractSyntax::operator ==(const DcmAbstractSyntax &as) const
{
    return m_uid == as.m_uid;
}

bool DcmAbstractSyntax::operator !=(const DcmAbstractSyntax &as) const
{
    return m_uid != as.m_uid;
}

DcmSize DcmAbstractSyntax::contentSize() const
{
    return m_uid.length();
}

bool DcmAbstractSyntax::isValid() const
{
    return !m_uid.isEmpty();
}

DcmStream& operator <<(DcmStream &stream, const DcmAbstractSyntax &pdu)
{
    char c[2] = {DcmPDUType_AbstractSyntax, 0};
    stream.dataStream().writeRawData(c, 2);
    DcmUnsignedShort length = pdu.contentSize();
    stream.writePDUSize16(length);
    stream.dataStream().writeRawData(pdu.uid().toLocal8Bit(), length);
    return stream;
}

DcmStream& operator >>(DcmStream &stream, DcmAbstractSyntax &pdu)
{
    char c[2];
    stream.dataStream().readRawData(c, 2);
    if (c[0] == DcmPDUType_AbstractSyntax && c[1] == 0) {
        DcmUnsignedShort length = stream.readPDUSize16();
        char *buffer = new char[length];
        stream.dataStream().readRawData(buffer, length);
        QString uid = QString::fromLocal8Bit(buffer, length);
        pdu = DcmAbstractSyntax(uid);
        delete[] buffer;
    } else {
        pdu = DcmAbstractSyntax::Invalid;
    }

    return stream;
}
