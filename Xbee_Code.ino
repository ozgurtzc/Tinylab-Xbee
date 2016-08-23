// coded by Özgür Tuzcu(@ozgurtzc)

#define RELAY_PIN A4
#include <LiquidTWI2.h>

LiquidTWI2 lcd(0x20);

byte relay_situation = 10;

int button1 = 9;
int button2 = 8;
int button1_amount = 0;
int button2_amount = 0;

void setup() 
{
  Serial1.begin(9600);
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);

  lcd.setMCPType(LTI_TYPE_MCP23008);
  lcd.begin(16, 2);
}

void loop() 
{
  if(Serial1.available())
  {
    relay_situation = Serial1.read();
    Serial.write(relay_situation);
  }

  if (relay_situation == 10)
  {
    lcd.setCursor(0, 0);
    lcd.print("Waiting for data");
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("from Xbee module");
    lcd.print("                ");
  }

  if (relay_situation == 255)
  {
    relay_situation = Serial1.read();
    Serial.write(relay_situation);

    lcd.setCursor(0, 0);
    lcd.print("Data came from");
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("Xbee module");
    lcd.print("                ");

    delay(2000);
    
    lcd.setCursor(0, 0);
    lcd.print("SWITCH ON");
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("Click S1 button");
    lcd.print("                ");

   
     while (relay_situation == 255) 
     {
        relay_situation = Serial1.read();
        Serial.write(relay_situation);
        
        button1_amount = digitalRead(button1);
        button2_amount = digitalRead(button2);
     
        if (button1_amount == LOW )
        {
        
        lcd.setBacklight(HIGH);
        lcd.setCursor(0, 0);
        lcd.print("Click S2 button");
        lcd.print("                ");
        lcd.setCursor(0, 1);
        lcd.print("ON");
        lcd.print("                ");
        digitalWrite(RELAY_PIN, HIGH);
        delay(10);
        }
      
     
        if (button2_amount == LOW) 
        {
        digitalWrite(RELAY_PIN, LOW);
        lcd.setCursor(0, 0);
        lcd.print("Click S1 button");
        lcd.print("                ");
        lcd.setCursor(0, 1);
        lcd.print("OFF");
        lcd.print("                ");
        delay(10);
        }
     }
  }

  if (relay_situation == 0)
  {
    digitalWrite(RELAY_PIN, LOW);
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print("SWITCH OFF");
    lcd.print("                ");
    delay(10);
  }
}
