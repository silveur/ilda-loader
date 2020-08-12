#ifndef PALETTE_H
#define PALETTE_H


struct paletteStruct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};



#define ILDA_DEFAULT_PALETTE_SIZE 64
extern const paletteStruct ildaDefaultPalette[ILDA_DEFAULT_PALETTE_SIZE];



#endif  // PALETTE_H
