/*!
 * @file setMonochromeLed.ino
 * @brief 通过宏定义设置多个指定引脚的亮度，实现包括流水灯等多种亮灯示例，请将12颗单色LED灯的负极连在12个ABC引脚上，正极接上电源
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
   * @brief 用宏定义指定引脚并控制引脚上单色灯的亮度，向芯片发送一组完整的数据
   * @param pinNo        宏定义引脚名，用“+”或“|”连接
   * @param brightness   设置亮度，8位灰阶数据模式时取值范围为0~255，16位时取值范围为0~65535
  */
  rgbDriver.setMonochromeLed(/*pinNo=*/A3|B3|C3|A2|B2|C2|A1|B1|C1|A0|B0|C0, /*brightness=*/0);
  //发送锁存信号使所有驱动工作
  rgbDriver.latch();
  delay(500);
  //逐渐变亮
  for(uint16_t i = 0; i <= 255; i+=5) {
    rgbDriver.setMonochromeLed(/*pinNo=*/A3|B3|C3|A2|B2|C2|A1|B1|C1|A0|B0|C0, /*brightness=*/i);
    //发送锁存信号使所有驱动工作
    rgbDriver.latch();
    delay(100);
  }
  //逐渐熄灭
  for(uint16_t i = 255; i > 0; i-=5) {
    rgbDriver.setMonochromeLed(/*pinNo=*/A3|B3|C3|A2|B2|C2|A1|B1|C1|A0|B0|C0, /*brightness=*/i);
    //发送锁存信号使所有驱动工作
    rgbDriver.latch();
    delay(100);
  }
  

  //walk，计数显示，灯亮表示1，灯灭表示0，用灯显示二进制值
  // i = 0 = 0x0表示12个led灯全部熄灭
  // i = 4095 = 0xfff表示12个led灯都亮了
  for (uint16_t i = 0; i <= 4095; i++) {
      rgbDriver.setMonochromeLed(/*pinNo=*/i, /*brightness=*/255);
      delay(50);
  }

  //流水灯
  for (uint16_t i = C0; i <= A3; i<<=1) {
    rgbDriver.setMonochromeLed(/*pinNo=*/i, /*brightness=*/255);
    //发送锁存信号使所有驱动工作
    rgbDriver.latch();
    delay(1000);
  }
  //流水灯，反向
  for (uint16_t i = A3; i >= C0; i>>=1) {
    rgbDriver.setMonochromeLed(/*pinNo=*/i, /*brightness=*/255);
    //发送锁存信号使所有驱动工作
    rgbDriver.latch();
    delay(1000);
  }

  //级别灯
  for (uint16_t i = C0; i <= 4095; i = (i<<1) + C0) {
    rgbDriver.setMonochromeLed(/*pinNo=*/i, /*brightness=*/255);
    //发送锁存信号使所有驱动工作
    rgbDriver.latch();
    delay(1000);
  }
  
  //反向级别灯
  for (uint16_t i = A3; i < 4095; i = (i>>1) +A3) {
    rgbDriver.setMonochromeLed(/*pinNo=*/i, /*brightness=*/255);
    //发送锁存信号使所有驱动工作
    rgbDriver.latch();
    delay(1000);
  }

  //弹跳灯，两个灯来回跳跃
  for (uint16_t i = B0|C0; i < (A3|B3); i<<=1) {
    rgbDriver.setMonochromeLed(/*pinNo=*/i, /*brightness=*/255);
    //发送锁存信号使所有驱动工作
    rgbDriver.latch();
    delay(1000);
  }
  for (uint16_t i = A3|B3; i >= (B0|C0); i>>=1) {
    rgbDriver.setMonochromeLed(/*pinNo=*/i, /*brightness=*/255);
    //发送锁存信号使所有驱动工作
    rgbDriver.latch();
    delay(1000);
  }
}