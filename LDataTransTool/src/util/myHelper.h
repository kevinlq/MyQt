#ifndef MYHELPER_H
#define MYHELPER_H

#include <QObject>
#include <QTextCodec>
#include <QDateTime>
#include <QTime>
#include <QFile>
#include <QDir>
#include <QTranslator>
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QProgressBar>
#include <QSlider>
#include <QStringList>
#include <QSettings>
#include <QTextStream>
#include <qfiledialog.h>

#define AppName "AIS"
#define AppPath qApp->applicationDirPath()
#define AppDeskWidth qApp->desktop()->availableGeometry().width()
#define AppDeskHeight qApp->desktop()->availableGeometry().height()

#define TIMEMS qPrintable (QTime::currentTime().toString("HH:mm:ss zzz"))
#define TIME qPrintable (QTime::currentTime().toString("HH:mm:ss"))
#define QDATE qPrintable (QDate::currentDate().toString("yyyy-MM-dd"))
#define QTIME qPrintable (QTime::currentTime().toString("HH-mm-ss"))
#define DATETIME qPrintable (QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))
#define STRDATETIME qPrintable (QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"))
#define STRDATETIMEMS qPrintable (QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss-zzz"))


class myHelper :public QObject
{
public:
    //设置为开机启动
    static void AutoRunWithSystem(bool IsAutoRun, QString Name, QString Path)
    {
        QSettings *reg = new QSettings(
                    "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
                    QSettings::NativeFormat);

        if (IsAutoRun) {
            reg->setValue(Name, Path);
        } else {
            reg->setValue(Name, "");
        }
    }

    static void setUtf8Code()
    {
        QTextCodec *code = QTextCodec::codecForName("UTF-8");
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
        QTextCodec::setCodecForLocale(code);
        QTextCodec::setCodecForLocale(code);
        QTextCodec::setCodecForTr(code);
#else
        QTextCodec::setCodecForLocale(code);
#endif
    }


    static void setStyle(const QString &stylePath)
    {
        QFile file(stylePath);
        file.open(QFile::ReadOnly);
        QString qss = QLatin1String(file.readAll());
        qApp->setStyleSheet(qss);
    }

    static void loadTranslation()
    {
        QTranslator *translator = new QTranslator(qApp);
        translator->load(":image/translation/qt_zh_CN.qm");
        qApp->installTranslator(translator);
    }

    static QStringList supportFormatsFilterDialogString()
    {
        QStringList filters;
        filters <<"Text files (*.txt)"
               << "Ais files (*.ais)"
               << "Any files (*)";
        return filters;
    }

    //判断是否是IP地址
    static bool IsIP(QString IP)
    {
        QRegExp RegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
        return RegExp.exactMatch(IP);
    }
    //IP正则限制
    static QRegExp getIpRegExp()
    {
        QRegExp IpRx("(?:(?:25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d)))\\.){3}(?:25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d)))");
        return IpRx;
    }

    //端口正则限制
    static QRegExp getPortRegExp()
    {
        QRegExp portRx("([0-9]|[1-9]\\d{1,3}|[1-5]\\d{4}|6[0-5]{2}[0-3][0-5])");
        return portRx;
    }

    //文件是否存在
    static bool FileIsExist(QString strFile)
    {
        QFile tempFile(strFile);
        return tempFile.exists ();
    }


    //延时
    static void Sleep(int sec)
    {
        QTime dieTime = QTime::currentTime().addMSecs(sec);
        while ( QTime::currentTime() < dieTime ) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
    }

    /**
      @brief getFileInfo 打开文件对话框，获取所选中的文件
    */
    static QString getFileInfo()
    {
        QString info;
        QFileDialog dialog;
        dialog.setFileMode(QFileDialog::ExistingFiles);
        dialog.setViewMode(QFileDialog::Detail);
        dialog.setNameFilter("(*.db)");
        if (dialog.exec()){
            //            qDebug()<<dialog.selectedFiles();
            info = dialog.selectedFiles().at(0);
        }
        return info;
    }

    static QString byteArrayToHexStr(QByteArray data)
    {
        QString temp = "";
        QString hex = data.toHex();

        for (int i = 0; i < hex.length(); i = i + 2) {
            temp += hex.mid(i, 2) + " ";
        }

        return temp.trimmed().toUpper();
    }

    /**
      @brief setBtnFlatStyle 设置按钮扁平化样式
    */
    static void setBtnFlatStyle(QPushButton *btn,
                                QString normalColor, QString normalTextColor,
                                QString hoverColor, QString hoverTextColor,
                                QString pressedColor, QString pressedTextColor)
    {
        QStringList qss;
        qss.append(QString("QPushButton{border-style:none;padding:10px;\
                           border-radius:5px;color:%1;background:%2;}").
    arg(normalTextColor).arg(normalColor));
    qss.append(QString("QPushButton:hover{color:%1;background:%2;}")
               .arg(hoverTextColor).arg(hoverColor));
    qss.append(QString("QPushButton:pressed{color:%1;background:%2;}")
               .arg(pressedTextColor).arg(pressedColor));
    btn->setStyleSheet(qss.join(""));
}

/**
      @brief setTxtFlatStyle 设置输入框(QLineEdit)扁平化样式
    */
void setTxtFlatStyle(QLineEdit *txt, QString normalColor,
                     QString focusColor)
{
    QStringList qss;
    qss.append(QString("QLineEdit{border-style:none;padding:6px;\
                       border-radius:5px;border:2px solid %1;}").arg(normalColor));
qss.append(QString("QLineEdit:focus{border:2px solid %1;}").arg(focusColor));
txt->setStyleSheet(qss.join(""));
}

/**
      @brief setBarFlatStyle 设置精度条框(QProgressBar)扁平化样式
    */
void setBarFlatStyle(QProgressBar *bar, QString normalColor,
                     QString chunkColor)
{
    int barHeight = 8;
    int barRadius = 8;

    QStringList qss;
    qss.append(QString("QProgressBar{font:9pt;height:%2px;background:%1;\
                       border-radius:%3px;text-align:center;border:1px solid %1;}")
.arg(normalColor).arg(barHeight).arg(barRadius));
qss.append(QString("QProgressBar:chunk{border-radius:%2px;background-color:%1;}")
           .arg(chunkColor).arg(barRadius));
bar->setStyleSheet(qss.join(""));
}

/**
      @brief setSliderFlatStyle 设置滑块(QSlider)扁平化样式
    */
void setSliderFlatStyle(QSlider *slider, QString normalColor,
                        QString grooveColor, QString handleColor)
{
    int sliderHeight = 8;
    int sliderRadius = 4;
    int handleWidth = 13;
    int handleRadius = 6;
    int handleOffset = 3;

    QStringList qss;
    qss.append(QString("QSlider::groove:horizontal,QSlider::add-page:horizontal{\
                       height:%2px;border-radius:%3px;background:%1;}")
.arg(normalColor).arg(sliderHeight).arg(sliderRadius));
qss.append(QString("QSlider::sub-page:horizontal{height:%2px;border-radius:%3px;\
                   background:%1;}")
.arg(grooveColor).arg(sliderHeight).arg(sliderRadius));
qss.append(QString("QSlider::handle:horizontal{width:%2px;margin-top:-%3px;\
                   margin-bottom:-%3px;border-radius:%4px;"
                                                          "background:qradialgradient(spread:pad,cx:0.5,cy:0.5,\
radius:0.5,fx:0.5,fy:0.5,stop:0.6 #FFFFFF,stop:0.8 %1);}")
.arg(handleColor).arg(handleWidth).arg(handleOffset).arg(handleRadius));
slider->setStyleSheet(qss.join(""));
}
};
#endif // MYHELPER_H
