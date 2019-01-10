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

#ifndef DCMTAGDESCRIPTION_H
#define DCMTAGDESCRIPTION_H

#include "DcmCoreApi.h"
#include "DcmTagKey.h"
#include "DcmVr.h"

/*! DICOM tag description.
 *
 * This class contains all information to describe a
 * single DICOM tag, such as tag key, name, value representation,
 * and multiplicity.
 */
class DCM_CORE_API DcmTagDescription
{
public:

    /**
     * Construct an invalid tag description.
     */
    DcmTagDescription();

    /**
     * Construct tag description.
     * \param name Tag name.
     * \param tagKey Tag key.
     * \param vr Tag value representation.
     * \param min Minimal multiplicity.
     * \param max Maximal multiplicity.
     * \param mod Multiplicity module.
     */
    DcmTagDescription(const QString &name,
                      const DcmTagKey &tagKey,
                      const DcmVr &vr,
                      int min = 1,
                      int max = DcmMultiplicity_Unknown,
                      int mod = 1);

    /**
     * Copy constructor.
     * \param tagDescription Tag description to be copied.
     */
    DcmTagDescription(const DcmTagDescription &tagDescription);

    /**
     * Assignment operator.
     * \param tagDescription Tag description to be set.
     */
    DcmTagDescription& operator =(const DcmTagDescription &tagDescription);

    /**
     * Tells whether this description object is valid.
     * A valid description has a non-empty name and valid value representation.
     * \return true if description is valid.
     */
    bool isValid() const;

    /**
     * Returns tag's name.
     * \return Tag's name.
     */
    QString name() const;

    /**
     * Returns tag's key.
     * \return Tag's key.
     */
    DcmTagKey tagKey() const;

    /**
     * Returns tag value representation.
     * \return Value representation.
     */
    DcmVr vr() const;

    /**
     * Returns minimal multiplicity of a tag.
     * \return Minimal multiplicity.
     */
    int vmMin() const;

    /**
     * Returns maximal multiplicity of a tag.
     * \return Maximal multiplicity.
     */
    int vmMax() const;

    /**
     * Returns multiplicity module.
     * The multiplicity value should be divisable by this
     * module in order to be valid.
     * \return Multiplicity module.
     */
    int vmMod() const;

    /**
     * Tells whether multiplicity value is correct according
     * to this tag description.
     * \param multiplicity Multiplicity to be validated.
     * \return true if multiplicity value is a valid one.
     */
    bool isValidMultiplicity(int multiplicity) const;

private:

    QString m_name; ///< Tag name.
    DcmTagKey m_tagKey; ///< Tag key.
    DcmVr m_vr;     ///< Tag value representation.
    int m_vmMin;    ///< Minimal multiplicity.
    int m_vmMax;    ///< Maximal multiplcity.
    int m_vmMod;    ///< Multiplicity module.

    /*
        In DICOM dictionary multiplicity is specified as
        '1-2n'. For this example min=1, max=unknown, mod=2.
     */

};

#endif // DCMTAGDESCRIPTION_H
