#include "viewcontrol.h"
#include "coreconstant.h"
#include "icore.h"
#include "iview.h"
#include "viewgroup.h"
#include "utils/rangebar.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QToolButton>
#include <QButtonGroup>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QVariant>
#include <QDebug>

using namespace RadarDisplay;

ViewControl::ViewControl(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    {
        QHBoxLayout *hlayout = new QHBoxLayout;
        hlayout->addSpacing(VIEW_LABEL_LEADING);
        QLabel *titleLabel = new QLabel(tr("View:"));
        titleLabel->setFixedWidth(VIEW_LABEL_WIDTH);
        titleLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        hlayout->addWidget(titleLabel);

        QButtonGroup *buttonGroup = new QButtonGroup(this);
        foreach (IView *view, ICore::viewGroup()->viewList()) {
            QToolButton *viewButton = new QToolButton;
            viewButton->setProperty("view", QVariant::fromValue(view));
            viewButton->setFixedWidth(50);
            viewButton->setText(view->name());
            viewButton->setAutoRaise(true);
            viewButton->setCheckable(true);
            if (view == ICore::currentView())
                viewButton->setChecked(true);
            else
                viewButton->setChecked(false);
            buttonGroup->addButton(viewButton);
            hlayout->addWidget(viewButton);
            m_viewButtons.append(viewButton);

            connect(viewButton, SIGNAL(clicked()), SLOT(viewButtonClicked()));
        }

        hlayout->addStretch(1);

        layout->addLayout(hlayout, 0, 0, 1, -1);

    }

    {
        QHBoxLayout *hlayout = new QHBoxLayout;
        hlayout->addSpacing(VIEW_LABEL_LEADING);

        QLabel *titleLabel = new QLabel(tr("Layer:"));
        titleLabel->setFixedWidth(VIEW_LABEL_WIDTH);
        titleLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        hlayout->addWidget(titleLabel);
        QButtonGroup *buttonGroup = new QButtonGroup(this);
        buttonGroup->setExclusive(false);

        m_plotButton = new QToolButton;
        m_plotButton->setFixedWidth(40);
        m_plotButton->setText(tr("Plot"));
        m_plotButton->setAutoRaise(true);
        m_plotButton->setCheckable(true);
        m_plotButton->setChecked(true);
        buttonGroup->addButton(m_plotButton);
        hlayout->addWidget(m_plotButton);
        connect(m_plotButton, SIGNAL(clicked()), SLOT(plotLayerButtonClicked()));

        m_trackButton = new QToolButton;
        m_trackButton->setFixedWidth(40);
        m_trackButton->setText(tr("Track"));
        m_trackButton->setAutoRaise(true);
        m_trackButton->setCheckable(true);
        m_trackButton->setChecked(true);
        buttonGroup->addButton(m_trackButton);
        hlayout->addWidget(m_trackButton);
        connect(m_trackButton, SIGNAL(clicked()), SLOT(trackLayerButtonClicked()));

        hlayout->addStretch(1);

        layout->addLayout(hlayout, 1, 0, 1, -1);
    }

    {
        QHBoxLayout *hlayout = new QHBoxLayout;

        QLabel *titleLabel = new QLabel(tr("Range:"));
        titleLabel->setFixedWidth(VIEW_LABEL_WIDTH);
        titleLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        hlayout->addWidget(titleLabel);

        m_rangeButton = new QToolButton;
        m_rangeButton->setText(tr("None"));
        m_rangeButton->setAutoRaise(true);
        m_rangeButton->setCheckable(true);
        hlayout->addWidget(m_rangeButton);
        connect(m_rangeButton, SIGNAL(clicked()), SLOT(rangeButtonClicked()));

        hlayout->addStretch(1);

        layout->addLayout(hlayout, 3, 0, 1, -1);
    }

    connect(ICore::instance(), SIGNAL(currentRadarChanged(IRadar*)), SLOT(currentRadarChanged(IRadar*)));
    connect(ICore::instance(), SIGNAL(currentViewAboutToChange(IView*)), SLOT(currentViewAboutToChange(IView*)));
    connect(ICore::instance(), SIGNAL(currentViewChanged(IView*)), SLOT(currentViewChanged(IView*)));
}

void ViewControl::viewButtonClicked()
{
    QToolButton *button = qobject_cast<QToolButton *>(sender());
    if (!button)
        return;
    IView *view = button->property("view").value<IView *>();
    if (!view)
        return;
    ICore::setCurrentView(view);
}

void ViewControl::plotLayerButtonClicked()
{
    if (!ICore::currentView())
        return;
    ICore::currentView()->enableLayer(IView::PlotLayer, m_plotButton->isChecked());
}

void ViewControl::trackLayerButtonClicked()
{
    if (!ICore::currentView())
        return;
    ICore::currentView()->enableLayer(IView::TrackLayer, m_trackButton->isChecked());
}

void ViewControl::rangeButtonClicked()
{
    if (!ICore::currentView())
        return;
    if (m_rangeButton->isChecked()) {
        if (m_lastSelection.isNone())
            m_rangeButton->setChecked(false);
        else
            ICore::currentView()->setCurrentSelection(m_lastSelection);
    } else
        ICore::currentView()->setCurrentSelection(IView::Selection());
}

void ViewControl::currentRadarChanged(IRadar *newRadar)
{
    Q_UNUSED(newRadar)
    m_lastSelection.setNone();
}

void ViewControl::currentViewAboutToChange(IView *newView)
{
    Q_UNUSED(newView)
    if (!ICore::currentView())
        return;
    ICore::currentView()->disconnect(this);
}

void ViewControl::currentViewChanged(IView *newView)
{
    foreach (QToolButton *button, m_viewButtons) {
        IView *view = button->property("view").value<IView *>();
        if (view == newView)
            button->setChecked(true);
        else
            button->setChecked(false);
    }
    if (newView) {
        m_lastSelection = newView->currentSelection();
        connect(newView, SIGNAL(currentSelectionChanged(IView::Selection)), SLOT(currentViewSelectionChanged(IView::Selection)));
        currentViewSelectionChanged(newView->currentSelection());
        connect(newView, SIGNAL(layersChanged(IView::Layers)), SLOT(currentViewLayersChanged(IView::Layers)));
        currentViewLayersChanged(newView->layers());
    }
}

void ViewControl::currentViewSelectionChanged(const IView::Selection &sel)
{
    m_rangeButton->setText(sel.toString());
    if (sel.isNone()) {
        m_rangeButton->setChecked(false);
    } else {
        m_rangeButton->setChecked(true);
        m_lastSelection = sel;
    }
}

void ViewControl::currentViewLayersChanged(const IView::Layers &layers)
{
    if (layers & IView::PlotLayer)
        m_plotButton->setChecked(true);
    else
        m_plotButton->setChecked(false);

    if (layers & IView::TrackLayer)
        m_trackButton->setChecked(true);
    else
        m_trackButton->setChecked(false);

}
