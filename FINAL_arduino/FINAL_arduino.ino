#include <TinyGPS.h>
#include <SoftwareSerial.h>

SoftwareSerial Gsm(7, 8);
char phone_no[] = "**********"; //replace with phone no. to get sms

int timesToSend=1;
int count=0;

int drowziness_pin=12;
int drowsiState=0;

TinyGPS gps;  //Creates a new instance of the TinyGPS object
 
void setup()
{
  Serial.begin(9600);
  pinMode(drowziness_pin, INPUT);
  pinMode(2, OUTPUT);
  Gsm.begin(9600);  
 
}
 
void loop()
{

  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
 
  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial.available())
    {
      char c = Serial.read();
      //Serial.print(c);
      if (gps.encode(c)) 
        newData = true;  
    }
  }

  drowsiState = digitalRead(drowziness_pin);
  Serial.print(drowsiState);
  if (newData==true && drowsiState==HIGH && count==0)      //If newData is true
  {
      float flat, flon;
      unsigned long age;
      gps.f_get_position(&flat, &flon, &age);   
      Gsm.print("AT+CMGF=1\r"); 
      delay(400);
      Gsm.print("AT+CMGS=\"");
      Gsm.print(phone_no);
      Gsm.println("\"");
      
      delay(300);
      Gsm.println("THE DRIVER IS DROWSY.");
      Gsm.print("https://www.google.com/maps/place/");
      
      Gsm.print("Lati tude = ");
      Gsm.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
      Gsm.print(" Longitude = ");
      Gsm.print(",");
      Gsm.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
      delay(200);
      Gsm.println((char)26);      // End AT command with a ^Z, ASCII code 26
      delay(200);
      Gsm.println();
      delay(20000);
      count++;

      
      //LED BLINKING
      while(drowsiState=HIGH)
        {
            digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
            delay(1000);                       // wait for a second
            digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
            delay(1000); 
        
        }
 
   }


   if (newData!=true && drowsiState==HIGH && count==0)      //If newData is not true
  {
      float flat, flon;
      unsigned long age;
      gps.f_get_position(&flat, &flon, &age);   
      Gsm.print("AT+CMGF=1\r"); 
      delay(400);
      Gsm.print("AT+CMGS=\"");
      Gsm.print(phone_no);
      Gsm.println("\"");
      
      delay(300);
      Gsm.println("THE DRIVER IS DROWSY.");
      delay(200);
      Gsm.println((char)26); // End AT command with a ^Z, ASCII code 26
      delay(200);
      Gsm.println();
      //delay(20000);
      count++;

      
      //LED BLINKING
      while(drowsiState=HIGH)
        {
            digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
            delay(1000);                       // wait for a second
            digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
            delay(1000); 
          
        }
 
   } 
              //Serial.println(failed);
             // if (chars == 0)
               // Serial.println("** No characters received from GPS: check wiring **");
   if (drowsiState==LOW && count>0)
   {
    count=0;
    
    }
}
