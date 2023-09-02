#pragma once

#include <QObject>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>
#include <QRect>
#include <QUrl>
#include <QColor>
#include <QLine>
#include <QPolygon>
#include <QUuid>
#include <QDate>
#include <QTime>
#include <QBitArray>
#include <QLocale>
#include <QDebug>

class DScore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString number READ number WRITE setNumber)

    Q_PROPERTY(QByteArray testByteArray MEMBER testByteArray)

    Q_PROPERTY(QTime testTime MEMBER testTime)
    Q_PROPERTY(QDate testDate MEMBER testDate)
    Q_PROPERTY(QUrl testUrl MEMBER testUrl)
    Q_PROPERTY(QUuid testUuid MEMBER testUuid)
    Q_PROPERTY(QBitArray testBitarray MEMBER testBitarray)
    Q_PROPERTY(QLocale testLocal MEMBER testLocal)

    Q_PROPERTY(QStringList testStringList MEMBER testStringList)
    Q_PROPERTY(QList<int> testIntList MEMBER testIntList)
    Q_PROPERTY(QList<float> testFloatList MEMBER testFloatList)
public:
    Q_INVOKABLE DScore(QObject *parent = nullptr);
    DScore(const DScore &other);

    bool operator ==(const DScore &other);
    DScore &operator =(const DScore &other);
    DScore &operator =(const QVariant &v);

    QJsonObject toJson() const;
    bool fromJson(const QJsonObject &jsObj);

    QString number() const;
    void setNumber(const QString &newNumber);
    QString name() const;
    void setName(const QString &newName);

public:
    QString m_number;
    QString m_name;
    QByteArray testByteArray;
    QTime testTime;
    QDate testDate;
    QUrl testUrl;
    QUuid testUuid;
    QBitArray testBitarray;
    QLocale testLocal;

    QStringList testStringList;
    QList<int> testIntList;
    QList<float> testFloatList;
};
Q_DECLARE_METATYPE(DScore)
Q_DECLARE_METATYPE(DScore*)

QDebug operator<<(QDebug d, const DScore &s);

class DStudent : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString number READ number WRITE setNumber)
    Q_PROPERTY(QString sex READ sex WRITE setSex)
    Q_PROPERTY(QDateTime birthday READ birthday WRITE setBirthda)

    // custome type
    Q_PROPERTY(DScore* sScore READ sScore WRITE setSScore)

    // test other type
    Q_PROPERTY(int testInt READ testInt WRITE setTestInt)
    Q_PROPERTY(bool testBool READ testBool WRITE setTestBool)
    Q_PROPERTY(double testDouble READ testDouble WRITE setTestDouble)
    Q_PROPERTY(char testChar READ testChar WRITE setTestChar)
    Q_PROPERTY(QUrl testUrl READ testUrl WRITE setTestUrl)
    Q_PROPERTY(QVariant testV READ testV WRITE setTestV)
    Q_PROPERTY(QStringList testStringList READ testStringList WRITE setTestStringList)
    Q_PROPERTY(QRect testRect READ testRect WRITE setTestRect)
    Q_PROPERTY(QRectF testRectf READ testRectf WRITE setTestRectf)
    Q_PROPERTY(QSize testSize READ testSize WRITE setTestSize)
    Q_PROPERTY(QSizeF testSizef READ testSizef WRITE setTestSizef)
    Q_PROPERTY(QPoint testPoint READ testPoint WRITE setTestPoint)
    Q_PROPERTY(QPointF testPointf READ testPointf WRITE setTestPointf)
    Q_PROPERTY(QList<int> testIntList READ testIntList WRITE setTestIntList)
    Q_PROPERTY(QList<QString> testListString READ testListString WRITE setTestListString)
    Q_PROPERTY(QList<bool> testBoolList READ testBoolList WRITE setTestBoolList)
    Q_PROPERTY(QList<float> testFloatList READ testFloatList WRITE setTestFloatList)
    Q_PROPERTY(QList<double> testDoubleList READ testDoubleList WRITE setTestDoubleList)

    Q_PROPERTY(QVector<int> testIntVector READ testIntVector WRITE setTestIntVector)

    // gui test
    Q_PROPERTY(QColor testColor READ testColor WRITE setTestColor)  // ok
    Q_PROPERTY(QPolygon testPolygon READ testPolygon WRITE setTestPolygon)  // null--ok
    Q_PROPERTY(QPolygonF testPolygonf READ testPolygonf WRITE setTestPolygonf)
    Q_PROPERTY(QLine testLine READ testLine WRITE setTestLine)
    Q_PROPERTY(QLineF testLinef READ testLinef WRITE setTestLinef)
    Q_PROPERTY(QUuid testUid READ testUid WRITE setTestUid)

public:
    explicit DStudent(QObject *parent = nullptr);

    QJsonObject toJson();
    bool fromJson(const QJsonObject &jsObj);

    QString name() const;
    void setName(const QString &newName);
    QString number() const;
    void setNumber(const QString &newNumber);

    QString sex() const;
    void setSex(const QString &newSex);

    QDateTime birthday() const;
    void setBirthda(const QDateTime &newBirthday);

    QVariant testV() const;
    void setTestV(const QVariant &newTestV);

    QStringList testStringList() const;
    void setTestStringList(const QStringList &newTestStringList);

    QRect testRect() const;
    void setTestRect(const QRect &newTestRect);

    QSize testSize() const;
    void setTestSize(const QSize &newTestSize);

    QPoint testPoint() const;
    void setTestPoint(QPoint newTestPoint);

    int testInt() const;
    void setTestInt(int newTestInt);

    bool testBool() const;
    void setTestBool(bool newTestBool);

    double testDouble() const;
    void setTestDouble(double newTestDouble);

    char testChar() const;
    void setTestChar(char newTestChar);

    QUrl testUrl() const;
    void setTestUrl(const QUrl &newTestUrl);

    QList<int> testIntList() const;
    void setTestIntList(const QList<int> &newTestIntList);

    QList<QString> testListString() const;
    void setTestListString(const QList<QString> &newTestListString);

    DScore *sScore() const;
    void setSScore(DScore *newSScore);

    QList<bool> testBoolList() const;
    void setTestBoolList(const QList<bool> &newTestBoolList);

    QList<float> testFloatList() const;
    void setTestFloatList(const QList<float> &newTestFloatList);

    QList<double> testDoubleList() const;
    void setTestDoubleList(const QList<double> &newTestDoubleList);

    QVector<int> testIntVector() const;
    void setTestIntVector(const QVector<int> &newTestIntVector);

    QColor testColor() const;
    void setTestColor(const QColor &newTestColor);

    QPolygon testPolygon() const;
    void setTestPolygon(const QPolygon &newTestPolygon);

    QPolygonF testPolygonf() const;
    void setTestPolygonf(const QPolygonF &newTestPolygonf);

    QLine testLine() const;
    void setTestLine(const QLine &newTestLine);

    QLineF testLinef() const;
    void setTestLinef(const QLineF &newTestLinef);

    QSizeF testSizef() const;
    void setTestSizef(const QSizeF &newTestSizef);

    QPointF testPointf() const;
    void setTestPointf(QPointF newTestPointf);

    QRectF testRectf() const;
    void setTestRectf(const QRectF &newTestRectf);

    QUuid testUid() const;
    void setTestUid(const QUuid &newTestUid);

private:
    QString m_name = "";
    QString m_number = "";
    QString m_sex = "";
    QDateTime m_birthday;
    QVariant m_testV;
    QStringList m_testStringList;
    QRect m_testRect;
    QSize m_testSize;
    QPoint m_testPoint;
    int m_testInt;
    bool m_testBool;
    double m_testDouble;
    char m_testChar;
    QUrl m_testUrl;
    QList<int> m_testIntList;
    QList<QString> m_testListString;
    DScore *m_sScore;
    QList<bool> m_testBoolList;
    QList<float> m_testFloatList;
    QList<double> m_testDoubleList;
    QVector<int> m_testIntVector;
    QColor m_testColor;
    QPolygon m_testPolygon;
    QPolygonF m_testPolygonf;
    QLine m_testLine;
    QLineF m_testLinef;
    QSizeF m_testSizef;
    QPointF m_testPointf;
    QRectF m_testRectf;
    QUuid m_testUid;
};

