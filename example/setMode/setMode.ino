/*!
 * @file setMode.ino
 * @brief 设置模式示例，选择灰阶为16位替换掉默认的8位模式，用3个16位的RGB设置灯的颜色，BRG三基色分别连接对应引脚A3、B3、C3，本示例将3号灯的颜色设置为橙色，如果不设置模式为16bit灰阶数据，0xffff前八位就会无效，灯变为黄色
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
  /**
   * @brief 设置灰阶为16位，值为3（二进制表示为11）
   * @param temp 保留位元
   * @param hspd 输出电流反应速度选择
   * @param bs  灰阶选择
   * @param gck 内置灰阶时钟频率选择
   * @param sep 输出电流打散与不打散选择
   * @param osc 灰阶时钟频率来源选择
   * @param pol 输出电流极性选择
   * @param cntset 自动更换画面模式或强制更换画面模式选择
   * @param onest 画面重复显示或只亮一次选择
   */
   rgbDriver.setMode(/*temp=*/0, /*hspd=*/1, /*bs=*/3, /*gck=*/1, /*sep=*/1, /*osc=*/0, /*pol=*/0, /*cntset=*/0, /*onest=*/0);
}

void loop() {
   /**
   * @brief 设置某个灯的颜色，这里将B3号引脚上的灯的亮度，如果灰阶选择为16位，将会观察到亮度变化
   * @param ledNo 设置的灯的编号，一共四路/颗灯，取值0~3
   * @param R     设置RGB红色分量，硬件应连接引脚B，取值范围0~0xffff
  */
  rgbDriver.setSingleColorLeds(/*pinNo=*/B3, /*brightness=*/0xffff);
  delay(1000);
  rgbDriver.setSingleColorLeds(/*pinNo=*/B3, /*brightness=*/0xff);
  delay(1000);
}