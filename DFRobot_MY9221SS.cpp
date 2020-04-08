/*!
 * @file DFRobot_MY9221SS.h
 * @brief Define the basic structure of class DFRobot_MY9221SS
 * @n 这是一个有12路引脚的LED灯驱动芯片，实现了下面这些功能
 * @n 控制12路单色LED灯的亮度
 * @n 控制4路带RGB引脚的LED灯闪烁、亮度和变色，支持12V电源供电的LED灯，最高承受17V
 * @n 驱动可级联，后一个驱动会跟随前一个驱动的状态进行工作
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
  //16位全亮无法识别
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
}


void DFRobot_MY9221SS::write(uint16_t* buf)//向芯片发送设置命令和灰阶数据
{
  sendCmd(_mode); //发送命令，选择模式
  for (uint8_t i = 0; i < 12; i++) { //发送灰阶数据，从A3引脚的buf开始发
    sendData(buf[i]);
  }
  //所有数据发送完后发送锁存信号，灰阶资料和命令锁存后才可使LED灯工作
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

void DFRobot_MY9221SS::setRgbLeds(uint8_t ledNo, uint16_t R, uint16_t G, uint16_t B)
{
  uint16_t  buf[LED_PIN_COUNT];
  for(uint8_t j = 0; j <= LED_RGB_NO; j++) {
    if (ledNo & 0x0008) {//从高位开始判断是否灯被指定
      if((_mode & 0x300 )== 0x300) {//判断是否是16位灰阶模式
        buf[3 * j + 0] = G ;
        buf[3 * j + 1] = R ;
        buf[3 * j + 2] = B ;
      } else {
        buf[3 * j + 0] = G & 0xff;
        buf[3 * j + 1] = R & 0xff;
        buf[3 * j + 2] = B & 0xff;
      }
    } else {
      buf[3 * j + 0] = 0 ;
      buf[3 * j + 1] = 0 ;
      buf[3 * j + 2] = 0 ;
    }
    ledNo<<=1;
  }
  write(buf);//向芯片写入数据，12个引脚，每个16bit
}

void DFRobot_MY9221SS::autoColorChange(void)//自动渐变随机色
{
  uint16_t  buf[LED_PIN_COUNT];
  uint16_t R = rand()%255;
  uint16_t G = rand()%255;
  uint16_t B = 255 - (R + G)/2;
  for(uint8_t bright = 20; bright > 1; bright-=2) {
    for(uint8_t i = 0; i < LED_PIN_COUNT; i++) {
      if(i%3 == 0) {
        buf[i] = G/bright ;
      } else if(i%3 == 1) {
        buf[i] = R/bright ;
      } else if(i%3 == 2) {
        buf[i] = B/bright ;
      }
    }
    write(buf);
    delay(50);
  }
  for(uint8_t bright = 1; bright < 20; bright+=2) {
    for(uint8_t i = 0; i < LED_PIN_COUNT; i++) {
      if(i%3 == 0) {
        buf[i] = G/bright ;
      } else if(i%3 == 1) {
        buf[i] = R/bright ;
      } else if(i%3 == 2) {
        buf[i] = B/bright ;
      }
    }
    write(buf);
    delay(100);
  }
  for(uint8_t i = 0; i < LED_PIN_COUNT; i++) {
    buf[i] = 0 ;
  }
  write(buf);
}

void DFRobot_MY9221SS::setSingleColorLeds(uint16_t pinNo, uint16_t brightness)//改用12位二进制指定引脚，用宏定义控制对应引脚LED亮度，最高位表示A11，最低位是C0
{
  uint16_t  buf[LED_PIN_COUNT];
  if((_mode & 0x300 )== 0x300) {//判断是否是16位灰阶模式
    for(uint8_t i = 0; i < LED_PIN_COUNT; i++) {
      if(pinNo & 0x0800) {
        buf[i] = brightness ;
      } else {
        buf[i] = 0;//每次发送数据，未设置的灯默认关闭
      }
      pinNo<<=1;
    }
    write(buf);//向芯片写入数据，12个引脚，每个16bit
  } else {
    for(uint8_t i = 0; i < LED_PIN_COUNT; i++) {
      if(pinNo & 0x0800) {//从高位开始判断是否灯被指定
        buf[i] = brightness & 0xff;
      } else {
        buf[i] = 0;//每次发送数据，未设置的灯默认关闭
      }
      pinNo<<=1;
    }
    write(buf);//向芯片写入数据，12个引脚，每个16bit
  }
}
