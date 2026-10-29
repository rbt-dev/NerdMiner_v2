// Waveshare ESP32-S3-LCD-1.47: 1.47" round IPS, ST7789V3, 172x320, SPI bus
// Pins from the official Waveshare wiki:
// MOSI=45 SCLK=40 CS=42 DC=41 RST=39 BL=48

#define USER_SETUP_ID 999

#define ST7789_DRIVER

#define CGRAM_OFFSET
#define TFT_RGB_ORDER TFT_RGB
#define TFT_INVERSION_ON

#define TFT_WIDTH  172
#define TFT_HEIGHT 320

#define TFT_MOSI 45
#define TFT_SCLK 40
#define TFT_CS   42
#define TFT_DC   41
#define TFT_RST  39

#define TFT_BL   48
#define TFT_BACKLIGHT_ON HIGH

#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF

#define SMOOTH_FONT

#define SPI_FREQUENCY       40000000
#define SPI_READ_FREQUENCY   5000000
#define SPI_TOUCH_FREQUENCY  2500000
