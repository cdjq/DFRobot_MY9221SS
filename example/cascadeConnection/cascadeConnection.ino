/*!
 * @file cascadeConnection.ino
 * @brief 使两个驱动上的3号LED灯同时呈现相同的颜色，但亮度不同，远端的LED灯更亮，发送一组数据前可以设置模式，本示例对最近的驱动发送命令前修改了它的灰阶模式（从8位变为16位），观察到其亮度明显变暗
 * @n 基色G对应引脚A0~A3、基色R对应引脚B0~B3、基色B对应引脚C0~C3，请将RGB灯的引脚按G、R、B的顺序连接A3、B3、C3
 * @n 本示例使用2个驱动芯片串联，将DO连接下一个驱动的D，将DC连接下一个驱动的C，最后接上正负极使用
 * @n 两个驱动的控制规则是，发送第一次数据控制的是较远的驱动，发送第二次数据控制较近的驱动，两个驱动的数据发送完成后再发送锁存信号，即可使驱动工作。否则远端驱动的状态将继承较近一个驱动的状态
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
 *供用户使用的宏定义LED灯名
 *LED0 LED1 LED2 LED3
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
  rgbDriver.setMonochromeLed(/*pinNo=*/A3|B3|C3, /*brightness=*/0xff);//较远驱动上的A3B3C3引脚上的灯
  rgbDriver.setMonochromeLed(/*pinNo=*/A3|B3|C3, /*brightness=*/0xf); //较近驱动上的A3B3C3引脚上的灯
  rgbDriver.latch();//发送锁存信号使所有驱动工作
  delay(1000);
  /**
   * @brief 用宏定义指定LED灯，并通过RGB各分量控制颜色，向芯片发送一组完整的数据  
   * @param ledNo 宏定义灯名，一共四路/颗灯，LED0~LED3
   * @param R     设置RGB红色分量，硬件应连接引脚B，8位灰阶数据模式时取值范围为0~255，16位时取值范围为0~65535
   * @param G     设置RGB绿色分量，硬件应连接引脚A，8位灰阶数据模式时取值范围为0~255，16位时取值范围为0~65535
   * @param B     设置RGB蓝色分量，硬件应连接引脚C，8位灰阶数据模式时取值范围为0~255，16位时取值范围为0~65535
  */
  rgbDriver.setRgbLed(/*ledNo=*/LED3,/*R=*/0xf, /*G=*/0,/*B=*/0);//较远驱动上的灯
  rgbDriver.setRgbLed(/*ledNo=*/LED3,/*R=*/0xff,/*G=*/0,/*B=*/0);//较近驱动上的灯
  rgbDriver.latch();//发送锁存信号使所有驱动工作
  delay(1000);
  rgbDriver.setRgbLed(/*ledNo=*/LED3,/*R=*/0,/*G=*/0xff,/*B=*/0);
  rgbDriver.setRgbLed(/*ledNo=*/LED3,/*R=*/0,/*G=*/0xf, /*B=*/0);
  rgbDriver.latch();//发送锁存信号使所有驱动工作
  delay(1000);
  rgbDriver.setRgbLed(/*ledNo=*/LED3,/*R=*/0,/*G=*/0,/*B=*/0xff);
  rgbDriver.setRgbLed(/*ledNo=*/LED3,/*R=*/0,/*G=*/0,/*B=*/0xf );
  rgbDriver.latch();//发送锁存信号使所有驱动工作
  delay(1000);
  rgbDriver.setRgbLed(/*ledNo=*/LED3,/*R=*/0,/*G=*/0xff,/*B=*/0xff);
  rgbDriver.setRgbLed(/*ledNo=*/LED3,/*R=*/0,/*G=*/0xf, /*B=*/0xf );
  rgbDriver.latch();//发送锁存信号使所有驱动工作
  delay(1000);
  rgbDriver.setRgbLed(/*ledNo=*/LED3,/*R=*/0xff,/*G=*/0,/*B=*/0xff);
  rgbDriver.setRgbLed(/*ledNo=*/LED3,/*R=*/0xf, /*G=*/0,/*B=*/0xf );
  rgbDriver.latch();//发送锁存信号使所有驱动工作
  delay(1000);
  rgbDriver.setRgbLed(/*ledNo=*/LED3,/*R=*/0xff,/*G=*/0xff,/*B=*/0);
  rgbDriver.setRgbLed(/*ledNo=*/LED3,/*R=*/0xf, /*G=*/0xf, /*B=*/0);
  rgbDriver.latch();//发送锁存信号使所有驱动工作
  delay(1000);


  //此处模式不同，使灯的亮度不一样
  rgbDriver.setRgbLed(/*ledNo=*/LED3,/*R=*/0xf,/*G=*/0xf,/*B=*/0xf);
  /**
  * @brief 设置灰阶为16位，其值为3
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
  rgbDriver.setMode(/*temp=*/0, /*hspd=*/0, /*bs=*/3, /*gck=*/0, /*sep=*/1, /*osc=*/0, /*pol=*/0, /*cntset=*/0, /*onest=*/0);
  rgbDriver.setRgbLed(/*ledNo=*/LED3,/*R=*/0xf,/*G=*/0xf,/*B=*/0xf);
  rgbDriver.latch();//发送锁存信号使所有驱动工作
  delay(5000);
  
  //模式相同，灯的亮度一样
  //恢复灰阶模式为8位
  rgbDriver.setMode(/*temp=*/0, /*hspd=*/0, /*bs=*/0, /*gck=*/0, /*sep=*/1, /*osc=*/0, /*pol=*/0, /*cntset=*/0, /*onest=*/0);
  rgbDriver.setRgbLed(/*ledNo=*/LED3,/*R=*/0xf,/*G=*/0xf,/*B=*/0xf);//较近驱动上的灯
  rgbDriver.setRgbLed(/*ledNo=*/LED3,/*R=*/0xf,/*G=*/0xf,/*B=*/0xf);//较远驱动上的灯
  rgbDriver.latch();//发送锁存信号使所有驱动工作
  delay(5000);

  //使用数组设置任意一个驱动的任意状态
  uint16_t  buf[12];
  //控制级联的第二个驱动的所有灯变为蓝色
  for(uint16_t i = 0, brightness = 1; i <= 11; i+=3) {
    buf[i] = 0;
    buf[i+1] = 0;
    buf[i+2] = 255;
  }
  /**
   *@brief 发送一组完整的数据，数组的元素从0到11分别控制引脚A3 B3 C3 A2 B2 C2 A1 B1 C1 A0 B0 C0
   *@param buf 指向192bit灰阶数据的指针
   */
  rgbDriver.write(buf);
  //控制级联的最近一个驱动的所有灯变为绿色
  for(uint16_t i = 0, brightness = 1; i <= 11; i+=3) {
    buf[i] = 255;
    buf[i+1] = 0;
    buf[i+2] = 0;
  }
  rgbDriver.write(buf);
  rgbDriver.latch();//发送锁存信号使所有驱动工作
  delay(5000);
}