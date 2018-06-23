/*
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 * 
 * ------------------------------------------------------------------------------------------
 * The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 6
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 */
 
#include <SPI.h>
#include <Servo.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
 
#define SS_PIN 53
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int pos=0;
float temp;
int tempPinLivingRoom = 0;
int tempPinBedRoom = 1;
int tempPinMasterBedRoom = 2;
float temp1;
float temp2;
float avg_Temp;
Servo myservo;
const int rs = 12, en = 11, d4 = 6, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() 
{
  lcd.begin(16, 2);
  lcd.print("Scan your RFID                                   ");
  myservo.attach(9);
  pinMode(13,OUTPUT);
  pinMode(44,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);
  pinMode(24,OUTPUT);
  
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  
  

}

void loop() 
{
  temp = analogRead(tempPinLivingRoom);
  temp = temp * 0.48828125;
  
  if(temp > 25){
    delay(200);
    analogWrite(44,255);
    Serial.println("Living Room Temperature Elevated beyond 29C."); 
  }
  else{
    delay(200);
    digitalWrite(22,LOW);
  }
  temp1 = analogRead(tempPinBedRoom);
  temp1 = temp1 * 0.48828125;
  if(temp1 > 25){
    delay(200);
    analogWrite(44,255);
    Serial.println("Bedroom Temperature Elevated beyond 29C."); 
  }
  else{
    delay(200);
    digitalWrite(23,LOW);
  }
  temp2 = analogRead(tempPinMasterBedRoom);
  temp2 = temp2 * 0.48828125;
  
  if(temp2 > 25){
    delay(200);
    analogWrite(44,255);
    Serial.println("Master Bedroom Temperature Elevated beyond 29C."); 
  }
  else{
    delay(200);
    digitalWrite(24,LOW);
  }
  avg_Temp = (temp + temp1 + temp2)/3.0;
  lcd.setCursor(0, 1);
  lcd.print("Temp C = ");
  lcd.setCursor(8,1);
  lcd.print(28.0057);
  lcd.setCursor(15,1);
  lcd.print("              ");
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  
  //Show UID on serial monitor
  //Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     //Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  //Serial.println();
  //Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "FB 32 25 83") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Priyanshu's RFID");
    //Serial.println();
    lcd.setCursor(0, 1);
    lcd.print("Authorized Access");
    
    digitalWrite(13,HIGH);
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.print("Welcome home    ");
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.println("Priyanshu Sinha ");
    
    for (pos = 90; pos <= 180
    ; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
       
    }
    
    
    delay(5000);
    digitalWrite(13,LOW);
    lcd.setCursor(0, 1);
    lcd.print("Door is Closing"); 
    
    for (pos = 180; pos >= 90; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);    
    }
    lcd.setCursor(0, 1);
    lcd.print("                     ");
  }
  else if (content.substring(1) == "11 68 E1 2E") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Mastercard Scanned");
    //Serial.println();
    lcd.setCursor(0, 1);
    lcd.print("Authorized Access");
    digitalWrite(13,HIGH);
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.print("Welcome home    ");
    delay(1000);
    
    for (pos = 90; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
       
    }
    lcd.setCursor(0, 1);
    lcd.println("Mrs. K Shreedevi");
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.println("MASTER KEY USED ");
    
    
    
    delay(5000);
    digitalWrite(13,LOW);
    lcd.setCursor(0, 1);
    lcd.print("Door is Closing"); 
    
    for (pos = 180; pos >= 90; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);    
    }
    lcd.setCursor(0, 1);
    lcd.print("                     ");
  }
 else if (content.substring(1) == "D5 0B 6F 01") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Saurav's RFID");
    //Serial.println();
    lcd.setCursor(0, 1);
    lcd.print("Authorized Access");
    digitalWrite(13,HIGH);
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.print("Welcome home    ");
    
    for (pos = 90; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
       
    }
    lcd.setCursor(0, 1);
    lcd.println("Saurav Shaurya  ");
    
    delay(5000);
    digitalWrite(13,LOW);
    lcd.setCursor(0, 1);
    lcd.print("Door is Closing"); 
    
    for (pos = 180; pos >= 90; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);    
    }
    lcd.setCursor(0, 1);
    lcd.print("                     ");
  }
  else if (content.substring(1) == "02 53 88 01") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Abhishek's RFID");
    //Serial.println();
    lcd.setCursor(0, 1);
    lcd.print("Authorized Access");
    digitalWrite(13,HIGH);
    
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.print("Welcome home    ");
    
    for (pos = 90; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
       
    }
    lcd.setCursor(0, 1);
    lcd.println("Abhishek Sinha  ");
    
    delay(5000);
    digitalWrite(13,LOW);
    lcd.setCursor(0, 1);
    lcd.print("Door is Closing"); 
    
    for (pos = 180; pos >= 90; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);    
    }
    lcd.setCursor(0, 1);
    lcd.print("                     ");
  }
  else if (content.substring(1) == "F2 1F D5 64") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Purusottam's RFID");
    //Serial.println();
    lcd.setCursor(0, 1);
    lcd.print("Authorized Access");
    digitalWrite(13,HIGH);
    
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.print("Welcome home    ");
    
    for (pos = 90; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
       
    }
    lcd.setCursor(0, 1);
    lcd.println("Purusottam Singh  ");
    
    delay(5000);
    digitalWrite(13,LOW);
    lcd.setCursor(0, 1);
    lcd.print("Door is Closing"); 
    
    for (pos = 180; pos >= 90; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);    
    }
    lcd.setCursor(0, 1);
    lcd.print("                     ");
  }
 else{
    Serial.println("Access denied");
    lcd.setCursor(0, 1);
    lcd.print("Access Denied   ");
    digitalWrite(8,HIGH);
    
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.print("Try Again                        ");
    delay(2000);
    digitalWrite(8,LOW);
    lcd.setCursor(0, 1);
    lcd.print("                      ");
    
  }
  
delay(1000);  
} 
