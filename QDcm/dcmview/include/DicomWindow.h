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

#ifndef DICOMWINDOW_H
#define DICOMWINDOW_H

#include <QMdiSubWindow>
#include <QTabWidget>
#include <QTreeView>
#include <QWidget>
#include "DcmDataset.h"
#include "DicomTreeModel.h"

class DicomWindow : public QMdiSubWindow
{
    Q_OBJECT

public:

    DicomWindow(DcmDataset &dataset, QWidget *parent = 0);
    ~DicomWindow();

    /**
     * Tells whether this DICOM window displays an image.
     * @return true if there is an image displayed.
     */
    bool containsImage() const;

private:

    Q_DISABLE_COPY(DicomWindow)

    QWidget *createDicomImageWidget();

    DcmDataset m_dataset;
    DicomTreeModel *m_treeModel;
    QTreeView *m_treeView;
    QWidget *m_imageView;
    QTabWidget *m_tabWidget;
};

#endif // DICOMWINDOW_H
