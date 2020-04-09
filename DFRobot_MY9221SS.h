/*!
 * @file DFRobot_MY9221SS.h
 * @brief Define the basic structure of class DFRobot_MY9221SS
 * @n 这是一个有12路引脚的LED灯驱动芯片，实现了下面这些功能
 * @n 控制12路单色LED灯的亮度
 * @n 控制4路带RGB引脚的LED灯闪烁、亮度和变色，支持12V电源供电的LED灯，最高承受17V
 * @n 驱动可级联，每次发送N个数据再锁存可以同时控制离主控最近的N个驱动，未受到控制的远端驱动继承较近一个驱动的状态
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [YeHangYu](hangyu.ye@dfrobot.com)
 * @version  V1.0
 * @date  2020-03-30
 * @https://github.com/DFRobot/DFRobot_MY9221SS
 */
#ifndef _DFROBOT_MY9221SS_H
#define _DFRobot_MY9221SS_H

#include <Arduino.h>


#define ENABLE_DBG   0
#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif


#define LED_PIN_COUNT   12            //每个芯片的LED引脚总数
#define LED_RGB_NO      3             //RGB灯的最大编号


class DFRobot_MY9221SS
{
  //引脚名的宏定义
  #define  C0  (1<<0)
  #define  B0  (1<<1)
  #define  A0  (1<<2)
  #define  C1  (1<<3)
  #define  B1  (1<<4)
  #define  A1  (1<<5)
  #define  C2  (1<<6)
  #define  B2  (1<<7)
  #define  A2  (1<<8)
  #define  C3  (1<<9)
  #define  B3  (1<<10)
  #define  A3  (1<<11)
  //RGB灯的引脚宏定义
  #define  LED0  (1<<0)
  #define  LED1  (1<<1)
  #define  LED2  (1<<2)
  #define  LED3  (1<<3)

public:
  /*
  *设置芯片模式的CMD数据格式
  * ------------------------------------------------------------------------------------------
  * |    b15   |   b14    |   b13    |   b12    |   b11    |    b10   |    b9    |    b8     |
  * ------------------------------------------------------------------------------------------
  * |                        Temp                          |   hspd   |          bs          |
  * ------------------------------------------------------------------------------------------
  * ------------------------------------------------------------------------------------------
  * |    b7    |    b6    |    b5    |    b4    |    b3    |    b2    |    b1     |    b0    |
  * ------------------------------------------------------------------------------------------
  * |               gck              |    sep   |    osc   |    pol   |   cntset  |   onest  |
  * ------------------------------------------------------------------------------------------
  */
  typedef struct {
    uint8_t   onest:1; /*!< 0 : frame cycle repeat mode 1 : frame cycle One-shot mode (Only usable when cntset = “1”) */
    uint8_t   cntset:1; /*!< 0 : free running mode 1 : counter reset mode (Only usable when osc = “1”) */
    uint8_t   pol:1; /*!< 0 : work as LED driver 1 : work as MY-PWM/APDM generator */
    uint8_t   osc:1; /*!< 0 : internal oscillator (8.6MHz) (internal GCK source) 1 : external clock from GCKI pin (external GCK source) */
    uint8_t   sep:1; /*!< 0 : MY-PWM output waveform (similar to traditional waveform) 1 : APDM output waveform */
    uint8_t   gck: 3; /*!< (If CMD[3]=1, please set CMD[7:5]=000)000 : original freq (8.6MHz) 001 : original freq/2 010 : original freq/4 011 : original freq/8 100 : original freq/16 101 : original freq64 110 : original freq/128 111 : original freq/256 */
    uint8_t   bs: 2; /*!< 00 : 8-bit grayscale application 01 : 12-bit grayscale application 10 : 14-bit grayscale application 11 : 16-bit grayscale application */
    uint8_t   hspd: 1; /*!< 0 :Iout slow mode 1 : Iout fast mode */
    uint8_t   temp: 5; /*!< Please filled with all “0” */
  } __attribute__ ((packed)) sMode_t;


public:
  /**
   *@brief 构造函数
   */
  DFRobot_MY9221SS(void);

  /**
   *@brief 初始化
   *@param clockPin 时钟引脚
   *@param dataPin  数据引脚
   */
  void begin(uint32_t clockPin, uint32_t dataPin);

  /**
   *@brief 发送16位命令
   *@param cmd 16位数据
   */
  void sendCmd(uint16_t cmd);

  /**
   *@brief 发送16位数据
   *@param data 16位数据
   */
  void sendData(uint16_t data);

  /**
   *@brief 设置模式
   *@param temp 保留位元
   *@param hspd 输出电流反应速度选择
   *@param bs  灰阶选择
   *@param gck 内置灰阶时钟频率选择
   *@param sep 输出电流打散与不打散选择
   *@param osc 灰阶时钟频率来源选择
   *@param pol 输出电流极性选择
   *@param cntset 自动更换画面模式或强制更换画面模式选择
   *@param onest 画面重复显示或只亮一次选择
   */
  void setMode(uint8_t temp=0, uint8_t hspd=0, uint8_t bs=0,\
               uint8_t gck=0, uint8_t sep=1, uint8_t osc=0,\
               uint8_t pol=0, uint8_t cntset=0, uint8_t onest=0);

  /**
   *@brief 发送全部数据，数组的元素从11到0分别控制引脚C0 B0 A0 C1 B1 A1 C2 B2 A2 C3 B3 A3
   *@param buf 指向192bit灰阶数据的指针
   */
  void write(uint16_t* buf);

  /**
   *@brief 发送锁存信号使所有驱动工作，所有数据发送完后，最先发送的一组数据控制级联的最远的一个驱动，最后发送的一组数据控制与主控相连的驱动
   */
  void latch();

  /**
   * @brief 用宏定义指定LED灯，并通过RGB各分量控制颜色  
   * @param ledNo 宏定义灯名，一共四路/颗灯，LED0~LED3
   * @param R     设置RGB红色分量，硬件应连接引脚B，8位灰阶数据模式时取值范围为0~255，16位时取值范围为0~65535
   * @param G     设置RGB绿色分量，硬件应连接引脚A，8位灰阶数据模式时取值范围为0~255，16位时取值范围为0~65535
   * @param B     设置RGB蓝色分量，硬件应连接引脚C，8位灰阶数据模式时取值范围为0~255，16位时取值范围为0~65535
  */
  void setRgbLed(uint8_t ledNo, uint16_t R, uint16_t G, uint16_t B);

  /**
   * @brief 用宏定义指定引脚并控制引脚上单色灯的亮度
   * @param pinNo      宏定义引脚名
   * @param brightness 亮度，8位灰阶数据模式时取值范围为0~255，16位时取值范围为0~65535
  */
  void setMonochromeLed(uint16_t pinNo, uint16_t brightness);

  /**
   * @brief 颜色随机，渐亮渐灭一次
  */
  void autoColorChange(void);

private:
  uint16_t _mode;
  uint16_t _bsMask;//灰阶位数掩码
  uint32_t _clockPin;
  uint32_t _dataPin;
};
#endif
