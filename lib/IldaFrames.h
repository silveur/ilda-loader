#ifndef ILDA_FRAMES_H
#define ILDA_FRAMES_H

#include "IldaFrame.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class IldaFrames
{
public:

                     IldaFrames             ();
                    ~IldaFrames             ();

    bool             openFile               (const string &fileName);


private:

    //
    // Methoden zum Einladen von ILDA Dateien
    //
    void             initIldaPalette        ();

    bool             seekIlda               (fstream &file)  const;

    string          openIldaFile           (const string &fileName);


private:

    //
    // Allgemeine Variablen
    //
    vector<IldaFrame> m_frames;


    //
    // Variablen für das Einladen von ILDA Dateien
    //
    #define NUMBER_OF_PROJECTORS    256
    #define PALETTE_SIZE            256
    uint8_t           m_paletteRed  [NUMBER_OF_PROJECTORS][PALETTE_SIZE];
    uint8_t           m_paletteGreen[NUMBER_OF_PROJECTORS][PALETTE_SIZE];
    uint8_t           m_paletteBlue [NUMBER_OF_PROJECTORS][PALETTE_SIZE];
};



#endif  // ILDA_FRAMES_H
