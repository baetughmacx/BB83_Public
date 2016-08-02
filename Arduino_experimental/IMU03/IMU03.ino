#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;

#define Gyr_Gain 0.00763358 

#define LED_PIN 13
bool blinkState = false;

float AccelX;
float AccelY;
float AccelZ;

float GyroX;
float GyroY;
float GyroZ;

float mixX;
float mixY;

float pitchAccel, rollAccel;

long previousMillis = 0;    // set up timers
unsigned long currentMillis;    
long interval = 20;        // time constant for timers

int dt=interval/1000;

void setup() {
  Wire.begin();
  accelgyro.initialize();
  pinMode(LED_PIN, OUTPUT);  
  Serial.begin(115200);
}

void loop() {

  currentMillis = millis();          // bookmark current time
  
  if (currentMillis - previousMillis >= interval)      // if the right amount of time has passed then...
      {
      previousMillis = currentMillis;                      // boomark the time again
    
      accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    
      AccelX = ax;
      AccelY = ay;
      AccelZ = az;
      GyroX = Gyr_Gain * (gx);
      GyroY = Gyr_Gain * (gy);
      GyroZ = Gyr_Gain * (gz);
    
      AccelY = (atan2(AccelY, AccelZ) * 180 / PI);
      AccelX = (atan2(AccelX, AccelZ) * 180 / PI);
    
      mixX = 0.98 *(mixX+GyroX*dt) + 0.02*AccelY;  
      mixY = 0.98 *(mixY+GyroY*dt) + 0.02*AccelX; 
     
       
      //Serial.print(AccelY);
      //Serial.print(" , ");
      //Serial.print(GyroX);
      //Serial.print(" , ");
            
      Serial.print(mixY, 4);
      Serial.print(",");
      Serial.print(mixX, 4);
      Serial.print('\n');

      // blink LED to indicate activity
      blinkState = !blinkState;
      digitalWrite(LED_PIN, blinkState);
    
      }
      


}








