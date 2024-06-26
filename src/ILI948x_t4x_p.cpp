#include "ILI948x_t4x_p.h"
#include "ILI948x_t4x_p_default_flexio_pins.h"


#if !defined(ARDUINO_TEENSY_MICROMOD) && !defined(ARDUINO_TEENSY41)
#warning This library only supports the Teensy Micromod and Teensy 4.1
#endif

//#define DEBUG
//#define DEBUG_VERBOSE

#ifndef DEBUG
#undef DEBUG_VERBOSE
void inline DBGPrintf(...){};
void inline DBGFlush(){};
#else
#define DBGPrintf Serial.printf
#define DBGFlush Serial.flush
#endif

#ifndef DEBUG_VERBOSE
void inline VDBGPrintf(...){};
#else
#define VDBGPrintf Serial.printf
#endif

//--------------------------------------------------
PROGMEM const uint8_t ILI9488_init_commands[] = {
    1, 120, 0x01, // SW RST
    1, 15, 0x11,  // Exit sleep
    1, 15, 0x28,  // Display Off
    3, 0, 0xC0, 0x19, 0x1A,
    3, 0, 0xC1, 0x45, 0x00,
    2, 0, 0xC2, 0x33,
    4, 0, 0xC5, 0x00, 0x12, 0x80,
    2, 0, 0xB4, 0x02,
    4, 0, 0xB6, 0x00, 0x02, 0x3B,
    2, 0, 0xB7, 0x07,
    16, 0, 0xE0, 0x00, 0x03, 0x09, 0x08, 0x16, 0x0A, 0x3F, 0x78, 0x4C, 0x09, 0x0A, 0x08, 0x16, 0x1A, 0x0F,
    16, 0, 0xE1, 0x00, 0x16, 0x19, 0x03, 0x0F, 0x05, 0x32, 0x45, 0x46, 0x04, 0x0E, 0x0D, 0x35, 0x37, 0x0F,
    2, 10, 0x36, 0x48,
    1, 120, 0x29, // Display On
    0};

PROGMEM const uint8_t ILI9486_init_commands[] = {
    1, 120, 0x01,
    1, 20, 0x11, // Sleep out, also SW reset
    2, 0, 0x3A, 0x55,
    2, 0, 0xC2, 0x44,
    5, 0, 0xC5, 0x00, 0x00, 0x00, 0x00,
    16, 0, 0xE0, 0x0F, 0x1F, 0x1C, 0x0C, 0x0C, 0x08, 0x48, 0x98, 0x37, 0x0A, 0x13, 0x04, 0x11, 0x0D, 0x00,
    16, 0, 0xE1, 0x0F, 0x32, 0x2E, 0x0B, 0x0D, 0x05, 0x47, 0x75, 0x37, 0x06, 0x10, 0x03, 0x24, 0x20, 0x00,
    2, 0, 0x36, 0x48,
    1, 0, 0x20,
    1, 120, 0x29, // Display ON
    0};

PROGMEM const uint8_t ILI9481_1_init_commands[] = {
    1, 120, ILI9488_SWRESET,
    1, 20, ILI9488_SLPOUT,
    4, 0, ILI9488_NVMEMWR, 0x07, 0x41, 0x1D,
    4, 0, ILI9488_NVMEMPROTKEY, 0x00, 0x2B, 0x1F,
    3, 0, ILI9488_NVMEMSTATRD, 0x01, 0x11,
    7, 0, ILI9488_PWCTR1, 0x10, 0x3B, 0x00, 0x02, 0x11, 0x00,
    2, 0, ILI9488_VMCTR1, 0x03,
    2, 0, ILI9488_CABCCTRL1, 0x80,
    13, 0, ILI9488_CABCCTRL2, 0x00, 0x14, 0x33, 0x10, 0x00, 0x16, 0x44, 0x36, 0x77, 0x00, 0x0F, 0x00,
    2, 0, 0xB0, 0x00,
    2, 0, 0xE4, 0xA0,
    2, 0, 0xF0, 0x08,
    3, 0, 0xF3, 0x40, 0x0A,
    1, 0, 0xF6, 0x84,
    1, 0, ILI9488_ADJCTL3, 0x80,
    5, 0, ILI9488_FRMCTR3, 0x00, 0x01, 0x06, 0x30,
    1, 0, ILI9488_INVCTR, 0x00,
    2, 0, ILI9488_RDCOLMOD, 0x00, 0x55,
    2, 0, ILI9488_MADCTL, 0x48,
    2, 0, ILI9488_COLMOD, 0x55,
    1, 120, ILI9488_INVON,
    1, 120, ILI9488_DISPON,
    0};

PROGMEM const uint8_t ILI9481_2_init_commands[] = {
    1, 150, 0x01,
    2, 150, 0x11,
    3, 150, 0xd0, 0x07, 0x44, 0x1E,
    3, 0, 0xd1, 0x00, 0x0C, 0x1A,
    4, 0, 0xC5, 0x03,
    3, 0, 0xd2, 0x01, 0x11,
    2, 0, 0xE4, 0xa0,
    3, 0, 0xf3, 0x00, 0x2a,
    13, 0, 0xc8, 0x00, 0x26, 0x21, 0x00, 0x00, 0x1f, 0x65, 0x23, 0x77, 0x00, 0x0f, 0x00,
    6, 0, 0xC0, 0x00, 0x3B, 0x00, 0x02, 0x11,
    2, 0, 0xc6, 0x83,
    2, 0, 0xf0, 0x01,
    2, 0, 0xE4, 0xa0,
    2, 0, 0x36, 0x8C,
    2, 0, 0x3a, 0x55,
    5, 255, 0xb4, 0x02, 0x00, 0x00, 0x01,
    5, 0, 0x2a, 0x00, 0x00, 0x01, 0x3F,
    5, 10, 0x2b, 0x00, 0x00, 0x01, 0xDf,
    1, 0, 0x29,
    1, 120, 0x2c,
    0};

PROGMEM const uint8_t R61519_init_commands[] = {
    1, 120, 0x01,
    1, 20, 0x11,
    2, 2, 0xB0, 0x04,
    16, 0, 0xB8, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    5, 0, 0xB9, 0x01, 0x00, 0xff, 0x18,
    6, 2, 0xB3, 0x00, 0x00, 0x00, 0x00,
    2, 0, 0xB4, 0x00,
    9, 0, 0xC0, 0x03, 0xDF, 0x40, 0x10, 0x00, 0x01, 0x00, 0x55,
    6, 0, 0xC1, 0x07, 0x27, 0x08, 0x08, 0x00,
    5, 0, 0xC4, 0x57, 0x00, 0x05, 0x03,
    2, 0, 0xC6, 0x04,
    25, 0, 0xC8, 0x03, 0x12, 0x1A, 0x24, 0x32, 0x4B, 0x3B, 0x29, 0x1F, 0x18, 0x12, 0x04, 0x03, 0x12, 0x1A, 0x24, 0x32, 0x4B, 0x3B, 0x29, 0x1F, 0x18, 0x12, 0x04,
    25, 0, 0xC9, 0x03, 0x12, 0x1A, 0x24, 0x32, 0x4B, 0x3B, 0x29, 0x1F, 0x18, 0x12, 0x04, 0x03, 0x12, 0x1A, 0x24, 0x32, 0x4B, 0x3B, 0x29, 0x1F, 0x18, 0x12, 0x04,
    25, 0, 0xCA, 0x03, 0x12, 0x1A, 0x24, 0x32, 0x4B, 0x3B, 0x29, 0x1F, 0x18, 0x12, 0x04, 0x03, 0x12, 0x1A, 0x24, 0x32, 0x4B, 0x3B, 0x29, 0x1F, 0x18, 0x12, 0x04,
    17, 0, 0xD0, 0x99, 0x06, 0x08, 0x20, 0x29, 0x04, 0x01, 0x00, 0x08, 0x01, 0x00, 0x06, 0x01, 0x00, 0x00, 0x20,
    5, 0, 0xD1, 0x00, 0x20, 0x20, 0x15,
    5, 0, 0xE0, 0x00, 0x00, 0x00, 0x00,
    7, 0, 0xE1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    2, 0, 0xE2, 0x00,
    2, 0, 0x3A, 0x55,
    5, 0, 0x2A, 0x00, 0x00, 0x01, 0x3F,
    5, 120, 0x2B, 0x00, 0x00, 0x01, 0xDF,
    1, 120, 0x29,
    0};

//--------------------------------------------------

FLASHMEM ILI948x_t4x_p::ILI948x_t4x_p(int8_t dc, int8_t cs, int8_t rst)
    : Teensy_Parallel_GFX(_TFTWIDTH, _TFTHEIGHT), _dc(dc), _cs(cs), _rst(rst),
      _data_pins{DISPLAY_D0, DISPLAY_D1, DISPLAY_D2, DISPLAY_D3, DISPLAY_D4, DISPLAY_D5, DISPLAY_D6, DISPLAY_D7},
      _wr_pin(DISPLAY_WR), _rd_pin(DISPLAY_RD) {
}

FLASHMEM void ILI948x_t4x_p::begin(uint8_t display_name, uint8_t buad_div) {
    // DBGPrintf("Bus speed: %d Mhz \n", buad_div);

    _display_name = display_name;

    switch (buad_div) {
    case 2:
        _baud_div = 120;
        break;
    case 4:
        _baud_div = 60;
        break;
    case 8:
        _baud_div = 30;
        break;
    case 12:
        _baud_div = 20;
        break;
    case 20:
        _baud_div = 12;
        break;
    case 24:
        _baud_div = 10;
        break;
    case 30:
        _baud_div = 8;
        break;
    case 40:
        _baud_div = 6;
        break;
    default:
        _baud_div = 20; // 12Mhz
        break;
    }
    DBGPrintf("Bus speed: %d Mhz Div: %d\n", buad_div, _baud_div);
    pinMode(_cs, OUTPUT);  // CS
    pinMode(_dc, OUTPUT);  // DC
    pinMode(_rst, OUTPUT); // RST

    *(portControlRegister(_cs)) = 0xFF;
    *(portControlRegister(_dc)) = 0xFF;
    *(portControlRegister(_rst)) = 0xFF;

    digitalWriteFast(_cs, HIGH);
    digitalWriteFast(_dc, HIGH);
    digitalWriteFast(_rst, HIGH);

    delay(15);
    digitalWrite(_rst, LOW);
    delay(15);
    digitalWriteFast(_rst, HIGH);
    delay(100);

    FlexIO_Init();

    displayInit(display_name);

    setBitDepth(_bitDepth);
    /*
    setTearingEffect(_bTearingOn);
    if (_bTearingOn == true) {
      setTearingScanLine(_tearingScanLine);
    }
    setFrameRate(_frameRate);
    */

    _width = _TFTWIDTH;
    _height = _TFTHEIGHT;

    setClipRect();
    setOrigin();
    setTextSize(1);
}

FLASHMEM uint8_t ILI948x_t4x_p::setBitDepth(uint8_t bitDepth) {
    uint8_t bd;

    switch (bitDepth) {
    case 16:
        _bitDepth = 16;
        bd = 0x55;
        break;
    case 18:
        _bitDepth = 18;
        bd = 0x66;
        break;
    case 24: // Unsupported
        return _bitDepth;
        break;
    default: // Unsupported
        return _bitDepth;
        break;
    }

    SglBeatWR_nPrm_8(ILI9488_COLMOD, &bd, 1);

    // Insert small delay here as rapid calls appear to fail
    delay(10);

    return _bitDepth;
}

FLASHMEM uint8_t ILI948x_t4x_p::getBitDepth() {
    return _bitDepth;
}

FLASHMEM void ILI948x_t4x_p::setFrameRate(uint8_t frRate) {
    _frameRate = frRate;

    uint8_t fr28Hz[2] = {0x00, 0x11}; // 28.78fps, 17 clocks
    uint8_t fr30Hz[2] = {0x10, 0x11}; // 30.38fps, 17 clocks
    uint8_t fr39Hz[2] = {0x50, 0x11}; // 39.06fps, 17 clocks
    uint8_t fr45Hz[2] = {0x70, 0x11}; // 45.57fps, 17 clocks
    uint8_t fr54Hz[2] = {0x90, 0x11}; // 54.69ps, 17 clocks
    uint8_t fr60Hz[2] = {0xA0, 0x11}; // 60.76fps, 17 clocks
    uint8_t fr68Hz[2] = {0xB0, 0x11}; // 68.36fps, 17 clocks (ILI9488 default)
    uint8_t fr78Hz[2] = {0xC0, 0x11}; // 78.13fps, 17 clocks
    uint8_t fr91Hz[2] = {0xD0, 0x11}; // 91.15fps, 17 clocks

    uint8_t frData[2];
    // Select parameters for frame rate
    switch (frRate) {
    case 28:
        memcpy(frData, fr28Hz, sizeof fr28Hz);
        break;
    case 30:
        memcpy(frData, fr30Hz, sizeof fr30Hz);
        break;
    case 39:
        memcpy(frData, fr39Hz, sizeof fr39Hz);
        break;
    case 45:
        memcpy(frData, fr45Hz, sizeof fr45Hz);
        break;
    case 54:
        memcpy(frData, fr54Hz, sizeof fr54Hz);
        break;
    case 60:
        memcpy(frData, fr60Hz, sizeof fr60Hz);
        break;
    case 68:
        memcpy(frData, fr68Hz, sizeof fr68Hz);
        break;
    case 78:
        memcpy(frData, fr78Hz, sizeof fr78Hz);
        break;
    case 91:
        memcpy(frData, fr91Hz, sizeof fr91Hz);
        break;
    default:
        memcpy(frData, fr60Hz, sizeof fr60Hz);
        _frameRate = 60;
        break;
    }

    SglBeatWR_nPrm_8(ILI9488_FRMCTR1, frData, 2);
}

FLASHMEM uint8_t ILI948x_t4x_p::getFrameRate() {
    return _frameRate;
}

FLASHMEM void ILI948x_t4x_p::setTearingEffect(bool tearingOn) {

    _bTearingOn = tearingOn;
    uint8_t mode = 0x00;

    CSLow();
    if (_bTearingOn == true) {
        SglBeatWR_nPrm_8(ILI9488_TEON, &mode, 1); // Tearing effect line on, mode 0 (V-Blanking)
    } else {
        SglBeatWR_nPrm_8(ILI9488_TEOFF, 0, 0);
    }
    CSHigh();
}

FLASHMEM bool ILI948x_t4x_p::getTearingEffect() {
    return _bTearingOn;
}

FLASHMEM void ILI948x_t4x_p::setTearingScanLine(uint16_t scanLine) {
    _tearingScanLine = scanLine;

    uint8_t params[2] = {(uint8_t)(_tearingScanLine << 8), (uint8_t)(_tearingScanLine & 0xFF)};
    SglBeatWR_nPrm_8(ILI9488_TESLWR, params, 2); // Tearing effect write scan line : 0x00 0x00 = line 0 (default), 0x00 0xA0 = line 160, 0x00 0xF0 = line 240
}

FLASHMEM uint16_t ILI948x_t4x_p::getTearingScanLine() {
    return _tearingScanLine;
}

FLASHMEM void ILI948x_t4x_p::setRotation(uint8_t r) {
    _rotation = r & 3;

    switch (_rotation) {
    case 0:
    case 2:
        _width = _TFTWIDTH;
        _height = _TFTHEIGHT;
        break;
    case 1:
    case 3:
        _width = _TFTHEIGHT;
        _height = _TFTWIDTH;
        break;
    }

    setClipRect();
    setOrigin();

    cursor_x = 0;
    cursor_y = 0;

    SglBeatWR_nPrm_8(ILI9488_MADCTL, &MADCTL[_rotation], 1);
}

FLASHMEM void ILI948x_t4x_p::invertDisplay(bool invert) {
    SglBeatWR_nPrm_8(invert ? ILI9488_INVON : ILI9488_INVOFF, 0, 0);
}

void ILI948x_t4x_p::setScroll(uint16_t offset) {
    //   SglBeatWR_nPrm_8(ILI9488_VSCRSADD, offset, 1); // Changed, offset is
    SglBeatWR_nPrm_16(ILI9488_VSCRSADD, &offset, 1); // a pointer to a 16 bit value.
}

FLASHMEM void ILI948x_t4x_p::onCompleteCB(CBF callback) {
    _callback = callback;
    isCB = true;
}

FASTRUN void ILI948x_t4x_p::displayInfo() {
    CSLow();
    Serial.printf("Manufacturer ID: 0x%02X\n", readCommand(ILI9488_RDID1));
    Serial.printf("Module Version ID: 0x%02X\n", readCommand(ILI9488_RDID2));
    Serial.printf("Module ID: 0x%02X\n", readCommand(ILI9488_RDID3));
    Serial.printf("Display Power Mode: 0x%02X\n", readCommand(ILI9488_RDMODE));
    Serial.printf("MADCTL Mode: 0x%02X\n", readCommand(ILI9488_RDMADCTL));
    Serial.printf("Pixel Format: 0x%02X\n", readCommand(ILI9488_RDCOLMOD));
    Serial.printf("Image Format: 0x%02X\n", readCommand(ILI9488_RDIMGFMT));
    Serial.printf("Signal Mode: 0x%02X\n", readCommand(ILI9488_RDDSM));
    uint8_t sdRes = readCommand(ILI9488_RDSELFDIAG);
    Serial.printf("Self Diagnostic: %s (0x%02X)\n", sdRes == 0xc0 ? "OK" : "Failed", sdRes);
    Serial.printf("Device Information: %06X\n", readCommandN(ILI9488_RDDID, 3));
    uint32_t device_status = readCommandN(ILI9488_RDDST, 4);
    Serial.printf("Device Status: %08X\n", device_status);
    Serial.printf("\tOrder: %s\n", (device_status & (1 << 26)) ? "BGR" : "RGB");
    Serial.print("\tinterface pixel format: ");
    switch ((device_status >> 20) & 0x7) {
    case 0x5:
        Serial.println("16 bit");
        break;
    case 0x6:
        Serial.println("18 bit");
        break;
    case 0x7:
        Serial.println("24 bit");
        break;
    default:
        Serial.println("????");
    }

    CSHigh();
}

FASTRUN void ILI948x_t4x_p::pushPixels16bit(const uint16_t *pcolors, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    while (WR_AsyncTransferDone == false) {
        // Wait for any DMA transfers to complete
    }
    uint32_t area = (x2 - x1 + 1) * (y2 - y1 + 1);
    setAddr(x1, y1, x2, y2);
    SglBeatWR_nPrm_16(ILI9488_RAMWR, pcolors, area);
}

FASTRUN void ILI948x_t4x_p::pushPixels16bitDMA(const uint16_t *pcolors, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    while (WR_AsyncTransferDone == false) {
        // Wait for any DMA transfers to complete
    }
    uint32_t area = (x2 - x1 + 1) * (y2 - y1 + 1);
    setAddr(x1, y1, x2, y2);
    MulBeatWR_nPrm_DMA(ILI9488_RAMWR, pcolors, area);
}

///////////////////
// Private functions
///////////////////
FLASHMEM void ILI948x_t4x_p::displayInit(uint8_t disp_name) {
    const uint8_t *addr;
    DBGPrintf("displayInit called\n");
    switch (disp_name) {
    case 2: // ILI9481-1
    {
        addr = ILI9481_1_init_commands;

        MADCTL[0] = MADCTL_BGR | MADCTL_SS;
        MADCTL[1] = MADCTL_MV | MADCTL_BGR;
        MADCTL[2] = MADCTL_BGR | MADCTL_GS;
        MADCTL[3] = MADCTL_MV | MADCTL_BGR | MADCTL_SS | MADCTL_GS;
        Serial.print("ILI9481 Initialized\n");
    } break;
    case 3: // ILI9481_2
    {
        addr = ILI9481_2_init_commands;

        MADCTL[0] = MADCTL_BGR | MADCTL_SS;
        MADCTL[1] = MADCTL_MV | MADCTL_BGR;
        MADCTL[2] = MADCTL_BGR | MADCTL_GS;
        MADCTL[3] = MADCTL_MV | MADCTL_BGR | MADCTL_SS | MADCTL_GS;
        Serial.print("ILI9481 Initialized\n");

    } break;
    case 1: // ILI9486
    {
        addr = ILI9486_init_commands;

        MADCTL[0] = MADCTL_MX | MADCTL_BGR;
        MADCTL[1] = MADCTL_MV | MADCTL_BGR;
        MADCTL[2] = MADCTL_MY | MADCTL_BGR;
        MADCTL[3] = MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR;
        MADCTL[4] = MADCTL_MY | MADCTL_MV | MADCTL_BGR;
        Serial.print("ILI9486 Initialized\n");
    } break;

    case 4: {
        addr = R61519_init_commands;

        MADCTL[0] = MADCTL_RGB;
        MADCTL[1] = MADCTL_MV | MADCTL_MX | MADCTL_RGB;
        MADCTL[2] = MADCTL_RGB | MADCTL_GS | MADCTL_MX;
        MADCTL[3] = MADCTL_MV | MADCTL_RGB | MADCTL_GS;
        Serial.print("R61519 Initialized\n");
    } break;

    case 0: // ILI9488
    default: {
        addr = ILI9488_init_commands;

        MADCTL[0] = MADCTL_MX | MADCTL_BGR;
        MADCTL[1] = MADCTL_MV | MADCTL_BGR,
        MADCTL[2] = MADCTL_MY | MADCTL_BGR;
        MADCTL[3] = MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR;
        MADCTL[4] = MADCTL_MY | MADCTL_MV | MADCTL_BGR;
        Serial.print("ILI9488 Initialized\n");
    } break;
    }

    uint8_t cmd, commandVals[25];
    while (1) {
        uint8_t count = *addr++;
        uint8_t ms = *addr++;
        if (count-- == 0)
            break;
        cmd = *addr++;
        uint8_t numArgs = 0;
        while (count-- > 0) {
            commandVals[numArgs] = *addr++;
            numArgs += 1;
        }
        DBGPrintf("$CNT: %d, MS: %d, CMD: 0x%x\n", numArgs, ms, cmd);
        for (uint8_t j = 0; j < numArgs; j++) {
            DBGPrintf(" 0x%x ", commandVals[j]);
        }
        Serial.println();
        SglBeatWR_nPrm_8(cmd, commandVals, numArgs);
        delay(ms);
    }
}

FASTRUN void ILI948x_t4x_p::CSLow() {
    digitalWriteFast(_cs, LOW); // Select TFT
}

FASTRUN void ILI948x_t4x_p::CSHigh() {
    digitalWriteFast(_cs, HIGH); // Deselect TFT
}

FASTRUN void ILI948x_t4x_p::DCLow() {
    digitalWriteFast(_dc, LOW); // Writing command to TFT
}

FASTRUN void ILI948x_t4x_p::DCHigh() {
    digitalWriteFast(_dc, HIGH); // Writing data to TFT
}

FASTRUN void ILI948x_t4x_p::microSecondDelay() {
    for (uint32_t i = 0; i < 99; i++)
        __asm__("nop\n\t");
}

FASTRUN void ILI948x_t4x_p::gpioWrite() {
    pFlex->setIOPinToFlexMode(_wr_pin);
    pinMode(_rd_pin, OUTPUT);
    digitalWriteFast(_rd_pin, HIGH);
}

FASTRUN void ILI948x_t4x_p::gpioRead() {
    pFlex->setIOPinToFlexMode(_rd_pin);
    pinMode(_wr_pin, OUTPUT);
    digitalWriteFast(_wr_pin, HIGH);
}

// If used this must be called before begin
// Set the FlexIO pins.  The first version you can specify just the wr, and read and optionsl first Data.
// it will use information in the Flexio library to fill in d1-d7
FASTRUN bool ILI948x_t4x_p::setFlexIOPins(uint8_t write_pin, uint8_t rd_pin, uint8_t tft_d0) {
    DBGPrintf("ILI948x_t4x_p::setFlexIOPins(%u, %u, %u) %u %u %u\n", write_pin, rd_pin, tft_d0, _data_pins[0], _wr_pin, _rd_pin);
    DBGFlush();
    if (tft_d0 != 0xff) {
#ifdef FLEX_IO_HAS_FULL_PIN_MAPPING
        DBGPrintf("\td0 != 0xff\n\n");

        uint8_t flexio_pin;
        pFlex = FlexIOHandler::mapIOPinToFlexIOHandler(tft_d0, flexio_pin);
        if ((pFlex == nullptr) || (flexio_pin == 0xff))
            return false;

        _data_pins[0] = tft_d0;

        // lets dos some quick validation of the pins.
        for (uint8_t i = 1; i < 8; i++) {
            flexio_pin++; // lets look up the what pins come next.
            _data_pins[i] = pFlex->mapFlexPinToIOPin(flexio_pin);
            if (_data_pins[i] == 0xff) {
                Serial.printf("Failed to find Teensy IO pin for Flexio pin %u\n", flexio_pin);
                return false;
            }
        }
#else
        return false;
#endif
    }
    // set the write and read pins and see if d0 is not 0xff set it and compute the others.
    if (write_pin != 0xff)
        _wr_pin = write_pin;
    if (rd_pin != 0xff)
        _rd_pin = rd_pin;

    DBGPrintf("FlexIO pins: data: %u %u %u %u %u %u %u %u WR:%u RD:%u\n",
              _data_pins[0], _data_pins[1], _data_pins[2], _data_pins[3], _data_pins[4], _data_pins[5], _data_pins[6], _data_pins[7],
              _wr_pin, _rd_pin);
    return true;
}

// Set the FlexIO pins.  Specify all of the pins for 8 bit mode. Must be called before begin
FLASHMEM bool ILI948x_t4x_p::setFlexIOPins(uint8_t write_pin, uint8_t rd_pin, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                                           uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {

    _data_pins[0] = d0;
    _data_pins[1] = d1;
    _data_pins[2] = d2;
    _data_pins[3] = d3;
    _data_pins[4] = d4;
    _data_pins[5] = d5;
    _data_pins[6] = d6;
    _data_pins[7] = d7;
    _wr_pin = write_pin;
    _rd_pin = rd_pin;

    DBGPrintf("FlexIO pins: data: %u %u %u %u %u %u %u %u WR:%u RD:%u\n",
              _data_pins[0], _data_pins[1], _data_pins[2], _data_pins[3], _data_pins[4], _data_pins[5], _data_pins[6], _data_pins[7],
              _wr_pin, _rd_pin);
    // Note this does not verify the pins are valid.
    return true;
}

FASTRUN void ILI948x_t4x_p::FlexIO_Init() {
    /* Get a FlexIO channel */
    // lets assume D0 is the valid one...
    DBGPrintf("FlexIO_Init: D0:%u WR:%u RD:%u\n", _data_pins[0], _wr_pin, _rd_pin);
    DBGFlush();
    pFlex = FlexIOHandler::mapIOPinToFlexIOHandler(_data_pins[0], _flexio_D0);
    // pFlex = FlexIOHandler::flexIOHandler_list[1]; // use FlexIO2
    /* Pointer to the port structure in the FlexIO channel */
    p = &pFlex->port();
    /* Pointer to the hardware structure in the FlexIO channel */
    hw = &pFlex->hardware();

    DBGPrintf("\tFlex:%p port:%p hw:%p\n", pFlex, p, hw);

    // lets dos some quick validation of the pins.
    for (uint8_t i = 1; i < 8; i++) {
        uint8_t flexio_pin = pFlex->mapIOPinToFlexPin(_data_pins[i]);
        if (flexio_pin != (_flexio_D0 + i)) {
            Serial.printf("ILI948x_t4x_p::FlexIO_Ini - Flex IO Data pins pin issue D0(%u), D%u(%u)\n", _flexio_D0, i, flexio_pin);
        }
    }

    // Lets reserve the timer and shifters.
    _flexio_timer = pFlex->requestTimers();
    _flexio_timer_mask = 1 << _flexio_timer;

    if (pFlex->claimShifter(0)) {
        _write_shifter = 0;
    } else if (pFlex->claimShifter(4)) {
        _write_shifter = 4;
    } else {
        Serial.println("ILI948x_t4x_p::FlexIO_Init could not claim write Shifter(0 or 4");
    }

    // Maybe this is optional
    if (pFlex->claimShifter(3)) {
        _read_shifter = 3;
    } else if (pFlex->claimShifter(7)) {
        _read_shifter = 7;
    } else {
        Serial.println("ILI948x_t4x_p::FlexIO_Init could not claim Read Shifter(3 or 7");
    }
    _write_shifter_mask = 1 << _write_shifter;
    _read_shifter_mask = 1 << _read_shifter;

    DBGPrintf("FlexIO Timer:%u Shifter Write:%u Read:%u\n", _flexio_timer, _write_shifter, _read_shifter);

    _flexio_WR = pFlex->mapIOPinToFlexPin(_wr_pin);
    _flexio_RD = pFlex->mapIOPinToFlexPin(_rd_pin);

    if ((_flexio_WR == 0xff) || (_flexio_RD == 0xff)) {
        Serial.printf("ILI948x_t4x_p::FlexIO_Ini - RD/WR pin issue: WR:%u(%u) RD:%u(%u)\n", _wr_pin, _flexio_WR, _rd_pin, _flexio_RD);
    }

    DBGPrintf("FlexIO pin mappings: D0(%u)=%u  WR(%u)=%u RD(%u)=%u\n)", _data_pins[0], _flexio_D0, _wr_pin, _flexio_WR, _rd_pin, _flexio_RD);

    // Now l
    for (uint8_t pin_index = 0; pin_index < 8; pin_index++) {
        pinMode(_data_pins[pin_index], OUTPUT);
    }

    /* Basic pin setup */
    pinMode(_wr_pin, OUTPUT); // FlexIO2:0 WR
    pinMode(_rd_pin, OUTPUT); // FlexIO2:1 RD

    digitalWriteFast(_wr_pin, HIGH);
    digitalWriteFast(_rd_pin, HIGH);

    /* High speed and drive strength configuration */
    *(portControlRegister(_wr_pin)) = 0xFF;
    *(portControlRegister(_rd_pin)) = 0xFF;

    for (uint8_t pin_index = 0; pin_index < 8; pin_index++) {
        *(portControlRegister(_data_pins[pin_index])) = 0xFF;
    }

    /* Set clock */
    pFlex->setClockSettings(3, 1, 0); // (480 MHz source, 1+1, 1+0) >> 480/2/1 >> 240Mhz

    /* Enable the clock */
    hw->clock_gate_register |= hw->clock_gate_mask;

    pFlex->setIOPinToFlexMode(_wr_pin);
    pFlex->setIOPinToFlexMode(_rd_pin);

    for (uint8_t pin_index = 0; pin_index < 8; pin_index++) {
        pFlex->setIOPinToFlexMode(_data_pins[pin_index]);
    }

    // Lets print out all of the pins, configurations
    for (uint8_t pin_index = 0; pin_index < 8; pin_index++) {
        DBGPrintf("Data%u: pin:%u Port:%08x Mux:%08x\n", pin_index, _data_pins[pin_index],
                  *(portControlRegister(_data_pins[pin_index])), *(portConfigRegister(_data_pins[pin_index])));
    }
    DBGPrintf("WR: pin:%u Port:%08x Mux:%08x\n", _wr_pin, *(portControlRegister(_wr_pin)), *(portConfigRegister(_wr_pin)));
    DBGPrintf("RD: pin:%u Port:%08x Mux:%08x\n", _rd_pin, *(portControlRegister(_rd_pin)), *(portConfigRegister(_rd_pin)));

    /* Enable the FlexIO with fast access */
    p->CTRL = FLEXIO_CTRL_FLEXEN /*| FLEXIO_CTRL_FASTACC */;

    gpioWrite();

    DBGPrintf("*** flexio_init completed ***\n");
}

FASTRUN void ILI948x_t4x_p::FlexIO_Config_SnglBeat_Read() {

    if (flex_config == CONFIG_SNGLREAD)
        return;
    flex_config = CONFIG_SNGLREAD;
    DBGPrintf("ILI948x_t4x_p::FlexIO_Config_SnglBeat_Read - Enter\n");
    p->CTRL &= ~FLEXIO_CTRL_FLEXEN;
    // p->CTRL |= FLEXIO_CTRL_SWRST;
    p->CTRL &= ~FLEXIO_CTRL_SWRST;

    gpioRead(); // write line high, pin 12(rst) as output

    /* Configure the shifters */
    p->SHIFTCFG[_read_shifter] =
        // FLEXIO_SHIFTCFG_INSRC                                                  /* Shifter input */
        FLEXIO_SHIFTCFG_SSTOP(0)     /* Shifter stop bit disabled */
        | FLEXIO_SHIFTCFG_SSTART(0)  /* Shifter start bit disabled and loading data on enabled */
        | FLEXIO_SHIFTCFG_PWIDTH(7); /* Bus width */

    p->SHIFTCTL[_read_shifter] =
        FLEXIO_SHIFTCTL_TIMSEL(_flexio_timer)        /* Shifter's assigned timer index */
        | FLEXIO_SHIFTCTL_TIMPOL * (1)               /* Shift on posedge of shift clock */
        | FLEXIO_SHIFTCTL_PINCFG(0)                  /* Shifter's pin configured as input */
        | FLEXIO_SHIFTCTL_PINSEL(_flexio_D0) /*D0 */ /* Shifter's pin start index */
        | FLEXIO_SHIFTCTL_PINPOL * (0)               /* Shifter's pin active high */
        | FLEXIO_SHIFTCTL_SMOD(1);                   /* Shifter mode as recieve */

    /* Configure the timer for shift clock */
    p->TIMCMP[_flexio_timer] =
        (((1 * 2) - 1) << 8)                /* TIMCMP[15:8] = number of beats x 2 – 1 */
        | (((ILI9488_CLOCK_READ) / 2) - 1); /* TIMCMP[7:0] = baud rate divider / 2 – 1 ::: 30 = 8Mhz with current controller speed */

    p->TIMCFG[_flexio_timer] =
        FLEXIO_TIMCFG_TIMOUT(0)       /* Timer output logic one when enabled and not affected by reset */
        | FLEXIO_TIMCFG_TIMDEC(0)     /* Timer decrement on FlexIO clock, shift clock equals timer output */
        | FLEXIO_TIMCFG_TIMRST(0)     /* Timer never reset */
        | FLEXIO_TIMCFG_TIMDIS(2)     /* Timer disabled on timer compare */
        | FLEXIO_TIMCFG_TIMENA(2)     /* Timer enabled on trigger high */
        | FLEXIO_TIMCFG_TSTOP(1)      /* Timer stop bit disabled */
        | FLEXIO_TIMCFG_TSTART * (0); /* Timer start bit disabled */

    p->TIMCTL[_flexio_timer] =
        FLEXIO_TIMCTL_TRGSEL((((_read_shifter) << 2) | 1)) /* Timer trigger selected as shifter's status flag */
        | FLEXIO_TIMCTL_TRGPOL * (1)                       /* Timer trigger polarity as active low */
        | FLEXIO_TIMCTL_TRGSRC * (1)                       /* Timer trigger source as internal */
        | FLEXIO_TIMCTL_PINCFG(3)                          /* Timer' pin configured as output */
        | FLEXIO_TIMCTL_PINSEL(_flexio_RD)                 /* Timer' pin index: RD pin */
        | FLEXIO_TIMCTL_PINPOL * (1)                       /* Timer' pin active low */
        | FLEXIO_TIMCTL_TIMOD(1);                          /* Timer mode as dual 8-bit counters baud/bit */


    // Clear the shifter status 
    p->SHIFTSTAT = _read_shifter_mask;
    p->SHIFTERR = _read_shifter_mask;
    
    /* Enable FlexIO */
    p->CTRL |= FLEXIO_CTRL_FLEXEN;
    DBGPrintf("ILI948x_t4x_p::FlexIO_Config_SnglBeat_Read - Exit\n");
}

FASTRUN uint8_t ILI948x_t4x_p::readCommand(uint8_t const cmd) {
    while (WR_AsyncTransferDone == false) {
        // Wait for any DMA transfers to complete
    }

    FlexIO_Config_SnglBeat();
    CSLow();
    DCLow();

    /* Write command index */
    p->SHIFTBUF[_write_shifter] = cmd;

    /*Wait for transfer to be completed */
    waitWriteShiftStat(__LINE__);
    waitTimStat(__LINE__);

    /* De-assert RS pin */
    microSecondDelay();
    DCHigh();

    FlexIO_Clear_Config_SnglBeat();
    FlexIO_Config_SnglBeat_Read();

    uint8_t dummy __attribute__((unused)) = 0;
    uint8_t data = 0;

    waitReadShiftStat(__LINE__);
    // digitalToggleFast(2);
    dummy = p->SHIFTBUFBYS[_read_shifter];

    waitReadShiftStat(__LINE__);
    // digitalToggleFast(2);
    data = p->SHIFTBUFBYS[_read_shifter];

    CSHigh();
    microSecondDelay();
    // Serial.printf("Dummy 0x%x, data 0x%x\n", dummy, data);

    // Set FlexIO back to Write mode
    FlexIO_Config_SnglBeat();
    return data;
};

// Note we could combine the above with thsi.
FASTRUN uint32_t ILI948x_t4x_p::readCommandN(uint8_t const cmd, uint8_t count_bytes) {
    while (WR_AsyncTransferDone == false) {
        // Wait for any DMA transfers to complete
    }

    FlexIO_Config_SnglBeat();
    CSLow();
    DCLow();

    /* Write command index */
    p->SHIFTBUF[_write_shifter] = cmd;

    /*Wait for transfer to be completed */
    waitWriteShiftStat(__LINE__);
    waitTimStat(__LINE__);

    /* De-assert RS pin */
    microSecondDelay();
    DCHigh();

    FlexIO_Clear_Config_SnglBeat();
    FlexIO_Config_SnglBeat_Read();

    uint8_t __attribute__((unused)) dummy = 0;
    uint32_t data = 0;

    waitReadShiftStat(__LINE__);
    // digitalToggleFast(2);
    dummy = p->SHIFTBUFBYS[_read_shifter];

    while (count_bytes--) {
        waitReadShiftStat(__LINE__);
        data = (data << 8) | (p->SHIFTBUFBYS[_read_shifter] & 0xff);
        // digitalToggleFast(2);
    }
    // Serial.printf("Dummy 0x%x, data 0x%x\n", dummy, data);

    // Set FlexIO back to Write mode
    microSecondDelay();
    CSHigh();
    microSecondDelay();
    FlexIO_Config_SnglBeat();
    return data;
};

void print_flexio_debug_data(FlexIOHandler *pFlex, uint8_t flexio_timer, uint8_t write_shifter, uint8_t read_shifter) {
    IMXRT_FLEXIO_t *p = &pFlex->port();
    Serial.println("\n**********************************");
    Serial.printf("FlexIO Index: %u Timer:%u Write Shifter:%u Read Shifter:%u\n", pFlex->FlexIOIndex(), flexio_timer, write_shifter, read_shifter);
    Serial.printf("CCM_CDCDR: %x\n", CCM_CDCDR);
    Serial.printf("CCM FlexIO1: %x FlexIO2: %x FlexIO3: %x\n", CCM_CCGR5 & CCM_CCGR5_FLEXIO1(CCM_CCGR_ON),
                  CCM_CCGR3 & CCM_CCGR3_FLEXIO2(CCM_CCGR_ON), CCM_CCGR7 & CCM_CCGR7_FLEXIO3(CCM_CCGR_ON));
    Serial.printf("VERID:%x PARAM:%x CTRL:%x PIN: %x\n", p->VERID, p->PARAM, p->CTRL, p->PIN);
    Serial.printf("SHIFTSTAT:%x SHIFTERR=%x TIMSTAT=%x\n", p->SHIFTSTAT, p->SHIFTERR, p->TIMSTAT);
    Serial.printf("SHIFTSIEN:%x SHIFTEIEN=%x TIMIEN=%x\n", p->SHIFTSIEN, p->SHIFTEIEN, p->TIMIEN);
    Serial.printf("SHIFTSDEN:%x SHIFTSTATE=%x\n", p->SHIFTSDEN, p->SHIFTSTATE);
    Serial.print("SHIFTCTL:");
    for (int i = 0; i < 8; i++) {
        Serial.printf(" %08x", p->SHIFTCTL[i]);
    }
    Serial.print("\nSHIFTCFG:");
    for (int i = 0; i < 8; i++) {
        Serial.printf(" %08x", p->SHIFTCFG[i]);
    }

    Serial.printf("\nTIMCTL:%x %x %x %x\n", p->TIMCTL[0], p->TIMCTL[1], p->TIMCTL[2], p->TIMCTL[3]);
    Serial.printf("TIMCFG:%x %x %x %x\n", p->TIMCFG[0], p->TIMCFG[1], p->TIMCFG[2], p->TIMCFG[3]);
    Serial.printf("TIMCMP:%x %x %x %x\n", p->TIMCMP[0], p->TIMCMP[1], p->TIMCMP[2], p->TIMCMP[3]);
}

FASTRUN void ILI948x_t4x_p::FlexIO_Config_SnglBeat() {

    if (flex_config == CONFIG_SNGLBEAT)
        return;
    flex_config = CONFIG_SNGLBEAT;

    static uint8_t DEBUG_COUNT = 1;

    gpioWrite();

    p->CTRL &= ~FLEXIO_CTRL_FLEXEN;
    // p->CTRL |= FLEXIO_CTRL_SWRST;
    // Make sure we are not in reset...
    p->CTRL &= ~FLEXIO_CTRL_SWRST;

    /* Configure the shifters */
    // try setting it twice
    p->SHIFTCFG[_write_shifter] =
        FLEXIO_SHIFTCFG_INSRC * (1)  /* Shifter input */
        | FLEXIO_SHIFTCFG_SSTOP(0)   /* Shifter stop bit disabled */
        | FLEXIO_SHIFTCFG_SSTART(0)  /* Shifter start bit disabled and loading data on enabled */
        | FLEXIO_SHIFTCFG_PWIDTH(7); /* Bus width */

    p->SHIFTCTL[_write_shifter] =
        FLEXIO_SHIFTCTL_TIMSEL(_flexio_timer) /* Shifter's assigned timer index */
        | FLEXIO_SHIFTCTL_TIMPOL * (0)        /* Shift on posedge of shift clock */
        | FLEXIO_SHIFTCTL_PINCFG(3)           /* Shifter's pin configured as output */
        | FLEXIO_SHIFTCTL_PINSEL(_flexio_D0)  /* Shifter's pin start index */
        | FLEXIO_SHIFTCTL_PINPOL * (0)        /* Shifter's pin active high */
        | FLEXIO_SHIFTCTL_SMOD(2);            /* Shifter mode as transmit */

    /* Configure the timer for shift clock */
    p->TIMCMP[_flexio_timer] =
        (((1 * 2) - 1) << 8)     /* TIMCMP[15:8] = number of beats x 2 – 1 */
        | ((_baud_div / 2) - 1); /* TIMCMP[7:0] = baud rate divider / 2 – 1 */

    p->TIMCFG[_flexio_timer] =
        FLEXIO_TIMCFG_TIMOUT(0)       /* Timer output logic one when enabled and not affected by reset */
        | FLEXIO_TIMCFG_TIMDEC(0)     /* Timer decrement on FlexIO clock, shift clock equals timer output */
        | FLEXIO_TIMCFG_TIMRST(0)     /* Timer never reset */
        | FLEXIO_TIMCFG_TIMDIS(2)     /* Timer disabled on timer compare */
        | FLEXIO_TIMCFG_TIMENA(2)     /* Timer enabled on trigger high */
        | FLEXIO_TIMCFG_TSTOP(0)      /* Timer stop bit disabled */
        | FLEXIO_TIMCFG_TSTART * (0); /* Timer start bit disabled */

    p->TIMCTL[_flexio_timer] =
        FLEXIO_TIMCTL_TRGSEL((((_write_shifter) << 2) | 1)) /* Timer trigger selected as shifter's status flag */
        | FLEXIO_TIMCTL_TRGPOL * (1)                        /* Timer trigger polarity as active low */
        | FLEXIO_TIMCTL_TRGSRC * (1)                        /* Timer trigger source as internal */
        | FLEXIO_TIMCTL_PINCFG(3)                           /* Timer' pin configured as output */
        | FLEXIO_TIMCTL_PINSEL(_flexio_WR)                  /* Timer' pin index: WR pin */
        | FLEXIO_TIMCTL_PINPOL * (1)                        /* Timer' pin active low */
        | FLEXIO_TIMCTL_TIMOD(1);                           /* Timer mode as dual 8-bit counters baud/bit */

    if (DEBUG_COUNT) {
        DEBUG_COUNT--;
        print_flexio_debug_data(pFlex, _flexio_timer, _write_shifter, _read_shifter);
    }

    /* Enable FlexIO */
    p->CTRL |= FLEXIO_CTRL_FLEXEN;
}

FASTRUN void ILI948x_t4x_p::FlexIO_Clear_Config_SnglBeat() {
    if (flex_config == CONFIG_CLEAR)
        return;
    DBGPrintf("ILI948x_t4x_p::FlexIO_Clear_Config_SnglBeat() - Enter\n");
    flex_config = CONFIG_CLEAR;

    p->CTRL &= ~FLEXIO_CTRL_FLEXEN;
    // p->CTRL |= FLEXIO_CTRL_SWRST;
    p->CTRL &= ~FLEXIO_CTRL_SWRST;

    p->SHIFTCFG[_write_shifter] = 0;
    p->SHIFTCTL[_write_shifter] = 0;
    p->SHIFTSTAT = _write_shifter_mask;
    p->TIMCMP[_flexio_timer] = 0;
    p->TIMCFG[_flexio_timer] = 0;
    p->TIMSTAT = _flexio_timer_mask; /* Timer start bit disabled */
    p->TIMCTL[_flexio_timer] = 0;

    /* Enable FlexIO */
    p->CTRL |= FLEXIO_CTRL_FLEXEN;
    DBGPrintf("ILI948x_t4x_p::FlexIO_Clear_Config_SnglBeat() - Exit\n");
}

FASTRUN void ILI948x_t4x_p::FlexIO_Config_MultiBeat() {
    if (flex_config == CONFIG_MULTIBEAT)
        return;
    flex_config = CONFIG_MULTIBEAT;
    DBGPrintf("ILI948x_t4x_p::FlexIO_Config_MultiBeat() - Enter\n");

    uint32_t i;
    uint8_t MulBeatWR_BeatQty = SHIFTNUM * sizeof(uint32_t) / sizeof(uint8_t); // Number of beats = number of shifters * beats per shifter
    /* Disable and reset FlexIO */
    p->CTRL &= ~FLEXIO_CTRL_FLEXEN;
    // p->CTRL |= FLEXIO_CTRL_SWRST;
    p->CTRL &= ~FLEXIO_CTRL_SWRST;

    gpioWrite();

    for (i = 0; i <= SHIFTNUM - 1; i++) {
        p->SHIFTCFG[_write_shifter + i] =
            FLEXIO_SHIFTCFG_INSRC * (1U)       /* Shifter input from next shifter's output */
            | FLEXIO_SHIFTCFG_SSTOP(0U)        /* Shifter stop bit disabled */
            | FLEXIO_SHIFTCFG_SSTART(0U)       /* Shifter start bit disabled and loading data on enabled */
            | FLEXIO_SHIFTCFG_PWIDTH(8U - 1U); /* 8 bit shift width */
    }

    p->SHIFTCTL[_write_shifter] =
        FLEXIO_SHIFTCTL_TIMSEL(_flexio_timer) /* Shifter's assigned timer index */
        | FLEXIO_SHIFTCTL_TIMPOL * (0U)       /* Shift on posedge of shift clock */
        | FLEXIO_SHIFTCTL_PINCFG(3U)          /* Shifter's pin configured as output */
        | FLEXIO_SHIFTCTL_PINSEL(_flexio_D0)  /* Shifter's pin start index */
        | FLEXIO_SHIFTCTL_PINPOL * (0U)       /* Shifter's pin active high */
        | FLEXIO_SHIFTCTL_SMOD(2U);           /* shifter mode transmit */

    for (i = 1; i <= SHIFTNUM - 1; i++) {
        p->SHIFTCTL[_write_shifter + i] =
            FLEXIO_SHIFTCTL_TIMSEL(_flexio_timer) /* Shifter's assigned timer index */
            | FLEXIO_SHIFTCTL_TIMPOL * (0U)       /* Shift on posedge of shift clock */
            | FLEXIO_SHIFTCTL_PINCFG(0U)          /* Shifter's pin configured as output disabled */
            | FLEXIO_SHIFTCTL_PINSEL(_flexio_D0)  /* Shifter's pin start index */
            | FLEXIO_SHIFTCTL_PINPOL * (0U)       /* Shifter's pin active high */
            | FLEXIO_SHIFTCTL_SMOD(2U);           /* shifter mode transmit */

        //p->SHIFTSTAT = 1 << (_write_shifter + i); // clear out any previous state
        p->SHIFTERR = 1 << (_write_shifter + i); // clear out any previous state
    }

    /* Configure the timer for shift clock */
    p->TIMCMP[_flexio_timer] =
        ((MulBeatWR_BeatQty * 2U - 1) << 8) /* TIMCMP[15:8] = number of beats x 2 – 1 */
        | (_baud_div / 2U - 1U);            /* TIMCMP[7:0] = shift clock divide ratio / 2 - 1 */

    p->TIMCFG[_flexio_timer] = FLEXIO_TIMCFG_TIMOUT(0U)       /* Timer output logic one when enabled and not affected by reset */
                               | FLEXIO_TIMCFG_TIMDEC(0U)     /* Timer decrement on FlexIO clock, shift clock equals timer output */
                               | FLEXIO_TIMCFG_TIMRST(0U)     /* Timer never reset */
                               | FLEXIO_TIMCFG_TIMDIS(2U)     /* Timer disabled on timer compare */
                               | FLEXIO_TIMCFG_TIMENA(2U)     /* Timer enabled on trigger high */
                               | FLEXIO_TIMCFG_TSTOP(0U)      /* Timer stop bit disabled */
                               | FLEXIO_TIMCFG_TSTART * (0U); /* Timer start bit disabled */

    p->TIMCTL[_flexio_timer] =
        FLEXIO_TIMCTL_TRGSEL((_write_shifter << 2) | 1U) /* Timer trigger selected as highest shifter's status flag */
        | FLEXIO_TIMCTL_TRGPOL * (1U)                    /* Timer trigger polarity as active low */
        | FLEXIO_TIMCTL_TRGSRC * (1U)                    /* Timer trigger source as internal */
        | FLEXIO_TIMCTL_PINCFG(3U)                       /* Timer' pin configured as output */
        | FLEXIO_TIMCTL_PINSEL(_flexio_WR)               /* Timer' pin index: WR pin */
        | FLEXIO_TIMCTL_PINPOL * (1U)                    /* Timer' pin active low */
        | FLEXIO_TIMCTL_TIMOD(1U);                       /* Timer mode 8-bit baud counter */


    /* Enable FlexIO */
    p->CTRL |= FLEXIO_CTRL_FLEXEN;

    print_flexio_debug_data(pFlex, _flexio_timer, _write_shifter, _read_shifter);

   // configure interrupts
    if (hw->shifters_dma_channel[SHIFTER_DMA_REQUEST] == 0xff) {
        DBGPrintf("ILI948x_t4x_p::FlexIO_Config_MultiBeat() - IRQ mode\n");
        attachInterruptVector(hw->flex_irq, flexio_ISR);
        NVIC_ENABLE_IRQ(hw->flex_irq);
        NVIC_SET_PRIORITY(hw->flex_irq, FLEXIO_ISR_PRIORITY);
        
        // disable interrupts until later
        p->SHIFTSIEN &= ~(1 << SHIFTER_IRQ);
        p->TIMIEN &= ~_flexio_timer_mask;

    } else {
        p->SHIFTSDEN |= 1U << (SHIFTER_DMA_REQUEST); // enable DMA trigger when shifter status flag is set on shifter SHIFTER_DMA_REQUEST
    }
    DBGPrintf("ILI948x_t4x_p::FlexIO_Config_MultiBeat() - Exit\n");
}

FASTRUN void ILI948x_t4x_p::SglBeatWR_nPrm_8(uint32_t const cmd, const uint8_t *value = NULL, uint32_t const length = 0) {
    DBGPrintf("ILI948x_t4x_p::SglBeatWR_nPrm_8(%x, %x, %u\n", cmd, value, length);
    while (WR_AsyncTransferDone == false) {
        // Wait for any DMA transfers to complete
    }

    FlexIO_Config_SnglBeat();
    uint32_t i;
    /* Assert CS, RS pins */

    // delay(1);
    CSLow();
    DCLow();

    /* Write command index */
    p->SHIFTBUF[_write_shifter] = cmd;

    /*Wait for transfer to be completed */
    waitWriteShiftStat(__LINE__);
    waitTimStat(__LINE__);

    /* De-assert RS pin */

    microSecondDelay();
    DCHigh();
    microSecondDelay();

    if (length) {
        for (i = 0; i < length; i++) {
            p->SHIFTBUF[_write_shifter] = *value++;
            waitWriteShiftStat(__LINE__);
        }
        waitTimStat(__LINE__);
    }
    microSecondDelay();
    CSHigh();
    /* De-assert CS pin */
}

FASTRUN void ILI948x_t4x_p::SglBeatWR_nPrm_16(uint32_t const cmd, const uint16_t *value, uint32_t const length) {
    DBGPrintf("ILI948x_t4x_p::SglBeatWR_nPrm_16(%x, %x, %u\n", cmd, value, length);
    while (WR_AsyncTransferDone == false) {
        // Wait for any DMA transfers to complete
    }
    FlexIO_Config_SnglBeat();
    uint16_t buf;
    /* Assert CS, RS pins */
    CSLow();
    DCLow();
    // microSecondDelay();

    /* Write command index */
    p->SHIFTBUF[_write_shifter] = cmd;

    /*Wait for transfer to be completed */
    waitTimStat(__LINE__);
    microSecondDelay();
    /* De-assert RS pin */
    DCHigh();
    microSecondDelay();

    if (length) {
        for (uint32_t i = 0; i < length - 1U; i++) {
            buf = *value++;
            waitWriteShiftStat(__LINE__);
            p->SHIFTBUF[_write_shifter] = buf >> 8;

            waitWriteShiftStat(__LINE__);
            p->SHIFTBUF[_write_shifter] = buf & 0xFF;
        }
        buf = *value++;
        /* Write the last byte */
        waitWriteShiftStat(__LINE__);
        p->SHIFTBUF[_write_shifter] = buf >> 8;

        waitWriteShiftStat(__LINE__);
        p->TIMSTAT |= _flexio_timer_mask;

        p->SHIFTBUF[_write_shifter] = buf & 0xFF;

        /*Wait for transfer to be completed */
        waitTimStat();
    }
    microSecondDelay();
    CSHigh();
}

void dumpDMA_TCD(DMABaseClass *dmabc, const char *psz_title) {
  if (psz_title)
    Serial.print(psz_title);
  Serial.printf("%x %x:", (uint32_t)dmabc, (uint32_t)dmabc->TCD);

  Serial.printf(
      "SA:%x SO:%d AT:%x NB:%x SL:%d DA:%x DO: %d CI:%x DL:%x CS:%x BI:%x\n",
      (uint32_t)dmabc->TCD->SADDR, dmabc->TCD->SOFF, dmabc->TCD->ATTR,
      dmabc->TCD->NBYTES, dmabc->TCD->SLAST, (uint32_t)dmabc->TCD->DADDR,
      dmabc->TCD->DOFF, dmabc->TCD->CITER, dmabc->TCD->DLASTSGA,
      dmabc->TCD->CSR, dmabc->TCD->BITER);
}


ILI948x_t4x_p *ILI948x_t4x_p::dmaCallback = nullptr;
DMAChannel ILI948x_t4x_p::flexDma;

FASTRUN void ILI948x_t4x_p::MulBeatWR_nPrm_DMA(uint32_t const cmd, const void *value, uint32_t const length) {
    Serial.printf("ILI948x_t4x_p::MulBeatWR_nPrm_DMA(%x, %x, %u\n", cmd, value, length);
    while (WR_AsyncTransferDone == false) {
        // Wait for any DMA transfers to complete
    }
    uint32_t BeatsPerMinLoop = SHIFTNUM * sizeof(uint32_t) / sizeof(uint8_t); // Number of shifters * number of 8 bit values per shifter
    uint32_t majorLoopCount, minorLoopBytes;
    uint32_t destinationModulo = 31 - (__builtin_clz(SHIFTNUM * sizeof(uint32_t))); // defines address range for circular DMA destination buffer

    FlexIO_Config_SnglBeat();
    CSLow();
    DCLow();

    /* Write command index */
    p->SHIFTBUF[_write_shifter] = cmd;

    /*Wait for transfer to be completed */

    waitTimStat(__LINE__);
    microSecondDelay();
    /* De-assert RS pin */
    DCHigh();
    microSecondDelay();

    if (length < 8) {
        // Serial.println ("In DMA but to Short to multibeat");
        const uint16_t *newValue = (uint16_t *)value;
        uint16_t buf;
        for (uint32_t i = 0; i < length; i++) {
            buf = *newValue++;
            waitWriteShiftStat(__LINE__);
            p->SHIFTBUF[_write_shifter] = buf >> 8;

            waitWriteShiftStat(__LINE__);
            p->SHIFTBUF[_write_shifter] = buf & 0xFF;
        }
        // Wait for transfer to be completed
        while (0 == (p->TIMSTAT & _flexio_timer_mask)) {
        }

        microSecondDelay();
        CSHigh();

    }

    else {
        // memcpy(framebuff, value, length);
        // arm_dcache_flush((void*)framebuff, sizeof(framebuff)); // always flush cache after writing to DMAMEM variable that will be accessed by DMA
        if ((uint32_t)value >= 0x20200000u) {
            arm_dcache_flush((void*)value, length*2);
        }

        FlexIO_Config_MultiBeat();

        MulBeatCountRemain = length % BeatsPerMinLoop;
        MulBeatDataRemain = (uint16_t *)value + ((length - MulBeatCountRemain)); // pointer to the next unused byte (overflow if MulBeatCountRemain = 0)
        TotalSize = (length - MulBeatCountRemain) * 2;                           /* in bytes */
        minorLoopBytes = SHIFTNUM * sizeof(uint32_t);
        majorLoopCount = TotalSize / minorLoopBytes;
        // Serial.printf("Length(16bit): %d, Count remain(16bit): %d, Data remain: %d, TotalSize(8bit): %d, majorLoopCount: %d \n",length, MulBeatCountRemain, MulBeatDataRemain, TotalSize, majorLoopCount );

        /* Configure FlexIO with multi-beat write configuration */
        flexDma.begin();

        /* Setup DMA transfer with on-the-fly swapping of MSB and LSB in 16-bit data:
         *  Within each minor loop, read 16-bit values from buf in reverse order, then write 32bit values to SHIFTBUFBYS[i] in reverse order.
         *  Result is that every pair of bytes are swapped, while half-words are unswapped.
         *  After each minor loop, advance source address using minor loop offset. */
        int destinationAddressOffset, destinationAddressLastOffset, sourceAddressOffset, sourceAddressLastOffset, minorLoopOffset;
        volatile void *destinationAddress, *sourceAddress;

        DMA_CR |= DMA_CR_EMLM; // enable minor loop mapping

        sourceAddress = (uint16_t *)value + minorLoopBytes / sizeof(uint16_t) - 1; // last 16bit address within current minor loop
        sourceAddressOffset = -sizeof(uint16_t);                                   // read values in reverse order
        minorLoopOffset = 2 * minorLoopBytes;                                      // source address offset at end of minor loop to advance to next minor loop
        sourceAddressLastOffset = minorLoopOffset - TotalSize;                     // source address offset at completion to reset to beginning
        destinationAddress = (uint32_t *)&p->SHIFTBUFBYS[SHIFTNUM - 1];            // last 32bit shifter address (with reverse byte order)
        destinationAddressOffset = -sizeof(uint32_t);                              // write words in reverse order
        destinationAddressLastOffset = 0;

        flexDma.TCD->SADDR = sourceAddress;
        flexDma.TCD->SOFF = sourceAddressOffset;
        flexDma.TCD->SLAST = sourceAddressLastOffset;
        flexDma.TCD->DADDR = destinationAddress;
        flexDma.TCD->DOFF = destinationAddressOffset;
        flexDma.TCD->DLASTSGA = destinationAddressLastOffset;
        flexDma.TCD->ATTR =
            DMA_TCD_ATTR_SMOD(0U) | DMA_TCD_ATTR_SSIZE(DMA_TCD_ATTR_SIZE_16BIT)                   // 16bit reads
            | DMA_TCD_ATTR_DMOD(destinationModulo) | DMA_TCD_ATTR_DSIZE(DMA_TCD_ATTR_SIZE_32BIT); // 32bit writes
        flexDma.TCD->NBYTES_MLOFFYES =
            DMA_TCD_NBYTES_SMLOE | DMA_TCD_NBYTES_MLOFFYES_MLOFF(minorLoopOffset) | DMA_TCD_NBYTES_MLOFFYES_NBYTES(minorLoopBytes);
        flexDma.TCD->CITER = majorLoopCount; // Current major iteration count
        flexDma.TCD->BITER = majorLoopCount; // Starting major iteration count

        flexDma.triggerAtHardwareEvent(hw->shifters_dma_channel[SHIFTER_DMA_REQUEST]);
        flexDma.disableOnCompletion();
        flexDma.interruptAtCompletion();
        flexDma.clearComplete();

        // Serial.println("Dma setup done");

        /* Start data transfer by using DMA */
        WR_AsyncTransferDone = false;
        flexDma.attachInterrupt(dmaISR);

        dumpDMA_TCD(&flexDma, "ILI948x_t4x_p)\n");

        flexDma.enable();
        // Serial.println("Starting transfer");
        dmaCallback = this;
    }
}

FASTRUN void ILI948x_t4x_p::_onCompleteCB() {
    if (_callback) {
        _callback();
    }
    return;
}

FASTRUN void ILI948x_t4x_p::dmaISR() {
    flexDma.clearInterrupt();
    asm volatile("dsb"); // prevent interrupt from re-entering
    dmaCallback->flexDma_Callback();
}

FASTRUN void ILI948x_t4x_p::flexDma_Callback() {
    // Serial.printf("DMA callback start triggred \n");

    /* the interrupt is called when the final DMA transfer completes writing to the shifter buffers, which would generally happen while
    data is still in the process of being shifted out from the second-to-last major iteration. In this state, all the status flags are cleared.
    when the second-to-last major iteration is fully shifted out, the final data is transfered from the buffers into the shifters which sets all the status flags.
    if you have only one major iteration, the status flags will be immediately set before the interrupt is called, so the while loop will be skipped. */
    while (0 == (p->SHIFTSTAT & (1U << (SHIFTNUM - 1)))) {
    }

    /* Wait the last multi-beat transfer to be completed. Clear the timer flag
    before the completing of the last beat. The last beat may has been completed
    at this point, then code would be dead in the while() below. So mask the
    while() statement and use the software delay .*/
    p->TIMSTAT |= (1U << 0U);

    /* Wait timer flag to be set to ensure the completing of the last beat.
    while(0 == (p->TIMSTAT & (1U << 0U)))
    {
    }
    */
    delayMicroseconds(200);

    if (MulBeatCountRemain) {
        // Serial.printf("MulBeatCountRemain in DMA callback: %d, MulBeatDataRemain %x \n", MulBeatCountRemain,MulBeatDataRemain);
        uint16_t value;
        /* Configure FlexIO with 1-beat write configuration */
        FlexIO_Config_SnglBeat();

        // Serial.printf("Starting single beat completion: %d \n", MulBeatCountRemain);

        /* Use polling method for data transfer */
        for (uint32_t i = 0; i < (MulBeatCountRemain); i++) {
            value = *MulBeatDataRemain++;
            waitWriteShiftStat(__LINE__);
            p->SHIFTBUF[_write_shifter] = value >> 8;

            waitWriteShiftStat(__LINE__);
            p->SHIFTBUF[_write_shifter] = value & 0xFF;
        }
        p->TIMSTAT |= _flexio_timer_mask;
        /*
        value = *MulBeatDataRemain++;
        //Write the last byte

        while(0 == (p->SHIFTSTAT & _flexio_timer_mask))
            {
            }
        p->SHIFTBUF[_write_shifter] = value >> 8;

        while(0 == (p->SHIFTSTAT & _flexio_timer_mask))
        {
        }
        p->TIMSTAT |= _flexio_timer_mask;

        p->SHIFTBUF[_write_shifter] = value & 0xFF;
        */
        /*Wait for transfer to be completed */
        waitTimStat();
        // Serial.println("Finished single beat completion");
    }

    microSecondDelay();
    CSHigh();
    /* the for loop is probably not sufficient to complete the transfer. Shifting out all 32 bytes takes (32 beats)/(6 MHz) = 5.333 microseconds which is over 3000 CPU cycles.
    If you really need to wait in this callback until all the data has been shifted out, the while loop is probably the correct solution and I don't think it risks an infinite loop.
    however, it seems like a waste of time to wait here, since the process otherwise completes in the background and the shifter buffers are ready to receive new data while the transfer completes.
    I think in most applications you could continue without waiting. You can start a new DMA transfer as soon as the first one completes (no need to wait for FlexIO to finish shifting). */

    WR_AsyncTransferDone = true;
    //    flexDma.disable(); // not necessary because flexDma is already configured to disable on completion
    if (isCB) {
        // Serial.printf("custom callback triggred \n");
        _onCompleteCB();
    }
    // Serial.printf("DMA callback end triggred \n");
}

void ILI948x_t4x_p::DMAerror() {
    if (flexDma.error()) {
        Serial.print("DMA error: ");
        Serial.println(DMA_ES, HEX);
    }
}

void ILI948x_t4x_p::beginWrite16BitColors() {
    while (WR_AsyncTransferDone == false) {
        // Wait for any DMA transfers to complete
    }
    DBGPrintf("ILI948x_t4x_p::beginWrite16BitColors() - 0x2c\n");
    FlexIO_Config_SnglBeat();
    /* Assert CS, RS pins */
    CSLow();
    DCLow();
    // microSecondDelay();

    /* Write command index */
    p->SHIFTBUF[_write_shifter] = ILI9488_RAMWR;

    /*Wait for transfer to be completed */
    waitTimStat(__LINE__);
    microSecondDelay();
    /* De-assert RS pin */
    DCHigh();
    microSecondDelay();
}

void ILI948x_t4x_p::write16BitColor(uint16_t color) {
    waitWriteShiftStat(__LINE__);
    p->SHIFTBUF[_write_shifter] = color >> 8;

    waitWriteShiftStat(__LINE__);
    p->SHIFTBUF[_write_shifter] = color & 0xFF;
}

void ILI948x_t4x_p::endWrite16BitColors() {
    /*Wait for transfer to be completed */
    waitTimStat();
    microSecondDelay();
    CSHigh();
}

//FASTRUN void ILI948x_t4x_p::write16BitColor(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, const uint16_t *pcolors, uint16_t count) {
FASTRUN void ILI948x_t4x_p::writeRectFlexIO(int16_t x, int16_t y, int16_t w, int16_t h, const uint16_t *pcolors) {
    while (WR_AsyncTransferDone == false) {
        // Wait for any DMA transfers to complete
    }
    uint32_t length = w * h;
    // bail if nothing to do
    if (length == 0) return;
    setAddr(x, y, x + w - 1, y + h -1);

    SglBeatWR_nPrm_16(ILI9488_RAMWR, pcolors, length);
}

void ILI948x_t4x_p::fillRectFlexIO(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    uint32_t length = w * h;
    // bail if nothing to do
    if (length == 0) return;
    setAddr(x, y, x + w - 1, y + h -1);

    FlexIO_Config_SnglBeat();
    /* Assert CS, RS pins */
    CSLow();
    DCLow();
    // microSecondDelay();

    /* Write command index */
    p->SHIFTBUF[_write_shifter] = ILI9488_RAMWR;

    /*Wait for transfer to be completed */
    waitTimStat(__LINE__);
    microSecondDelay();
    /* De-assert RS pin */
    DCHigh();
    microSecondDelay();
    while (length-- > 1) {
        waitWriteShiftStat(__LINE__);
        p->SHIFTBUF[_write_shifter] = color >> 8;

        waitWriteShiftStat(__LINE__);
        p->SHIFTBUF[_write_shifter] = color & 0xFF;
    }
    /* Write the last pixel */
    waitWriteShiftStat(__LINE__);
    p->SHIFTBUF[_write_shifter] = color >> 8;

    waitWriteShiftStat(__LINE__);
    p->TIMSTAT |= _flexio_timer_mask;

    p->SHIFTBUF[_write_shifter] = color & 0xFF;

    /*Wait for transfer to be completed */
    waitTimStat(__LINE__);
    microSecondDelay();
    CSHigh();
}

void ILI948x_t4x_p::readRectFlexIO(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t *pcolors) {
    DBGPrintf("readRectFlexIO(%d, %d, %d, %d, %p)\n", x, y, w, h, pcolors);
    //  first do any clipping.
    if ((x >= _displayclipx2) || (y >= _displayclipy2))
        return;
    if (((x + w) <= _displayclipx1) || ((y + h) <= _displayclipy1))
        return;
    if (x < _displayclipx1) {
        w -= (_displayclipx1 - x);
        x = _displayclipx1;
    }
    if (y < _displayclipy1) {
        h -= (_displayclipy1 - y);
        y = _displayclipy1;
    }
    if ((x + w - 1) >= _displayclipx2)
        w = _displayclipx2 - x;
    if ((y + h - 1) >= _displayclipy2)
        h = _displayclipy2 - y;

    // We probably need to set the rectangle
    setAddr(x, y, x + w - 1, y + h - 1);
    // now set to ramRD command
    FlexIO_Config_SnglBeat();
    /* Assert CS, RS pins */
    CSLow();
    DCLow();
    // microSecondDelay();

    /* Write command index */
    DBGPrintf("\tOutput ILI9488_RAMRD\n");
    p->SHIFTBUF[_write_shifter] = ILI9488_RAMRD;

    /*Wait for transfer to be completed */
    waitTimStat(__LINE__);
    microSecondDelay();

    /* De-assert RS pin */
    DCHigh();
    microSecondDelay();
    // delayMicroseconds(50);

    DBGPrintf("\tcall FlexIO_Clear_Config_SnglBeat\n");
    FlexIO_Clear_Config_SnglBeat();
    DBGPrintf("\tcall FlexIO_Config_SnglBeat_Read\n");
    FlexIO_Config_SnglBeat_Read();

    uint8_t dummy __attribute__((unused)) = 0;
#define DUMMY_COUNT 1
    for (uint8_t i = 0; i < DUMMY_COUNT; i++) {
        // read in dummy bytes
        waitReadShiftStat(__LINE__);
        dummy = p->SHIFTBUFBYS[_read_shifter];
        // digitalToggleFast(2);
        // Serial.printf("\tD%u=%x\n", i, dummy);
    }
    /*Wait for transfer to be completed */
    if (_display_name != ILI9488) {
        // 16 bit mode
        int count_pixels = w * h;
        uint8_t *pc = (uint8_t *)pcolors;
        while (count_pixels--) {
            waitReadShiftStat(__LINE__);
            // digitalToggleFast(2);
            uint8_t b1 = (p->SHIFTBUFBYS[_read_shifter] & 0xff);

            waitReadShiftStat(__LINE__);
            // digitalToggleFast(2);
            *pc++ = (p->SHIFTBUFBYS[_read_shifter] & 0xff);
            *pc++ = b1;
        }
    } else {
        int count_pixels = w * h;
        while (count_pixels--) {
            uint8_t r, g, b;
            waitReadShiftStat(__LINE__);
            // digitalToggleFast(2);
            r = (p->SHIFTBUFBYS[_read_shifter] & 0xff);

            waitReadShiftStat(__LINE__);
            // digitalToggleFast(2);
            g = (p->SHIFTBUFBYS[_read_shifter] & 0xff);

            waitReadShiftStat(__LINE__);
            // digitalToggleFast(2);
            b = (p->SHIFTBUFBYS[_read_shifter] & 0xff);

            *pcolors++ = color565(r, g, b);
        }
    }

    CSHigh();
    microSecondDelay();
    // Set FlexIO back to Write mode
    FlexIO_Config_SnglBeat();
}

ILI948x_t4x_p * ILI948x_t4x_p::IRQcallback = nullptr;


FASTRUN void ILI948x_t4x_p::MulBeatWR_nPrm_IRQ(uint32_t const cmd,  const void *value, uint32_t const length) 
{
    if (length == 0) return; // bail if no data to output

    DBGPrintf("ILI948x_t4x_p::MulBeatWR_nPrm_IRQ(%x, %p, %u) - entered\n", cmd, value, length);
  while(WR_AsyncTransferDone == false)
  {
    //Wait for any DMA transfers to complete
  }
    FlexIO_Config_SnglBeat();
    CSLow();
    DCLow();

    /* Write command index */
    p->SHIFTBUF[_write_shifter] = cmd;

    /*Wait for transfer to be completed */
    waitTimStat(__LINE__);
    microSecondDelay();
    /* De-assert RS pin */
    DCHigh();
    microSecondDelay();


    FlexIO_Config_MultiBeat();
    WR_AsyncTransferDone = false;
    uint32_t bytes = length*2U;

    bursts_to_complete = bytes / BYTES_PER_BURST;

    int remainder = bytes % BYTES_PER_BURST;
    if (remainder != 0) {
        memset(finalBurstBuffer, 0, sizeof(finalBurstBuffer));
        memcpy(finalBurstBuffer, (uint8_t*)value + bytes - remainder, remainder);
        bursts_to_complete++;
    }

    bytes_remaining = bytes;
    readPtr = (uint32_t*)value;
    Serial.printf ("arg addr: %x, readPtr addr: %x \n", value, readPtr);
    Serial.printf("START::bursts_to_complete: %d bytes_remaining: %d \n", bursts_to_complete, bytes_remaining);
  
    uint8_t beats = SHIFTNUM * BEATS_PER_SHIFTER;
    p->TIMCMP[_flexio_timer] = ((beats * 2U - 1) << 8) | (_baud_div / 2U - 1U);

    p->TIMSTAT = _flexio_timer_mask; // clear timer interrupt signal
    
    asm("dsb");
    
    IRQcallback = this;
    // enable interrupts to trigger bursts
    print_flexio_debug_data(pFlex, _flexio_timer, _write_shifter, _read_shifter);

//    digitalToggleFast(2);
    p->TIMIEN |= _flexio_timer_mask;
    p->SHIFTSIEN |= (1 << SHIFTER_IRQ);
}


    // Called by GFX to do updateScreenAsync and new writeRectAsync(;
bool ILI948x_t4x_p::writeRectAsyncFlexIO(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t *pcolors)
{
    // Start off only supporting shifters with DMA Requests
    if (hw->shifters_dma_channel[SHIFTER_DMA_REQUEST] != 0xff) {
        pushPixels16bitDMA(pcolors, x, y, x+w-1, y + h - 1);
    } else {
        // FlexIO3 IRQ version.
        setAddr(x, y, x + w - 1, y + h - 1);
        MulBeatWR_nPrm_IRQ(ILI9488_RAMWR, pcolors, w * h);
    }
    return true;
}


bool ILI948x_t4x_p::writeRectAsyncActiveFlexIO() { 
    // return the state of last transfer
    // may depend on if the FlexIO shifter supports DMA or not on how
    // we implement this.
    return !WR_AsyncTransferDone; 
}


FASTRUN void ILI948x_t4x_p::flexIRQ_Callback(){
    digitalWriteFast(2, HIGH);
    DBGPrintf("%x %x %u %u ", p->TIMSTAT, p->SHIFTSTAT, bursts_to_complete, bytes_remaining);
  
 if (p->TIMSTAT & _flexio_timer_mask) { // interrupt from end of burst
        //Serial.write('T');
        p->TIMSTAT = _flexio_timer_mask; // clear timer interrupt signal
        bursts_to_complete--;
        if (bursts_to_complete == 0) {
            p->TIMIEN &= ~_flexio_timer_mask; // disable timer interrupt
            asm("dsb");
            WR_AsyncTransferDone = true;
            microSecondDelay();
            CSHigh();
            _onCompleteCB();
            digitalWriteFast(2, LOW);
            //Serial.write("END");
            return;
        }
    }

    if (p->SHIFTSTAT & (1 << SHIFTER_IRQ)) { // interrupt from empty shifter buffer
        //Serial.write('S');
        // note, the interrupt signal is cleared automatically when writing data to the shifter buffers
        if (bytes_remaining == 0) { // just started final burst, no data to load
            p->SHIFTSIEN &= ~(1 << SHIFTER_IRQ); // disable shifter interrupt signal
        } else if (bytes_remaining < BYTES_PER_BURST) { // just started second-to-last burst, load data for final burst
            uint8_t beats = bytes_remaining / BYTES_PER_BEAT;
            p->TIMCMP[0] = ((beats * 2U - 1) << 8) | (_baud_div / 2U - 1); // takes effect on final burst
            readPtr = finalBurstBuffer;
            bytes_remaining = 0;
            #if 1
            for (int i = SHIFTNUM - 1; i >= 0; i--) {
                digitalToggleFast(3);
                uint32_t data = readPtr[i];
                p->SHIFTBUFBYS[i] = ((data >> 16) & 0xFFFF) | ((data << 16) & 0xFFFF0000);

            }
            #else
            for (int i = 0; i < SHIFTNUM; i++) {
                uint32_t data = *readPtr++;
                p->SHIFTBUFBYS[i] = ((data >> 16) & 0xFFFF) | ((data << 16) & 0xFFFF0000);
            }
            #endif
        } else {
            bytes_remaining -= BYTES_PER_BURST;
            #if 1
            // try filling in reverse order
            for (int i = SHIFTNUM - 1; i >= 0; i--) {
                digitalToggleFast(3);
                uint32_t data = readPtr[i];
                p->SHIFTBUFBYS[i] = ((data >> 16) & 0xFFFF) | ((data << 16) & 0xFFFF0000);

            }
            readPtr += SHIFTNUM;
            #else
            for (int i = 0; i < SHIFTNUM; i++) {
                digitalToggleFast(3);
                uint32_t data = *readPtr++;
                p->SHIFTBUFBYS[i] = ((data >> 16) & 0xFFFF) | ((data << 16) & 0xFFFF0000);

                uint8_t repeat_count = 255;
                while ((0 == (p->SHIFTSTAT & (1U << SHIFTER_IRQ))) && --repeat_count) {}
                //if (repeat_count == 0) {
                //    Serial.printf(" TO:%u %x\n", i, p->SHIFTSTAT);
                //}
            }
            #endif
        }
        if (bytes_remaining == 0) {
            //Serial.write('L');
            p->SHIFTSIEN &= ~(1 << SHIFTER_IRQ);
        }
    }
    //Serial.write('\n');
    asm("dsb");
    digitalWriteFast(2, LOW);

}



FASTRUN void ILI948x_t4x_p::flexio_ISR()
{
  asm("dsb");
  IRQcallback->flexIRQ_Callback();
 }
