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

#ifndef DCMDICTIONARY_H
#define DCMDICTIONARY_H

#include <QMap>
#include "DcmCoreApi.h"
#include "DcmTagDescription.h"

/*! DICOM dictionary.
 *
 * In order to handle correctly DICOM tags one has to maintain
 * a dictionary that links tags keys with its names, value
 * representations and multiplicity.
 * The dictionary allows translating from tag key or name to tag description.
 *
 * The dictionary data can be stored as XML file, but loading from
 * DCMTK dictionary is also supported.
 */
class DCM_CORE_API DcmDictionary
{
public:

    /**
     * Construct empty DICOM dictionary.
     */
    DcmDictionary();

    /**
     * Add tag description in the dictionary.
     * If tag description already exists, it will be replaced.
     * \param tagDescription Tag description to be added.
     */
    void addTagDescription(const DcmTagDescription &tagDescription);

    /**
     * Find tag description by tag's key.
     * If tag's key cannot be found in the dictionary, an invalid
     * description is returned.
     * \param tagKey Tag key to look for.
     * \return Found tag description or invalid description if not found.
     */
    DcmTagDescription findByTagKey(const DcmTagKey &tagKey) const;

    /**
     * Find tag description by tag's name.
     * This method is case-insencitive as for the tag name.
     * If not found, an invalid description is returned.
     * \param name Tag name to look for.
     * \return Found tag description or invalid if not found.
     */
    DcmTagDescription findByName(const QString &name) const;

    /**
     * Populate DICOM dictionary from DCMTK dictionary file.
     * This method does not support tag group ranges. It is provided
     * for convinience and normally should never be used.
     * \param fileName DCMTK dictionary file path.
     */
    void populateFromDCMTK(const QString &fileName);

    /**
     * Saves this dictionary as an XML file.
     * \param fileName File path to be written to.
     * \return true if Ok, false if unable to dump.
     */
    bool dumpToXML(const QString &fileName);

    /**
     * Populate DICOM dictionary from XML dictionary file.
     * The dictionary XML file must respect format used by
     * dumpToXML method.
     * \see dumpToXML.
     * \param fileName XML file path to be loaded from.
     */
    void populateFromXML(const QString &fileName);

    /**
     * Returns a static instance of the DICOM dictionary.
     * This method implements singleton pattern to
     * assure the dictionary is loaded only once.
     * \return Pointer to DICOM dictionary instance.
     */
    static DcmDictionary* getInstancePtr();

private:

    /**
     * DICOM dictionary presents a large ammount of data,
     * it is not a good idea to copy it anyway.
     */
    Q_DISABLE_COPY(DcmDictionary)

    /**
     * Parse DCMTK-style DICOM dictionary line and
     * populate the dictionary if parsed succesfully.
     * Comment lines (started with '#' are ignored).
     * This method does not support tag group ranges. Such
     * lines are simply ignored.
     * \param line DCMTK dictionary line.
     */
    void parseAndAddDCMTK(const QString &line);

    bool parseMultiplicity(const QString &str, int &mvMin, int &vmMax, int &vmMod);

    QMap<DcmHash, DcmTagDescription> m_hashToDescriptionMap;    ///< Map hash to description.
    QMap<QString, DcmHash> m_nameToHashMap; ///< Map tag name to hash.
};

#endif // DCMDICTIONARY_H
