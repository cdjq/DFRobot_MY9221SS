# DFRobot_MY9221SS  LED驱动库
DFRobot_MY9221SS是使用MY9221SS芯片的LED驱动库，芯片可承受最大输出电压17伏特以支持多颗LED串联，解决了现在很多交互场景需要用到灯带或LED均为12V，使用5V/3.3V类主控不能驱动的问题。该LED驱动可分别驱动4路大功率RGBLed，可级联   <br>

![正反面svg效果图](https://github.com/ouki-wang/DFRobot_Sensor/raw/master/resources/images/SEN0245svg1.png)


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

  DFRobot_DS3231M(TwoWire *pWire = &Wire){_pWire = pWire;};
  ~DFRobot_DS3231M();
  /*!
   *@brief Init chip 
   *@return True means IIC communication succeeds, false means it fails. 
   */
  bool begin(void);
  
  /*!
   *@brief get year of now in sensor
   *@return year
   */
  uint8_t getYear();
  
  /*!
   *@brief get month of now in sensor
   *@return month
   */
  uint8_t  getMonth();
  
  /*!
   *@brief get date of now in sensor
   *@return date
   */
  uint8_t  getDate();
  
  /*!
   *@brief get hour of now in sensor
   *@return hour
   */
  uint8_t  getHour();
  
  /*!
   *@brief get minute of now in sensor
   *@return minute
   */
  uint8_t  getMinute();
  
  /*!
   *@brief get second of now in sensor
   *@return second
   */
  uint8_t  getSecond();
  
  /*!
   *@brief get day of week
   *@return day of week
   */
  uint8_t  dayOfTheWeek() const ;
  
  /*!
   *@brief Set year + 2000
   *@param year (20 means 2020, -30 means 1970)
   */
  void setYear(uint8_t year);
  
  /*!
   *@brief Set month
   *@param month(1-12)
   */
  void setMonth(uint8_t month);
  
  /*!
   *@brief Set Date 
   *@param date(1-31)
   */
  void setDate(uint8_t date);
  
  /*!
   *@brief Set the hours and 12hours or 24hours
   *@param hour:1-12 in 12hours,0-23 in 24hours
   *@param mode:e24hours, eAM, ePM
   */
  void setHour(uint8_t hour, ehours mode);
  
  /*!
   *@brief Set minute 
   *@param Minute(0-60)
   */
  void setMinute(uint8_t minute);
  
  /*!
   *@brief Set second
   *@param Second(0-60)
   */
  void setSecond(uint8_t second);
  
  /*!
   *@brief Set the last compiled time as the current time 
   *@param date Input compiling  date 
   *@param time Input compiling time 
   */
  void dateTime(const __FlashStringHelper* date, const __FlashStringHelper* time);
  
  /*!
   *@brief 将设定好的时间写入rtc
   */
  void adjust();
  
  /*!
   *@brief output AM or PM of time 
   */
  const char* getAMorPM();
  
  /*!
   *@brief Get current temperature 
   *@return Current temperautre, unit: ℃ 
   */
  float getTemperatureC();
  
  /*!
   *@brief Get current temperature 
   *@return Current temperautre, unit: ℉ 
   */
  float getTemperatureF();
  
  /*!
   *@brief Judge if it is power-down 
   *@return If retrun true, power down, time needs to reset; false, work well. 
   */
  bool isLostPower(void);
  
  /*!
   *@brief Read the value of pin sqw
   *@return eDS3231M_OFF             = 0x01 // Off
   *@n      eDS3231M_SquareWave_1Hz  = 0x00 // 1Hz square wave
   *@n      eDS3231M_SquareWave_1kHz = 0x08 // 1kHz square wave
   *@n      eDS3231M_SquareWave_4kHz = 0x10 // 4kHz square wave
   *@n      eDS3231M_SquareWave_8kHz = 0x18 // 8kHz square wave
   */
  eDs3231MSqwPinMode_t readSqwPinMode();
  
  /*!
   *@brief Set the vaule of pin sqw
   *@param mode eDS3231M_OFF             = 0x01 // Off
   *@n          eDS3231M_SquareWave_1Hz  = 0x00 // 1Hz square wave
   *@n          eDS3231M_SquareWave_1kHz = 0x08 // 1kHz square wave
   *@n          eDS3231M_SquareWave_4kHz = 0x10 // 4kHz square wave
   *@n          eDS3231M_SquareWave_8kHz = 0x18 // 8kHz square wave
   */
  void writeSqwPinMode(eDs3231MSqwPinMode_t mode);
  
  /*!
   *@brief Set alarm clock
   *@param alarmType Alarm clock working mode typedef enum{
   *@n                                  eEverySecond,
   *@n                                  eSecondsMatch,
   *@n                                  eSecondsMinutesMatch,
   *@n                                  eSecondsMinutesHoursMatch,
   *@n                                  eSecondsMinutesHoursDateMatch,
   *@n                                  eSecondsMinutesHoursDayMatch, //Alarm1
   *@n                                  eEveryMinute,
   *@n                                  eMinutesMatch,
   *@n                                  eMinutesHoursMatch,
   *@n                                  eMinutesHoursDateMatch,
   *@n                                  eMinutesHoursDayMatch,        //Alarm2
   *@n                                  eUnknownAlarm
   *@n                                  }eAlarmTypes;
   *@param days    Alarm clock Day (day)
   *@param hours   Alarm clock Hour (hour)
   *@param mode:   e24hours, eAM, ePM
   *@param minutes Alarm clock (minute)
   *@param seconds Alarm clock (second)
   */
  void setAlarm(const uint8_t alarmType,int16_t days,int8_t hours,ehours mode,
                int8_t minutes,int8_t seconds, const bool state  = true);
  
  /*!
   *@brief Judge if the alarm clock is triggered 
   *@return true, triggered; false, not trigger
   */
  bool isAlarm();
  /*!
   *@brief Clear trigger flag
   */
  void clearAlarm();
  
  /*!
   *@brief enable or disable the interrupt of alarm 
   */
  void enAbleAlarm1Int();
  void disAbleAlarm1Int();
  void enAbleAlarm2Int();
  void disAbleAlarm2Int();
  
  /*!
   *@brief enable the 32k output 
   */
  void enAble32k();
  
  /*!
   *@brief disable the 32k output 
   */
  void disAble32k();
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

- Data 2019-8-19
- Version V0.1


## Credits

Written by(yufeng.luo@dfrobot.com), 2019. (Welcome to our [website](https://www.dfrobot.com/))





