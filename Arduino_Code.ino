#include<LiquidCrystal_I2C.h>
#define ph_sensor A1
#define turbidity A0

float ph_value , sensor_value = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  lcd.begin();
  Serial.begin(9600);
  lcd.backlight();
  lcd.clear();
}

void loop(){
  ph_value = analogRead(ph_sensor);
  float turbidity =analogRead(turbidity);
  turbidity = turbidity*(5.0/1024.0)*3;
  //volt = volt/100;
  
  sensor_value=(ph_value-200)/35;
  Serial.println(String(sensor_value, 2) + "," + String(turbidity, 2));

  lcd.clear();
  lcd.print("Ph:" + String(sensor_value, 2));
  lcd.setCursor(0, 1);
  lcd.print("Turbidity: " + String(turbidity, 2));
  delay(1000);
}
