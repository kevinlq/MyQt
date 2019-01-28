#include "fancyheaderview.h"
#include "utilstranslation.h"
#include <QContextMenuEvent>
#include <QMenu>
using namespace RadarDisplay;

FancyHeaderView::FancyHeaderView(Qt::Orientation orient, QWidget *parent) :
    QHeaderView(orient, parent)
{
    UtilsTranslation::load();
    QString text;
    m_resizeAction = new QAction(tr("Adjust width"), this);
    m_autoResizeAction = new QAction(tr("Auto resize"), this);
    m_autoResizeAction->setCheckable(true);
}

void FancyHeaderView::contextMenuEvent(QContextMenuEvent *event)
{
    int sectionCount;
    if (orientation() == Qt::Horizontal)
        sectionCount = model()->columnCount();
    else
        sectionCount = model()->rowCount();
    QMenu contextMenu(this);
    for (int i = 0; i < sectionCount; i++) {
        QAction *action = new QAction(model()->headerData(i, orientation()).toString(),
                                      &contextMenu);
        action->setCheckable(true);
        action->setChecked(!isSectionHidden(i));
        action->setData(i);
        contextMenu.addAction(action);
    }
    contextMenu.addSeparator();
    contextMenu.addAction(m_resizeAction);
//    m_autoResizeAction->setChecked((sectionResizeMode(0) == QHeaderView::ResizeToContents));
    m_autoResizeAction->setChecked(true);

    contextMenu.addAction(m_autoResizeAction);
    QAction *action = contextMenu.exec(event->globalPos());
    if (!action)
        return;
    else if (action == m_resizeAction) {
        resizeSections(QHeaderView::ResizeToContents);
    } else if (action == m_autoResizeAction) {
//        if (sectionResizeMode(0) == QHeaderView::ResizeToContents)
//            setSectionResizeMode(QHeaderView::Interactive);
//        else
//            setSectionResizeMode(QHeaderView::ResizeToContents);
    } else {
        int index = action->data().toInt();
        if (isSectionHidden(index)) {
            emit sectionAboutToBeShown(index, orientation());
            setSectionHidden(index, false);
            emit sectionShown(index, orientation());
        } else {
            emit sectionAboutToBeHidden(index, orientation());
            setSectionHidden(index, true);
            emit sectionHidden(index, orientation());
        }
    }
}
