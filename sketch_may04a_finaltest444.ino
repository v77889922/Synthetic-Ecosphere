/* 
Stepper Motor Control - one revolution 

This program drives a unipolar or bipolar stepper motor. 
The motor is attached to digital pins 8 - 11 of the Arduino. 

The motor should revolve one revolution in one direction, then 
one revolution in the other direction. 


Created 11 Mar. 2007 
Modified 30 Nov. 2009 
by Tom Igoe 

*/ 

#include <Stepper.h> 
#include <LiquidCrystal.h>
#include <DHT.h>

const int stepsPerRevolution = 200; // change this to fit the number of steps per revolution 
// for your motor 

// initialize the stepper library on pins 8 through 11: 
Stepper myStepper(stepsPerRevolution, 31, 32, 33, 34); 


String buf; 
char c; 
int flower0=6; 
int flower1=2; 
int flower2=7; 
int flower3=5; 
int flower4=53; 
int flower5=47; 
int flower6=38; 


// ### LCD ###
// set the DHT Pin
#define DHTPIN 28
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int buttonPin = 29;
int lcdPin = 30;
int buttonState = 0;         // variable for reading the pushbutton status
int stage;
int isTrigger = 0;  
int lcdWord = 0;
float h;
float f;

//initialize the library with the numbers of the interface pins
LiquidCrystal lcd(27, 26, 25, 24, 23, 22);
// ### LCD ###

// ### LED ###
//int ledPin0 = 0;
//int ledPin1 = 1;
//int ledPin2 = 2;
int ledPin3 = 3;
int ledPin4 = 4;
//int ledPin5 = 5;
//int ledPin6 = 6;
//int ledPin7 = 7;
int ledPin8 = 8;
int ledPin9 = 9;
int ledPin10 = 10;
int ledPin11 = 11;
int ledPin12 = 12;
int ledPin13 = 13;
// ### LED ###

byte rbuf[2];


void setup() { 

  // ### LCD ###
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);

  dht.begin();

  //button
  int stage = 0; 
  pinMode(buttonPin,INPUT);
  pinMode(lcdPin, OUTPUT);
  //digitalWrite(lcdPin,LOW);

  //led & flower0~4
  for(int i=2;i<=13;i++){
    pinMode(i, OUTPUT);
  }

  //led
  for(int i=2;i<5;i++){
    pinMode(i, OUTPUT);
  }
 
  // Print a message to the LCD.
  lcd.print("Temp:  Humidity:");
  // ### LCD ###

  //flower
  //pinMode(flower0,OUTPUT); 
  //pinMode(flower1,OUTPUT); 
  //pinMode(flower2,OUTPUT); 
  //pinMode(flower3,OUTPUT); 
  pinMode(flower4,OUTPUT); 
  pinMode(flower5,OUTPUT);
  pinMode(flower6,OUTPUT); 

  myStepper.setSpeed(60); 
  // initialize the serial port: 
  Serial.begin(9600); 
} 

void loop() { 
  isTrigger = 0;
  byte rbuf[2];
  delayWithLcdWork(500);
  while (Serial.available() > 0) { 
    //if(Serial.readBytes(rbuf, 1) == "o"){
    if(1){  Serial.read(); 
//      digitalWrite(ledPin4 ,HIGH); 
      processMessage();
    }
  } 
} 

void processMessage() { 
  Serial.println("processMessage"); 
  isTrigger = 1;
  //if (buf.equals("on")) { 
  if(1){
    lcdWord = random(5);

    //0.005"wire 
    digitalWrite(flower0,HIGH); 
    digitalWrite(flower1,HIGH); 
    digitalWrite(flower2,HIGH); 

    //delay(2500); 
    delayWithLcdWork(2500);
    digitalWrite(flower0,LOW); 
    digitalWrite(flower1,LOW); 
    digitalWrite(flower2,LOW); 

    //delay(10000); 
    //delayWithLcdWork(10000);

    for(int i=0;i<2;i++){ 
      // step one revolution in one direction: 
      Serial.println("clockwise"); 
      myStepper.step(stepsPerRevolution); 
      //delay(500); 
      delayWithLcdWork(500);

      // step one revolution in the other direction: 
      Serial.println("counterclockwise"); 
      myStepper.step(-stepsPerRevolution); 
      //delay(500); 
      delayWithLcdWork(500);
    } 

    //delayWithLcdWork(500);

    //0.005"wire 
    digitalWrite(flower3,HIGH); 
    digitalWrite(flower4,HIGH); 
    digitalWrite(flower5,HIGH);
//     digitalWrite(flower6,OUTPUT); 

    //delay(2500); 
    delayWithLcdWork(2500);
    digitalWrite(flower3,LOW); 
    digitalWrite(flower4,LOW); 
    digitalWrite(flower5,LOW); 

    delayWithLcdWork(8000);

  } 
}

// ### LCD ###
void delayWithLcdWork(int time){
  while(time>0){
    buttonState = digitalRead(buttonPin);
    // read humidity
    h = dht.readHumidity();
    //read temperature in Fahrenheit
    f = dht.readTemperature(true);
  
    if (buttonState == HIGH && stage == 0) {    
      stage = 1;
      //delay(500);
      delayWithLED(500);
    } else if(buttonState == HIGH && stage == 1) {
      digitalWrite(lcdPin,LOW); // Hides the LCD cursor 
      stage = 0;
      //delay(500);
      delayWithLED(500);
    } else {
      //delay(500);
      delayWithLED(500);
    }

    if(buttonState == LOW && stage == 1) {
      LCD();   
    }
    time-=500;
  }
}

void LCD(){  
  //delay(500);
  digitalWrite(lcdPin,HIGH);
  if(isTrigger==0){
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    //digitalWrite(lcdPin,HIGH);
    lcd.print("Temp:  Humidity:");
    lcd.setCursor(0, 1);
    if (isnan(h) || isnan(f)) {
      lcd.print("ERROR");
      return;
    }

    lcd.print(f);
    lcd.setCursor(7,1);
    lcd.print(h);
  }else{
    //lcdWord = random(5);
    switch(lcdWord){
      case 0:
        lcd.print("synesthesia");
        lcd.setCursor(0, 4);
        lcd.print("mm");
        break;
      case 1:
        lcd.print("plant is comming");
        lcd.setCursor(0, 4);
        lcd.print("mm");
        break;
      case 2:
        lcd.print("hello plant");
        lcd.setCursor(0, 4);
        lcd.print("mm");
        break;
      case 3:
        lcd.print("synthetic");
        lcd.setCursor(0, 4);
        lcd.print("mm");
        break;
      case 4:
        lcd.print("you");
        lcd.setCursor(0, 4);
        lcd.print("mm");
        break;
      case 5:
        lcd.print("You again");
        lcd.setCursor(0, 4);
        lcd.print("mm");
        break;
      default:
        lcd.print("666");
    }
  }
}


// ### LED ###
void delayWithLED(int time){
  while(time>0){

    if(isTrigger){
      //analogWrite(ledPin3, random(120)+135);
      analogWrite(ledPin3, random(255));
      analogWrite(ledPin4, random(255));
      analogWrite(ledPin8, random(255));
      analogWrite(ledPin9, random(255));
      analogWrite(ledPin10, random(255));
      analogWrite(ledPin11, random(255));
      analogWrite(ledPin12, random(255));
      analogWrite(ledPin13, random(255));
    }

    delay(100);
    time-=100;
  }
}
// ### LED ###
/* 
Stepper Motor Control - one revolution 

This program drives a unipolar or bipolar stepper motor. 
The motor is attached to digital pins 8 - 11 of the Arduino. 

The motor should revolve one revolution in one direction, then 
one revolution in the other direction. 


Created 11 Mar. 2007 
Modified 30 Nov. 2009 
by Tom Igoe 

*/ 


