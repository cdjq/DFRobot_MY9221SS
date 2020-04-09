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
#include <DFRobot_MY9221SS.h>

DFRobot_MY9221SS::DFRobot_MY9221SS(void)
{

}
void DFRobot_MY9221SS::begin(uint32_t clockPin, uint32_t dataPin)//初始化
{
  _dataPin = dataPin;
  _clockPin = clockPin;
  pinMode(_clockPin, OUTPUT);
  pinMode(_dataPin, OUTPUT);
  setMode();//设置模式
}
void DFRobot_MY9221SS::sendCmd(uint16_t cmd)//发送16位CMD命令
{
  for (uint8_t i = 0, polar = 1; i < 16; i++) {
    digitalWrite(_dataPin, cmd & 0x8000 ? HIGH : LOW);//数据发送
    digitalWrite(_clockPin, polar);//时钟上升沿下降沿，数据有效
    polar = 1-polar;
    cmd <<= 1;
  }
}
void DFRobot_MY9221SS::sendData(uint16_t data)//每次调用发送16位数据
{
  for (uint8_t i = 0, polar = 1; i < 16; i++) {
    digitalWrite(_dataPin, data & 0x8000 ? HIGH : LOW);//数据发送
    digitalWrite(_clockPin, polar);//时钟上升沿下降沿，数据有效
    polar = 1 - polar;
    data <<= 1;
  }
}

void DFRobot_MY9221SS::setMode(uint8_t temp, uint8_t hspd, uint8_t bs, \
                               uint8_t gck, uint8_t sep, uint8_t osc, \
                               uint8_t pol, uint8_t cntset, uint8_t onest)//模式设置
{
  sMode_t  mode;
  mode.temp = temp;
  mode.hspd = hspd;
  mode.bs = bs;
  mode.gck = gck;
  mode.sep = sep;
  mode.osc = osc;
  mode.pol = pol;
  mode.cntset = cntset;
  mode.onest = onest;
  _mode = *((uint16_t*)&mode);
  _bsMask = (mode.bs == 3) ? 0xffff : 0xff;//判断灰阶模式并设置相应的掩码
}


void DFRobot_MY9221SS::write(uint16_t* buf)//向芯片发送设置命令和灰阶数据
{
  sendCmd(_mode); //发送命令，选择模式
  for (uint8_t i = 0; i < 12; i++) { //发送灰阶数据，从A3引脚的buf开始发
    sendData(buf[i]);
  }
}

void DFRobot_MY9221SS::latch()//内部栓锁的控制，发送锁存信号使所有驱动工作，所有数据发送完后，最先发送的一组数据控制级联的最远的一个驱动，最后发送的一组数据控制与主控相连的驱动
{
  digitalWrite(_dataPin, LOW);
  delayMicroseconds(240);//固定延时
  digitalWrite(_dataPin, HIGH);
  digitalWrite(_dataPin, LOW);
  digitalWrite(_dataPin, HIGH);
  digitalWrite(_dataPin, LOW);
  digitalWrite(_dataPin, HIGH);
  digitalWrite(_dataPin, LOW);
  digitalWrite(_dataPin, HIGH);
  digitalWrite(_dataPin, LOW);
  delayMicroseconds(1);//Tsop(最小值)必须大于[200ns+N*10ns]，其中 N 为芯片串接数目
}


void DFRobot_MY9221SS::setRgbLed(uint8_t ledNo, uint16_t R, uint16_t G, uint16_t B)
{
  uint16_t  buf[LED_PIN_COUNT];
  for(uint8_t j = 0; j <= LED_RGB_NO; j++) {
    if (ledNo & 0x0008) {//从高位开始判断是否灯被指定
      buf[3 * j + 0] = G & _bsMask;
      buf[3 * j + 1] = R & _bsMask;
      buf[3 * j + 2] = B & _bsMask;
    } else {
      buf[3 * j + 0] = 0 ;
      buf[3 * j + 1] = 0 ;
      buf[3 * j + 2] = 0 ;
    }
    ledNo<<=1;
  }
  write(buf);//向芯片写入数据，12个引脚，每个16bit
}

void DFRobot_MY9221SS::setMonochromeLed(uint16_t pinNo, uint16_t brightness)//设置单色灯，采用12位二进制指定引脚，用宏定义控制对应引脚LED亮度，最高位表示A11，最低位是C0
{
  uint16_t  buf[LED_PIN_COUNT];
  for(uint8_t i = 0; i < LED_PIN_COUNT; i++) {
    if(pinNo & 0x0800) {//从高位开始判断是否灯被指定
      buf[i] = brightness & _bsMask;
    } else {
      buf[i] = 0;//每次发送数据，未设置的灯默认关闭
    }
    pinNo<<=1;
  }
  write(buf);//向芯片写入数据，12个引脚，每个16bit
}

void DFRobot_MY9221SS::autoColorChange(void)//自动渐变随机色
{
  uint16_t  buf[LED_PIN_COUNT];
  uint16_t R = rand()%_bsMask;
  uint16_t G = rand()%_bsMask;
  uint16_t B = _bsMask - (R + G)/2;
  for(uint8_t bright = 20; bright > 1; bright-=2) {//渐亮
    for(uint8_t i = 0; i < LED_PIN_COUNT; i+=3) {
      buf[i] = G/bright ;
      buf[i+1] = R/bright ;
      buf[i+2] = B/bright ;
    }
    write(buf);
    //发送锁存信号使所有驱动工作
    latch();
    delay(50);
  }
  for(uint8_t bright = 1; bright < 20; bright+=2) {//渐灭
    for(uint8_t i = 0; i < LED_PIN_COUNT; i+=3) {
      buf[i] = G/bright ;
      buf[i+1] = R/bright ;
      buf[i+2] = B/bright ;
    }
    write(buf);
    //发送锁存信号使所有驱动工作
    latch();
    delay(100);
  }
  for(uint8_t i = 0; i < LED_PIN_COUNT; i++) {//熄灭
    buf[i] = 0 ;
  }
  write(buf);
  //发送锁存信号使所有驱动工作
  latch();
}

