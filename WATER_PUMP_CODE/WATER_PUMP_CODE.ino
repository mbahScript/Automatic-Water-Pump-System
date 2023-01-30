#include <LiquidCrystal.h>
#define rs 5
#define en 4
#define d4 3
#define d5 2
#define d6 1
#define d7 0
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int buzzer = 8;
int error_led = 10; //red led
int blue_led = 13; //lvl 1 led...
int green_led = 12; //lvl 2 led...or full indicator.
//int on_led = 6; //orange.
int well_check = A4;
int lvl_1 = A3;
int lvl_2 = A2;
int trigger = 7;
int reference = 100;
int level_1;
int level_2;
int dry_check;

byte line1[8] = 
{ 0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111 
};
byte line2[8] = 
{ 0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111 
};
byte line3[8] = 
{ 0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111 
};
byte line4[8] = 
{ 0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111 
};
byte line5[8] = 
{ 0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111 
};
byte line6[8] = 
{ 0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111 
};
byte line7[8] = 
{ 0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111 
};
byte line8[8] = 
{ 0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111 
};

void setup() {
  // put your setup code here, to run once:
pinMode(rs,OUTPUT);
pinMode(en,OUTPUT);
pinMode(d4,OUTPUT);
pinMode(d5,OUTPUT);
pinMode(d6,OUTPUT);
pinMode(d7,OUTPUT);
pinMode(trigger,OUTPUT);
pinMode(buzzer,OUTPUT);
pinMode(error_led,OUTPUT);
pinMode(blue_led,OUTPUT);
pinMode(green_led,OUTPUT);
//pinMode(on_led,OUTPUT);
pinMode(lvl_1,INPUT);
pinMode(lvl_2,INPUT);
pinMode(well_check,INPUT);

lcd.createChar(1, line1);
lcd.createChar(2, line2);
lcd.createChar(3, line3);
lcd.createChar(4, line4);
lcd.createChar(5, line5);
lcd.createChar(6, line6);
lcd.createChar(7, line7);
lcd.createChar(8, line8);
lcd.begin(16,2);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("SAM-TECHNOLOGIES");
lcd.setCursor(0,1);
lcd.print("Initializing... ");
delay(1000);
lcd.clear();
lcd.print("AUTOMATIC  WATER");
lcd.setCursor(0,1);
lcd.print(" PUMPING SYSTEM ");
//digitalWrite(on_led,HIGH);
delay(300);
lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
level_1 = analogRead(lvl_1);
level_2 = analogRead(lvl_2);
dry_check = analogRead(well_check);

if((dry_check < reference)&&(level_1 < reference)&&(level_2 < reference)){
  digitalWrite(trigger,LOW);
  lcd.setCursor(0,0);
  lcd.print("SUMP TANK EMPTY!");
  lcd.setCursor(0,1);
  lcd.print("LOW");
  lcd.setCursor(12,1);
  lcd.print("HIGH");
  lcd.setCursor(3,1);
  lcd.print("         ");
  dry_well();
  digitalWrite(green_led,LOW);
  digitalWrite(blue_led,LOW);
}else if((dry_check > reference)&&(level_1 < reference)&&(level_2 < reference)){
  digitalWrite(trigger,HIGH);
  lcd.setCursor(0,0);
  lcd.print("AUTO WATER PUMP ");
  lcd.setCursor(0,1);
  lcd.print("Water Pumping...");
  digitalWrite(error_led,LOW);
  digitalWrite(buzzer,LOW);
  digitalWrite(green_led,LOW);
  digitalWrite(blue_led,LOW);
}else{
  if((level_2 > reference)&&(level_1 < reference)&&(dry_check < reference)){
    show_error();
    digitalWrite(trigger,LOW);
    digitalWrite(green_led,LOW);
    digitalWrite(blue_led,LOW);
    lcd.setCursor(0,0);
    lcd.print("SUMP TANK EMPTY!");
    lcd.setCursor(0,1);
    lcd.print("Error Detected! ");
  }else if((level_2 > reference)&&(level_1 < reference)&&(dry_check > reference)){
    error();
    digitalWrite(trigger,HIGH);
    digitalWrite(green_led,LOW);
    digitalWrite(blue_led,LOW);
    lcd.setCursor(0,0);
    lcd.print("WATER LVL METER ");
    lcd.setCursor(0,1);
    lcd.print("Error Detected! ");
  }else{
    if((level_2 > reference)&&(dry_check < reference)){
      digitalWrite(trigger,LOW);
      digitalWrite(error_led,LOW);
      digitalWrite(buzzer,LOW);
      digitalWrite(green_led,HIGH);
      digitalWrite(blue_led,HIGH);
      lcd.setCursor(0,0);
      lcd.print("SUMP TANK EMPTY!");
      lcd.setCursor(0,1);
      lcd.print("LOW");
      lcd.setCursor(12,1);
      lcd.print("HIGH");
      lcd.setCursor(3,1);
      lcd.write(byte(1));
      lcd.setCursor(4,1);
      lcd.write(byte(2));
      lcd.setCursor(5,1);
      lcd.write(byte(3));
      lcd.setCursor(6,1);
      lcd.write(byte(4));
      lcd.setCursor(7,1);
      lcd.write(byte(4));
      lcd.setCursor(8,1);
      lcd.write(byte(5));
      lcd.setCursor(9,1);
      lcd.write(byte(6));
      lcd.setCursor(10,1);
      lcd.write(byte(7));
      lcd.setCursor(11,1);
      lcd.write(byte(8));
    }else if(level_2 > reference){
      digitalWrite(trigger,LOW);
      digitalWrite(error_led,LOW);
      digitalWrite(buzzer,LOW);
      digitalWrite(green_led,HIGH);
      digitalWrite(blue_led,HIGH);
      lcd.setCursor(0,0);
      lcd.print("WATER LVL METER ");
      lcd.setCursor(0,1);
      lcd.print("LOW");
      lcd.setCursor(12,1);
      lcd.print("HIGH");
      lcd.setCursor(3,1);
      lcd.write(byte(1));
      lcd.setCursor(4,1);
      lcd.write(byte(2));
      lcd.setCursor(5,1);
      lcd.write(byte(3));
      lcd.setCursor(6,1);
      lcd.write(byte(4));
      lcd.setCursor(7,1);
      lcd.write(byte(4));
      lcd.setCursor(8,1);
      lcd.write(byte(5));
      lcd.setCursor(9,1);
      lcd.write(byte(6));
      lcd.setCursor(10,1);
      lcd.write(byte(7));
      lcd.setCursor(11,1);
      lcd.write(byte(8));
    }else if((level_1 > reference)&&(dry_check < reference)){
      dry_well();
      digitalWrite(trigger,LOW);
      digitalWrite(green_led,LOW);
      digitalWrite(blue_led,HIGH);
      lcd.setCursor(0,0);
      lcd.print("SUMP TANK EMPTY!");
      lcd.setCursor(0,1);
      lcd.print("LOW");
      lcd.setCursor(12,1);
      lcd.print("HIGH");
      lcd.setCursor(3,1);
      lcd.write(1);
      lcd.setCursor(4,1);
      lcd.write(2);
      lcd.setCursor(5,1);
      lcd.write(3);
      lcd.write(4);
      lcd.setCursor(7,1);
      lcd.print("     ");
    }else{
      digitalWrite(trigger,HIGH);
      digitalWrite(error_led,LOW);
      digitalWrite(buzzer,LOW);
      digitalWrite(green_led,LOW);
      digitalWrite(blue_led,HIGH);
      lcd.setCursor(0,0);
      lcd.print("WATER LVL METER ");
      lcd.setCursor(0,1);
      lcd.print("LOW");
      lcd.setCursor(12,1);
      lcd.print("HIGH");
      lcd.setCursor(3,1);
      lcd.write(1);
      lcd.setCursor(4,1);
      lcd.write(2);
      lcd.setCursor(5,1);
      lcd.print("  ");
      lcd.setCursor(5,1);
      lcd.write(3);
      lcd.write(4);
      lcd.setCursor(5,1);
      lcd.print("  ");
      lcd.setCursor(5,1);
      lcd.write(3);
      lcd.write(4);
      lcd.setCursor(7,1);
      lcd.print("     ");
    }
  }
}
delay(100);
}

void show_error(){
  digitalWrite(trigger,LOW);
  digitalWrite(buzzer,HIGH);
  digitalWrite(error_led,LOW);
  delay(50);
  digitalWrite(buzzer,LOW);
  digitalWrite(error_led,HIGH);
}

void dry_well(){
  digitalWrite(trigger,LOW);
  digitalWrite(buzzer,HIGH);
  digitalWrite(error_led,LOW);
  delay(100);
  digitalWrite(buzzer,LOW);
  digitalWrite(error_led,HIGH);
}

void error(){
  digitalWrite(buzzer,HIGH);
  digitalWrite(error_led,LOW);
  delay(50);
  digitalWrite(buzzer,LOW);
  digitalWrite(error_led,HIGH);
}
