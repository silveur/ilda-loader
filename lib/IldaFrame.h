#ifndef ILDA_FRAME_H
#define ILDA_FRAME_H
#include <string>
#include <vector>
using namespace std;

struct Color {
  Color(uint8_t rc, uint8_t gc, uint8_t bc): r(rc), g(gc), b(bc) {}
  uint8_t      r;
  uint8_t      g;
  uint8_t      b;
};

struct IldaPoint
{
    int16_t      x;
    int16_t      y;
    int16_t      z;

    bool        blanked;

    uint8_t      r;
    uint8_t      g;
    uint8_t      b;


    bool isBlanked()  const
    {
        return (blanked);
    }

    Color getColor()  const
    {
        return (Color(r, g, b));
    }
};




class IldaFrame
{
public:

                     IldaFrame          (const string &frameName = string(), const string &companyName = string(), int frameNumber = 0, int numberOfFrames = 1);
                    ~IldaFrame          ();

    void             appendPoint        (const IldaPoint &point);

    int              getNumberOfPoints  ()  const;
    IldaPoint        getPoint           (int index)  const;


private:

    string          m_frameName;
    string          m_companyName;

    int              m_frameNumber;
    int              m_numberOfFrames;

    vector<IldaPoint> m_points;
};



#endif  // ILDA_FRAME_H
