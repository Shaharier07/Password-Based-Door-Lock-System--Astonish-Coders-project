#include <ServoTimer2.h>
#include <VirtualWire.h>
#define buzzer 12
ServoTimer2 servo;
int a=1;
char pas [5]={'1','3','5','7','9'};
int t=0;
int count =0,b=0,c=0;
int pos=0;
int rows[4]={2,3,4,5};
int cols[3]= {8,9,10};
int ir,jc,scan;
char keypad [4][3]={{'*','0','#'},
                    {'7','8','9'},
                    {'4','5','6'},
                    {'1','2','3'}};

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzer,OUTPUT);
  servo.attach(11);
  pinMode(11,OUTPUT);
  //servo.write(pos);
  Serial.begin(9600);
  for(ir=0;ir<4;ir++)
      {
        pinMode(rows[ir],INPUT);
        digitalWrite(rows[ir],HIGH);
       }
   for(jc=0;jc<3;jc++)
     {
        pinMode(cols[jc],OUTPUT);
        digitalWrite(cols[jc],HIGH);
     }
    
    vw_set_rx_pin(13);
    vw_setup(2000);
    
    vw_rx_start();
  
  }
void loop() {
  // put your main code here, to run repeatedly:
  

  for(jc=0;jc<3;jc++)
  {
    digitalWrite(cols[jc],LOW);
    for(ir=0;ir<4;ir++)
    {
      scan=digitalRead(rows[ir]);
      if(scan==LOW)
      {
        Serial.println(keypad[ir][jc]);
        delay(500);
        if( keypad[ir][jc] == pas[t])
        {
          count++;
          t++;
          
          }        
          else
          {
            count=0;
            t=0;
          }
          b++;   
      }
      
    }
    digitalWrite(cols[jc],HIGH);
  }

  if( count == 5)
  {
    if(a%2==1)
    {
      Serial.println("Door Open ");
       servo.write(2250);
       delay(1000);
      a++;
    }
    else {
      Serial.println("Door Close ");
        servo.write(1500);
        delay(1000);
      a++;
    }
    
     t=0;
     count=0;
     b=0;
     c=0;
  }
  
  if(b==5)
  {
    Serial.println("Access Denied");
    t=0;
    count=0;
    b=0; 
    c++;  
  }
  
  if(c==3)
  {
    tone(buzzer,1000);
    delay(1000);
    noTone(buzzer);
    delay(1000);
    tone(buzzer,1000);
    delay(1000);
    noTone(buzzer);
    delay(1000);
    tone(buzzer,1000);
    delay(1000);
    noTone(buzzer);
    delay(1000);
    c=0;
  }

  uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN; 
 
    if (vw_get_message(buf, &buflen))
    {
      if(buf[0]=='a')
      {  
        Serial.println("Door Open ");
        servo.write(2250);
        delay(1000);
      }  
      else if(buf[0]=='b')
      {
        Serial.println("Door Close ");
        servo.write(1500);
        delay(1000);
      }
    }

}
