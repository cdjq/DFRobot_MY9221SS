# DFRobot_MY9221SS  LED驱动库
DFRobot_MY9221SS是使用MY9221SS芯片的LED驱动库，芯片可承受最大输出电压17伏特以支持多颗LED串联，解决了现在很多交互场景需要用到灯带或LED均为12V，使用5V/3.3V类主控不能驱动的问题。该LED驱动可分别驱动4路大功率RGBLed，可级联   <br>




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

* Read the time the program was last compiled. <br>
* Set a alarm clock to trigger at a specified time. <br>
* Measure ambient temperature. <br>

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
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





