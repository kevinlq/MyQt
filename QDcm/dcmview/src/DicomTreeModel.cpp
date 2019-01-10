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

#include <QLinkedList>

#include "DcmDictionary.h"
#include "DcmTagGroup.h"
#include "DcmTagSQ.h"
#include "DcmTagItem.h"
#include "DcmTagPixelData.h"

#include "DicomTreeModel.h"

// Maximal number of symbols to be used to display large tags data
const int TagPreviewLength = 128;

DicomTreeModel::DicomTreeModel(DcmDataset &dataset, QObject *parent)
    : QStandardItemModel(parent)
{
    attachTagList(invisibleRootItem(), dataset.tagGroups());
}

QVariant DicomTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return tr("Tag");
        case 1:
            return tr("Name");
        case 2:
            return tr("VR");
        case 3:
            return tr("VM");
        case 4:
            return tr("Value");
        default:
            return QVariant();
        }
    }

    return QVariant();
}

QList<QStandardItem *> DicomTreeModel::createRowForTag(DcmTag *tag)
{
    Q_ASSERT(tag);

    DcmDictionary *dict = DcmDictionary::getInstancePtr();
    Q_ASSERT(dict);

    DcmTagDescription tagDesc = dict->findByTagKey(tag->tagKey());

    QList<QStandardItem *> row;

    int multMin = tagDesc.vmMin();
    int multMax = tagDesc.vmMax();
    int multMod = tagDesc.vmMod();
    QString multStr;
    if (multMin > 0) {
        multStr = QString::number(multMin);

        if (multMax != DcmMultiplicity_Unknown) {
            if (multMax != multMin) {
                multStr += QString("-") + QString::number(multMax);
            }
        } else {
            if (multMod > 1) {
                if (multMax == DcmMultiplicity_Unknown) {
                    multStr += QString("-") + QString("%1n").arg(QString::number(multMod));
                }
            }
        }
    }

    row << new QStandardItem(tag->tagKey().toString());
    row << new QStandardItem(tagDesc.name());
    row << new QStandardItem(tag->vr().toString());
    row << new QStandardItem(multStr);

    QString strValue;

    if (tag->vr().isBinary() || tag->tagKey() == DcmTagKey::Item) {
        strValue = QString("< Binary data >");
    } else {
        strValue = tag->value().toString();
        if (strValue.length() > TagPreviewLength) {
            strValue = strValue.left(TagPreviewLength) + QString("...");
        }
    }

    row << new QStandardItem(strValue);

    return row;
}

void DicomTreeModel::attachTagList(QStandardItem *item, DcmTagList &tagList)
{
    Q_ASSERT(item);

    foreach (DcmTag *tag, tagList.list()) {
        Q_ASSERT(tag);
        QList<QStandardItem *> row = createRowForTag(tag);

        item->appendRow(row);

        if (tag->isGroup()) {
            // Group of tags
            DcmTagGroup *tagGroup = dynamic_cast<DcmTagGroup *>(tag);
            Q_ASSERT(tagGroup);
            attachTagList(row.at(0), tagGroup->tags());
        } else if (tag->vr() == DcmVr::SQ) {
            // Sequence
            DcmTagSQ *tagSq = dynamic_cast<DcmTagSQ *>(tag);
            Q_ASSERT(tagSq);
            attachTagList(row.at(0),tagSq->items());
        } else if (tag->tagKey() == DcmTagKey::Item) {
            if (tag->isBinary()) {
                // Binary item of compressed data
            } else {
                // Normal item
                DcmTagItem *tagItem = dynamic_cast<DcmTagItem *>(tag);
                Q_ASSERT(tagItem);
                attachTagList(row.at(0), tagItem->tagGroups());
            }
        } else if (tag->tagKey() == DcmTagKey::PixelData) {
            // Pixel data
            DcmTagPixelData *tagPixelData = dynamic_cast<DcmTagPixelData*>(tag);
            Q_ASSERT(tagPixelData);
            if (tagPixelData->isEncapsulated()) {
                attachTagList(row.at(0), tagPixelData->items());
            }
        }
    }
}
