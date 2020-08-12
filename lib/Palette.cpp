#include "Palette.h"



//
// Suggested Default Color Palette (siehe "ILDA_IDTF14_rev011.pdf" Appendix A)
//
// The color palette described here was originally developed by LFI and Aura Technologies.
// It contains 64 colors of the full saturated hues and white.
// This color palette is used by most ILDA files that do not contain a color palette,
// including the ILDA test pattern.
//
const paletteStruct ildaDefaultPalette[ILDA_DEFAULT_PALETTE_SIZE] =
{
    //
    // Red   Green   Blue            Index
    //
    {  255,     0,     0  },     //    0        Red
    {  255,    16,     0  },     //    1
    {  255,    32,     0  },     //    2
    {  255,    48,     0  },     //    3
    {  255,    64,     0  },     //    4
    {  255,    80,     0  },     //    5
    {  255,    96,     0  },     //    6
    {  255,   112,     0  },     //    7
    {  255,   128,     0  },     //    8
    {  255,   144,     0  },     //    9
    {  255,   160,     0  },     //   10
    {  255,   176,     0  },     //   11
    {  255,   192,     0  },     //   12
    {  255,   208,     0  },     //   13
    {  255,   224,     0  },     //   14
    {  255,   240,     0  },     //   15

    {  255,   255,     0  },     //   16        Yellow
    {  224,   255,     0  },     //   17
    {  192,   255,     0  },     //   18
    {  160,   255,     0  },     //   19
    {  128,   255,     0  },     //   20
    {   96,   255,     0  },     //   21
    {   64,   255,     0  },     //   22
    {   32,   255,     0  },     //   23
    {    0,   255,     0  },     //   24        Green
    {    0,   255,    36  },     //   25
    {    0,   255,    73  },     //   26
    {    0,   255,   109  },     //   27
    {    0,   255,   146  },     //   28
    {    0,   255,   182  },     //   29
    {    0,   255,   219  },     //   30
    {    0,   255,   255  },     //   31        Cyan

    {    0,   227,   255  },     //   32
    {    0,   198,   255  },     //   33
    {    0,   170,   255  },     //   34
    {    0,   142,   255  },     //   35
    {    0,   113,   255  },     //   36
    {    0,    85,   255  },     //   37
    {    0,    56,   255  },     //   38
    {    0,    28,   255  },     //   39
    {    0,     0,   255  },     //   40        Blue
    {   32,     0,   255  },     //   41
    {   64,     0,   255  },     //   42
    {   96,     0,   255  },     //   43
    {  128,     0,   255  },     //   44
    {  160,     0,   255  },     //   45
    {  192,     0,   255  },     //   46
    {  224,     0,   255  },     //   47

    {  255,     0,   255  },     //   48        Magenta
    {  255,    32,   255  },     //   49
    {  255,    64,   255  },     //   50
    {  255,    96,   255  },     //   51
    {  255,   128,   255  },     //   52
    {  255,   160,   255  },     //   53
    {  255,   192,   255  },     //   54
    {  255,   224,   255  },     //   55
    {  255,   255,   255  },     //   56        White
    {  255,   224,   224  },     //   57
    {  255,   192,   192  },     //   58
    {  255,   160,   160  },     //   59
    {  255,   128,   128  },     //   60
    {  255,    96,    96  },     //   61
    {  255,    64,    64  },     //   62
    {  255,    32,    32  },     //   63
};
