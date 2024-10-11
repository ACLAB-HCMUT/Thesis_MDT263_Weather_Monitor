//#include "../src/Headers/TaskLCD.h"
//
//LiquidCrystal_I2C lcd(0x21, 16, 2);
//
//void LCD_Display(void *pvParameters)
//{
//    lcd.setCursor(0, 0);
//    lcd.println(String(temperature));
//
//    lcd.setCursor(0, 1);
//    lcd.println(String(humidity));
//}
//
//void LCD_init ()
//{
//    Wire.begin(11, 12); // SDA = GPIO 11, SCL = GPIO 12
//    lcd.init();
//    lcd.backlight();
//    xTaskCreate(LCD_Display,"LCD_Display", 4096, NULL, 1, NULL);
//}