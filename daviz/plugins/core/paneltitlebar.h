#ifndef PANELTITLEBAR_H
#define PANELTITLEBAR_H

#include <QWidget>

namespace RadarDisplay {
class PanelTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit PanelTitleBar(const QString &text, QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);
    
signals:
    void toggled(bool);
    
public slots:
    
private:
    QString m_text;
    int m_titleHeight;
    bool m_toggled;
    bool m_highlighted;
};
}

#endif // PANELTITLEBAR_H
