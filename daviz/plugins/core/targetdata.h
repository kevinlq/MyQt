#ifndef TARGET_H
#define TARGET_H

#include <QDateTime>

namespace RadarDisplay {

enum TargetTypes {
    Target_Normal,
    Target_Extrapolated
};

struct TargetData
{
    TargetData() {}
    TargetData(int _id, TargetTypes _type, float _distance, float _azimuth,
               float _elevation, float _height, float _orientation,
               float _speed, int msecs) :
        trackId(_id),
        type(_type),
        distance(_distance),
        azimuth(_azimuth),
        elevation(_elevation),
        height(_height),
        orientation(_orientation),
        speed(_speed),
        milliseconds(msecs)
    {}
    int trackId;
    TargetTypes type;
    float distance;
    float azimuth;
    float elevation;
    float height;
    float orientation;
    float speed;
    int milliseconds;
};

}

#endif // TARGET_H
