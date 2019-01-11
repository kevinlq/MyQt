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

#ifndef DCMPRESENTATIONCONTEXT_H
#define DCMPRESENTATIONCONTEXT_H

#include <QList>
#include "DcmNetApi.h"
#include "DcmStream.h"
#include "DcmPDUItem.h"
#include "DcmAbstractSyntax.h"
#include "DcmTransferSyntax.h"

/*! Presentation context.
 * Presentation context defines a set of transfer syntaxes
 * that can be used for a given abstract syntax.
 */
class DCM_NET_API DcmPresentationContext: public DcmPDUItem
{
public:

    static const DcmPresentationContext Invalid;    ///< Invalid presentation context.

    /**
     * Construct an invalid presentation context.
     */
    DcmPresentationContext();

    /**
     * Construct presentation context.
     * \param as Abstract syntax.
     * \param id Presentation context id (0..255).
     */
    DcmPresentationContext(const DcmAbstractSyntax &as, int id = 0);

    /**
     * Copy constructor.
     * \param pd Presentation context to be copied.
     */
    DcmPresentationContext(const DcmPresentationContext &pc);

    /**
     * Assignment operator.
     * \param pc Presentation context to be assigned.
     * \return This presentation context.
     */
    DcmPresentationContext& operator =(const DcmPresentationContext &pc);

    /**
     * Clone this PDU item.
     * \return Pointer to cloned PDU item.
     */
    DcmPDUItem* clone() const;

    /**
     * Destructor.
     */
    ~DcmPresentationContext();

    /**
     * Returns abstract syntax of this presentation context.
     * \return Abstract syntax.
     */
    DcmAbstractSyntax abstractSyntax() const;

    /**
     * Returns the list of transfer syntaxes of this presentation context.
     * \return List of transfer syntaxes.
     */
    QList<DcmTransferSyntax> transferSyntaxes() const;

    /**
     * Add a transfer syntax to this presentation context.
     * If invalid or already existing, the transfer syntax will not be added.
     * \param ts Transfer syntax to be added.
     */
    void addTransferSyntax(const DcmTransferSyntax &ts);

    /**
     * Returns the presentation context id.
     * \return Id.
     */
    int id() const;

    /**
     * Assign presentation context id.
     * \param id Id to be set.
     */
    void setId(int id);

    /**
     * Returns PDU item content size in bytes.
     * \return PDU item context size.
     */
    DcmSize contentSize() const;

    /**
     * Tells whether this presentation context is valid.
     * A valid context has to have a valid abstract syntax and
     * at least one transfer syntax set.
     * \return true if this presentation context is valid.
     */
    bool isValid() const;

    // I/O operations
    DCM_NET_API friend DcmStream& operator <<(DcmStream &stream, const DcmPresentationContext &pdu);
    DCM_NET_API friend DcmStream& operator >>(DcmStream &stream, DcmPresentationContext &pdu);

private:

    DcmUnsignedByte m_id;   ///< Presentation context id.
    DcmAbstractSyntax m_abstractSyntax; ///< Abstract syntax.
    QList<DcmTransferSyntax> m_transferSyntaxList;  ///< List of transfer syntaxes.
};

DCM_NET_API DcmStream& operator <<(DcmStream &stream, const DcmPresentationContext &pdu);
DCM_NET_API DcmStream& operator >>(DcmStream &stream, DcmPresentationContext &pdu);

#endif // DCMPRESENTATIONCONTEXT_H
