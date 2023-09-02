#include "DStudent.h"
#include "KHelper.h"
#include "KHelper_p.h"

QDebug operator<<(QDebug dbg, const DScore &s)
{
    QDebugStateSaver saver(dbg);
    dbg.nospace() << "DScore(" << "name:" << s.name() << ',' << "number:" << s.number() << ')';
    return dbg;
}

DScore::DScore(QObject *parent)
    : QObject(parent)
{
    setObjectName("DScore");
}

DScore::DScore(const DScore &other)
{
    this->setName(other.name());
    this->setNumber(other.number());
}

bool DScore::operator ==(const DScore &other)
{
    if(this->name() == other.name()
        && this->number() == other.number())
    {
        return true;
    }
    return false;
}

DScore &DScore::operator =(const DScore &other)
{
    if(this != &other)
    {
        this->setName(other.name());
        this->setNumber(other.number());
    }
    return *this;
}

DScore &DScore::operator =(const QVariant &v)
{
    fromJson(v.toJsonObject());
    qDebug() << "= " << v;
    return *this;
}

QJsonObject DScore::toJson() const
{
    return KJsonHelp::instance()->object2Json(this);
}

bool DScore::fromJson(const QJsonObject &jsObj)
{
    return KJsonHelp::instance()->json2Object(jsObj, this);
}

QString DScore::name() const
{
    return m_name;
}

void DScore::setName(const QString &newName)
{
    m_name = newName;
}

QString DScore::number() const
{
    return m_number;
}

void DScore::setNumber(const QString &newNumber)
{
    m_number = newNumber;
}


DStudent::DStudent(QObject *parent)
    : QObject{parent}
{
}

#define JSON_PRINT(x) QJsonDocument(x).toJson().constData()

QJsonObject DStudent::toJson()
{
    QJsonObject jsObj = KJsonHelp::instance()->object2Json(this);
    //jsObj.insert("sScore", m_sScore.toJson());

    auto v = KJsonHelp::instance()->serialize(this);
    //qDebug() << "v serial:" << v;
    qDebug() << "json :" << JSON_PRINT(v.toObject());

    return jsObj;
}

bool DStudent::fromJson(const QJsonObject &jsObj)
{
    return KJsonHelp::instance()->json2Object(jsObj, this);
}

QString DStudent::name() const
{
    return m_name;
}

void DStudent::setName(const QString &newName)
{
    m_name = newName;
}

QString DStudent::number() const
{
    return m_number;
}

void DStudent::setNumber(const QString &newNumber)
{
    m_number = newNumber;
}

QString DStudent::sex() const
{
    return m_sex;
}

void DStudent::setSex(const QString &newSex)
{
    m_sex = newSex;
}

QDateTime DStudent::birthday() const
{
    return m_birthday;
}

void DStudent::setBirthda(const QDateTime &newBirthday)
{
    m_birthday = newBirthday;
}

QVariant DStudent::testV() const
{
    return m_testV;
}

void DStudent::setTestV(const QVariant &newTestV)
{
    m_testV = newTestV;
}

QStringList DStudent::testStringList() const
{
    return m_testStringList;
}

void DStudent::setTestStringList(const QStringList &newTestStringList)
{
    m_testStringList = newTestStringList;
}

QRect DStudent::testRect() const
{
    return m_testRect;
}

void DStudent::setTestRect(const QRect &newTestRect)
{
    m_testRect = newTestRect;
}

QSize DStudent::testSize() const
{
    return m_testSize;
}

void DStudent::setTestSize(const QSize &newTestSize)
{
    m_testSize = newTestSize;
}

QPoint DStudent::testPoint() const
{
    return m_testPoint;
}

void DStudent::setTestPoint(QPoint newTestPoint)
{
    m_testPoint = newTestPoint;
}

int DStudent::testInt() const
{
    return m_testInt;
}

void DStudent::setTestInt(int newTestInt)
{
    m_testInt = newTestInt;
}

bool DStudent::testBool() const
{
    return m_testBool;
}

void DStudent::setTestBool(bool newTestBool)
{
    m_testBool = newTestBool;
}

double DStudent::testDouble() const
{
    return m_testDouble;
}

void DStudent::setTestDouble(double newTestDouble)
{
    m_testDouble = newTestDouble;
}

char DStudent::testChar() const
{
    return m_testChar;
}

void DStudent::setTestChar(char newTestChar)
{
    m_testChar = newTestChar;
}

QUrl DStudent::testUrl() const
{
    return m_testUrl;
}

void DStudent::setTestUrl(const QUrl &newTestUrl)
{
    m_testUrl = newTestUrl;
}

QList<int> DStudent::testIntList() const
{
    return m_testIntList;
}

void DStudent::setTestIntList(const QList<int> &newTestIntList)
{
    m_testIntList = newTestIntList;
}

QList<QString> DStudent::testListString() const
{
    return m_testListString;
}

void DStudent::setTestListString(const QList<QString> &newTestListString)
{
    m_testListString = newTestListString;
}

DScore* DStudent::sScore() const
{
    return m_sScore;
}

void DStudent::setSScore(DScore *newSScore)
{
    m_sScore = newSScore;
}

QList<bool> DStudent::testBoolList() const
{
    return m_testBoolList;
}

void DStudent::setTestBoolList(const QList<bool> &newTestBoolList)
{
    m_testBoolList = newTestBoolList;
}

QList<float> DStudent::testFloatList() const
{
    return m_testFloatList;
}

void DStudent::setTestFloatList(const QList<float> &newTestFloatList)
{
    m_testFloatList = newTestFloatList;
}

QList<double> DStudent::testDoubleList() const
{
    return m_testDoubleList;
}

void DStudent::setTestDoubleList(const QList<double> &newTestDoubleList)
{
    m_testDoubleList = newTestDoubleList;
}

QVector<int> DStudent::testIntVector() const
{
    return m_testIntVector;
}

void DStudent::setTestIntVector(const QVector<int> &newTestIntVector)
{
    m_testIntVector = newTestIntVector;
}

QColor DStudent::testColor() const
{
    return m_testColor;
}

void DStudent::setTestColor(const QColor &newTestColor)
{
    m_testColor = newTestColor;
}

QPolygon DStudent::testPolygon() const
{
    return m_testPolygon;
}

void DStudent::setTestPolygon(const QPolygon &newTestPolygon)
{
    m_testPolygon = newTestPolygon;
}

QPolygonF DStudent::testPolygonf() const
{
    return m_testPolygonf;
}

void DStudent::setTestPolygonf(const QPolygonF &newTestPolygonf)
{
    m_testPolygonf = newTestPolygonf;
}

QLine DStudent::testLine() const
{
    return m_testLine;
}

void DStudent::setTestLine(const QLine &newTestLine)
{
    m_testLine = newTestLine;
}

QLineF DStudent::testLinef() const
{
    return m_testLinef;
}

void DStudent::setTestLinef(const QLineF &newTestLinef)
{
    m_testLinef = newTestLinef;
}

QSizeF DStudent::testSizef() const
{
    return m_testSizef;
}

void DStudent::setTestSizef(const QSizeF &newTestSizef)
{
    m_testSizef = newTestSizef;
}

QPointF DStudent::testPointf() const
{
    return m_testPointf;
}

void DStudent::setTestPointf(QPointF newTestPointf)
{
    m_testPointf = newTestPointf;
}

QRectF DStudent::testRectf() const
{
    return m_testRectf;
}

void DStudent::setTestRectf(const QRectF &newTestRectf)
{
    m_testRectf = newTestRectf;
}

QUuid DStudent::testUid() const
{
    return m_testUid;
}

void DStudent::setTestUid(const QUuid &newTestUid)
{
    m_testUid = newTestUid;
}
