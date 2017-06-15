#include "formdatabase.h"
#include "ui_formdatabase.h"
#include "util/config.h"

#include "db/ConnectionPool.h"
#include "db/ldbhandle.h"

#include "db/readfieldobj.h"

#include <QSqlDatabase>

#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include <QThread>

FormDatabase::FormDatabase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDatabase)
{
    ui->setupUi(this);

    init ();
}

FormDatabase::~FormDatabase()
{
    delete ui;
}

void FormDatabase::init()
{
    ui->lineEdit_dbName->installEventFilter(this);
    ui->radioButton_sqlite->setChecked(true);
    if (ui->radioButton_sqlite->isChecked()){
        ui->lineEdit_dbIp->setEnabled(false);
        ui->lineEdit_dbPort->setEnabled(false);
        ui->lineEdit_dbUserName->setEnabled(false);
        ui->lineEdit_dbPwd->setEnabled(false);
    }

    m_file = "";

    m_preadObj = new ReadFieldObj;
    m_preadThread = new QThread;
    m_preadObj->moveToThread(m_preadThread);
    connect(m_preadThread,SIGNAL(started()),
            m_preadObj,SLOT(slotStartReadDbField()));
    connect(qApp,SIGNAL(aboutToQuit()),
            m_preadObj,SLOT(deleteLater()));
    connect(m_preadObj,SIGNAL(destroyed(QObject*)),
            m_preadThread,SLOT(quit()));

    connect(m_preadObj,SIGNAL(signalSendDbField(QString)),
            this,SIGNAL(signalSendDbFieldInfo(QString)));
}

QString FormDatabase::getFileInfo()
{
    QString info;
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter("(*.db)");
    if (dialog.exec()){
        info = dialog.selectedFiles().at(0);
    }

    return info;
}

void FormDatabase::showSqliteInfo()
{
    m_file = getFileInfo();
    ui->lineEdit_dbName->setText(m_file);
}

//打开数据库
void FormDatabase::on_pbn_openDb_clicked()
{
    Config &config = Singleton<Config>::getInstance();

    QString type;
    QString dbName = ui->lineEdit_dbName->text();
    QString dbIp = ui->lineEdit_dbIp->text();
    int dbPort = ui->lineEdit_dbPort->text().toInt();
    QString dbUser = ui->lineEdit_dbUserName->text();
    QString dbPwd = ui->lineEdit_dbPwd->text();

    if (dbName.isEmpty() || dbIp.isEmpty() || dbUser.isEmpty() || dbPwd.isEmpty())
        return;

    if (ui->radioButton_sqlite->isChecked())
        type = "QSQLITE";
    else type = "QMYSQL";

    QVariantMap params;
    params["type"]          = type;
    params["host"]          = dbIp;
    params["port"]          = dbPort;
    params["database_name"] = dbName;
    params["username"]      = dbUser;
    params["password"]      = dbPwd;

    config.writeInitfile("database",params);

    ui->comboBox_tableField->clear();
    ui->comboBox_tableName->clear();

    ui->comboBox_tableName->addItems(LDbHandle::getTableNames());
}

bool FormDatabase::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->lineEdit_dbName)
    {
        if (event->type() == QEvent::MouseButtonDblClick)
        {
            showSqliteInfo();
        }
    }
    return QWidget::eventFilter(obj,event);
}

void FormDatabase::on_comboBox_tableName_currentIndexChanged(const QString &arg1)
{
    ui->comboBox_tableField->clear();
    ui->comboBox_tableField->addItems(LDbHandle::getTableFieldNames(arg1));
}

void FormDatabase::on_radioButton_mysql_toggled(bool checked)
{
    ui->lineEdit_dbIp->setEnabled(checked);
    ui->lineEdit_dbPort->setEnabled(checked);
    ui->lineEdit_dbUserName->setEnabled(checked);
    ui->lineEdit_dbPwd->setEnabled(checked);
}

void FormDatabase::on_pbn_read_clicked()
{
    if (!m_preadThread->isRunning())
        m_preadThread->start();
}

void FormDatabase::on_comboBox_tableField_currentIndexChanged(const QString &arg1)
{

    Q_UNUSED(arg1);

    m_preadObj->setTablInfo(ui->comboBox_tableName->currentText(),
                            ui->comboBox_tableField->currentText());
}
