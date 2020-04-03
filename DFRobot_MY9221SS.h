/*!
 * @file DFRobot_MY9221SS.h
 * @brief Define the basic structure of class DFRobot_MY9221SS
 * @n
 *
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


#define LED_PIN_COUNT   12            //芯片的RGB引脚总数

/*
*亮度调节
*0是熄灭，255是最亮，数值越大灯会越亮
*/
#define LED_TURN_OFF           0     //关闭LED灯
#define LED_FULL_BRIGHTNESS    0xff  //打开LED灯（最亮）


class DFRobot_MY9221SS
{
  //RGB Driver的各引脚名的宏定义
  #define  C0  0
  #define  B0  1
  #define  A0  2
  #define  C1  3
  #define  B1  4
  #define  A1  5
  #define  C2  6
  #define  B2  7
  #define  A2  6
  #define  C3  9
  #define  B3  10
  #define  A3  11
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
    uint8_t   temp: 5; /*!< Please filled with all “0” */
    uint8_t   hspd: 1; /*!< 0 :Iout slow mode 1 : Iout fast mode */
    uint8_t   bs: 2; /*!< 00 : 8-bit grayscale application 01 : 12-bit grayscale application 10 : 14-bit grayscale application 11 : 16-bit grayscale application */
    uint8_t   gck: 3; /*!< (If CMD[3]=1, please set CMD[7:5]=000)000 : original freq (8.6MHz) 001 : original freq/2 010 : original freq/4 011 : original freq/8 100 : original freq/16 101 : original freq64 110 : original freq/128 111 : original freq/256 */
    uint8_t   sep:1; /*!< 0 : MY-PWM output waveform (similar to traditional waveform) 1 : APDM output waveform */
    uint8_t   osc:1; /*!< 0 : internal oscillator (8.6MHz) (internal GCK source) 1 : external clock from GCKI pin (external GCK source) */
    uint8_t   pol:1; /*!< 0 : work as LED driver 1 : work as MY-PWM/APDM generator */
    uint8_t   cntset:1; /*!< 0 : free running mode 1 : counter reset mode (Only usable when osc = “1”) */
    uint8_t   onest:1; /*!< 0 : frame cycle repeat mode 1 : frame cycle One-shot mode (Only usable when cntset = “1”) */
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
   *@brief 发送16位CMD命令
   *@param bits 16位数据
   */
  void sendCmd(uint16_t bits);

  /**
   *@brief 每次调用发送16位数据
   *@param bits 16位数据
   */
  void sendData(uint16_t bits);

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
  void setMode(uint8_t temp=0, uint8_t hspd=1, uint8_t bs=0, uint8_t gck=0, uint8_t sep=0, uint8_t osc=0, uint8_t pol=0, uint8_t cntset=0, uint8_t onest=0);

  /**
   *@brief 发送全部208位数据
   *@param buf 指向192bit灰阶数据的指针，从控制引脚A3的16bit数据开始发送
   */
  void write(uint16_t* buf);

  /**
   * @brief 设置某个灯的RGB颜色，4号灯对应引脚A3B3C3
   * @param ledNo 设置的灯的编号，一共四路/颗灯，取值1~4
   * @param R     设置RGB红色分量，硬件应连接引脚B，取值范围0~255
   * @param G     设置RGB绿色分量，硬件应连接引脚C，取值范围0~255
   * @param B     设置RGB蓝色分量，硬件应连接引脚A，取值范围0~255
  */
  void setLed(uint8_t ledNo, uint16_t R, uint16_t G, uint16_t B);

  /**
   * @brief 设置所有灯的RGB颜色
   * @param R     设置RGB红色分量，硬件应连接引脚B，取值范围0~255
   * @param G     设置RGB绿色分量，硬件应连接引脚C，取值范围0~255
   * @param B     设置RGB蓝色分量，硬件应连接引脚A，取值范围0~255
  */
  void setAllLed(uint16_t R, uint16_t G, uint16_t B);

  /**
   * @brief 点亮所有灯，RGB颜色随机
  */
  void autoColorChange(void);

  /**
   * @brief 设置单个引脚的亮度，可用于调节单色灯的亮度
   * @param pinNo        设置的单个引脚的编号，使用引脚名即可，引脚名的宏定义与实物完全一致
   * @param brightness   设置亮度，取值范围0~255
  */
  void setSinglePin(uint8_t pinNo, uint16_t brightness);

  /**
   * @brief 改用12位二进制，指定引脚并控制对应引脚亮度
   * @param bits        用二进制指定对应引脚，12位二进制从左往右依次对应引脚C0 B0 A0 C1 B1 A1 C2 B2 A2 C3 B3 A3，范围从0到0xfff
   * @param brightness   设置亮度，取值范围0~255
  */
  void setPins(uint16_t bits, uint16_t brightness);



private:
  uint16_t _mode;
  uint32_t _clockPin;
  uint32_t _dataPin;
};
#endif
