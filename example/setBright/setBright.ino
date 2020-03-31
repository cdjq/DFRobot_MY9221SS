/*!
 * @file setBright.ino
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
#define MY9221SS_D   7
#define MY9221SS_DCK 5
/*ESP32 and ESP8266*/
#elif defined(ESP32) || defined(ESP8266)
#define MY9221SS_D   D3
#define MY9221SS_DCK D4
/*AVR系列主板*/
#else
#define MY9221SS_D   2
#define MY9221SS_DCK 3
#endif

/**
 * @brief Constructor  芯片通信的构造函数
 * @param pinClock 时钟引脚
 * @param pinData  数据引脚
 */
DFRobot_MY9221SS rgbdriver(/*pinClock=*/MY9221SS_DCK, /*pinData=*/MY9221SS_D);

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
 *LED_BIN_COUNT       12   引脚数
 */
void setup() {
  //初始化串口
  Serial.begin(115200);
  while (!Serial)
  {
    ; //等待串口连接
  }
  //初始化LED灯驱动
  rgbdriver.begin();
}

void loop()
{
  //灯由暗变亮
  for(uint8_t brightness = 0; brightness <= 250; brightness+=5)
  {
    /**
     * @brief 设置某个灯的颜色和亮度，这里是4号灯，对应引脚A3B3C3
     * @param ledNo         设置的灯的编号，取值范围1~4
     * @param color         用宏定义控制led灯，格式是RGB565
     * @param brightness    亮度控制，取值范围0~255
    */
    setLed(/*ledNo=*/4,/*color=*/COLOR_RGB565_WHITE,/*brightness=*/brightness);
    delay(100);
  }
}


void setLed(uint8_t ledNo, uint16_t color, uint8_t brightness)
{
  uint16_t  led[LED_BIN_COUNT];
  uint16_t R,G,B;
  //转换为RGB888
  R = (color >> 11) * 8 * brightness/0xff;
  G = ((color >> 6) & 31) * 8 * brightness/0xff;
  B = (color & 31) * 8 * brightness/0xff;
  ledNo = 5 - ledNo;
  if(ledNo <= 4 || ledNo >= 1)
  {
    for(uint8_t i = 0; i < LED_BIN_COUNT; i++)
    {
      if(i == ledNo*3-3)
      {
        led[i] = B;
      }
      else if(i == ledNo*3-2)
      {
        led[i] = R;
      }
      else if(i == ledNo*3-1)
      {
        led[i] = G;
      }
      else
      {
        led[i] = LED_TURN_OFF;
      }
    }
    rgbdriver.send(led);//向芯片发送数据，12个引脚，每个16bit，共208bit
  }
  else
  {
    Serial.println("ledNo error");
  }
}
