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

#ifndef DCMTAGSTRING_H
#define DCMTAGSTRING_H

#include <QString>
#include <QStringList>
#include "DcmCoreApi.h"
#include "DcmTag.h"

/*! Base class for string-based tags.
 *
 * This is a base class of all string-based tags.
 * It is still an abstract class however and must not be used
 * directly.
 */
class DCM_CORE_API DcmTagString: public DcmTag
{
public:

    /**
     * Default constructor.
     * Constructs an invalid tag.
     */
    DcmTagString();

    /**
     * Construst a string-based tag.
     * If the VR passed is not string-based, and invalid tag
     * will be created.
     * \param tagKey Tag key.
     * \param vr Tag VR.
     */
    DcmTagString(const DcmTagKey &tagKey, const DcmVr &vr);

    /**
     * Copy constructor.
     * \param tag Tag to be copied.
     */
    DcmTagString(const DcmTagString &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag.
     */
    DcmTagString& operator =(const DcmTagString &tag);

    /**
     * Clone this tag.
     * \return Pointer to a new cloned tag.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagString();

    /**
     * Returns value of this tag.
     * \return Tag's value as variant type.
     */
    QVariant value() const;

    /**
     * Returns list of tag's values.
     * \return Values list.
     */
    QVariantList values() const;

    /**
     * Assign tag value.
     * The value will be trimmed to remove leading and trailing spaces.
     * \param v Value to be set as variant type.
     */
    void setValue(const QVariant &v);

    /**
     * Append value to the list of values.
     * \param v Value to be added.
     */
    void appendValue(const QVariant &v);

    /**
     * Assign tag value.
     * \param v Value to be assigned.
     * \return This tag.
     */
    DcmTagString& operator =(const QVariant &v);

    /**
     * Returns the tag value multiplicity.
     * In case of string-based tag the values are separated
     * by '\' symbol. So this method actually counts the number of
     * '\' symbols and returns the number incremented by one (for
     * the number of values).
     * Empty string value returns multiplicity of zero.
     * \return Tag value multiplicity.
     */
    int multiplicity() const;

    /**
     * Returns tag value as string.
     * \return Tag value as string.
     */
    QString asString() const;

    /**
     * Assign tag's string value.
     * The value will be trimmed to remove leading and trailing spaces.
     * \param str String value to be assigned.
     */
    void setString(const QString &str);

    /**
     * Append string value to the list of values.
     * The string is trimmed to the maximal length of the tag's VR
     * (e.g. the CS string are limited to 16 symbols).
     * \param str Value to be added.
     */
    void appendString(const QString &str);

    /**
     * Returns tag value splitted into a list of values.
     * \return List of string values.
     */
    QStringList asStringList() const;

    /**
     * Assign values list.
     * Every value will be trimmed to remove leading and trailing spaces
     * before added to this tag.
     * \param strList List of values to be assigned.
     */
    void setStringList(const QStringList &strList);

    /**
     * Returns string-based tag content size.
     * \param transferSyntax Transfer syntax to encode this tag.
     * \return Tag's raw content size in bytes.
     */
    DcmSize contentSize(const DcmTransferSyntax &transferSyntax) const;

    /**
     * Create string tag with specified tag key and value representation.
     * If VR is not string-based, null will be returned.
     * \param tagKey Tag key.
     * \param vr Value representation (string-based).
     * \return Pointer to created string tag or null.
     */
    static DcmTagString* create(const DcmTagKey &tagKey, const DcmVr &vr);

private:

    QString m_string;   ///< Tag string value.
};

#endif // DCMTAGSTRING_H
