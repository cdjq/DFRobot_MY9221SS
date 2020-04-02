/*!
 * @file DFRobot_MY9221SS.h
 * @brief Define the basic structure of class DFRobot_MY9221SS
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [YeHangYu](hangyu.ye@dfrobot.com)
 * @version  V1.0
 * @date  2020-03-30
 * @https://github.com/DFRobot/DFRobot_MY9221SS
 */
#include "DFRobot_MY9221SS.h"

DFRobot_MY9221SS::DFRobot_MY9221SS(void)
{

}
void DFRobot_MY9221SS::begin(uint32_t pinClock, uint32_t pinData)//初始化
{
  _pinData = pinData;
  _pinClock = pinClock;
  pinMode(_pinClock, OUTPUT);
  pinMode(_pinData, OUTPUT);
  //设置模式
  setDefaultMode();
}
void DFRobot_MY9221SS::sendCmd(uint16_t bits)//发送16位CMD命令
{
  for (uint8_t i = 0, clk = 1; i < 16; i++) {
    digitalWrite(_pinData, bits & 0x8000 ? HIGH : LOW);//数据发送
    digitalWrite(_pinClock, clk);//时钟上升沿下降沿，数据有效
    clk = 1-clk;
    bits <<= 1;
  }
}
void DFRobot_MY9221SS::sendData(uint16_t bits)//每次调用发送16位数据
{
  for (uint8_t i = 0, clk = 1; i < 16; i++) {
    digitalWrite(_pinData, bits & 0x8000 ? HIGH : LOW);//数据发送
    digitalWrite(_pinClock, clk);//时钟上升沿下降沿，数据有效
    clk = 1-clk;
    bits <<= 1;
  }
}

void DFRobot_MY9221SS::setDefaultMode(void)//模式设置
{
  sMode_t  mode;
  mode.temp = 0;
  mode.hspd = 1;//输出电流设置为慢速可能会出现问题
  mode.bs = 0;
  mode.gck = 0;
  mode.sep = 0;
  mode.osc = 0;
  mode.pol = 0;
  mode.cntset = 0;
  mode.onest = 0;
  _mode = *((uint16_t*)&mode);
}

void DFRobot_MY9221SS::latch()//锁存信号
{
  digitalWrite(_pinData, LOW);
  digitalWrite(_pinClock, HIGH);
  digitalWrite(_pinClock, LOW);
  digitalWrite(_pinClock, HIGH);
  digitalWrite(_pinClock, LOW);
  delayMicroseconds(240);
  digitalWrite(_pinData, HIGH);
  digitalWrite(_pinData, LOW);
  digitalWrite(_pinData, HIGH);
  digitalWrite(_pinData, LOW);
  digitalWrite(_pinData, HIGH);
  digitalWrite(_pinData, LOW);
  digitalWrite(_pinData, HIGH);
  digitalWrite(_pinData, LOW);
  delayMicroseconds(1);
  digitalWrite(_pinClock, HIGH);
  digitalWrite(_pinClock, LOW);
}

void DFRobot_MY9221SS::write(uint16_t* buf)//向芯片发送所有数据
{
  sendCmd(_mode); //发送命令，选择模式
  for (uint8_t i = 0; i < 12; i++) { //发送灰阶数据，从A3引脚的buf开始发
    sendData(buf[i]);
  }
  latch();//锁存
  return;
}

void DFRobot_MY9221SS::setLedColor(uint8_t ledNo, uint16_t color, uint8_t brightness)//用RGB565和亮度值来设置某一个RGB灯的颜色
{
  uint16_t  buf[LED_BIN_COUNT];
  uint16_t R,G,B;
  //变为RGB888
  R = (color >> 11) * 8 * brightness/0xff;
  G = ((color >> 6) & 31) * 8 * brightness/0xff;
  B = (color & 31) * 8 * brightness/0xff;
  ledNo = 5 - ledNo;
  if(ledNo <= 4 || ledNo >= 1) {
    for(uint8_t i = 0; i < LED_BIN_COUNT; i++) {
      if(i == ledNo*3-3) {
        buf[i] = B;
      } else if(i == ledNo*3-2) {
        buf[i] = R;
      } else if(i == ledNo*3-1) {
        buf[i] = G;
      } else {
        buf[i] = LED_TURN_OFF;
      }
    }
    write(buf);//向芯片发送数据，12个引脚，每个16bit
  } else {
    Serial.println("ledNo error");
  }
}

void DFRobot_MY9221SS::setLed(uint8_t ledNo, uint16_t R, uint16_t G, uint16_t B)//用RGB888设置某一个RGB灯的颜色
{
  uint16_t  buf[LED_BIN_COUNT];
  ledNo = 5 - ledNo;
  if(ledNo <= 4 || ledNo >= 1) {
    for(uint8_t i = 0; i < LED_BIN_COUNT; i++) {
      if(i == ledNo*3-3) {
        buf[i] = G ;
      } else if(i == ledNo*3-2) {
        buf[i] = R ;
      } else if(i == ledNo*3-1) {
        buf[i] = B ;
      } else {
        buf[i] = LED_TURN_OFF;
      }
    }
    write(buf);//向芯片发送数据，12个引脚，每个16bit，共208bit
  } else {
    Serial.println("ledNo error");
  }
}

void DFRobot_MY9221SS::setAllLed(uint16_t R, uint16_t G, uint16_t B)//用RGB888设置所有RGB灯的颜色
{
  uint16_t  buf[LED_BIN_COUNT];
  for(uint8_t i = 0; i < LED_BIN_COUNT; i++) {
    if(i%3 == 0) {
      buf[i] = G ;
    } else if(i%3 == 1) {
      buf[i] = R ;
    } else if(i%3 == 2) {
      buf[i] = B ;
    }
  }
  write(buf);//向芯片发送数据，12个引脚，每个16bit，共208bit
}

void DFRobot_MY9221SS::autoColorChange(void)//所有RGB灯自动改变颜色
{
  uint16_t  buf[LED_BIN_COUNT];
  uint16_t R = 0xff; 
  uint16_t G = 0xff; 
  uint16_t B = 0xff; 
  uint8_t r = (rand()%255);
  for(uint8_t i = 0; i < LED_BIN_COUNT; i++) {
    if(i%3 == 0) {
      buf[i] = G / (r - 150) ;
    } else if(i%3 == 1) {
      buf[i] = R / (r - 80) ;
    } else if(i%3 == 2) {
      buf[i] = B / (r - 0) ;
    }
  }
  write(buf);//向芯片发送数据，12个引脚，每个16bit，共208bit
}

