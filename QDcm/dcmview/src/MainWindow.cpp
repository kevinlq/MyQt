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

#include <QApplication>
#include <QDesktopWidget>
#include <QList>
#include <QMenuBar>
#include <QCloseEvent>
#include <QMessageBox>
#include <QMdiSubWindow>
#include <QFileDialog>

#include "DcmFile.h"
#include "DcmDataset.h"

#include "DicomWindow.h"

#include "MainWindow.h"

// Default size of DICOM window
const QSize DefaultDicomWindowSize(800, 600);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("QDCM simple DICOM viewer"));

    m_mdiArea = new QMdiArea(this);
    m_mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setCentralWidget(m_mdiArea);

    m_windowsMapper = new QSignalMapper(this);
    connect(m_windowsMapper, SIGNAL(mapped(QWidget*)), this, SLOT(setActiveSubWindow(QWidget*)));

    createActions();
    createMenus();
    createToolBars();
}

MainWindow::~MainWindow()
{
}

void MainWindow::moveToDesktopCenter()
{
    QRect r = frameGeometry();
    QRect d = QApplication::desktop()->availableGeometry();
    r.moveCenter(QPoint(d.width()/2, d.height()/2));
    move(r.topLeft());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int ret = QMessageBox::question(this,
                                    tr("Quit"),
                                    tr("Do you want to quit the application?"),
                                    QMessageBox::Yes | QMessageBox::No);
    if (ret != QMessageBox::Yes) {
        event->ignore();
        return;
    }

    m_mdiArea->closeAllSubWindows();
    if (m_mdiArea->currentSubWindow()) {
        event->ignore();
    }
}

void MainWindow::onOpenAction()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open DICOM file"),
                                                    "/",
                                                    "*.*");
    if (!fileName.isEmpty()) {
        DcmFile dcmFile(fileName);
        DcmDataset dataset = dcmFile.read();
        if (dcmFile.isError()) {
            QMessageBox::warning(this,
                                 tr("Error"),
                                 tr("Unable to read file %1. %2").arg(fileName, dcmFile.errorText()),
                                 QMessageBox::Ok);
        } else {
            DicomWindow *dicomWindow = new DicomWindow(dataset);
            dicomWindow->setWindowTitle(fileName);
            dicomWindow->setWindowFilePath(fileName);
            dicomWindow->resize(dicomWindow->sizeHint());
            m_mdiArea->addSubWindow(dicomWindow);
            dicomWindow->show();
            if (!dicomWindow->containsImage()) {
                dicomWindow->resize(DefaultDicomWindowSize);
            }
        }
    }
}

void MainWindow::updateWindowMenu()
{
    m_windowMenu->clear();
    m_windowMenu->addAction(m_closeAction);
    m_windowMenu->addAction(m_closeAllAction);
    m_windowMenu->addSeparator();
    m_windowMenu->addAction(m_tileAction);
    m_windowMenu->addAction(m_cascadeAction);
    m_windowMenu->addSeparator();
    m_windowMenu->addAction(m_nextAction);
    m_windowMenu->addAction(m_previousAction);
    m_windowMenu->addAction(m_separatorAction);

    QList<QMdiSubWindow *> windows = m_mdiArea->subWindowList();
    m_separatorAction->setVisible(!windows.isEmpty());

    for (int i = 0; i < windows.size(); i++) {
        QMdiSubWindow *subWindow = windows.at(i);
        QString text = subWindow->windowTitle();

        QAction *action = m_windowMenu->addAction(text);
        action->setToolTip(subWindow->windowFilePath());
        action->setCheckable(true);
        action->setChecked(subWindow == activeMdiChild());
        connect(action, SIGNAL(triggered()), m_windowsMapper, SLOT(map()));
        m_windowsMapper->setMapping(action, subWindow);
    }
}

void MainWindow::createActions()
{
    m_openAction = new QAction(QIcon(":/icons/open.png"), tr("&Open..."), this);
    m_openAction->setShortcuts(QKeySequence::Open);
    m_openAction->setStatusTip(tr("Open DICOM file"));
    connect(m_openAction, SIGNAL(triggered()), this, SLOT(onOpenAction()));

    m_exitAction = new QAction(tr("E&xit"), this);
    m_exitAction->setShortcuts(QKeySequence::Quit);
    m_exitAction->setStatusTip(tr("Quit the application"));
    connect(m_exitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    m_closeAction = new QAction(tr("Cl&ose"), this);
    m_closeAction->setStatusTip(tr("Close the active window"));
    connect(m_closeAction, SIGNAL(triggered()), m_mdiArea, SLOT(closeActiveSubWindow()));

    m_closeAllAction = new QAction(tr("Close &All"), this);
    m_closeAllAction->setStatusTip(tr("Close all the windows"));
    connect(m_closeAllAction, SIGNAL(triggered()), m_mdiArea, SLOT(closeAllSubWindows()));

    m_tileAction = new QAction(tr("&Tile"), this);
    m_tileAction->setStatusTip(tr("Tile the windows"));
    connect(m_tileAction, SIGNAL(triggered()), m_mdiArea, SLOT(tileSubWindows()));

    m_cascadeAction = new QAction(tr("&Cascade"), this);
    m_cascadeAction->setStatusTip(tr("Cascade the windows"));
    connect(m_cascadeAction, SIGNAL(triggered()), m_mdiArea, SLOT(cascadeSubWindows()));

    m_nextAction = new QAction(tr("Ne&xt"), this);
    m_nextAction->setShortcuts(QKeySequence::NextChild);
    m_nextAction->setStatusTip(tr("Move the focus to the next window"));
    connect(m_nextAction, SIGNAL(triggered()), m_mdiArea, SLOT(activateNextSubWindow()));

    m_previousAction = new QAction(tr("Pre&vious"), this);
    m_previousAction->setShortcuts(QKeySequence::PreviousChild);
    m_previousAction->setStatusTip(tr("Move the focus to the previous window"));
    connect(m_previousAction, SIGNAL(triggered()), m_mdiArea, SLOT(activatePreviousSubWindow()));

    m_separatorAction = new QAction(this);
    m_separatorAction->setSeparator(true);
}

void MainWindow::createMenus()
{
    m_fileMenu = menuBar()->addMenu(tr("&File"));
    m_fileMenu->addAction(m_openAction);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAction);

    m_windowMenu = menuBar()->addMenu(tr("&Window"));
    updateWindowMenu();
    connect(m_windowMenu, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));
}

void MainWindow::createToolBars()
{
    m_fileToolBar = this->addToolBar(tr("File"));
    m_fileToolBar->addAction(m_openAction);
}

QMdiSubWindow* MainWindow::activeMdiChild()
{
    return m_mdiArea->activeSubWindow();
    return 0;
}

void MainWindow::setActiveSubWindow(QWidget *widget)
{
    if (widget) {
        m_mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow*>(widget));
    }
}
