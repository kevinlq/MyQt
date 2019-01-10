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

#ifndef DCMFILE_H
#define DCMFILE_H

#include "DcmCoreApi.h"
#include "DcmDataset.h"
#include "DcmDictionary.h"

/*! DICOM file handler.
 * This class provides interface to access DICOM files for
 * reading and writing. The I/O operations are performed
 * via DICOM stream object actually.
 */
class DCM_CORE_API DcmFile
{
public:

    /**
     * Construct DICOM file.
     * \param path Path to DICOM file.
     */
    DcmFile(const QString &path);

    /**
     * Returns path to DICOM file.
     * \return File path.
     */
    QString path() const;

    /**
     * Tells whether the DICOM file exists.
     * \return True if file exists.
     */
    bool exists() const;

    /**
     * Read DICOM dataset from the file.
     * \param dictionaryPtr Pointer to DICOM dictionary to be used to
     *  decode the file. If not specified, default one is used.
     * \return Read dataset.
     */
    DcmDataset read(DcmDictionary *dictionaryPtr = 0);

    /**
     * Write DICOM dataset to file.
     * One should check error flag after using this method.
     * \param dataset Dataset to be written.
     * \param transferSyntax Transfer syntax to use.
     */
    void write(DcmDataset &dataset, const DcmTransferSyntax &transferSyntax = DcmTransferSyntax::ImplicitLittleEndian);

    /**
     * Tells whether there is an error detected while
     * reading the file.
     * \return True on error.
     */
    bool isError() const;

    /**
     * Returns error description text.
     * \return Error text.
     */
    QString errorText() const;

private:

    /// No copy allowed.
    Q_DISABLE_COPY(DcmFile)

    /**
     * Enable error flag and assign error message.
     * Passing void string unsets the error flag
     * and clears the error message.
     * \param text Error message to be set.
     */
    void setError(const QString &text = QString());

    /**
     * Tells whether DICOM file has an appropriate header.
     * \return True if header is present.
     */
    static bool hasHeader(const QString &path);

    /**
     * Probe specified transfer syntax.
     * This function tries to decode DICOM file using
     * specified transfer syntax.
     * \param path DICOM file path.
     * \param transferSyntax Transfer syntax to probe.
     * \param skipHeader Whether to skip DICOM header.
     * \param dictionaryPtr Pointer to DICOM dictionary.
     * \return True is transfer syntax matches.
     */
    static bool probeTransferSyntax(const QString &path,
                                    const DcmTransferSyntax &transferSyntax,
                                    bool skipHeader,
                                    DcmDictionary *dictionaryPtr = 0);

    /**
     * Probe several transfer syntaxes to guess which one to use
     * for file decoding.
     * \param path DICOM file path.
     * \param skipHeader Whether to skiip DICOM header.
     * \param dictionaryPtr Pointer to DICOM dictionary.
     * \return Found transfer syntax or invalid if cannot guess.
     */
    static DcmTransferSyntax guessTransferSyntax(const QString &path,
                                                 bool skipHeader,
                                                 DcmDictionary *dictionaryPtr = 0);

    QString m_path;         ///< DICOM file path.
    bool m_error;           ///< Error flag.
    QString m_errorText;    ///< Error text message.
};

#endif // DCMFILE_H
