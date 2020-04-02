/*!
 * @file blink.ino
 * @brief 通过RGB设置红绿蓝三基色让LED灯闪烁
 * @n 本示例支持的主板有ESP8266、FireBeetle-M0,MAGE2560，UNO、ESP32、Leonardo 、Mega2560
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
 * @brief Constructor LED驱动构造函数
 */
DFRobot_MY9221SS rgbdriver; 

/*
 *用到的宏定义
 *LED_FULL_BRIGHTNESS 0xff 最高亮度
 *LED_TURN_OFF        0    不亮
 */
void setup() {
  //初始化串口
  Serial.begin(115200);
  while (!Serial)
  {
    ; //等待串口连接
  }
  /**
  * @brief  初始化LED驱动
  * @param pinClock 时钟引脚
  * @param pinData  数据引脚
  */
  rgbdriver.begin(/*pinClock=*/CLK_PIN, /*pinData=*/DATA_PIN);
}

void loop() {
  /**
   * @brief 所有灯随机改变颜色
  */
  rgbdriver.autoColorChange();
  delay(1000);
}