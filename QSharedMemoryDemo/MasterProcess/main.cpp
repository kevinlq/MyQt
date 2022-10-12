#include <QCoreApplication>
#include <QString>
#include <QUuid>
#include <QSharedMemory>
#include <QProcess>
#include <QBuffer>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc ,argv);

    QString key = QUuid::createUuid().toString();

    // 创建共享内存
    QSharedMemory sharedM(key);
    if (sharedM.isAttached())
    {
        sharedM.detach();
    }

    QVariantMap map;
    map["fun"] = "add";
    map["paramA"] = 1;
    map["paramB"] = 1;

    QJsonDocument doc = QJsonDocument::fromVariant(map);
    QByteArray sendData = doc.toJson();

    sharedM.create(sendData.size());
    sharedM.lock();
    memcpy((char*)sharedM.data(), sendData.data(), sendData.size());
    sharedM.unlock();

    // 启动子进程，等待子进程处理完成后读取子进程处理完成的结果
    QString strChildExePath = QString("%1/%2.exe").arg(QCoreApplication::applicationDirPath()).arg(APP_CHILD);
    QStringList arguments = {key};

    qDebug() << "Begin child process:" << key << sendData;
    QProcess process;
    process.start(strChildExePath, arguments);
    process.waitForStarted();
    process.waitForFinished();

    qDebug() << "End child process result:" << process.exitCode() << process.errorString();

    // 子进程执行结束，再读取一次看看子进程写入的数据是否存在
    QBuffer buf;
    buf.open(QIODevice::WriteOnly);
    buf.write((char*)sharedM.data());
    buf.close();

    qDebug() << "child process read data:" << buf.data();

    return app.exec();
}
