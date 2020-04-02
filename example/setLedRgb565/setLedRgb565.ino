/*!
 * @file setLedRgb565.ino
 * @brief 用给出的宏定义设置图片颜色和亮度
 * @n 本示例支持的主板有ESP8266、FireBeetle-M0,MAGE2560，UNO
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [YeHangYu](hangyu.ye@dfrobot.com)
 * @version  V0.1
 * @date  2020-03-20
 * @url https://github.com/DFRobot/DFRobot_MY9221SS
 */

#include <DFRobot_MY9221SS.h>

//自定义通信引脚
/*FireBeetle-M0*/
#if defined ARDUINO_SAM_ZERO
#define DATA_PIN   7
#define CLK_PIN    5
/*ESP32 and ESP8266*/
#elif defined(ESP32) || defined(ESP8266)
#define DATA_PIN   D3
#define CLK_PIN    D4
/*AVR系列主板*/
#else
#define DATA_PIN   2
#define CLK_PIN    3
#endif

/**
 * @brief Constructor  LED驱动构造函数
 */
DFRobot_MY9221SS rgbdriver;

/*
 *可供用户选择的宏定义颜色
 *COLOR_RGB565_BLACK   COLOR_RGB565_NAVY    COLOR_RGB565_DGREEN   COLOR_RGB565_DCYAN 
 *COLOR_RGB565_MAROON  COLOR_RGB565_PURPLE  COLOR_RGB565_OLIVE    COLOR_RGB565_LGRAY
 *COLOR_RGB565_DGRAY   COLOR_RGB565_BLUE    COLOR_RGB565_GREEN    COLOR_RGB565_CYAN  
 *COLOR_RGB565_RED     COLOR_RGB565_MAGENTA COLOR_RGB565_YELLOW   COLOR_RGB565_WHITE
 */
 
/*
 *用到的宏定义
 *LED_FULL_BRIGHTNESS 0xff 最高亮度
 *LED_TURN_OFF        0    不亮
 */
void setup() {
  //初始化串口
  Serial.begin(115200);
  /**
  * @brief  初始化LED驱动
  * @param pinClock 时钟引脚
  * @param pinData  数据引脚
  */
  rgbdriver.begin(/*pinClock=*/CLK_PIN, /*pinData=*/DATA_PIN);
}

void loop()
{
  /**
   * @brief 设置某个灯的颜色和亮度，这里是4号灯，对应引脚A3B3C3
   * @param ledNo         设置的灯的编号，取值范围1~4
   * @param color         用宏定义控制led灯，格式是RGB565
   * @param brightness    亮度控制，取值范围0~255
  */
  rgbdriver.setLedColor(/*ledNo=*/4,/*color=*/COLOR_RGB565_GREEN,/*brightness=*/LED_FULL_BRIGHTNESS);
  delay(1000);
  rgbdriver.setLedColor(/*ledNo=*/4,/*color=*/COLOR_RGB565_RED,/*brightness=*/LED_FULL_BRIGHTNESS);
  delay(1000);
  rgbdriver.setLedColor(/*ledNo=*/4,/*color=*/COLOR_RGB565_BLUE,/*brightness=*/LED_FULL_BRIGHTNESS);
  delay(1000);
}

