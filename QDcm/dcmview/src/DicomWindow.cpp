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

#include <QHeaderView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "DcmTagPixelData.h"
#include "DcmImage.h"
#include "DcmMonochromeImage.h"
#include "DicomWindow.h"

DicomWindow::DicomWindow(DcmDataset &dataset, QWidget *parent)
    : QMdiSubWindow(parent)
{
    m_dataset = dataset;
    m_treeModel = new DicomTreeModel(m_dataset, this);
    m_treeView = new QTreeView();
    m_treeView->setModel(m_treeModel);
    m_treeView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_treeView->header()->setDefaultAlignment(Qt::AlignCenter);
    m_treeView->expandAll();
    m_treeView->resizeColumnToContents(0);
    m_treeView->resizeColumnToContents(1);

    m_tabWidget = 0;
    m_imageView = 0;

    DcmTag *tag = m_dataset.findTag(DcmTagKey::PixelData);
    if (tag) {
        // This is an image
        DcmTagPixelData *tagPixelData = dynamic_cast<DcmTagPixelData *>(tag);
        Q_ASSERT(tagPixelData);
        if (!tagPixelData->isEncapsulated()) {
            // The image is uncompressed
            m_imageView = createDicomImageWidget();
        }
    }

    QVBoxLayout *rootLayout = new QVBoxLayout();
    rootLayout->setMargin(0);
    QWidget *rootWidget = new QWidget();

    if (m_imageView) {
        m_tabWidget = new QTabWidget();
        m_tabWidget->addTab(m_imageView, tr("Image"));
        m_tabWidget->addTab(m_treeView, tr("DICOM tags"));
        rootLayout->addWidget(m_tabWidget);
    } else {
        rootLayout->addWidget(m_treeView);
    }

    rootWidget->setLayout(rootLayout);

    layout()->addWidget(rootWidget);
}

DicomWindow::~DicomWindow()
{
}

bool DicomWindow::containsImage() const
{
    return m_imageView != 0;
}

QWidget* DicomWindow::createDicomImageWidget()
{
    DcmImage image(m_dataset);
    if (image.photometricInterpretation().isGrayscale()) {
        DcmMonochromeImage monoImage(image.dataset());

        DcmImageTransferFunction tf;

        double windowCenter = monoImage.windowCenter();
        double windowWidth = monoImage.windowWidth();

        tf.addReferencePoint(windowCenter - windowWidth / 2, QColor(0, 0, 0));
        tf.addReferencePoint(windowCenter + windowWidth / 2, QColor(255, 255, 255));
        QImage qImage = monoImage.toQImage(tf);
        QLabel *imageLabel = new QLabel();
        imageLabel->setPixmap(QPixmap::fromImage(qImage));
        imageLabel->setAlignment(Qt::AlignCenter);
        return imageLabel;
    }

    return 0;
}
