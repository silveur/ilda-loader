#include "IldaFrame.h"

// Die maximale Anzahl an Punkten kann beliebig verändert werden
#define MAX_NUMBER_OF_POINTS 32768




IldaFrame::IldaFrame(const string &frameName, const string &companyName, int frameNumber, int numberOfFrames)
{
    m_frameName      = frameName;
    m_companyName    = companyName;

    m_frameNumber    = frameNumber;
    m_numberOfFrames = numberOfFrames;
}


IldaFrame::~IldaFrame()
{
}



void IldaFrame::appendPoint(const IldaPoint &point)
{
    if (m_points.size() < MAX_NUMBER_OF_POINTS)
    {
        m_points.push_back(point);
    }
}



int IldaFrame::getNumberOfPoints()  const
{
    return (m_points.size());
}



IldaPoint IldaFrame::getPoint(int index)  const
{
    if (    (index >= 0)
         && (index < m_points.size()))
    {
        return (m_points[index]);
    }


    IldaPoint point;

    point.x       = 0;
    point.y       = 0;
    point.z       = 0;
    point.blanked = true;
    point.r       = 0;
    point.g       = 0;
    point.b       = 0;

    return (point);
}
