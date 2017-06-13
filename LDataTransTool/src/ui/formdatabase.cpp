#include "formdatabase.h"
#include "ui_formdatabase.h"
#include "util/config.h"

#include "db/ConnectionPool.h"
#include "db/ldbhandle.h"

#include <QSqlDatabase>

#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>

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
}

QString FormDatabase::getFileInfo()
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


    //QFileInfo fileInfo(m_file);

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
