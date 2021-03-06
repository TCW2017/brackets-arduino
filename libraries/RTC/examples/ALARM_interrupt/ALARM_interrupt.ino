/*****************************************************************************************************************************************************************************
* This sketch demonstrate how to use alarm in interrupt mode.
This mode is more conveniently because you use processor for other tasks and when alarm match occurs interrupt routine is executed.
In this way, alarm flag checking is indipendent from main program flow.
******************************************************************************************************************************************************************************/


#include <RTCInt.h>

RTCInt rtc;

void setup() 
{
  Serial.begin(9600);       //serial communication initializing
  pinMode(13,OUTPUT);
  rtc.begin(TIME_H24);      //RTC initializing with 24 hour representation mode
  rtc.setTime(17,0,5,0);    //setting time (hour minute and second)
  rtc.setDate(13,8,15);     //setting date
  rtc.enableAlarm(SEC,ALARM_INTERRUPT,alarm_int); //enabling alarm in polled mode and match on second
  rtc.local_time.hour=17;
  rtc.local_time.minute=5;
  rtc.local_time.second=10;  //setting second to match
  rtc.setAlarm();  //write second in alarm register
}

void loop()
{
  digitalWrite(13,HIGH);   //main program code
  delay(100);
  digitalWrite(13,LOW);
  delay(900);
  
}


/*************** Interrupt routine for alarm ******************************/
void alarm_int(void)
{
  Serial.println("Alarm match!");
    for(int i=0; i < 10; i++)
    {
      digitalWrite(13,HIGH);
      //delay(200);
      for(int j=0; j < 1000000; j++) asm("NOP");  //in interrupt routine you cannot use delay function then an alternative is NOP instruction cicled many time as you need
      digitalWrite(13,LOW);
      //delay(800);
      for(int j=0; j < 2000000; j++) asm("NOP");
    }
    RTC->MODE2.INTFLAG.bit.ALARM0=1; //clearing alarm0 flag
}    
