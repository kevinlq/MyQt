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

#ifndef DCMABSTRACTSYNTAX_H
#define DCMABSTRACTSYNTAX_H

#include "DcmNetApi.h"
#include "DcmStream.h"
#include "DcmPDUItem.h"

/*! Abstract syntax PDU item.
 * Abstract syntax is used to describe the service type
 * used between DICOM entities. It specifies DICOM data type
 * to exchange with.
 */
class DCM_NET_API DcmAbstractSyntax: public DcmPDUItem
{
public:

    /* Predefined syntaxes */
    static const DcmAbstractSyntax Invalid;
    static const DcmAbstractSyntax Verification;
    static const DcmAbstractSyntax DicomApplicationContextName;
    static const DcmAbstractSyntax ModalityPerformedProcedureStep;
    static const DcmAbstractSyntax ModalityPerformedProcedureStepRetreive;
    static const DcmAbstractSyntax ModalityPerformedProcedureStepNotification;
    static const DcmAbstractSyntax StudyFind;
    static const DcmAbstractSyntax StudyGet;
    static const DcmAbstractSyntax StudyMove;
    static const DcmAbstractSyntax PatientFind;
    static const DcmAbstractSyntax PatientGet;
    static const DcmAbstractSyntax PatientMove;
    static const DcmAbstractSyntax PatientStudyMove;
    static const DcmAbstractSyntax ModalityWorklistFind;
    static const DcmAbstractSyntax CRImageStorage;
    static const DcmAbstractSyntax CTImageStorage;
    static const DcmAbstractSyntax MRImageStorage;
    static const DcmAbstractSyntax USImageStorage;
    static const DcmAbstractSyntax NMImageStorage;
    static const DcmAbstractSyntax PETImageStorage;
    static const DcmAbstractSyntax RTImageStorage;
    static const DcmAbstractSyntax RTDoseStorage;
    static const DcmAbstractSyntax RTStructStorage;
    static const DcmAbstractSyntax RTBeamsTreatmentRecordStorage;
    static const DcmAbstractSyntax RTIonBeamsTreatmentRecordStorage;
    static const DcmAbstractSyntax RTPlanStorage;
    static const DcmAbstractSyntax RTBranchyTreatmentRecordStorage;
    static const DcmAbstractSyntax RTTreatmentSummaryRecordStorage;
    static const DcmAbstractSyntax RTIonPlanStorage;
    static const DcmAbstractSyntax PrintBasicFilm;
    static const DcmAbstractSyntax PrintBasicFilmBox;
    static const DcmAbstractSyntax PrintBasicGrayscaleImageBox;

    /**
     * Construct an invalid syntax.
     */
    DcmAbstractSyntax();

    /**
     * Construct abstract syntax.
     * \param uid Abstract syntax UID.
     */
    DcmAbstractSyntax(const QString &uid);

    /**
     * Copy constructor.
     * \param as Abstract syntax to be copied.
     */
    DcmAbstractSyntax(const DcmAbstractSyntax &as);

    /**
     * Assignment operator.
     * \param as Abstract syntax to be assigned.
     * \return This abstract syntax.
     */
    DcmAbstractSyntax& operator =(const DcmAbstractSyntax &as);

    /**
     * Clone this PDU item.
     * \return Pointer to cloned PDU item
     */
    DcmPDUItem* clone() const;

    /**
     * Destructor.
     */
    ~DcmAbstractSyntax();

    /**
     * Returns UID of this abstract syntax.
     * \return UID.
     */
    QString uid() const;

    /**
     * Compare this abstract syntax with another one.
     * \param as Abstract syntax to compare with.
     * \return true if abstract syntaxes are the same.
     */
    bool operator ==(const DcmAbstractSyntax &as) const;

    /**
     * Compare this abstract syntax with another one.
     * \param as Abstract syntax to compare with.
     * \return true if abstract syntaxes are different.
     */
    bool operator !=(const DcmAbstractSyntax &as) const;

    /**
     * Returns this PDU item content size in bytes.
     * \return PDU item content size.
     */
    DcmSize contentSize() const;

    /**
     * Tells whether this abstract syntax is valid.
     * \return true if this abstract syntax PDU is valid.
     */
    bool isValid() const;

    // I/O operations
    DCM_NET_API friend DcmStream& operator <<(DcmStream &stream, const DcmAbstractSyntax &pdu);
    DCM_NET_API friend DcmStream& operator >>(DcmStream &stream, DcmAbstractSyntax &pdu);

private:
    QString m_uid;  ///< Abstract syntax UID.
};

DCM_NET_API DcmStream& operator <<(DcmStream &stream, const DcmAbstractSyntax &pdu);
DCM_NET_API DcmStream& operator >>(DcmStream &stream, DcmAbstractSyntax &pdu);

#endif // DCMABSTRACTSYNTAX_H
