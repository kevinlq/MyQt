/*********************************************************************************
  *Copyright(C),kevinlq.com
  *FileName:
  *Author:  qi_li
  *Version: V1.0
  *Date:  2019-12-19
  *Description:
  * This file is part of QFrameworkKit
  *History:
     1.Date:
       Author:
       Modification:
**********************************************************************************/
#include "LayoutSelectPanel.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>

#include <QMouseEvent>
#include <QResizeEvent>
#include <QDebug>

#define BACKGROUND_STYLE QLatin1String("QWidget{background-color:rgb(90,90,90);}")
#define NORMAL_STYLE QLatin1String("QWidget{background-color:rgb(130,130,130);}")
#define HIGHLINE_STYLE QLatin1String("QWidget{background-color:rgb(180,180,180);}")
#define ITEM_SPACING    4

using namespace QfwUtil;

class LayoutSelectPanelPrivate
{
public:
    LayoutSelectPanelPrivate(LayoutSelectPanel *q);
    ~LayoutSelectPanelPrivate();

    void setPanelLayout(int nRow, int nColumn );

    bool createLayout(int nRow, int nColumn );

    void updateLayout();

    // 鼠标移动实时刷新item样式
    void updateStyleForMouseMove(const QPoint& ptHover);

    // 鼠标按下后计算当前选择的行列
    void updateSelectLayout(const QPoint& ptPress);

public:
    LayoutSelectPanel*  q_ptr;
    int                 m_nRow;                 // 当前布局行
    int                 m_nColumn;
    int                 m_nSelectRow;           // 鼠标点击选择的行
    int                 m_nSelectColumn;

    QList<QWidget*>     m_lsLayoutItems;        // 存储布局中所有的item
    QGridLayout*        m_pGridLayout;
};

LayoutSelectPanelPrivate::LayoutSelectPanelPrivate(LayoutSelectPanel *q)
    :q_ptr(q)
    ,m_nRow(6)
    ,m_nColumn(6)
    ,m_nSelectRow(0)
    ,m_nSelectColumn(0)
    ,m_pGridLayout(new QGridLayout())
{
    m_lsLayoutItems.clear();
}

LayoutSelectPanelPrivate::~LayoutSelectPanelPrivate()
{
    qDeleteAll(m_lsLayoutItems);
    if (nullptr != m_pGridLayout)
    {
        delete m_pGridLayout;
        m_pGridLayout = nullptr;
    }
}

void LayoutSelectPanelPrivate::setPanelLayout(int nRow, int nColumn)
{
    m_nRow = nRow;
    m_nColumn = nColumn;

    createLayout(m_nRow, m_nColumn);
}

bool LayoutSelectPanelPrivate::createLayout(int nRow, int nColumn)
{
    if (nullptr == m_pGridLayout)
    {
        return false;
    }

    if (nRow == m_pGridLayout->rowCount()
        && nColumn == m_pGridLayout->columnCount())
    {
        return true;
    }

    // 要创建的和现有的不相等，则删除后再重新创建
    for (auto w: m_lsLayoutItems)
    {
        m_pGridLayout->removeWidget(w);
    }

    qDeleteAll(m_lsLayoutItems);
    m_lsLayoutItems.clear();

    m_pGridLayout->setSpacing(ITEM_SPACING);
    m_pGridLayout->setVerticalSpacing(ITEM_SPACING);

    // 根据面板尺寸，计算每个item的尺寸
    int nWidth = q_ptr->width();
    int nHeight = q_ptr->height();
    int nTmpLength = qMin(nWidth, nHeight);

    // 如果是不规则的布局，取最小宽高计算.
    int nItemWidth = nTmpLength / nColumn;
    int nItemHeight = nTmpLength / nRow;

    for (int i = 0; i < nRow; i++)
    {
        for (int j = 0; j < nColumn; j++)
        {
            QWidget* pWidget = new QWidget(q_ptr);
            pWidget->setMouseTracking(true);
            pWidget->setMinimumSize(nItemWidth,nItemHeight);
            pWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            pWidget->setStyleSheet(NORMAL_STYLE);

            m_lsLayoutItems.push_back(pWidget);
            m_pGridLayout->addWidget(pWidget, i, j/*, 1, 1, Qt::AlignHCenter*/);
        }
    }

    return true;
}

void LayoutSelectPanelPrivate::updateLayout()
{
    // 根据面板尺寸，计算每个item的尺寸
    int nWidth = q_ptr->width();
    int nHeight = q_ptr->height();
    int nTmpLength = qMin(nWidth, nHeight);

    // 如果是不规则的布局，取最小宽高计算.
    int nItemWidth = nTmpLength / m_nColumn;
    int nItemHeight = nTmpLength / m_nRow;

    for (auto w: m_lsLayoutItems)
    {
        w->setMinimumSize(nItemWidth, nItemHeight);
    }
}

void LayoutSelectPanelPrivate::updateStyleForMouseMove(const QPoint &ptHover)
{
    for (auto w: m_lsLayoutItems)
    {
        if (ptHover.x() >= w->pos().x() && ptHover.y() >= w->pos().y())
        {
            w->setStyleSheet(HIGHLINE_STYLE);
        }
        else
        {
            w->setStyleSheet(NORMAL_STYLE);
        }
    }
}

void LayoutSelectPanelPrivate::updateSelectLayout(const QPoint &ptPress)
{
    m_nSelectColumn = 0;
    m_nSelectRow = 0;

    for (auto w: m_lsLayoutItems)
    {
        if (ptPress.x() > w->pos().x())
        {
            m_nSelectColumn++;
        }

        if (ptPress.y() >= w->pos().y())
        {
            m_nSelectRow++;
        }
    }

    m_nSelectColumn/= m_nColumn;
    m_nSelectRow /= m_nRow;
}

LayoutSelectPanel::LayoutSelectPanel(QWidget *parent)
    : QWidget(parent)
    , m_pPanelImpl(new LayoutSelectPanelPrivate(this))
{
    resize(200,200);

    setStyleSheet(BACKGROUND_STYLE);
    m_pPanelImpl->createLayout(6,6);

    QHBoxLayout* pHLayout = new QHBoxLayout;
    pHLayout->addLayout(m_pPanelImpl->m_pGridLayout);
    pHLayout->addStretch();
    pHLayout->setContentsMargins(0,0,0,0);

    QVBoxLayout* pLayout = new QVBoxLayout(this);
    pLayout->addLayout(pHLayout);
    pLayout->addStretch();
    pLayout->setContentsMargins(2,2,2,2);

    setLayout(pLayout);

    setMouseTracking(true);
}

LayoutSelectPanel::~LayoutSelectPanel()
{
    if (nullptr != m_pPanelImpl)
    {
        delete m_pPanelImpl;
        m_pPanelImpl = nullptr;
    }
}

void LayoutSelectPanel::setPanelLayout(int nRow, int nColumn)
{
    m_pPanelImpl->setPanelLayout(nRow, nColumn);
}

void LayoutSelectPanel::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);

    m_pPanelImpl->updateStyleForMouseMove(QPoint(0, 0));
}

void LayoutSelectPanel::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    QPoint ptPos = event->pos();

    if (!rect().contains(ptPos))
    {
        return;
    }

    m_pPanelImpl->updateSelectLayout(ptPos);

    emit signalSelectLayoutChange(m_pPanelImpl->m_nSelectColumn, m_pPanelImpl->m_nSelectRow);
}

void LayoutSelectPanel::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    QPoint ptPos = event->pos();

    m_pPanelImpl->updateStyleForMouseMove(ptPos);
}
