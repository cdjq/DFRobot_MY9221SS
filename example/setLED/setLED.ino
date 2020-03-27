#include <DFRobot_LedDriver.h>

//自定义通信引脚
/*FireBeetle-M0*/
#if defined ARDUINO_SAM_ZERO
#define D  7
#define C  5
/*ESP32 and ESPLED_FULL_BRIGHTNESS266*/
#elif defined(ESP32) || defined(ESPLED_FULL_BRIGHTNESS266)
#define D  D3
#define C  D4
/*AVR系列主板*/
#else
#define D  2
#define C  3
#endif

DFRobot_LedDriver rgbdriver(C, D); 

/*
 *可供用户选择的宏定义颜色
 *COLOR_RGB565_BLACK   COLOR_RGB565_NAVY    COLOR_RGB565_DGREEN   COLOR_RGB565_DCYAN 
 *COLOR_RGB565_MAROON  COLOR_RGB565_PURPLE  COLOR_RGB565_OLIVE    COLOR_RGB565_LGRAY
 *COLOR_RGB565_DGRAY   COLOR_RGB565_BLUE    COLOR_RGB565_GREEN    COLOR_RGB565_CYAN  
 *COLOR_RGB565_RED     COLOR_RGB565_MAGENTA COLOR_RGB565_YELLOW   COLOR_RGB565_WHITE  
 */
void setup() {
  Serial.begin(115200);
}

void loop() {
  /**
   * @brief 设置所有灯的RGB颜色，这里设置为白色
   * @param R 设置RGB红色分量，硬件应连接引脚B
   * @param G 设置RGB绿色分量，硬件应连接引脚C
   * @param B 设置RGB蓝色分量，硬件应连接引脚A
  */
  rgbdriver.setAllLed(/*R=*/LED_FULL_BRIGHTNESS,/*G=*/LED_FULL_BRIGHTNESS,/*B=*/LED_FULL_BRIGHTNESS);
  delay(1000);

  //灯由暗变亮
  for(uint8_t brightness = 0; brightness <= 250; brightness+=5)
  {
  rgbdriver.setLed(/*ledNo=*/4,/*color=*/COLOR_RGB565_RED,/*brightness=*/brightness);
  delay(100);
  }
  
  //循环显示颜色，亮度最小为8
  while(1){
    rgbdriver.setLed(/*ledNo=*/4,/*color=*/COLOR_RGB565_GREEN,/*brightness=*/8);
    delay(1000);
    rgbdriver.setLed(/*ledNo=*/4,/*color=*/COLOR_RGB565_RED,/*brightness=*/8);
    delay(1000);
    rgbdriver.setLed(/*ledNo=*/4,/*color=*/COLOR_RGB565_BLUE,/*brightness=*/8);
    delay(1000);
  }
  delay(5000);
}
