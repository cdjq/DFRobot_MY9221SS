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

DFRobot_MY9221SS::DFRobot_MY9221SS(uint32_t pinClock, uint32_t pinData)
  :_pinData(pinData),
   _pinClock(pinClock)
{

}
void DFRobot_MY9221SS::begin(void)//初始化
{
  pinMode(_pinClock, OUTPUT);
  pinMode(_pinData, OUTPUT);
  //设置模式
  switchMode();
}
void DFRobot_MY9221SS::sendcmd(uint16_t bits)//发送16位CMD命令
{
  for (uint8_t i = 0, clk = 1; i < 16; i++)
  {
    digitalWrite(_pinData, bits & 0x8000 ? HIGH : LOW);//数据发送
    digitalWrite(_pinClock, clk);//时钟上升沿下降沿，数据有效
    clk = 1-clk;
    bits <<= 1;
  }
}
void DFRobot_MY9221SS::senddata(uint16_t bits)//每次调用发送16位数据
{
  for (uint8_t i = 0, clk = 1; i < 16; i++)
  {
    digitalWrite(_pinData, bits & 0x8000 ? HIGH : LOW);//数据发送
    digitalWrite(_pinClock, clk);//时钟上升沿下降沿，数据有效
    clk = 1-clk;
    bits <<= 1;
  }
}

void DFRobot_MY9221SS::switchMode(void)//模式设置
{
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

void DFRobot_MY9221SS::latch()//内部栓锁的控制
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

void DFRobot_MY9221SS::send(uint16_t* buf)//向芯片发送所有数据
{
  sendcmd(_mode); //发送命令，选择模式
  for (uint8_t i = 0; i < 12; i++)//发送灰阶数据，从A3引脚的buf开始发
  {
    senddata(buf[i]);
  }
  latch();//锁存
  return;
}