#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    void init();

    void initMap();

    void addMarker(const QString &lot, const QString &lat,
                   const QString &micon,const QString &name,
                   const QString &mmsi);

    void bmapOneMarker(const QString &lot, const QString &lat,
                       const QString &msg,const QString &img);

public Q_SLOTS:
    void getCoordinate(const QString &lot, const QString &lat);

private slots:
     void slotPopulateJavaScriptWindowObject();

    void on_pbnAddMarker_clicked();

    void on_pbnSetCircle_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
