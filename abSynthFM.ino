#include "notedefs.h"
#include "FMSynth.h"
#include "Arduboy2.h"
Arduboy2 arduboy;

#define DRAW_PIXEL(x,y,c)    arduboy.drawPixel((x), (y), (c));
#define GET_PIXEL(x,y)      arduboy.getPixel((x), (y))
#define DRAW_LINE(fx,fy,tx,ty,c) arduboy.drawLine((fx),(fy),(tx),(ty),(c))
#define DRAW_BITMAP(x,y,b,w,h,c) arduboy.drawBitmap((x), (y), (b), (w), (h), (c))
#define DRAW_RECT(x,y,w,h,c)  arduboy.drawRect((x), (y), (w), (h), (c))
#define FILL_RECT(x,y,w,h,c)  arduboy.fillRect((x), (y), (w), (h), (c))
#define DRAW_H_LINE(x,y,l,c)  arduboy.drawFastHLine((x),(y),(l),(c))
#define DRAW_V_LINE(x,y,l,c)  arduboy.drawFastVLine((x),(y),(l),(c))
#define G_TXT_CURSOR(c,r)   arduboy.setCursor((c),(r))
#define G_PRINT(s)        arduboy.print((s))
#define G_DRAWCHAR(x, y, ch, c)    arduboy.drawChar(x,y,ch,c,((c)==0),1)
#define G_CLEAR()   arduboy.clear()

#define KEY_PRESSED(k)    arduboy.pressed((k))
#define KEY_NOT_PRESSED(k)  arduboy.notPressed((k))

void draw_string(uint8_t x, uint8_t y, const char *s, uint8_t color) {
  while (*s) {
    G_DRAWCHAR(x, y, *s++, color);
    x += 6;
  }
}

void draw_2digit(uint8_t x, uint8_t y, uint8_t n, uint8_t color) {
  G_DRAWCHAR(x, y, '0' + n / 10, color);
  G_DRAWCHAR(x + 6, y, '0' + n % 10, color);
}


const unsigned char PROGMEM synth_img[] =
{
  //width = 128, height = 64
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0x02, 0x01, 0xc2, 0xe4, 0xc2, 0x01, 0x02, 0xa4, 0xf2, 0xf1,
  0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1,
  0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1,
  0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1,
  0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1,
  0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1,
  0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1,
  0xf2, 0xf4, 0x02, 0x11, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0x80, 0x00, 0x86, 0x4e, 0x86, 0x00, 0x80, 0x4a, 0x9f, 0x1f,
  0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f,
  0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f,
  0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f,
  0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f,
  0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f,
  0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f,
  0x9f, 0x5f, 0x80, 0x11, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11, 0x02, 0xa4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1,
  0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0x01, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11,
  0x02, 0xa4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0x01,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11, 0x02, 0xa4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1,
  0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0x01, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11,
  0x02, 0xa4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0x01,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11, 0x02, 0xa4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1,
  0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0x01, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11, 0x80, 0x4a, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f,
  0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x00, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11,
  0x80, 0x4a, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x00,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11, 0x80, 0x4a, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f,
  0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x00, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11,
  0x80, 0x4a, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x00,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11, 0x80, 0x4a, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f,
  0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x00, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0xf1, 0x7a, 0x1c, 0x0e, 0x07, 0x06, 0x03, 0x03, 0x03,
  0x03, 0x03, 0x06, 0x07, 0x0e, 0x1c, 0x7a, 0xf1, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0xf1,
  0x7a, 0x1c, 0x0e, 0x07, 0x06, 0x03, 0x03, 0x03, 0x03, 0x03, 0x06, 0x07, 0x0e, 0x1c, 0x7a, 0xf1,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0xf1, 0x7a, 0x1c, 0x0e, 0x07, 0x06, 0x03, 0x03, 0x03,
  0x03, 0x03, 0x06, 0x07, 0x0e, 0x1c, 0x7a, 0xf1, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0xf1,
  0x7a, 0x1c, 0x0e, 0x07, 0x06, 0x03, 0x03, 0x03, 0x03, 0x03, 0x06, 0x07, 0x0e, 0x1c, 0x7a, 0xf1,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0xf1, 0x7a, 0x1c, 0x0e, 0x07, 0x06, 0x03, 0x03, 0x03,
  0x03, 0x03, 0x06, 0x07, 0x0e, 0x1c, 0x7a, 0xf1, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaf, 0x3f, 0xf0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xf0, 0x3f, 0xaf, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaf, 0x3f,
  0xf0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xf0, 0x3f,
  0xaf, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaf, 0x3f, 0xf0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xf0, 0x3f, 0xaf, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaf, 0x3f,
  0xf0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xf0, 0x3f,
  0xaf, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaf, 0x3f, 0xf0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xf0, 0x3f, 0xaf, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x04, 0x2a, 0x11, 0x2a, 0x85, 0xab, 0x93, 0xab, 0x86, 0xae, 0x16,
  0xae, 0x86, 0xab, 0x93, 0xab, 0x85, 0x2a, 0x11, 0x2a, 0x04, 0x2a, 0x51, 0x2a, 0x04, 0xaa, 0x11,
  0x2a, 0x05, 0xab, 0x13, 0xab, 0x86, 0x2e, 0x96, 0xae, 0x06, 0xab, 0x93, 0x2b, 0x85, 0xaa, 0x91,
  0xaa, 0x04, 0x2a, 0x51, 0x2a, 0x04, 0x2a, 0x11, 0x2a, 0x85, 0xab, 0x93, 0xab, 0x86, 0xae, 0x16,
  0x2e, 0x86, 0xab, 0x13, 0x2b, 0x05, 0x2a, 0x11, 0x2a, 0x04, 0x2a, 0x51, 0x2a, 0x04, 0x2a, 0x91,
  0xaa, 0x85, 0xab, 0x93, 0xab, 0x06, 0x2e, 0x96, 0xae, 0x86, 0xab, 0x93, 0x2b, 0x05, 0x2a, 0x91,
  0xaa, 0x04, 0x2a, 0x51, 0x2a, 0x04, 0xaa, 0x91, 0xaa, 0x85, 0xab, 0x93, 0x2b, 0x06, 0xae, 0x96,
  0xae, 0x86, 0xab, 0x13, 0x2b, 0x05, 0xaa, 0x91, 0xaa, 0x04, 0x2a, 0x11, 0xaa, 0x44, 0xaa, 0x11,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x00, 0x80, 0x00, 0x80, 0x3f, 0xbf, 0x04, 0x84, 0x04, 0x80, 0x00,
  0xbf, 0x3f, 0xa4, 0x24, 0xa4, 0x3f, 0x9b, 0x00, 0x80, 0x00, 0x80, 0x55, 0x80, 0x00, 0xbf, 0x3f,
  0x8e, 0x3f, 0xbf, 0x00, 0x9f, 0x3f, 0xa0, 0x3f, 0x9f, 0x00, 0xbf, 0x3f, 0xa0, 0x00, 0xbf, 0x3f,
  0x80, 0x00, 0x80, 0x55, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x3f, 0xbf, 0x00, 0x80, 0x00,
  0x80, 0x3f, 0xbf, 0x20, 0xa0, 0x20, 0xa0, 0x00, 0x80, 0x00, 0x80, 0x55, 0x80, 0x00, 0x80, 0x20,
  0xbf, 0x3f, 0xa0, 0x20, 0xbf, 0x1f, 0x80, 0x3f, 0xbf, 0x0c, 0x9c, 0x37, 0xa3, 0x00, 0x81, 0x3f,
  0xbf, 0x00, 0x80, 0x55, 0x80, 0x00, 0xa0, 0x3f, 0xbf, 0x20, 0xa0, 0x3f, 0x9f, 0x00, 0xbf, 0x3f,
  0x8c, 0x1c, 0xb7, 0x23, 0x80, 0x31, 0xb9, 0x2c, 0xa7, 0x23, 0x80, 0x00, 0xaa, 0x44, 0xaa, 0x11,
};

const unsigned char PROGMEM sequencer_img[] =
{
  //width = 128, height = 64
  0x00, 0x00, 0xd8, 0xdc, 0xd8, 0x00, 0x00, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe,
  0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x00, 0xaa, 0x15, 0xca, 0xe5,
  0x22, 0xe5, 0xca, 0x15, 0xaa, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff,
  0xff, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff,
  0xff, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff,
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff,
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff,
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xaa, 0x55,
  0xa8, 0x50, 0xa8, 0x51, 0xa8, 0x50, 0xa8, 0x53, 0xab, 0x53, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
  0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xab, 0x53, 0xab, 0x53, 0xab, 0x50, 0xaa, 0x00, 0x7f, 0xff,
  0x80, 0xff, 0x7f, 0x00, 0xaa, 0x00, 0xff, 0xff, 0xfc, 0x00, 0xfc, 0xff, 0xfc, 0x00, 0xfc, 0xff,
  0xff, 0x00, 0xff, 0xff, 0xfc, 0x00, 0xfc, 0xff, 0xfc, 0x00, 0xfc, 0xff, 0xfc, 0x00, 0xfc, 0xff,
  0xff, 0x00, 0xff, 0xff, 0xfc, 0x00, 0xfc, 0xff, 0xfc, 0x00, 0xfc, 0xff, 0xff, 0x00, 0xff, 0xff,
  0xfc, 0x00, 0xfc, 0xff, 0xfc, 0x00, 0xfc, 0xff, 0xfc, 0x00, 0xfc, 0xff, 0xff, 0x00, 0xff, 0xff,
  0xfc, 0x00, 0xfc, 0xff, 0xfc, 0x00, 0xfc, 0xff, 0xff, 0x00, 0xff, 0xff, 0xfc, 0x00, 0xfc, 0xff,
  0xfc, 0x00, 0xfc, 0xff, 0xfc, 0x00, 0xfc, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xaa, 0x55,
  0xaa, 0x55, 0x2a, 0x15, 0x2a, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0x28, 0x14, 0x28, 0x54, 0xa8, 0x54,
  0xa8, 0x54, 0x28, 0x14, 0x28, 0x54, 0xaa, 0x55, 0xaa, 0x55, 0x2a, 0x15, 0x2a, 0x55, 0xaa, 0x54,
  0xaa, 0x54, 0x2a, 0x15, 0x2a, 0x54, 0xa9, 0x55, 0xa9, 0x54, 0x29, 0x15, 0x29, 0x54, 0xa9, 0x55,
  0xa9, 0x54, 0x29, 0x15, 0x29, 0x54, 0xa9, 0x55, 0xa9, 0x54, 0x29, 0x15, 0x29, 0x54, 0xa9, 0x55,
  0xa9, 0x54, 0x29, 0x15, 0x29, 0x54, 0xa9, 0x55, 0xa9, 0x54, 0x29, 0x15, 0x29, 0x54, 0xa9, 0x55,
  0xa9, 0x54, 0x29, 0x15, 0x29, 0x54, 0xa9, 0x55, 0xa9, 0x54, 0x29, 0x15, 0x29, 0x54, 0xa9, 0x55,
  0xa9, 0x54, 0x29, 0x15, 0x29, 0x54, 0xa9, 0x55, 0xa9, 0x54, 0x29, 0x15, 0x29, 0x54, 0xa9, 0x55,
  0xa9, 0x54, 0x29, 0x15, 0x29, 0x54, 0xa9, 0x55, 0xa9, 0x54, 0x29, 0x15, 0x29, 0x54, 0xaa, 0x55,
  0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55, 0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55,
  0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55, 0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x01,
  0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55, 0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55,
  0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55, 0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x01,
  0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55, 0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55,
  0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55, 0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x01,
  0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55, 0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55,
  0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55, 0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55, 0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x5d,
  0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55, 0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x50,
  0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55, 0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55,
  0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55, 0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x50,
  0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55, 0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55,
  0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55, 0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x50,
  0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55, 0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55,
  0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55, 0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55,
};



const int8_t dial_x[32] =
{
  -3, -4, -5, -6, -6, -7, -7, -7,
  -7, -6, -5, -4, -3, -2, -1, -1,
  0, 1, 2, 3, 4, 5, 6, 7,
  7, 7, 7, 7, 6, 5, 4, 3
};
const int8_t dial_y[32] =
{
  6, 5, 4, 3, 2, 1, 0, -1,
  -2, -3, -4, -5, -6, -6, -6, -7,
  -7, -7, -6, -6, -5, -4, -3, -2,
  -1, 0, 1, 2, 3, 4, 5, 6
};


#define NUM_INST (7)

const int8_t preset_progs[NUM_INST][6] = {
  //
  // +---- OP0 ----+  OP1 oct
  // FB MULT  TL  DR  DR  shift
  { 5,  2,  27,  1,  2,  0 }, // Acoustic Piano
  { 7,  5,  38,  5,  2,  0 }, // Electric Piano
  { 5,  9,  32,  2,  2,  0 }, // Tubular Bells
  { 0,  8,  34,  8,  7,  0 }, // Marimba
  { 7,  3,  32,  1,  2,  0 }, // Jazz Guitar
  { 4,  1,  16,  1,  2, -2 }, // Finger Bass
  { 4,  1,   8,  3,  2, -2 }, // Slap Bass
};

const char progname[NUM_INST][16] = {
  "Acoustic Piano",
  "Electric Piano",
  "Tubular Bells",
  "Marimba",
  "Jazz Guitar",
  "Finger Bass",
  "Slap Bass",
};

#define Param1st  0
#define ParamProg 1
#define ParamFB   2
#define ParamMult 3
#define ParamTL   4
#define ParamDR1  5
#define ParamDR2  6
#define ParamLast 7

#define Seq1st    0
#define SeqTempo  1
#define SeqTrans  2
#define SeqNotes  3
#define SeqLast   19


uint8_t selectorindicator[8][4] = {
  { 0, 0, 0, 0 },
  { 6, 3, 7, 11 },
  { 5, 54, 22, 9 },
  { 28, 54, 23, 9 },
  { 52, 54, 23, 9 },
  { 76, 54, 23, 9 },
  { 100, 54, 24, 9 },
  { 0, 0, 0, 0 },
};

struct SynthNumericParam {
  int8_t value;
  int8_t max;
  uint8_t x;
  uint8_t y;
  uint8_t c_x;
  uint8_t c_y;
};

struct SynthNumericParam g_params[5] =
{
  { 0, 7, 11, 21, 15, 41 },
  { 0, 15, 35, 21, 39, 41 },
  { 0, 63, 59, 21, 63, 41 },
  { 0, 15, 83, 21, 87, 41 },
  { 0, 15, 107, 21, 111, 41 },
};

enum Mode {
  Synthesizer,
  Sequencer
} g_mode;

#define SEQ_LEN (16)
#define MAXNOTE (84)
#define MINNOTE (M_C4)

struct Sequencer {
  uint8_t tempo = 120;
  uint8_t pos = 0;
  uint8_t prev = 0;
  uint8_t prev2 = 0;
  int8_t transpose = 0;
  int16_t dur_cnt = 0;
  bool  playing = true;
  int8_t notes[SEQ_LEN] =
  { M_C5, M_C5, M_G5, M_G5,
    M_A5, M_A5, M_G5, M_REST,
    M_F5, M_F5, M_E5, M_E5,
    M_D5, M_D5, M_C5, M_REST
  };
}g_sequencer;

uint8_t g_selector_syn;
uint8_t g_selector_seq;
bool g_blink_state;
uint8_t g_blinkcount;
int8_t g_program;
FMop g_fm_operator[2];


void blink_indicator_syn(uint8_t s) {
  g_blink_state = !g_blink_state;
  if (g_blink_state)
    DRAW_RECT(selectorindicator[s][0], selectorindicator[s][1], selectorindicator[s][2], selectorindicator[s][3], WHITE);
  else
    DRAW_RECT(selectorindicator[s][0], selectorindicator[s][1], selectorindicator[s][2], selectorindicator[s][3], BLACK);
}

void copy_param_to_synth(FMop op[2]) {
  op[0].FB = g_params[0].value;
  op[0].MULT = g_params[1].value;
  op[0].TL = g_params[2].value;
  op[0].DR = g_params[3].value;
  op[1].DR = g_params[4].value;
}

void draw_dial(struct SynthNumericParam *p, uint8_t color) {
  long v;
  v = p->value;
  v = 31 * v / p->max;
  DRAW_LINE(p->c_x, p->c_y, p->c_x + dial_x[v], p->c_y + dial_y[v], color);
}

void set_param(struct SynthNumericParam *p, int8_t v) {
  draw_dial(p, BLACK);
  p->value = v;
  if (p->value < 0) p->value = 0;
  if (p->value > p->max) p->value = p->max;
  FILL_RECT(p->x, p->y, 12, 7, WHITE);
  draw_2digit(p->x, p->y, p->value, BLACK);
  copy_param_to_synth(g_fm_operator);
  draw_dial(p, WHITE);
}

void set_program(int8_t p) {
  if (p < 0) p = 0;
  if (p >= NUM_INST) p = NUM_INST - 1;
  g_program = p;
  FILL_RECT(13, 4, 101, 9, WHITE);
  draw_string(15, 5, progname[p], BLACK);
  for (uint8_t i = 0; i < 5; i++) {
    set_param(&g_params[i], preset_progs[p][i]);
  }
  copy_param_to_synth(g_fm_operator);
}

void set_selector_syn(uint8_t s) {
  if (g_blink_state)
    blink_indicator_syn(g_selector_syn);
  if (s >= ParamLast)
    s = ParamDR2;
  if (s <= Param1st)
    s = ParamProg;
  g_selector_syn = s;
  blink_indicator_syn(g_selector_syn);
}

struct KeyStatus {
  bool up;
  uint8_t up_repeat;
  bool down;
  uint8_t down_repeat;
  bool left;
  bool right;
  bool a;
  bool b;
} g_keystat;

void change_syn_value(int8_t delta) {
  switch (g_selector_syn) {
  case ParamProg:
    set_program(g_program + delta);
    break;
  case ParamFB:
    set_param(&g_params[0], g_params[0].value + delta);
    break;
  case ParamMult:
    set_param(&g_params[1], g_params[1].value + delta);
    break;
  case ParamTL:
    set_param(&g_params[2], g_params[2].value + delta);
    break;
  case ParamDR1:
    set_param(&g_params[3], g_params[3].value + delta);
    break;
  case ParamDR2:
    set_param(&g_params[4], g_params[4].value + delta);
    break;
  default:
    break;
  }
}

void draw_playing(struct Sequencer *s) {
  const static uint8_t play[6] PROGMEM = { 0x41, 0x41, 0x63, 0x63, 0x77, 0x77 };
  const static uint8_t stop[6] PROGMEM = { 0x7f, 0x63, 0x63, 0x63, 0x7f, 0x7f };
  FILL_RECT(14, 11, 6, 7, WHITE);
  if (s->playing)
    DRAW_BITMAP(14, 11, play, 6, 7, BLACK);
  else
    DRAW_BITMAP(14, 11, stop, 6, 7, BLACK);
}

void draw_transpose_slider(struct Sequencer *s) {
  const static uint8_t line[5] PROGMEM = { 1, 1, 1, 1, 1 };
  uint8_t y = 10 - 2 * s->transpose;
  DRAW_BITMAP(30, y, line, 5, 1, 3);
}

void draw_keyboard_marker(uint8_t n) {
  const static uint8_t marker[3] PROGMEM = { 2, 7, 2 };
  if ((n >= M_C4) && (n <= (M_B6 + 1))) {
    uint8_t k = (n - M_C4) % 12;
    uint8_t x, y;
    switch (k) {
    case 0: x = 38; y = 12; break;
    case 1: x = 40; y = 4; break;
    case 2: x = 42; y = 12; break;
    case 3: x = 44; y = 4; break;
    case 4: x = 46; y = 12; break;
    case 5: x = 50; y = 12; break;
    case 6: x = 52; y = 4; break;
    case 7: x = 54; y = 12; break;
    case 8: x = 56; y = 4; break;
    case 9: x = 58; y = 12; break;
    case 10: x = 60; y = 4; break;
    case 11: x = 62; y = 12; break;
    }
    x += (n - M_C4) / 12 * 28;
    DRAW_BITMAP(x, y, marker, 3, 3, 3);
  }
}

void blink_indicator_seq(uint8_t s) {
  const static uint8_t marker[7] PROGMEM = { 1, 0, 3, 0x0c, 3, 0, 1 };

  g_blink_state = !g_blink_state;
  if (s == SeqTempo) {
    if (g_blink_state)
      DRAW_RECT(0, 0, 7, 11, WHITE);
    else
      DRAW_RECT(0, 0, 7, 11, BLACK);
  }
  else {
    uint8_t x, y;
    if (s == SeqTrans) {
      x = 29;
      y = 0;
    }
    else {
      x = 8 * (s - SeqNotes);
      y = 19;
    }
    DRAW_BITMAP(x, y, marker, 7, 4, 3);
  }
}

void draw_seq_marker(struct Sequencer *s, uint8_t n) {
  const static uint8_t marker[5] PROGMEM = { 0, 5, 2, 5, 0 };
  if (s->notes[n] > M_REST) {
    uint8_t x = 1 + 8 * n;
    uint8_t y = 24 + (MAXNOTE - s->notes[n]);
    DRAW_BITMAP(x, y, marker, 5, 3, 3);
    draw_keyboard_marker(s->notes[n]);
  }
}

void draw_seq_slider(struct Sequencer *s, uint8_t n) {
  const static uint8_t line[5] PROGMEM = { 2, 2, 2, 2, 2 };

  if (s->notes[n] > M_REST) {
    uint8_t x = 1 + 8 * n;
    uint8_t y = 24 + (MAXNOTE - s->notes[n]);
    DRAW_BITMAP(x, y, line, 5, 3, 3);
  }
}

void change_tempo(uint8_t delta) {
  uint8_t t = g_sequencer.tempo += delta;
  if (t > 240) t = 240;
  if (t < 56) t = 56;
  FILL_RECT(8, 2, 18, 7, WHITE);
  if (t > 99) {
    G_DRAWCHAR(8, 2, '0' + t / 100, BLACK);
  }
  draw_2digit(14, 2, t % 100, BLACK);
  g_sequencer.tempo = t;
}

void change_trans(int8_t delta) {
  int8_t t = g_sequencer.transpose + delta;
  if (t > 2) t = 2;
  if (t < -2) t = -2;
  draw_transpose_slider(&g_sequencer);
  g_sequencer.transpose = t;
  draw_transpose_slider(&g_sequencer);
}

void play_cur_note(struct Sequencer *s, FMop op[2]) {
  if (M_REST < s->notes[s->pos]) {
    for (uint8_t i = 0; i < 2; i++) {
      op[i].gate_on(s->notes[s->pos] + s->transpose * 12, 127);
    }
  }
}

void change_note(int8_t delta) {
  uint8_t idx = g_selector_seq - SeqNotes;
  int8_t n = g_sequencer.notes[idx];
  int8_t n2 = n + delta;

  if ((n <= M_REST) && (delta > 0))
      n2 = MINNOTE;
  if ((n <= M_REST) && (delta < 0))
    n2 = MAXNOTE;
  if (n > M_REST) {
    if ((n2 < MINNOTE) || (n2 > MAXNOTE))
      n2 = M_REST;
  }
  
  if (idx == g_sequencer.prev2)
    draw_seq_marker(&g_sequencer, g_sequencer.prev2);
  draw_seq_slider(&g_sequencer, idx);
  g_sequencer.notes[idx] = n2;
  draw_seq_slider(&g_sequencer, idx);
  if (idx == g_sequencer.prev2) {
    draw_seq_marker(&g_sequencer, g_sequencer.prev2);
    play_cur_note(&g_sequencer, g_fm_operator);
  }
}


void change_seq_value(uint8_t delta) {
  switch (g_selector_seq) {
  case SeqTempo:
    change_tempo(delta);
    break;
  case SeqTrans:
    change_trans(delta);
    break;
  case Seq1st:
  case SeqLast:
    break;
  default:
    change_note(delta);
    break;
  }

}

void set_selector_seq(uint8_t s) {
  if (g_blink_state)
    blink_indicator_seq(g_selector_seq);
  if (s >= SeqLast)
    s = SeqNotes;
  if (s <= SeqTempo)
    s = SeqTempo;
  g_selector_seq = s;
  blink_indicator_seq(g_selector_seq);

  if (!g_sequencer.playing && (s >= SeqNotes)) {
    draw_seq_marker(&g_sequencer, g_sequencer.prev2);
    uint8_t i = s - SeqNotes;
    g_sequencer.pos = i;
    g_sequencer.prev = i;
    g_sequencer.prev2 = i;
    draw_seq_marker(&g_sequencer, g_sequencer.prev2);
    play_cur_note(&g_sequencer, g_fm_operator);
  }
}

void update_seq(struct Sequencer *s, FMop op[2]) {
  if (s->playing) {
    if (0 > (--(s->dur_cnt))) {
      play_cur_note(s, op);
      int16_t unit_dur = (((39248 / (s->tempo)) + 1));
      s->dur_cnt = L_4 * unit_dur - 1;
      if (SEQ_LEN <= ++(s->pos)) s->pos = 0;
    }
  }
}

void up_released() {
  switch (g_mode) {
  case Synthesizer:
    change_syn_value(1);
    break;
  case Sequencer:
    change_seq_value(1);
    break;
  default:
    break;
  }
}

void down_released() {
  switch (g_mode) {
  case Synthesizer:
    change_syn_value(-1);
    break;
  case Sequencer:
    change_seq_value(-1); 
    break;
  default:
    break;
  }
}

void left_released() {
  switch (g_mode) {
    case Synthesizer:
      set_selector_syn(g_selector_syn - 1);
    break;
    case Sequencer:
      set_selector_seq(g_selector_seq - 1);
      break;
    default:
      break;
  }
}

void right_released() {
  switch (g_mode) {
  case Synthesizer:
    set_selector_syn(g_selector_syn + 1);
    break;
  case Sequencer:
    set_selector_seq(g_selector_seq + 1);
    break;
  default:
    break;
  }
}


bool process_button(bool *state, uint8_t *repeat_count, uint8_t keycode, void(*release_func)()) {
  uint8_t dummy = 255;
  bool  result = false;

  if (repeat_count == NULL) {
    repeat_count = &dummy;
  }
  if (*state) {
    if (KEY_NOT_PRESSED(keycode)) {
      *state = false;
      release_func();
      result = true;
    }
    else if ((*repeat_count)-- == 0) {
      *repeat_count = 1;
      release_func();
      result = true;
    }
  }
  else if (KEY_PRESSED(keycode)) {
    *state = true;
    *repeat_count = 5;
  }
  return result;
}

void init_globals() {
  setup_synth(g_fm_operator);
  g_selector_syn = ParamProg;
  g_selector_seq = SeqTempo;
  g_program = 0;
  g_keystat = { false, false, false, false, false, false };
}

void draw_screen() {
  G_CLEAR();
  g_blink_state = false;
  g_blinkcount = 0;

  switch (g_mode) {
  case Synthesizer:
    arduboy.drawBitmap(0, 0, synth_img, 128, 64, WHITE);
    draw_string(15, 5, progname[g_program], BLACK);
    for (uint8_t i = 0; i < 5; i++) {
      set_param(&g_params[i], g_params[i].value);
    }
    blink_indicator_syn(g_selector_syn);
    break;
  case Sequencer:
    arduboy.drawBitmap(0, 0, sequencer_img, 128, 64, WHITE);
    draw_playing(&g_sequencer);
    draw_transpose_slider(&g_sequencer);
    for (uint8_t i = 0; i < SEQ_LEN; i++)
      draw_seq_slider(&g_sequencer, i);
    draw_seq_marker(&g_sequencer, g_sequencer.prev2);
    change_tempo(0);
    blink_indicator_seq(g_selector_seq);
    break;
  }
}

void a_released() {
  g_sequencer.playing = !g_sequencer.playing;
  if (g_mode == Sequencer) {
    draw_playing(&g_sequencer);
  }
}

void b_released() {
  g_keystat = { false, 0, false, 0, false, false, false, false };
  if (g_mode == Synthesizer) {
    g_mode = Sequencer;
  }
  else {
    g_mode = Synthesizer;
  }
  draw_screen();
}

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(15);

  g_mode = Synthesizer;
  init_globals();

  draw_screen();
  set_program(g_program);
  arduboy.display();
}

void loop() {
  if (update_synth(g_fm_operator)){
    update_seq(&g_sequencer, g_fm_operator);
    if (!(arduboy.nextFrame()))
      return;

    bool scrn_update = false;

    scrn_update |= process_button(&g_keystat.up, &g_keystat.up_repeat, UP_BUTTON, up_released);
    scrn_update |= process_button(&g_keystat.down, &g_keystat.down_repeat, DOWN_BUTTON, down_released);
    scrn_update |= process_button(&g_keystat.left, NULL, LEFT_BUTTON, left_released);
    scrn_update |= process_button(&g_keystat.right, NULL, RIGHT_BUTTON, right_released);
    scrn_update |= process_button(&g_keystat.a, NULL, A_BUTTON, a_released);
    scrn_update |= process_button(&g_keystat.b, NULL, B_BUTTON, b_released);
    switch (g_mode) {
    case Synthesizer:
      break;
    case Sequencer:
      if (g_sequencer.prev != g_sequencer.pos) {
        draw_seq_marker(&g_sequencer, g_sequencer.prev2);
        draw_seq_marker(&g_sequencer, g_sequencer.prev);
        g_sequencer.prev2 = g_sequencer.prev;
        g_sequencer.prev = g_sequencer.pos;
        scrn_update = true;
      }
      break;
    }

    if (scrn_update)
      arduboy.display();
  }
}

