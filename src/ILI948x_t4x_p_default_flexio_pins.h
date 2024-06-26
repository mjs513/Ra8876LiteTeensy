//=============================================================================
// Default flexio pins - Can be setup for different teensy 4.x boards
//=============================================================================

#if defined(ARDUINO_TEENSY41)
// FlexIO pins: data: 19 18 14 15 40 41 17 16 WR:36 RD:37
//  FlexIO3
#define DISPLAY_WR 36
#define DISPLAY_RD 37

#define DISPLAY_D0 19
#define DISPLAY_D1 18
#define DISPLAY_D2 14
#define DISPLAY_D3 15
#define DISPLAY_D4 40
#define DISPLAY_D5 41
#define DISPLAY_D6 17
#define DISPLAY_D7 16

#else // #if defined(ARDUINO_TEENSY_MICROMOD)
// FLEXIO2 pins.

#define DISPLAY_WR 7  // FLEXIO2:17
#define DISPLAY_RD 8 // FLEXIO2:16

#define DISPLAY_D0 40 // 40      B0_04   FlexIO2:4
#define DISPLAY_D1 41 // 41      B0_05   FlexIO2:5
#define DISPLAY_D2 42 // 42      B0_06   FlexIO2:6
#define DISPLAY_D3 43 // 43      B0_07   FlexIO2:7
#define DISPLAY_D4 44 // 44      B0_08   FlexIO2:8
#define DISPLAY_D5 45 // 45      B0_09   FlexIO2:9
#define DISPLAY_D6 6  // 6       B0_10   FlexIO2:10
#define DISPLAY_D7 9  // 9       B0_11   FlexIO2:11
#endif