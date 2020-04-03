/*!
 * @file setLedRgb888.ino
 * @brief 用3个八位的RGB设置灯的颜色，点亮4号灯，BRG三基色分别连接对应引脚A3、B3、C3
 * @n 本示例支持的主板有ESP8266、FireBeetle-M0、UNO、ESP32、Leonardo 、Mega2560
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
DFRobot_MY9221SS rgbDriver;

/*
 *可用的宏定义
 *LED_FULL_BRIGHTNESS 0xff 最高亮度
 *LED_TURN_OFF        0    不亮
 */
void setup() {
  //初始化串口
  Serial.begin(115200);
  
  /**
  * @brief  初始化LED驱动
  * @param clockPin 时钟引脚
  * @param dataPin  数据引脚
  */
  rgbDriver.begin(/*clockPin=*/CLK_PIN, /*dataPin=*/DATA_PIN);
}

void loop() {
  /**
   * @brief 设置某个灯的RGB颜色，这里将4号灯设置为黄色，对应引脚A3B3C3  
   * @param ledNo 设置的灯的编号，一共四路/颗灯，取值1~4
   * @param R     设置RGB红色分量，硬件应连接引脚B，取值范围0~255
   * @param G     设置RGB绿色分量，硬件应连接引脚C，取值范围0~255
   * @param B     设置RGB蓝色分量，硬件应连接引脚A，取值范围0~255
  */
  rgbDriver.setLed(/*ledNo=*/4,/*R=*/LED_FULL_BRIGHTNESS,/*G=*/LED_FULL_BRIGHTNESS,/*B=*/LED_TURN_OFF );
  delay(1000);
}


