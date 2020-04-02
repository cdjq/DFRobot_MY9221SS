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


#define LED_BIN_COUNT   12            //芯片的RGB引脚总数

/*
*亮度调节
*00000000 暗
*00000011 变亮
*........
*11111111 最亮
*/
#define LED_TURN_OFF           0     //关闭LED灯
#define LED_FULL_BRIGHTNESS    0xff  //打开LED灯（最亮）

#define  COLOR_RGB565_BLACK     0x0000      // 黑色    
#define  COLOR_RGB565_NAVY      0x000F      // 深蓝色  
#define  COLOR_RGB565_DGREEN    0x03E0      // 深绿色  
#define  COLOR_RGB565_DCYAN     0x03EF      // 深青色  
#define  COLOR_RGB565_PURPLE    0x780F      // 紫色  
#define  COLOR_RGB565_MAROON    0x7800      // 深红色      
#define  COLOR_RGB565_OLIVE     0x7BE0      // 橄榄绿      
#define  COLOR_RGB565_LGRAY     0xC618      // 灰白色
#define  COLOR_RGB565_DGRAY     0x7BEF      // 深灰色      
#define  COLOR_RGB565_BLUE      0x001F      // 蓝色    
#define  COLOR_RGB565_GREEN     0x07E0      // 绿色 
#define  COLOR_RGB565_CYAN      0x07FF      // 青色  
#define  COLOR_RGB565_RED       0xF800      // 红色       
#define  COLOR_RGB565_MAGENTA   0xF81F      // 品红    
#define  COLOR_RGB565_YELLOW    0xFFE0      // 黄色
#define  COLOR_RGB565_WHITE     0xFFFF      // 白色


class DFRobot_MY9221SS
{
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
   *@param pinClock 时钟引脚
   *@param pinData  数据引脚
   */
  void begin(uint32_t pinClock, uint32_t pinData);

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
   *@brief 锁存信号
   */
  void latch(void);

  /**
   *@brief 发送全部208位数据
   *@param buf 指向192bit灰阶数据的指针，从控制引脚A3的16bit数据开始发送
   */
  void write(uint16_t* buf);

  /**
   * @brief 设置某个灯的RGB颜色，4号灯对应引脚A3B3C3
   * @param ledNo 设置的灯的编号，取值1~4
   * @param R     设置RGB红色分量，硬件应连接引脚B，取值范围0~255
   * @param G     设置RGB绿色分量，硬件应连接引脚C，取值范围0~255
   * @param B     设置RGB蓝色分量，硬件应连接引脚A，取值范围0~255
  */
  void setLed(uint8_t ledNo, uint16_t R, uint16_t G, uint16_t B);

  /**
   * @brief 设置某个灯的颜色和亮度，4号灯对应引脚A3B3C3
   * @param ledNo         设置的灯的编号，取值范围1~4
   * @param color         用宏定义控制led灯，格式是RGB565
   * @param brightness    亮度控制，取值范围0~255
  */
  void setLedColor(uint8_t ledNo, uint16_t color, uint8_t brightness);

  /**
   * @brief 设置所有灯的RGB颜色
   * @param R     设置RGB红色分量，硬件应连接引脚B，取值范围0~255
   * @param G     设置RGB绿色分量，硬件应连接引脚C，取值范围0~255
   * @param B     设置RGB蓝色分量，硬件应连接引脚A，取值范围0~255
  */
  void setAllLed(uint16_t R, uint16_t G, uint16_t B);

  /**
   * @brief 所有灯的RGB颜色随机
  */
  void autoColorChange(void);


private:
  void setDefaultMode(void);//设置默认模式

private:
  uint16_t _mode;
  uint32_t _pinClock;
  uint32_t _pinData;
};
#endif
