# DFRobot_MY9221SS  RGB驱动库
DFRobot_MY9221SS是基于MY9221SS芯片的RGB驱动库，其芯片最大可承受17V电压，可以驱动带12V电源线和RGB引脚的LED灯，通过PWM调节灯的红绿蓝三基色的亮度从而组成混色。<br>
该驱动支持级联，可以将多个驱动级联同时进行相同的工作。<br>
每个驱动可分别控制4颗大功率LED灯，每颗LED灯可串联多颗。<br>
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
* 驱动可级联做相同的工作. <br>

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
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
  void setMode(uint8_t temp=0, uint8_t hspd=1, uint8_t bs=0,\
               uint8_t gck=0, uint8_t sep=0, uint8_t osc=0, \
               uint8_t pol=0, uint8_t cntset=0, uint8_t onest=0);

  /**
   *@brief 发送全部208位数据
   *@param buf 指向192bit灰阶数据的指针，从控制引脚A3的16bit数据开始发送
   */
  void write(uint16_t* buf);

  /**
   * @brief 设置某个灯的颜色，4号灯对应引脚A3B3C3
   * @param ledNo 设置的灯的编号，一共四路/颗灯，取值1~4
   * @param R     设置RGB红色分量，硬件应连接引脚B，8位灰阶数据模式取值范围为0~255，16位时取值范围0~65535
   * @param G     设置RGB绿色分量，硬件应连接引脚C，8位灰阶数据模式取值范围为0~255，16位时取值范围0~65535
   * @param B     设置RGB蓝色分量，硬件应连接引脚A，8位灰阶数据模式取值范围为0~255，16位时取值范围0~65535
  */
  void setLedColor(uint8_t ledNo, uint16_t R, uint16_t G, uint16_t B);

  /**
   * @brief 设置所有灯的颜色
   * @param R     设置RGB红色分量，硬件应连接引脚B，8位灰阶数据模式取值范围为0~255，16位时取值范围0~65535
   * @param G     设置RGB绿色分量，硬件应连接引脚C，8位灰阶数据模式取值范围为0~255，16位时取值范围0~65535
   * @param B     设置RGB蓝色分量，硬件应连接引脚A，8位灰阶数据模式取值范围为0~255，16位时取值范围0~65535
  */
  void setAllLed(uint16_t R, uint16_t G, uint16_t B);

  /**
   * @brief 点亮所有灯，RGB颜色随机
  */
  void autoColorChange(void);

  /**
   * @brief 用宏定义，指定引脚并控制对应单色灯的亮度
   * @param pinNo        宏定义引脚名
   * @param brightness   设置亮度，8位灰阶数据模式取值范围为0~255，16位时取值范围0~65535
  */
  void setSingleColorLeds(uint16_t pinNo, uint16_t brightness); 
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno        |      √       |              |             | 
Mega2560        |      √       |              |             | 
Leonardo        |      √       |              |             | 
ESP32        |      √       |              |             | 
ESP8266        |      √       |              |             | 
FireBeetle-M0        |      √       |              |             | 


## History

- Data 2020-3-31
- Version V0.1


## Credits

Written by(hangyu.ye@dfrobot.com), 2020. (Welcome to our [website](https://www.dfrobot.com/))





