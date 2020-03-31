/*!
 * @file setAllLED.ino
 * @brief 用RGB值设置LED灯的颜色
 * @n 本示例支持的主板有ESP8266、FireBeetle-M0,MAGE2560，UNO、ESP32、Leonardo 、Mega2560
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

void loop() {
  /**
   * @brief 设置所有灯的RGB颜色，这里设置为白色，最亮
   * @param R     设置RGB红色分量，硬件应连接引脚B，取值范围0~255
   * @param G     设置RGB绿色分量，硬件应连接引脚C，取值范围0~255
   * @param B     设置RGB蓝色分量，硬件应连接引脚A，取值范围0~255
  */
  setAllLed(/*R=*/LED_FULL_BRIGHTNESS,/*G=*/LED_FULL_BRIGHTNESS,/*B=*/LED_FULL_BRIGHTNESS);
  delay(200);
  //关灯
  setAllLed(/*R=*/LED_TURN_OFF,/*G=*/LED_TURN_OFF,/*B=*/LED_TURN_OFF);
  delay(200);
}


void setAllLed(uint16_t R, uint16_t G, uint16_t B)
{
  uint16_t  led[LED_BIN_COUNT];
  for(uint8_t i = 0; i < LED_BIN_COUNT; i++)
  {
    if(i%3 == 0)
    {
      led[i] = G ;
    }
    else if(i%3 == 1)
    {
      led[i] = R ;
    }
    else if(i%3 == 2)
    {
      led[i] = B ;
    }
  }
  rgbdriver.send(led);//向芯片发送数据，12个引脚，每个16bit，共208bit
}




  
