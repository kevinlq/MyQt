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

#ifndef DICOMTREEMODEL_H
#define DICOMTREEMODEL_H

#include <QList>
#include <QStandardItem>
#include <QStandardItemModel>
#include "DcmDataset.h"

/*! Model for a tree view to represent DICOM dataset structire.
 */
class DicomTreeModel : public QStandardItemModel
{
    Q_OBJECT

public:

    DicomTreeModel(DcmDataset &dataset, QObject *parent = 0);

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:

    /// Create table row for a single tag.
    static QList<QStandardItem *> createRowForTag(DcmTag *tag);

    /// Attach list of tags to tree model item.
    static void attachTagList(QStandardItem *item, DcmTagList &tagList);

};

#endif // DICOMTREEMODEL_H
