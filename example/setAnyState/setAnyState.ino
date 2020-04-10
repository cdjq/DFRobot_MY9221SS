/*!
 * @file setAnyState.ino
 * @brief 本示例可设置任意驱动的任何状态，用数组存放12个灰阶数据控制12个引脚，数组的元素从0到11分别控制引脚A3 B3 C3 A2 B2 C2 A1 B1 C1 A0 B0 C0
 * @n 请将12颗单色LED灯的负极连在12个ABC引脚上，正极接上电源
 * @n 如果使用RGB灯，请将RGB引脚连接在一组ABC上，基色B对应引脚A0~A3、基色R对应引脚B0~B3、基色G对应引脚C0~C3
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
  //点亮最近一个驱动的所有灯，8位灰阶数据模式时取值范围为0~255，16位时取值范围为0~65535
  uint16_t  buf[12]={/*A3*/255,/*B3*/255,/*C3*/255,
                     /*A2*/255,/*B2*/255,/*C2*/255,
                     /*A1*/255,/*B1*/255,/*C1*/255,
                     /*A0*/255,/*B0*/255,/*C0*/255};
  /**
   *@brief 发送一组完整的数据，数组的元素从0到11分别控制引脚A3 B3 C3 A2 B2 C2 A1 B1 C1 A0 B0 C0
   *@param buf 指向192bit灰阶数据的指针
   */
  rgbDriver.write(buf);
  rgbDriver.latch();//发送锁存信号使所有驱动工作
  delay(1000);

  //将所有A号引脚设置为较暗，所有B号引脚设置为较亮，所有C号引脚设置为亮
  for(uint16_t i = 0; i <= 11; i+=3) {
    buf[i] = 1;     //A
    buf[i+1] = 64;  //B
    buf[i+2] = 255; //C
  }
  rgbDriver.write(buf);
  rgbDriver.latch();//发送锁存信号使所有驱动工作
  delay(1000);

  //同时点亮驱动的所有灯，由A0B0C0到A3B3C3呈逐渐变亮
  for(uint16_t i = 0, brightness = 1; i <= 11; i+=3) {
    buf[i] = brightness;
    buf[i+1] = brightness;
    buf[i+2] = brightness;
    brightness += 50;
  }
  rgbDriver.write(buf);
  rgbDriver.latch();//发送锁存信号使所有驱动工作
  delay(5000);
}

