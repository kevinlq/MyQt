#ifndef FANCYTABWIDGET_H
#define FANCYTABWIDGET_H

#include "utils_global.h"
#include <QTabWidget>
#include <QString>
#include <QIcon>

namespace RadarDisplay {
class UTILS_EXPORT FancyTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit FancyTabWidget(QWidget *parent = 0);
    void setPlaceHolderText(const QString &text);
    void setPlaceHolderIcon(const QIcon &icon);
    void setPlaceHolderWidget(QWidget *widget);
    void setPlaceHolder(QWidget *widget, const QIcon &icon, const QString &text);
    void setPlaceHolder(QWidget *widget, const QString &text);
    void tabInserted(int index);
    void tabRemoved(int index);
    void updateEmptyTab();
signals:
    
public slots:
    
private:
    bool m_isEmpty;
    QString m_text;
    QIcon m_icon;
    QWidget *m_widget;
};
}
#endif // FANCYTABWIDGET_H
