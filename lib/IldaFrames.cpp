#include "IldaFrames.h"
#include "Palette.h"




IldaFrames::IldaFrames()
{
    initIldaPalette();
}


IldaFrames::~IldaFrames()
{
}




bool IldaFrames::openFile(const string &fileName)
{
    m_frames.clear();


    string error;

    error = openIldaFile(fileName);


    if (! error.empty())
    {
        m_frames.clear();
        std::cout <<error << std::endl;
        return (false);
    }


    return (true);
}





//
//
// ILDA Dateien
//
//

void IldaFrames::initIldaPalette()
{
    for (int projector = 0; projector < NUMBER_OF_PROJECTORS; projector++)
    {
        int i;

        for (i = 0; i < ILDA_DEFAULT_PALETTE_SIZE; i++)
        {
            m_paletteRed  [projector][i] = ildaDefaultPalette[i].red;
            m_paletteGreen[projector][i] = ildaDefaultPalette[i].green;
            m_paletteBlue [projector][i] = ildaDefaultPalette[i].blue;
        }

        for (; i < PALETTE_SIZE; i++)
        {
            m_paletteRed  [projector][i] = 255;
            m_paletteGreen[projector][i] = 255;
            m_paletteBlue [projector][i] = 255;
        }
    }
}



bool IldaFrames::seekIlda (istream &file)  const
{
   
     char c1 = 0;
      char c2 = 0;
      char c3 = 0;
      char c4 = 0;

      do
      {
          c1 = c2;
          c2 = c3;
          c3 = c4;
          file.read (&c4, 1);
          if (file.eof())
          {
              return (false);
          }
      }
      while ((c1 != 'I') || (c2 != 'L') || (c3 != 'D') || (c4 != 'A'));

      return (true);
}



string IldaFrames::openIldaFile(const string &fileName)
{
    initIldaPalette();


    if (fileName.empty())
    {
        return string("No file specified!");
    }

    ifstream file (fileName, std::ifstream::binary);

    if (! file)
    {
      return string("Cannot open '%1'!");
    }


    bool anyIlda = false;

    for (;;)
    {
      char * header = new char [32];

        if (! seekIlda(file))
        {
            if (! anyIlda)
            {
                file.close();
                return string("No ILDA header found!");
            }

            if (file.eof())
            {
                // Missing end of file header!

                file.close();
                return (string());
            }
            else
            {
                file.close();
                return string("Error reading file!");
            }
        }

        anyIlda = true;

      
        file.read (&header[4], 28);
        std::cout << header << std::endl;
//        if (file.read((char *) &header[4], 28) != 28)
//        {
//            file.close();
//            return string("Invalid ILDA header!");
//        }


        uint32_t format = (header[4] << 24) | (header[5] << 16) | (header[6] << 8) | header[7];

        if (    (format == 0)
             || (format == 1)
             || (format == 2)
             || (format == 4)
             || (format == 5))
        {
            int i;

            string frameName;

            for (i = 8; i < 16 && header[i] != 0; i++)
            {
                frameName += header[i];
            }

            string companyName;

            for (i = 16; i < 24 && header[i] != 0; i++)
            {
                companyName += header[i];
            }

            uint16_t numberOfRecords = (header[24] << 8) | header[25];
            uint16_t frameNumber     = (header[26] << 8) | header[27];
            uint16_t numberOfFrames  = (header[28] << 8) | header[29];
            uint8_t  projector       =  header[30];
            uint8_t  future          =  header[31];

            (void) future;

            if (numberOfRecords == 0)
            {
                //
                // End-Of-File Header
                //
                if (file.eof())
                {
                    file.close();
                    return (string());
                }
                else
                {
                    // Data follow after end of file header!

                    file.close();
                    return (string());
                }
            }


            if (format == 0)
            {
                //
                // Format 0  (3D Coordinates with Indexed Color)
                //
                IldaFrame frame(frameName, companyName, frameNumber, numberOfFrames);

                for (i = 0; i < numberOfRecords; i++)
                {
                  std::cout << "Record:" + to_string(i) << std::endl;
                  char * buffer = new char [8];
                  file.read (buffer, 8);
                  std::cout << buffer << std::endl;
//                  if (is)
//                    {
//                        file.close();
//                        return string("Invalid data section (Format 0)!");
//                    }

                    IldaPoint point;

                    point.x = (buffer[0] << 8) | buffer[1];
                    point.y = (buffer[2] << 8) | buffer[3];
                    point.z = (buffer[4] << 8) | buffer[5];

                    point.blanked = ((buffer[6] & (1<<6)) != 0);

                    uint8_t colorIndex = buffer[7];

                    point.r = m_paletteRed  [projector][colorIndex];
                    point.g = m_paletteGreen[projector][colorIndex];
                    point.b = m_paletteBlue [projector][colorIndex];

                    frame.appendPoint(point);
                }

                m_frames.push_back(frame);
            }
            else if (format == 1)
            {
                //
                // Format 1  (2D Coordinates with Indexed Color)
                //
                IldaFrame frame(frameName, companyName, frameNumber, numberOfFrames);

                for (i = 0; i < numberOfRecords; i++)
                {
                    uint8_t buffer[6];
                  std::string line;
                  std::getline(file, line);
                  if (line.length() != 6)
                    {
                        file.close();
                        return string("Invalid data section (Format 1)!");
                    }

                    IldaPoint point;

                    point.x = (buffer[0] << 8) | buffer[1];
                    point.y = (buffer[2] << 8) | buffer[3];
                    point.z = 0;

                    point.blanked = ((buffer[4] & (1<<6)) != 0);

                    uint8_t colorIndex = buffer[5];

                    point.r = m_paletteRed  [projector][colorIndex];
                    point.g = m_paletteGreen[projector][colorIndex];
                    point.b = m_paletteBlue [projector][colorIndex];

                    frame.appendPoint(point);
                }

                m_frames.push_back(frame);
            }
            else if (format == 2)
            {
                //
                // Format 2  (Color Palette for Indexed Color Frames)
                //
                for (i = 0; i < numberOfRecords; i++)
                {
                    uint8_t buffer[3];
                    std::string line;
                    std::getline(file, line);
                  if (line.length() != 3)
                    {
                        file.close();
                        return string("Invalid data section (Format 2)!");
                    }

                    uint8_t r = buffer[0];
                    uint8_t g = buffer[1];
                    uint8_t b = buffer[2];

                    if (i >= 0 && i < PALETTE_SIZE)
                    {
                        m_paletteRed  [projector][i] = r;
                        m_paletteGreen[projector][i] = g;
                        m_paletteBlue [projector][i] = b;
                    }
                }
            }
            else if (format == 4)
            {
                //
                // Format 4  (3D Coordinates with True Color)
                //
                IldaFrame frame(frameName, companyName, frameNumber, numberOfFrames);

                for (i = 0; i < numberOfRecords; i++)
                {
                    uint8_t buffer[10];
                    std::string line;
                    std::getline(file, line);
                  if (line.length() != 10)
                    {
                        file.close();
                        return string("Invalid data section (Format 4)!");
                    }

                    IldaPoint point;

                    point.x = (buffer[0] << 8) | buffer[1];
                    point.y = (buffer[2] << 8) | buffer[3];
                    point.z = (buffer[4] << 8) | buffer[5];

                    point.blanked = ((buffer[6] & (1<<6)) != 0);

                    point.b = buffer[7];
                    point.g = buffer[8];
                    point.r = buffer[9];

                    frame.appendPoint(point);
                }

                m_frames.push_back(frame);
            }
            else if (format == 5)
            {
                //
                // Format 5  (2D Coordinates with True Color)
                //
                IldaFrame frame(frameName, companyName, frameNumber, numberOfFrames);

                for (i = 0; i < numberOfRecords; i++)
                {
                    uint8_t buffer[8];
                    std::string line;
                    std::getline(file, line);
                  if (line.length() != 8)
                    {
                        file.close();
                        return string("Invalid data section (Format 5)!");
                    }

                    IldaPoint point;

                    point.x = (buffer[0] << 8) | buffer[1];
                    point.y = (buffer[2] << 8) | buffer[3];
                    point.z =  0;

                    point.blanked = ((buffer[4] & (1<<6)) != 0);

                    point.b = buffer[5];
                    point.g = buffer[6];
                    point.r = buffer[7];

                    frame.appendPoint(point);
                }

                m_frames.push_back(frame);
           }
        }
        else
        {
            file.close();
            return (string("Unknown format (%1)!"));
        }
    }
}
