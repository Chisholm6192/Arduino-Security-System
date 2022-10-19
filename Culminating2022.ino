//Grade 12 Computer Engineering Culmianting Project
//January 31st 2022

#include <IRremote.h> //include infared remote library
#include <LiquidCrystal_I2C.h>  //include lcd sceen library
#include <Wire.h>

//defining integers for inputs
int trigPin = 13; 
int echoPin = 12; 
long duration; 
int distance; 
int buzzer = 3; 
int IR_RECEIVE_PIN = 2; 
IRrecv ir_receiver(IR_RECEIVE_PIN); 
LiquidCrystal_I2C lcd (0x27,20,4); //set dimensions for lcd screeb

void setup()
{
  //defining outputs
  lcd.init();
  lcd.backlight();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  IrReceiver.begin(IR_RECEIVE_PIN);
  pinMode(buzzer, OUTPUT);  
}


void loop()
{
  //loop for ultrasonic sensor to scan surroundings for distance
  digitalWrite(trigPin ,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  //create 'distance' interger
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034/2;
  Serial.println(distance); //print serial data from sensor

  
  if (distance < 150) //if sensor detects something less than 150 millameters away
  {
    digitalWrite(11, HIGH); //turn LED on
    lcd.setCursor(0,0);
    lcd.print("security breach");
    digitalWrite(buzzer, HIGH); //turn buzzer on
  }
  
   if (distance > 150)  //if sensor detects somethign but is greater than 150 millameters away
    {
      digitalWrite(11, LOW);  //turn LED off
      lcd.setCursor(0,0);
      lcd.println("armed           ");
      noTone(buzzer); //turn buzzer off
    }

    if(IrReceiver.decode()) //if the infared receiver detects a signal from the remote
    {
      digitalWrite(11,LOW); //turn LED off
      noTone(buzzer); //turn buzzer off
      lcd.setCursor(0,0);
      lcd.print("disarmed        ");
      delay(5000);
      lcd.setCursor(0,0);
      lcd.print("armed              ");
      lcd.setCursor(5,0);
      lcd.print("      ");
      IrReceiver.resume();  //continue loop
    }
}
    
 
