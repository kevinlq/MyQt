#ifndef PLOT_H
#define PLOT_H

#include <QDateTime>

namespace RadarDisplay {

struct PlotData
{
    PlotData() {}
    PlotData(int _id, float _distance, float _azimuth, float _elevation,
             float _height, int msecs) :
        id(_id),
        distance(_distance),
        azimuth(_azimuth),
        elevation(_elevation),
        height(_height),
        milliSeconds(msecs)
    {}
    int id;
    float distance;
    float azimuth;
    float elevation;
    float height;
    int milliSeconds;
};

}

#endif // PLOT_H
