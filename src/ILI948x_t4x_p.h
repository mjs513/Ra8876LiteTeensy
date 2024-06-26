#ifndef _ILI948X_T4X_P_H_
#define _ILI948X_T4X_P_H_

// uncomment below the line corresponding to your screen:

// #define ILI9481_1
// #define ILI9481_2
// #define ILI9486
// #define ILI9488
// #define R61529

#include "Arduino.h"
#include "DMAChannel.h"
#include "FlexIO_t4.h"

#include "Teensy_Parallel_GFX.h"

#define SHIFTNUM 4            // number of shifters used (must be 1, 2, 4, or 8)
#define SHIFTER_DMA_REQUEST (_write_shifter + SHIFTNUM - 1) // only 0, 1, 2, 3 expected to work
#define SHIFTER_IRQ (_write_shifter + SHIFTNUM - 1)
#define BYTES_PER_BEAT (sizeof(uint8_t))
#define BEATS_PER_SHIFTER (sizeof(uint32_t)/BYTES_PER_BEAT)
#define BYTES_PER_BURST (sizeof(uint32_t)*SHIFTNUM)
#define FLEXIO_ISR_PRIORITY 64 // interrupt is timing sensitive, so use relatively high priority (supersedes USB)

#define _TFTWIDTH 320  // ILI9488 TFT width in default rotation
#define _TFTHEIGHT 480 // ILI9488 TFT height in default rotation

#define ILI9488_NOP 0x00     // No-op
#define ILI9488_SWRESET 0x01 // Software reset
#define ILI9488_RDDID 0x04   // Read display ID
#define ILI9488_RDDST 0x09   // Read display status

#define ILI9488_SLPIN 0x10  // Enter Sleep Mode
#define ILI9488_SLPOUT 0x11 // Sleep Out
#define ILI9488_PTLON 0x12  // Partial Mode ON
#define ILI9488_NORON 0x13  // Normal Display Mode ON

#define ILI9488_RDMODE 0x0A     // Read Display Power Mode
#define ILI9488_RDMADCTL 0x0B   // Read Display MADCTL
#define ILI9488_RDCOLMOD 0x0C   // Read Display Pixel Format
#define ILI9488_RDIMGFMT 0x0D   // Read Display Image Mode
#define ILI9488_RDDSM 0x0E      // Read Display Signal Mode
#define ILI9488_RDSELFDIAG 0x0F // Read Display Self-Diagnostic Result

#define ILI9488_INVOFF 0x20   // Display Inversion OFF
#define ILI9488_INVON 0x21    // Display Inversion ON
#define ILI9488_GAMMASET 0x26 // Gamma Set
#define ILI9488_DISPOFF 0x28  // Display OFF
#define ILI9488_DISPON 0x29   // Display ON

#define ILI9488_CASET 0x2A // Column Address Set
#define ILI9488_PASET 0x2B // Page Address Set
#define ILI9488_RAMWR 0x2C // Memory Write
#define ILI9488_RAMRD 0x2E // Memory Read

#define ILI9488_PTLAR 0x30    // Partial Area
#define ILI9488_TEOFF 0x34    // Tearing effect line off
#define ILI9488_TEON 0x35     // Tearing effect line on
#define ILI9488_MADCTL 0x36   // Memory Access Control
#define ILI9488_VSCRSADD 0x37 // Vertical Scrolling Start Address
#define ILI9488_COLMOD 0x3A   // Interface pixel format

#define ILI9488_TESLWR 0x44 // Write tear scan line

#define ILI9488_FRMCTR1 0xB1 // Frame Rate Control (Normal Mode / Full Colors)
#define ILI9488_FRMCTR2 0xB2 // Frame Rate Control (Idle Mode / 8 Colors)
#define ILI9488_FRMCTR3 0xB3 // Frame Rate Control (Partial Mode / Full Colors)
#define ILI9488_INVCTR 0xB4  // Display Inversion Control
#define ILI9488_DFUNCTR 0xB6 // Display Function Control
#define ILI9488_ETMOD 0xB7   // Entry Mode Set

#define ILI9488_PWCTR1 0xC0    // Power Control 1
#define ILI9488_PWCTR2 0xC1    // Power Control 2
#define ILI9488_PWCTR3 0xC2    // Power Control 3 (For Normal Mode)
#define ILI9488_PWCTR4 0xC3    // Power Control 4 (For Idle Mode)
#define ILI9488_PWCTR5 0xC4    // Power Control 5 (For Partial Mode)
#define ILI9488_VMCTR1 0xC5    // VCOM Control
#define ILI9488_CABCCTRL1 0xC6 // CABC Control 1
#define ILI9488_CABCCTRL2 0xC8 // CABC Control 2

#define ILI9488_NVMEMWR 0xD0      // NV Memory Write
#define ILI9488_NVMEMPROTKEY 0xD1 // NV Memory Protection Key
#define ILI9488_NVMEMSTATRD 0xD2  // NV Memory Status Read

#define ILI9488_PGAMCTRL 0xE0 // Positive Gamma Control
#define ILI9488_NGAMCTRL 0xE1 // Negative Gamma Control
#define ILI9488_SETIMAGE 0xE9 // Set Image Function

#define ILI9488_ADJCTL3 0xF7

#define ILI9488_RDID1 0xDA // Read ID1 value
#define ILI9488_RDID2 0xDB // Read ID2 value
#define ILI9488_RDID3 0xDC // Read ID3 value

#define MADCTL_MY 0x80  // Bottom to top
#define MADCTL_MX 0x40  // Right to left
#define MADCTL_MV 0x20  // Row/Column exchange
#define MADCTL_ML 0x10  // LCD refresh Bottom to top
#define MADCTL_RGB 0x00 // Red-Green-Blue pixel order
#define MADCTL_BGR 0x08 // Blue-Green-Red pixel order
#define MADCTL_MH 0x04  // LCD refresh right to left
#define MADCTL_GS 0x01
#define MADCTL_SS 0x02

// MADCTL 0,1,2,3 for setting rotation and 4 for screenshot
/*
#if defined (ILI9488) || defined (ILI9486)
#define MADCTL_ARRAY { MADCTL_MX | MADCTL_BGR, MADCTL_MV | MADCTL_BGR, MADCTL_MY | MADCTL_BGR, MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR, MADCTL_MY | MADCTL_MV | MADCTL_BGR } // ILI9488/9486
#elif defined (ILI9481_1) || defined (ILI9481_2)
#define MADCTL_ARRAY { MADCTL_BGR | MADCTL_SS, MADCTL_MV | MADCTL_BGR, MADCTL_BGR | MADCTL_GS, MADCTL_MV | MADCTL_BGR | MADCTL_SS | MADCTL_GS } // ILI9481
#elif defined (R61529)
#define MADCTL_ARRAY { MADCTL_RGB, MADCTL_MV | MADCTL_MX | MADCTL_RGB, MADCTL_RGB | MADCTL_GS | MADCTL_MX, MADCTL_MV | MADCTL_RGB | MADCTL_GS } // R61529
#endif
*/

/****************************************************************************************/
// #define ILI9488_CLOCK_READ 30   //equates to 8mhz
//#define ILI9488_CLOCK_READ 60 // equates to 4mhz
#define ILI9488_CLOCK_READ 120   //equates to 2mhz

enum {
    ILI9488 = 0,
    ILI9486 = 1,
    ILI9486_1 = 2,
    ILI9486_2 = 3,
    R61529 = 4
};

#ifdef __cplusplus
class ILI948x_t4x_p : public Teensy_Parallel_GFX {
  public:
    ILI948x_t4x_p(int8_t dc, int8_t cs = -1, int8_t rst = -1);
    void begin(uint8_t display_name = ILI9488, uint8_t buad_div = 20);
    uint8_t getBusSpd();

    // If used this must be called before begin
    // Set the FlexIO pins.  The first version you can specify just the wr, and read and optionsl first Data.
    // it will use information in the Flexio library to fill in d1-d7
    bool setFlexIOPins(uint8_t write_pin, uint8_t rd_pin, uint8_t tft_d0 = 0xff);

    // Set the FlexIO pins.  Specify all of the pins for 8 bit mode. Must be called before begin
    bool setFlexIOPins(uint8_t write_pin, uint8_t rd_pin, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                       uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

    uint8_t setBitDepth(uint8_t bitDepth);
    uint8_t getBitDepth();

    void setFrameRate(uint8_t frRate);
    uint8_t getFrameRate();

    void setTearingEffect(bool tearingOn);
    bool getTearingEffect();

    void setTearingScanLine(uint16_t scanLine);
    uint16_t getTearingScanLine();

    void setRotation(uint8_t r);
    void invertDisplay(bool invert);
    void displayInfo();

    void pushPixels16bit(const uint16_t *pcolors, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
    void pushPixels16bitDMA(const uint16_t *pcolors, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

    uint8_t readCommand(uint8_t const cmd);
    uint32_t readCommandN(uint8_t const cmd, uint8_t count_bytes);

    // Added functions to read pixel data...
    // uint16_t readPixel(int16_t x, int16_t y);
    void readRectFlexIO(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t *pcolors);
    
    // Called by GFX to do updateScreenAsync and new writeRectAsync(;
    bool writeRectAsyncFlexIO(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t *pcolors);
    bool writeRectAsyncActiveFlexIO();

    // void pushPixels16bitTearing(uint16_t * pcolors, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 );
    // void pushPixels24bitTearing(uint16_t * pcolors, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 );
    void DMAerror();

    /**************************************************************/
    void setScroll(uint16_t offset);

    uint16_t _previous_addr_x0 = 0xffff;
    uint16_t _previous_addr_x1 = 0xffff;
    uint16_t _previous_addr_y0 = 0xffff;
    uint16_t _previous_addr_y1 = 0xffff;

    void setAddr(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
        __attribute__((always_inline)) {

        uint8_t Command;
        uint8_t CommandValue[4];
        if ((x0 != _previous_addr_x0) || (x1 != _previous_addr_x1)) {
            Command = 0x2A;
            CommandValue[0U] = x0 >> 8U;
            CommandValue[1U] = x0 & 0xFF;
            CommandValue[2U] = x1 >> 8U;
            CommandValue[3U] = x1 & 0xFF;
            SglBeatWR_nPrm_8(Command, CommandValue, 4U);
            _previous_addr_x0 = x0;
            _previous_addr_x1 = x1;
        }
        if ((y0 != _previous_addr_y0) || (y1 != _previous_addr_y1)) {
            Command = 0x2B;
            CommandValue[0U] = y0 >> 8U;
            CommandValue[1U] = y0 & 0xFF;
            CommandValue[2U] = y1 >> 8U;
            CommandValue[3U] = y1 & 0xFF;
            SglBeatWR_nPrm_8(Command, CommandValue, 4U);
            _previous_addr_y0 = y0;
            _previous_addr_y1 = y1;
        }
    }
    enum { WRITE_SHIFT_TO = 20,
           READ_SHIFT_TO = 20,
           WRITE_TIMER_TO = 20 };
    void waitWriteShiftStat(int error_identifier = 0) __attribute__((always_inline)) {
        elapsedMillis em = 0;
        while (0 == (p->SHIFTSTAT & _write_shifter_mask)) {
            if (em > WRITE_SHIFT_TO) {
                Serial.printf(">>>waitWriteShiftStat(%d) TO\n", error_identifier);
                if (Serial.available()) {
                    while (Serial.read() != -1) {
                    }
                    Serial.println("*** Paused ***");
                    while (Serial.read() == -1) {
                    }
                    while (Serial.read() != -1) {
                    }
                }
                return; // bail
            }
        }
    }

    void waitReadShiftStat(int error_identifier = 0) __attribute__((always_inline)) {
        elapsedMillis em = 0;
        while (0 == (p->SHIFTSTAT & _read_shifter_mask)) {
            if (em > READ_SHIFT_TO) {
                Serial.printf(">>>waitReadShiftStat(%d) TO\n", error_identifier);
                if (Serial.available()) {
                    while (Serial.read() != -1) {
                    }
                    Serial.println("*** Paused ***");
                    while (Serial.read() == -1) {
                    }
                    while (Serial.read() != -1) {
                    }
                }
                return; // bail
            }
        }
    }

    void waitTimStat(int error_identifier = 0) __attribute__((always_inline)) {
        elapsedMillis em = 0;
        while (0 == (p->TIMSTAT & _flexio_timer_mask)) {
            if (em > WRITE_SHIFT_TO) {
                Serial.printf(">>>waitWriteShiftStat(%d) TO\n", error_identifier);
                if (Serial.available()) {
                    while (Serial.read() != -1) {
                    }
                    Serial.println("*** Paused ***");
                    while (Serial.read() == -1) {
                    }
                    while (Serial.read() != -1) {
                    }
                }
                return; // bail
            }
        }
    }

    void beginWrite16BitColors();
    void write16BitColor(uint16_t color);
    void endWrite16BitColors();
//    void write16BitColor(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, const uint16_t *pcolors, uint16_t count);
    void writeRectFlexIO(int16_t x, int16_t y, int16_t w, int16_t h, const uint16_t *pcolors);
    void fillRectFlexIO(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

    typedef void (*CBF)();
    CBF _callback;
    void onCompleteCB(CBF callback);

  protected:
  private:
    uint8_t _display_name = 0;
    FlexIOHandler *pFlex;
    IMXRT_FLEXIO_t *p;
    const FlexIOHandler::FLEXIO_Hardware_t *hw;
    static DMAChannel flexDma;

    uint8_t _baud_div = 20;

    uint8_t _bitDepth = 16;
    uint8_t _rotation = 0;
    uint8_t MADCTL[5];

    uint8_t _frameRate = 60;

    bool _bTearingOn = false;
    uint16_t _tearingScanLine = 0;

    // int16_t _width, _height;
    int8_t _dc, _cs, _rst;

    // The Teensy IO pins used for data and Read and Write
    uint8_t _data_pins[8], _wr_pin, _rd_pin;

    uint8_t _flexio_D0, _flexio_WR, _flexio_RD; // which flexio pins do they map to
    uint8_t _write_shifter = 0;
    uint8_t _write_shifter_mask = (1 << 0);
    uint8_t _read_shifter = 3;
    uint8_t _read_shifter_mask = (1 << 3);
    uint8_t _flexio_timer = 0;
    uint8_t _flexio_timer_mask = 1 << 0;

    uint8_t _dummy;
    uint8_t _curMADCTL;

    volatile bool WR_AsyncTransferDone = true;
    uint32_t MulBeatCountRemain;
    uint16_t *MulBeatDataRemain;
    uint32_t TotalSize;

    void displayInit(uint8_t display_name);
    void CSLow();
    void CSHigh();
    void DCLow();
    void DCHigh();
    void gpioWrite();
    void gpioRead();

    void FlexIO_Init();
    typedef enum { CONFIG_CLEAR = 0,
                   CONFIG_SNGLBEAT,
                   CONFIG_MULTIBEAT,
                   CONFIG_SNGLREAD } Flexio_config_state_t;
    Flexio_config_state_t flex_config = CONFIG_CLEAR;
    void FlexIO_Config_SnglBeat();
    void FlexIO_Clear_Config_SnglBeat();
    void FlexIO_Config_MultiBeat();
    void FlexIO_Config_SnglBeat_Read();

    void SglBeatWR_nPrm_8(uint32_t const cmd, uint8_t const *value, uint32_t const length);
    void SglBeatWR_nPrm_16(uint32_t const cmd, const uint16_t *value, uint32_t const length);
    // Works on FlexIO1 and FlexIO2 but not 3 and only on Shifters 0-3
    void MulBeatWR_nPrm_DMA(uint32_t const cmd, const void *value, uint32_t const length);

    // Works on FlexIO3 and others as well
    void MulBeatWR_nPrm_IRQ(uint32_t const cmd,  const void *value, uint32_t const length);
    static void flexio_ISR();
    void flexIRQ_Callback();


    void microSecondDelay();

    static void dmaISR();
    void flexDma_Callback();
    static ILI948x_t4x_p *IRQcallback;

    bool isCB = false;
    void _onCompleteCB();

    static ILI948x_t4x_p *dmaCallback;

    /* variables used by ISR */
    volatile uint32_t bytes_remaining;
    volatile unsigned int bursts_to_complete;
    volatile uint32_t *readPtr;
    uint32_t finalBurstBuffer[SHIFTNUM];

};
#endif //__cplusplus
#endif //_IILI948x_t4x_p.h_