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

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

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
  * |                      保留位元                        | 电流快慢 |       灰阶选择       |
  * ------------------------------------------------------------------------------------------
  * ------------------------------------------------------------------------------------------
  * |    b7    |    b6    |    b5    |    b4    |    b3    |    b2    |    b1     |    b0    |
  * ------------------------------------------------------------------------------------------
  * |      内部振荡器频率选择        | 输出波形 |灰度时钟源| 输出极性 |计数器复位 | 单次模式 |
  * ------------------------------------------------------------------------------------------
  */
  typedef struct
  {
    uint8_t   temp: 5; /*!< 没有用，全部填0 */
    uint8_t   hspd: 1; /*!< 1：输出电流快速模式 0：输出电流慢速模式 */
    uint8_t   bs: 2; /*!< 0：8位灰度级应用，1：12位灰度级应用，2：14位灰度级应用，3：16位灰度级应用 */
    uint8_t   gck: 3; /*!< 0：原始频率(8.6MHz)(如果osc="1"则此处应设置为0)，1：原始/2，2：原始/4，3：原始/8，4：原始/16，5：原始/64，6：原始/128，7：原始/256 */
    uint8_t   sep:1; /*!< 1：APDM输出波形（打散） 0：MY-PWM输出波形(与传统波形相似) */
    uint8_t   osc:1; /*!< 1：外部时钟（GCKI 脚位传送） 0：内部振荡器(8.6MHz) */
    uint8_t   pol:1; /*!< 1：作为MY-PWM/APDM生成器工作 0：作为LED驱动工作 */
    uint8_t   cntset:1; /*!< 1：强制更换画面模式(仅当osc="1"时可用) 0：自动更换画面模式 */
    uint8_t   onest:1; /*!< 1：画面只亮一次模式(仅当cntset="1"时可用) 0：画面重复显示模式 */
  } __attribute__ ((packed)) sMode_t;

  
public:
  /*!
   *@brief 构造函数
   *@param pinClock 时钟引脚
   *@param pinData  数据引脚
   */
  DFRobot_MY9221SS(uint32_t pinClock, uint32_t pinData);
  
  /*!
   *@brief 初始化
   */
  void begin(void);

  /*!
   *@brief 发送16位CMD命令
   *@param bits 16位数据
   */
  void sendcmd(uint16_t bits);  

  /*!
   *@brief 每次调用发送16位数据
   *@param bits 16位数据
   */
  void senddata(uint16_t bits); 

  /*!
   *@brief 内部栓锁的控制
   */
  void latch(void);   

  /*!
   *@brief 发送全部208位数据
   *@param buf 指向192bit灰阶数据的指针，从控制引脚A3的16bit数据开始发送
   */
  void send(uint16_t* buf);     

private:
  uint32_t _pinClock;
  uint32_t _pinData;
  sMode_t  mode;
  uint16_t _mode;
};
#endif
