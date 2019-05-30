
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"
MPU6050 mpu;
uint8_t mpuIntStatus;
uint16_t packetSize;
uint16_t fifoCount;
uint8_t fifoBuffer[64];
Quaternion q;
VectorFloat gravity;
float ypr[3];
float y,p,r;
int pf,rf;
static int count;
volatile bool mpuInterrupt = false;
void dmpDataReady() {mpuInterrupt = true;}
int k[4]={8,9,10,11};
int i=0;

             void setup() {
  

   
    Wire.begin();
   
        
        TWBR = 24;
    mpu.initialize();
    mpu.dmpInitialize();
    mpu.setDMPEnabled(true);
    attachInterrupt(0, dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();
    packetSize = mpu.dmpGetFIFOPacketSize();


    Serial.begin(115200);
     for(i=0;i<4;++i)
       {
       pinMode(k[i],OUTPUT);
                    }

}


              void loop(){
count=0;
    while (!mpuInterrupt && fifoCount < packetSize) {






    }

  
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();
    fifoCount = mpu.getFIFOCount();
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        mpu.resetFIFO();
        //COMENTAR_OFICIAL
        Serial.println(F("FIFO overflow!"));
    }
    else if (mpuIntStatus & 0x02) {
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        fifoCount -= packetSize;
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
        
        //COMENTAR_OFICIAL
        if(count>100);
       { Serial.print("ypr\t");
        Serial.print(ypr[0]*180/M_PI);
        y=ypr[0]*180/M_PI;
        Serial.print("\t");
        Serial.print(ypr[1]*180/M_PI);
        p=ypr[1]*180/M_PI;
        Serial.print("\t");
        Serial.print(ypr[2]*180/M_PI);
        r=ypr[2]*180/M_PI;
        Serial.println();
        Serial.println("initializing the process for the rotor");
        if(-15<p&&p<15&&(r<-15||r>15))
        {Serial.println("left  right");
          //pf=1;
        //rf=0;
        
        if(r<0)                  //LEFT RIGHT CONTROL
        {Serial.println("left");
        
        digitalWrite(k[0],HIGH);
        digitalWrite(k[1],LOW);
        digitalWrite(k[2],LOW);
        digitalWrite(k[3],LOW);
        }
        else{
          Serial.println("right");
        digitalWrite(k[0],LOW);
        digitalWrite(k[1],HIGH);
        digitalWrite(k[2],LOW);
        digitalWrite(k[3],LOW);

        }
        
        }
          else if(-15<r&&r<15&&(p<-15||p>15))
          {//rf=1;
          //pf=0;
          Serial.println("front back");
          
             if(p<0)                  //front back  CONTROL
        {Serial.println("front ");
       digitalWrite(k[0],LOW);
        digitalWrite(k[1],LOW);
        digitalWrite(k[2],HIGH);
        digitalWrite(k[3],LOW);
        }
          
          else
          {Serial.println("back");
           digitalWrite(k[0],LOW);
        digitalWrite(k[1],LOW);
        digitalWrite(k[2],LOW);
        digitalWrite(k[3],HIGH);
        }
          
          }

            else if(-15<p&&p<15&&-15<r&&r<15)
          {//pf=1;
          //rf=1;
          {digitalWrite(k[0],LOW);
        digitalWrite(k[1],LOW);
        digitalWrite(k[2],LOW);
        digitalWrite(k[3],LOW);
        }
          
          
          
          }
          else
          {pf=0;
          rf=0;
          digitalWrite(k[0],LOW);
        digitalWrite(k[1],LOW);
        digitalWrite(k[2],LOW);
        digitalWrite(k[3],LOW);
          }

          
          
          
    }
    //delay(1000);

    }
}










