#include<stdlib.h>
#include<string.h>
#include<stdio.h>





int right[2]={6,7};
int left[2]={3,5};
int d[4]={8,9,10,11};
int k[4]={0,0,0,0};
int i,val=0,value=0;
String ch,chf,chT,chff;

void forward()
{Serial.println("forward");
analogWrite(right[0],255);
analogWrite(right[1],0);
analogWrite(left[0],255);
analogWrite(left[1],0);

}
void backward()
{Serial.println("backward");
analogWrite(right[0],0);
analogWrite(right[1],255);
analogWrite(left[0],0);
analogWrite(left[1],255);

}

void rightturn()
{Serial.println("rightturn");
analogWrite(right[0],80);
analogWrite(right[1],0);
analogWrite(left[0],0);
analogWrite(left[1],80);

}

void leftturn()
{Serial.println("leftturn");
analogWrite(right[0],0);
analogWrite(right[1],80);
analogWrite(left[0],80);
analogWrite(left[1],0);

}
void setup() 
{
Serial.begin(9600);
 for(i=0;i<4;++i)
 {
   if(i<2)
   {
   pinMode(right[i],OUTPUT);
   pinMode(left[i],OUTPUT);
   }
   pinMode(d[i],INPUT);
}
 
}



void loop() {
  
  for(i=0;i<4;++i)
  k[i]=digitalRead(d[i]);
  
 //for(i=0;i<4;++i)
 //Serial.println(k[i]);
 //delay(1000);}
 //Serial.println("end");

if( k[0]==0 && k[1]==0 && k[2]==1 && k[3]==0 )
forward();

else if( k[0]==0 && k[1]==0 && k[2]==0 && k[3]==1 )
backward();

else if( k[0]==1 && k[1]==0 && k[2]==0 && k[3]==0 )
leftturn();

else if( k[0]==0 && k[1]==1 && k[2]==0 && k[3]==0 )
rightturn();
else if( k[0]==0 && k[1]==0 && k[2]==0 && k[3]==0 )
{Serial.println("stop");
  analogWrite(right[0],0);
analogWrite(right[1],0);
analogWrite(left[0],0);
analogWrite(left[1],0);
  
}
}
