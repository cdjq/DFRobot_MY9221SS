/*!
 * @file setSinglePin.ino
 * @brief 通过设置A3引脚的亮度，点亮和关闭引脚上的灯，需将单色LED灯的负极接A3引脚，电源线接上合适的电压源
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
 *可用的宏定义
 *LED_FULL_BRIGHTNESS 0xff 最高亮度
 *LED_TURN_OFF        0    不亮
 *引脚名
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
   * @brief 控制单个引脚的亮度，推荐使用只有正负引脚的LED灯观察现象
   * @param pinNo   设置的单个引脚的编号，范围0~11，使用引脚名亦可，引脚名宏定义与实物完全一致
   * @param brightness   设置亮度，取值范围0~255
   */
  rgbDriver.setSinglePin(/*pinNo=*/A3, /*brightness=*/LED_FULL_BRIGHTNESS);
  delay(500);
  rgbDriver.setSinglePin(/*pinNo=*/A3, /*brightness=*/LED_TURN_OFF);
  delay(500);
}