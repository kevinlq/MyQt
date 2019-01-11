#ifndef TESTPDUITEMS_H
#define TESTPDUITEMS_H

#include <QtTest/QtTest>
#include "DcmAAbort.h"
#include "DcmPresentationContext.h"
#include "DcmPDUImplementationClassUID.h"
#include "DcmPDUImplementationVersionName.h"
#include "DcmPDUMaxLength.h"
#include "DcmPDUUserInfo.h"
#include "DcmAAssociateRequest.h"
#include "DcmAAssociateAccept.h"

class TestPDUItems : public QObject
{
    Q_OBJECT

private slots:

    void initTestCase()
    {}

    void testDcmAAbort()
    {
        DcmAAbort pduAAbort(DcmAssociationSourceType_ServiceUser,
                            DcmAssociationReasonType_ApplicationContextNotSupported);
        QVERIFY(pduAAbort.type() == DcmPDUType_AAbort);
        QVERIFY(pduAAbort.isAssociationLevel());
        QVERIFY(pduAAbort.source() == DcmAssociationSourceType_ServiceUser);
        QVERIFY(pduAAbort.reason() == DcmAssociationReasonType_ApplicationContextNotSupported);

        DcmAAbort pduAAbort2(pduAAbort);
        QVERIFY(pduAAbort2.type() == DcmPDUType_AAbort);
        QVERIFY(pduAAbort2.source() == DcmAssociationSourceType_ServiceUser);
        QVERIFY(pduAAbort2.reason() == DcmAssociationReasonType_ApplicationContextNotSupported);

        pduAAbort2.setSource(DcmAssociationSourceType_ServiceProvider);
        pduAAbort2.setReason(DcmAssociationReasonType_CalledAENotRecognized);
        QVERIFY(pduAAbort2.source() == DcmAssociationSourceType_ServiceProvider);
        QVERIFY(pduAAbort2.reason() == DcmAssociationReasonType_CalledAENotRecognized);

        QVERIFY(pduAAbort.contentSize() == 4);
        QVERIFY(pduAAbort.size() == 10);

        DcmPDUItem *pduPtr = pduAAbort.clone();
        QVERIFY(pduPtr);
        QVERIFY(pduPtr->type() == DcmPDUType_AAbort);
        DcmAAbort *pduAAbortPtr = dynamic_cast<DcmAAbort*>(pduPtr);
        QVERIFY(pduAAbortPtr);
        QVERIFY(pduAAbortPtr->type() == pduAAbort.type());
        QVERIFY(pduAAbortPtr->source() == pduAAbort.source());
        QVERIFY(pduAAbortPtr->reason() == pduAAbort.reason());

        delete pduAAbortPtr;
    }

    void testDcmPresentationContext()
    {
        DcmPresentationContext pduPresentationContext;
        QVERIFY(pduPresentationContext.type() == DcmPDUType_PresentationContext);
        QVERIFY(!pduPresentationContext.isAssociationLevel());

        pduPresentationContext = DcmPresentationContext(DcmAbstractSyntax::CTImageStorage, 33);
        QVERIFY(pduPresentationContext.abstractSyntax() == DcmAbstractSyntax::CTImageStorage);
        QVERIFY(pduPresentationContext.id() == 33);

        QVERIFY(pduPresentationContext.transferSyntaxes().count() == 0);
        QVERIFY(!pduPresentationContext.isValid());

        pduPresentationContext.addTransferSyntax(DcmTransferSyntax::ImplicitLittleEndian);
        QVERIFY(pduPresentationContext.transferSyntaxes().count() == 1);
        QVERIFY(pduPresentationContext.transferSyntaxes().at(0) == DcmTransferSyntax::ImplicitLittleEndian);
        QVERIFY(pduPresentationContext.isValid());
        pduPresentationContext.addTransferSyntax(DcmTransferSyntax::ExplicitLittleEndian);
        QVERIFY(pduPresentationContext.transferSyntaxes().count() == 2);
        QVERIFY(pduPresentationContext.transferSyntaxes().at(1) == DcmTransferSyntax::ExplicitLittleEndian);
        QVERIFY(pduPresentationContext.isValid());

        DcmPresentationContext another(pduPresentationContext);
        QVERIFY(another.type() == DcmPDUType_PresentationContext);
        QVERIFY(!another.isAssociationLevel());
        QVERIFY(another.abstractSyntax() == DcmAbstractSyntax::CTImageStorage);
        QVERIFY(another.id() == 33);
        QVERIFY(another.isValid());
        QVERIFY(another.transferSyntaxes().count() == 2);
        QVERIFY(another.transferSyntaxes().at(0) == DcmTransferSyntax::ImplicitLittleEndian);
        QVERIFY(another.transferSyntaxes().at(1) == DcmTransferSyntax::ExplicitLittleEndian);
    }

    void testDcmPDUUserInfo()
    {
        DcmPDUUserInfo pduUser;

        QVERIFY(pduUser.type() == DcmPDUType_UserInfo);
        QVERIFY(!pduUser.isAssociationLevel());
        QVERIFY(pduUser.count() == 0);
        QVERIFY(!pduUser.isValid());

        DcmPDUImplementationClassUID pduImplementationClassUID("1.2.3.4.5");
        QVERIFY(pduImplementationClassUID.type() == DcmPDUType_ImplementationClassUID);
        QVERIFY(!pduImplementationClassUID.isAssociationLevel());
        QVERIFY(pduImplementationClassUID.isValid());
        QVERIFY(pduImplementationClassUID.uid() == "1.2.3.4.5");

        DcmPDUImplementationVersionName pduImplementationVersionName("VERSION");
        QVERIFY(pduImplementationVersionName.type() == DcmPDUType_ImplementationVersionName);
        QVERIFY(!pduImplementationVersionName.isAssociationLevel());
        QVERIFY(pduImplementationVersionName.isValid());
        QVERIFY(pduImplementationVersionName.name() == "VERSION");

        DcmPDUMaxLength pduMaxLength(12345);
        QVERIFY(pduMaxLength.type() == DcmPDUType_PDUMaxLength);
        QVERIFY(!pduMaxLength.isAssociationLevel());
        QVERIFY(pduMaxLength.isValid());
        QVERIFY(pduMaxLength.length() == 12345);

        pduUser.append(pduImplementationClassUID);
        QVERIFY(pduUser.count() == 1);
        pduUser.append(pduImplementationVersionName);
        QVERIFY(pduUser.count() == 2);
        pduUser.append(pduMaxLength);
        QVERIFY(pduUser.count() == 3);

        QVERIFY(pduUser.isValid());

        QVERIFY(pduUser.at(0)->type() == DcmPDUType_ImplementationClassUID);
        QVERIFY(pduUser.at(1)->type() == DcmPDUType_ImplementationVersionName);
        QVERIFY(pduUser.at(2)->type() == DcmPDUType_PDUMaxLength);

        QVERIFY(pduUser.implementationClassUID() == "1.2.3.4.5");
        QVERIFY(pduUser.implementationVersionName() == "VERSION");
        QVERIFY(pduUser.pduMaxLength() == 12345);
    }

    void testDcmAAssociateRequest()
    {
        DcmAAssociateRequest pduARequest;

        QVERIFY(pduARequest.type() == DcmPDUType_AAssociateRq);
        QVERIFY(pduARequest.isAssociationLevel());
        QVERIFY(pduARequest.protocolVersion() == 0x0100);
        QVERIFY(pduARequest.applicationContext() == DcmApplicationContext::Default);

        pduARequest.setCalledAE("CALLEDAE");
        pduARequest.setCallingAE("CALLINGAE");
        QVERIFY(pduARequest.calledAE() == "CALLEDAE");
        QVERIFY(pduARequest.callingAE() == "CALLINGAE");

        QVERIFY(pduARequest.numberOfPresentationContexts() == 0);

        DcmPresentationContext ctxCR(DcmAbstractSyntax::CRImageStorage, 1);
        ctxCR.addTransferSyntax(DcmTransferSyntax::ImplicitLittleEndian);
        ctxCR.addTransferSyntax(DcmTransferSyntax::ExplicitLittleEndian);

        DcmPresentationContext ctxCT(DcmAbstractSyntax::CTImageStorage, 3);
        ctxCT.addTransferSyntax(DcmTransferSyntax::ImplicitLittleEndian);
        ctxCT.addTransferSyntax(DcmTransferSyntax::ExplicitLittleEndian);

        pduARequest.addPresentationContext(ctxCR);
        pduARequest.addPresentationContext(ctxCT);

        QVERIFY(pduARequest.numberOfPresentationContexts() == 2);
        QVERIFY(pduARequest.presentationContextAt(0)->abstractSyntax() == DcmAbstractSyntax::CRImageStorage);
        QVERIFY(pduARequest.presentationContextAt(1)->abstractSyntax() == DcmAbstractSyntax::CTImageStorage);
    }

    void testDcmAAssociateAccept()
    {
        DcmAAssociateAccept aAccept;
        QVERIFY(aAccept.type() == DcmPDUType_AAssociateAc);
        QVERIFY(aAccept.protocolVersion() == 0x0100);
        QVERIFY(aAccept.applicationContext() == DcmApplicationContext::Default);
        QVERIFY(aAccept.isAssociationLevel());

        aAccept.setCalledAE("CALLEDAE");
        aAccept.setCallingAE("CALLINGAE");

        DcmPresentationContext ctxCR(DcmAbstractSyntax::CRImageStorage, 1);
        ctxCR.addTransferSyntax(DcmTransferSyntax::ImplicitLittleEndian);
        ctxCR.addTransferSyntax(DcmTransferSyntax::ExplicitLittleEndian);

        DcmAcceptedPresentationContext aCtxCR(DcmTransferSyntax::ImplicitLittleEndian,
                                              DcmAcceptedPresentationContext::Reason_Acceptance,
                                              ctxCR.id());
        aAccept.addAcceptedPresentationContext(aCtxCR);

        DcmPresentationContext ctxCT(DcmAbstractSyntax::CTImageStorage, 3);
        ctxCT.addTransferSyntax(DcmTransferSyntax::ImplicitLittleEndian);
        ctxCT.addTransferSyntax(DcmTransferSyntax::ExplicitLittleEndian);

        DcmAcceptedPresentationContext aCtxCT(DcmTransferSyntax::ExplicitLittleEndian,
                                              DcmAcceptedPresentationContext::Reason_Acceptance,
                                              ctxCT.id());
        aAccept.addAcceptedPresentationContext(aCtxCT);

        DcmPDUUserInfo pduUser;
        pduUser.append(DcmPDUImplementationClassUID("1.2.3.4.5"));
        pduUser.append(DcmPDUImplementationVersionName("VERSION"));
        pduUser.append(DcmPDUMaxLength(12345));
        aAccept.setUserInfoPDU(pduUser);

        QVERIFY(aAccept.calledAE() == "CALLEDAE");
        QVERIFY(aAccept.callingAE() == "CALLINGAE");

        QVERIFY(aAccept.isValid());
        QVERIFY(aAccept.numberOfAcceptedPresentationContexts() == 2);
        QVERIFY(aAccept.acceptedPresentationContextAt(0)->id() == 1);
        QVERIFY(aAccept.acceptedPresentationContextAt(0)->transferSyntax() == DcmTransferSyntax::ImplicitLittleEndian);
        QVERIFY(aAccept.acceptedPresentationContextAt(1)->id() == 3);
        QVERIFY(aAccept.acceptedPresentationContextAt(1)->transferSyntax() == DcmTransferSyntax::ExplicitLittleEndian);
    }

    void cleanupTestCase()
    {}
};

#endif // TESTPDUITEMS_H
