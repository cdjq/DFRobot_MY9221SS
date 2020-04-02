# DFRobot_MY9221SS  RGB驱动库
DFRobot_MY9221SS是基于MY9221SS芯片的RGB驱动库，其芯片最大可承受17V电压，可以驱动带12V电源线和RGB引脚的LED灯，通过PWM调节灯的红绿蓝三基色的亮度从而组成混色。
该驱动支持级联，可以将多个驱动级联同时进行相同的工作。
每个驱动可分别控制4颗大功率LED灯，每颗LED灯可串联多颗。
该库也可以用于驱动12颗单色灯，通过PWM可分别控制调节每一颗灯的亮度。  <br>




## Product Link （链接到英文商城）
    SKU：产品名称
   
## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

* 控制12路单色LED灯的亮度 <br>
* 分别控制4路带RGB和12V电源引脚的LED灯闪烁、亮度和改变色. <br>

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
  /*!
   *@brief 构造函数
   */
  DFRobot_MY9221SS();
  
  /*!
   *@brief 初始化
   *@param clockPin 时钟引脚
   *@param dataPin  数据引脚
   */
  void begin(/*clockPin=*/CLK_PIN, /*dataPin=*/DATA_PIN);

  /*!
   *@brief 发送16位CMD命令
   *@param bits 16位数据
   */
  void sendCmd(uint16_t bits);  

  /*!
   *@brief 每次调用发送16位数据
   *@param bits 16位数据
   */
  void sendData(uint16_t bits); 

  /*!
   *@brief 内部栓锁的控制
   */
  void latch(void);   

  /*!
   *@brief 发送全部208位数据
   *@param buf 指向192bit灰阶数据的指针，从控制引脚A3的16bit数据开始发送
   */
  void write(uint16_t* buf); 
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno        |      √       |              |             | 
Mega2560        |      √       |              |             | 
Leonardo        |      √       |              |             | 
ESP32        |      √       |              |             | 
micro:bit        |      √       |              |             | 


## History

- Data 2020-3-31
- Version V0.1


## Credits

Written by(hangyu.ye@dfrobot.com), 2020. (Welcome to our [website](https://www.dfrobot.com/))





