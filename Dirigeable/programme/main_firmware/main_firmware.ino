#include <Maixduino_GC0328.h>
#include <Sipeed_ST7789.h>
#include "MBNet_1000.h"
#include "Maix_KPU.h"

SPIClass spi_(SPI0); // MUST be SPI0 for Maix series on board LCD
Sipeed_ST7789 lcd(320, 240, spi_);
Maixduino_GC0328 camera(224, 224, PIXFORMAT_RGB565);
KPUClass KPU;
MBNet_1000 mbnet(KPU, lcd, camera);

const char* kmodel_name = "m";


void setup()
{
    Serial.begin(115200);
    Serial.println("begin");
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    
    Serial.println("init mobile net, load kmodel from SD card, it may takes a long time");
    if( mbnet.begin(kmodel_name) != 0)
    {
        Serial.println("mobile net init fail");
        while(1);
    }

}

void loop()
{
    if(mbnet.detect() != 0)
    {
        Serial.println("detect object fail");
        return;
    }
    mbnet.show();
}
