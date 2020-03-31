/*!
 * @file setLedRgb888.ino
 * @brief 用给出的宏定义设置图片颜色和亮度
 * @n 本示例支持的主板有ESP8266、FireBeetle-M0,MAGE2560，UNO
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [YeHangYu](hangyu.ye@dfrobot.com)
 * @version  V0.1
 * @date  2020-03-20
 * @url https://github.com/DFRobot/DFRobot_G
 */
#include <DFRobot_LedDriver.h>

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
 *可能用到的宏定义
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

void loop() {
  /**
   * @brief 设置某个灯的RGB颜色，这里将4号灯设置为紫色，对应引脚A3B3C3  
   * @param ledNo 设置的灯的编号，取值1~4
   * @param R     设置RGB红色分量，硬件应连接引脚B，取值范围0~255
   * @param G     设置RGB绿色分量，硬件应连接引脚C，取值范围0~255
   * @param B     设置RGB蓝色分量，硬件应连接引脚A，取值范围0~255
  */
  setLed(/*ledNo=*/4,/*R=*/1,/*G=*/0,/*B=*/1);
  delay(1000);                                                                              
}

void setLed(uint8_t ledNo, uint16_t R, uint16_t G, uint16_t B)
{
  uint16_t  led[LED_BIN_COUNT];
  ledNo = 5 - ledNo;
  if(ledNo <= 4 || ledNo >= 1)
  {
    for(uint8_t i = 0; i < LED_BIN_COUNT; i++)
    {
      if(i == ledNo*3-3)
      {
        led[i] = G ;
      }
      else if(i == ledNo*3-2)
      {
        led[i] = R ;
      }
      else if(i == ledNo*3-1)
      {
        led[i] = B ;
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
