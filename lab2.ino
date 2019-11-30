#include <Arduino.h>
#include <MD_TCS230.h>
#include <LedControl.h>

#define  S0_OUT  2
#define  S1_OUT  3
#define  S2_OUT  4
#define  S3_OUT  5

const int displaysCount = 1;
const int dataPin = 12;
const int clkPin = 10;
const int csPin = 11;
LedControl lc = LedControl(dataPin, clkPin, csPin, displaysCount);
MD_TCS230 ColorSensor(S2_OUT, S3_OUT, S0_OUT, S1_OUT);

void setup()
{
    sensorData whiteCalibration;
    whiteCalibration.value[TCS230_RGB_R] = 25220;
    whiteCalibration.value[TCS230_RGB_G] = 22900;
    whiteCalibration.value[TCS230_RGB_B] = 78350;
    sensorData blackCalibration;
    blackCalibration.value[TCS230_RGB_R] = 11130;
    blackCalibration.value[TCS230_RGB_G] = 9800;
    blackCalibration.value[TCS230_RGB_B] = 35610;

    ColorSensor.begin();
    ColorSensor.setDarkCal(&blackCalibration);
    ColorSensor.setWhiteCal(&whiteCalibration);
 
    lc.shutdown(0, false);
    lc.setIntensity(0, 16);
}

void loop() 
{
    colorData rgb;
    ColorSensor.read();
    while (!ColorSensor.available())
        ;
    ColorSensor.getRGB(&rgb);
    lc.clearDisplay(0);
       
    set_value_in_lc(0, 1, rgb.value[TCS230_RGB_R]);
    set_value_in_lc(3, 4, rgb.value[TCS230_RGB_G]);
    set_value_in_lc(6, 7, rgb.value[TCS230_RGB_B]);
}


void set_value_in_lc(int column1, int column2, int rgb_value){
    int countRow = rgb_value / 32;
    for (int i = 0; i <= countRow; i++) {
        lc.setLed(0, column1, i, true);
        lc.setLed(0, column2, i, true);
    }
}
