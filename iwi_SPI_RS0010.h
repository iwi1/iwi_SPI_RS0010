#ifndef SPI_RS0010_H
#define SPI_RS0010_H

#include "Arduino.h"
#include "fontbold.h"
#include "fontglcd.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>


// commands
#define RS_CLEARDISPLAY 0x01  	//Clear
#define RS_RETURNHOME 0x02 	//
#define RS_ENTRYMODESET 0x04
#define RS_DISPLAYCONTROL 0x08
#define RS_CURSORSHIFT 0x10
#define RS_FUNCTIONSET 0x30
#define RS_SETCGRAMADDR 0x40	//CGRAM
#define RS_SETDDRAMADDR 0x80	//DDRAM
#define RS_SETLOWCOLUMN 0x00
#define RS_SETHIGHCOLUMN 0x20
#define RS_SETSTARTLINE 0x40

// flags for display entry mode
#define RS_ENTRYRIGHT 0x00
#define RS_ENTRYLEFT 0x02
#define RS_ENTRYSHIFTINCREMENT 0x06
#define RS_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control ws0010
#define RS_DISPLAYON 0x04
#define RS_DISPLAYOFF 0x00
#define RS_CURSORON 0x02
#define RS_CURSOROFF 0x00
#define RS_BLINKON 0x01
#define RS_BLINKOFF 0x00

// flags for display/cursor shift
#define RS_DISPLAYMOVE 0x08
#define RS_CURSORMOVE 0x00
#define RS_MOVERIGHT 0x04
#define RS_MOVELEFT 0x00

// flags for function set
#define RS_2LINE 0x3B  	//111011 2linie, 5x8, WesternEuropean II
#define RS_1LINE 0x33  	//110011 1linia, 5x8, WesternEuropean II
#define RS_GRAPHIC 0x1F 	//1F Graphic mode; Power ON.
#define RS_CHARACTER 0x17 	//17-character mode; Power ON.

// Definicja wielkości wyświetlacza
#define RS0010_WIDTH 100
#define RS0010_HEIGHT 16
#define BUF_SIZE (RS0010_WIDTH * RS0010_HEIGHT / 8)

//Refresh
#define REFRESH_MIN 0x80
#define REFRESH_MID 0xB0
#define REFRESH_MAX 0xF0

//Color
#define BLACK 0
#define WHITE 1


//#define RS_SPICOMMAND (0)
//#define RS_SPIDATA (1)
class SPI_RS0010 {
public:
  uint8_t rs0010_buf[BUF_SIZE] = {
	0x3C,0xE0,0x8C,0x3B,0xC0,0x30,0x18,0x0E,0x00,0x00,0x00,0xE0,0x18,0x18,0xE0,0x00,
	0x00,0xE0,0x40,0x20,0x00,0xC0,0x20,0x20,0x20,0xFC,0x00,0xE0,0x00,0x00,0x00,0xE0,
	0x00,0xE8,0x00,0xE0,0x20,0x20,0x20,0xC0,0x00,0xC0,0x20,0x20,0x20,0xC0,0x00,0x00,
	0x00,0x00,0xE0,0x00,0x80,0x60,0x80,0x00,0xE0,0x00,0x00,0x00,0x00,0xFC,0x00,0xC0,
	0xA0,0xA0,0xA0,0xC0,0x00,0xC0,0xA0,0x20,0x20,0x00,0xE8,0x00,0xC0,0xA0,0xA0,0xA0,
	0xC0,0x00,0x00,0x00,0x03,0x0C,0x38,0xC0,0x00,0xFF,0xF1,0x98,0x86,0x42,0x60,0x30,
	0x08,0x08,0x08,0x00,0x00,0x00,0x03,0x7E,0xDB,0xDE,0x04,0x00,0x00,0x00,0x07,0x01,
	0x01,0x01,0x01,0x07,0x00,0x07,0x00,0x00,0x00,0x03,0x04,0x04,0x04,0x07,0x00,0x03,
	0x04,0x04,0x04,0x07,0x00,0x07,0x00,0x07,0x00,0x00,0x00,0x07,0x00,0x03,0x04,0x04,
	0x04,0x03,0x00,0x00,0x00,0x00,0x01,0x06,0x01,0x00,0x01,0x06,0x01,0x00,0x00,0x00,
	0x00,0x07,0x00,0x03,0x04,0x04,0x04,0x02,0x00,0x04,0x04,0x05,0x03,0x00,0x07,0x00,
	0x03,0x04,0x04,0x04,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x7F,0xFC,0x87,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

  void initSPI(uint8_t miso, uint8_t mosi, uint8_t clk, uint8_t cs);
  void begin(uint8_t cols, uint8_t rows, uint8_t mode);
  void grafika(uint8_t dat[]);
  void displayBuf(void);
  void clearBuf(void);
  void createChar(uint8_t[], uint8_t dlugosc);
  void grafika2(uint8_t charmap[], uint8_t x, uint8_t dlugosc);
  void setCursor(uint8_t, uint8_t); 
  void drawPixel(int8_t x, int8_t y, uint8_t color);
  void drawBitmap_P(int x, int y, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color );
  void drawLine(int8_t x0, int8_t y0, int8_t x1, int8_t y1, uint8_t color);
  void drawFastVLine(int8_t x, int8_t y, int8_t h, uint8_t color);
  void drawFastHLine(int8_t x, int8_t y, int8_t w, uint8_t color);
  void fillRect(int8_t x, int8_t y, int8_t w, int8_t h, uint8_t color);
  void drawChar(int x, int y, unsigned char c, uint8_t color, uint8_t bg, uint8_t size);
  void drawString(int x, int y, const char * cstring, uint8_t color, uint8_t bg, uint8_t text_size);
  void drawInteger(int x, int y, int data, uint8_t color, uint8_t bg, uint8_t text_size);
  void drawFloat(int x, int y, float data, uint8_t places, uint8_t color, uint8_t bg, uint8_t text_size);
  void drawBoldChar(int x, int y, unsigned char c, uint8_t color, uint8_t bg);
  void drawBoldString(int x, int y, const char * cstring, uint8_t color, uint8_t bg);
  void drawBoldInteger(int x, int y, int data, uint8_t color, uint8_t bg);
  char * floatToString(char * outstr, float value, int places, int minwidth=0, bool rightjustify=false);
  
  
  void clear();
  void home();

  void noDisplay();
  void display();
  void noBlink();
  void blink();
  void noCursor();
  void cursor();
  void scrollDisplayLeft();
  void scrollDisplayRight();
  void leftToRight();
  void rightToLeft();
  void autoscroll();
  void noAutoscroll();



  size_t write(uint8_t);

  void command(uint8_t);
private:
  inline void send(uint8_t dat);
  
  uint8_t _clk, _mosi, _miso, _cs;  // SPI interface

  uint8_t _displayfunction;
  uint8_t _displaycontrol;
  uint8_t _displaymode;
  uint8_t _initialized;
  uint8_t _numlines, _currline;
  
  protected:
    GFXfont  *gfxFont;
	//boolean  wrap,   // If set, 'wrap' text at right edge of display
    int _cp437;
};

#endif // SPI_RS0010_H
