#include <QString>
#include <QSharedMemory>
#include <QProcess>
#include <QBuffer>
#include <QDebug>
#include <QJsonDocument>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        qWarning() << "command size error ";
        return 0;
    }

    QString key = argv[1];

    // 创建共享内存
    QSharedMemory sharedM(key);
    if(!sharedM.attach())
    {
        qWarning() << "can not attach shared memory!";
        return 0;
    }

    sharedM.lock();
    QBuffer buf;
    buf.open(QIODevice::WriteOnly);
    buf.write((char*)sharedM.data());
    buf.close();

    QByteArray baContent = buf.data();

    // 清空共享内存段数据
    char * pPath = (char*)sharedM.data();
    memset(pPath, ' \0 ' , strlen(pPath) + 1 ) ;

    QJsonDocument doc = QJsonDocument::fromJson(baContent);
    QVariantMap map = doc.toVariant().toMap();

    qDebug() << "read memory data:" << buf.data();

    QString fun = map.value("fun").toString();
    int paramA = map.value("paramA").toInt();
    int paramB = map.value("paramB").toInt();

    baContent = "error";
    if(fun == "add")
    {
        baContent = QString::number(paramA+paramB).toLocal8Bit();
    }

    // 计算结果写入共享内存
    memcpy((char*)sharedM.data(), baContent.data(), baContent.size());

    sharedM.unlock();

    return 0;
}
