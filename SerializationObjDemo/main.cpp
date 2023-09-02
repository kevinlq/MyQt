#include <QCoreApplication>
#include <QJsonDocument>
#include "DStudent.h"
#include "KSerialize.h"

#define JSON_PRINT(x) QJsonDocument(x).toJson().constData()

int main(/*int argc, char *argv[]*/)
{
    // From::function() const
    qRegisterMetaType<DScore>("DScore");

    DStudent st;
    st.setName(QStringLiteral("法外狂徒张三"));
    st.setNumber("123456789");
    st.setSex(QStringLiteral("男"));
    st.setBirthda(QDateTime::currentDateTime());

    // test other type
    st.setTestInt(10);
    st.setTestBool(true);
    st.setTestV(12);
    st.setTestDouble(12.121212);
    st.setTestChar('k');        //->string
    st.setTestUrl(QUrl("http://kevinlq.com/")); // -> string
    st.setTestStringList(QStringList() << "stringList1" << "stringList2");
    st.setTestRect(QRect(10,10,10,10));             // null
    st.setTestRectf(QRectF(10.1,10.2,10.3,10.4));  // null
    st.setTestSize(QSize(10,10));                   // null
    st.setTestSizef(QSizeF(10.1,10.2));           // null
    st.setTestPoint(QPoint(10, 10));                // null
    st.setTestPointf(QPointF(10.1, 10.2));        // null
    st.setTestIntList({11, 12});                    // null
    st.setTestLine(QLine(1,2,3,4));
    st.setTestLinef(QLineF(1.1,2.2,3.3,4.4));
    st.setTestListString({"kevinlq", "devstone"});  // null
    st.setTestBoolList({true, false});
    st.setTestFloatList({0.1f, 0.2f});
    st.setTestDoubleList({0.001, 0.002});

    st.setTestIntVector({21, 22});

    // gui
    st.setTestColor(QColor(255, 0, 0, 255));
    st.setTestUid(QUuid::createUuid());

    QPolygon pl({QPoint(1,1), QPoint(1,2)});
    QPolygonF plf({QPointF(1.1,1.2), QPointF(2.2,2.3), QPointF(3.3, 3.4)});
    st.setTestPolygon(pl);
    st.setTestPolygonf(plf);

    DScore *score = new DScore;
    score->setName("computer");
    score->setNumber("001");
    score->testStringList = QStringList{"s1", "s2", "s3", "s4"};
    score->testIntList = {1,2,3,4};
    score->testFloatList = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
    score->testTime = QTime::currentTime();
    score->testDate = QDate::currentDate();
    score->testUrl = QUrl("http://127.0.0.1");
    score->testUuid = QUuid::createUuid();

    QBitArray bitArray(10, true);
    bitArray.setBit(0, false);
    score->testBitarray = bitArray;
    score->testLocal = QLocale(QLocale::Chinese, QLocale::China);

    QByteArray byteArray;
    byteArray.append("byteAyyay1 ");
    byteArray.append("byteAyyay2 ");
    byteArray.append("byteAyyay3 ");
    score->testByteArray = byteArray;

    st.setSScore(score);                            // null


    //QJsonObject jsObj = st.toJson();
    //qDebug() << "st:" << jsObj;
    // serial obj from json
    //DStudent st2;
    //st2.fromJson(jsObj);

    //QJsonObject jsObj2 = st2.toJson();
    //qDebug() << "st2:" << jsObj2;

    // KSerialize
    KSerialize serial;

    auto json = serial.serialize(score);
    qDebug() << "score:" << JSON_PRINT(json.toObject());

    //json = serial.serialize(&st);
    //qDebug() << "st:" << JSON_PRINT(json.toObject());

    auto deserScore = serial.deserialize<DScore*>(json);
    qDebug() << "deserialize result:";
    qDebug() << "name:" << deserScore->name();
    qDebug() << "number:" << deserScore->number();
    qDebug() << "testDate:" << deserScore->testDate;
    qDebug() << "testTime:" << deserScore->testTime;
    qDebug() << "testUrl:" << deserScore->testUrl;
    qDebug() << "testUuid:" << deserScore->testUuid;
    qDebug() << "testStringList:" << deserScore->testStringList;
    qDebug() << "testIntList:" << deserScore->testIntList;
    qDebug() << "testFloatList:" << deserScore->testFloatList;
    qDebug() << "testBitarray:" << deserScore->testBitarray;
    qDebug() << "testByteArray:" << deserScore->testByteArray;
    qDebug() << "testLocal:" << deserScore->testLocal;

}
