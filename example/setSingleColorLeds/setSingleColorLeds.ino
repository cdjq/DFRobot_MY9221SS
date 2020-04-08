/*!
 * @file setSingleColorLeds.ino
 * @brief 通过宏定义设置多个指定引脚的亮度，这里控制A3和B3，请将两个单色LED灯的负极连在A3和B3引脚，正极接电源
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
 * @brief Constructor LED驱动构造函数
 */
DFRobot_MY9221SS rgbDriver; 

/*
 *供用户使用的宏定义引脚名
 *C0 B0 A0 C1 B1 A1 C2 B2 A2 C3 B3 A3
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
   * @brief 用宏定义指定引脚并控制引脚上单色灯的亮度
   * @param pinNo        宏定义引脚名
   * @param brightness   设置亮度，8位灰阶数据模式取值范围为0~255，16位时取值范围0~65535
  */
  rgbDriver.setSingleColorLeds(/*pinNo=*/A3+B3, /*brightness=*/0);
  delay(500);
  //逐渐变亮
  for(uint16_t i = 0; i <= 255; i+=5) {
    rgbDriver.setSingleColorLeds(/*pinNo=*/A3+B3, /*brightness=*/i);
    delay(100);
  }
  //逐渐熄灭
  for(uint16_t i = 255; i > 0; i-=5) {
    rgbDriver.setSingleColorLeds(/*pinNo=*/A3+B3, /*brightness=*/i);
    delay(100);
  }
}