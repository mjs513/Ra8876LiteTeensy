// Set which Display we are using and at what speed
// Currently I have options for both MICROMOD and T42 to make it
// easier for testing

#include "Arduino.h"
#include "RA8876_t41_p.h"
#include "font_Arial.h"
#include "flexio_teensy_mm.c"
#include "T41_top_card.c"

uint8_t dc = 13;
uint8_t cs = 11;
uint8_t rst = 12;

RA8876_t41_p tft = RA8876_t41_p(dc,cs,rst); //(dc, cs, rst)

void setup() {
    Serial.begin(115200);
    delay(1000);
    if (CrashReport) {
        Serial.print(CrashReport);
    }

  tft.begin(20); // 20 is working in 8bit and 16bit mode on T41
  tft.graphicMode(true);
  tft.setTextCursor(0,0);
  tft.setFont(Arial_14);


  for(uint8_t rotation = 0;  rotation < 4; rotation++) {
    tft.setRotation(rotation);
    displayRotation(rotation);
    delay(1000);
    tft.fillScreen(BLACK);
  }
  tft.setRotation(0);

}

void loop() {
  for(uint8_t rotation = 0;  rotation < 4; rotation++) {
    tft.setRotation(rotation);
    displayRotation(rotation);
    nextPage();

    uint16_t *rotatedImage = tft.rotateImageRect(400, 272, td_t4_top, rotation);
    tft.writeRotatedRect(CENTER, CENTER, 400, 272, rotatedImage );  // 480x320
    free(rotatedImage);
    nextPage();
    rotatedImage = tft.rotateImageRect(480, 320, flexio_teensy_mm, rotation);
    tft.writeRotatedRect(CENTER, CENTER, 480, 320, rotatedImage );  // 480x320
    free(rotatedImage);
    nextPage();
    tft.writeRect(CENTER, CENTER, 480, 320, flexio_teensy_mm );  // 480x320
    nextPage();
  }
}

void nextPage()
{
  Serial.println("Press anykey to continue");
  while (Serial.read() == -1) ;
  while (Serial.read() != -1) ;

  tft.fillScreen(BLACK);
}

void displayRotation(uint8_t rotation) {
  tft.fillScreen(RED);
  tft.setCursor(tft.width()/2, tft.height()/2, true);
  tft.printf("Rotation: %d", rotation);
  Serial.printf("WIDTH: %d, HEIGHT: %d\n", tft.width(), tft.height());
  tft.setCursor(200, 300);
  Serial.printf("  Set cursor(200, 300), retrieved(%d %d)",
                tft.getCursorX(), tft.getCursorY());
  tft.setCursor(50, 50);
  tft.write('0');
  tft.setCursor(tft.width() - 50, 50);
  tft.write('1');
  tft.setCursor(50, tft.height() - 50);
  tft.write('2');
  tft.setCursor(tft.width() - 50, tft.height() - 50);
  tft.write('3');
}
