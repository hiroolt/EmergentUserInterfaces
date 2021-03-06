// CS-E4200 Emergent UI sample code
// Created by Hiroki Sunagawa
// Description: The code aims for Arduino Uno with pressure sensor, accelerometer, and gyro sensor.
// The output is something like this.
//     Pressure sensor: touched / not touched
//     Accelerometer(Movement): moving / not moving
//     Gyro sensor (Position): 0 / 1 / 2 / 3 / 4 / 5 <= These are corresponding to something like dice
// The output format is "Bool(pressure), Bool(movement), Int(position)", for example, "1, 0, 5"


// This library allows you to communicate with I2C / TWI devices.
#include<Wire.h>
#include<Tone.h>

//setup variables for accelerometer and gyro sensor
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,GyX,GyY,GyZ;
int16_t AcX_ = 0;
int16_t AcY_ = 0;
int16_t AcZ_ = 0;

// setup variables for pressure sensor
int fsrAnalogPin = 0; // FSR is connected to analog 0

// setup variables for the output
bool mov;
int pos = 1;

// setup Tone object
Tone tone1;
Tone tone2;
Tone tone3;

void setup(){
// Accelerometer setup
  I2C_Mode_Setup();
  tone1.begin(13);
  tone2.begin(12); 
  
  Serial.begin(9600);

}



// Main function

void loop(){

  Serial.print(READ_Pressure());
  Serial.print(", ");
  Serial.print(READ_Accelerometor());
  Serial.print(", ");
  Serial.println(READ_Gyro());

  int val = READ_Gyro();
  
  if ((READ_Pressure() == true) && (READ_Accelerometor() == false))
  {
    switch(val) {
      case 1:
        tone1.play(NOTE_B3, 300);
        tone2.play(NOTE_B4, 300);
        break;
      case 2:
        tone1.play(NOTE_A3, 300);
        tone2.play(NOTE_A4, 300);
        break;
      case 3:
        tone1.play(NOTE_C3, 300);
        tone2.play(NOTE_C4, 300);
        break;
      case 4:
        tone1.play(NOTE_D3, 300);
        tone2.play(NOTE_D4, 300);
        break;
      case 5:
        tone1.play(NOTE_E3, 300);
        tone2.play(NOTE_E4, 300);
        break;
      case 6:
        tone1.play(NOTE_F3, 300);
        tone2.play(NOTE_F4, 300);
        break;
      default:
        break;
    }
  } 
  else if ((READ_Pressure() == true) && (READ_Accelerometor() == true))
  {
    switch(val) {
      case 1:
        for(int x = 0; x < 20; x++){
        tone1.play(NOTE_B3, 30);
        tone2.play(NOTE_B4, 30);
        delay(30);
        }
        break;
      case 2:
        for(int x = 0; x < 20; x++){
        tone1.play(NOTE_A3, 30);
        tone2.play(NOTE_A4, 30);
        delay(30);
        }
        break;
      case 3:
        for(int x = 0; x < 20; x++){
        tone1.play(NOTE_C3, 30);
        tone2.play(NOTE_C4, 30);
        delay(30);
        }
        break;
      case 4:
        for(int x = 0; x < 20; x++){
        tone1.play(NOTE_D3, 30);
        tone2.play(NOTE_D4, 30);
        delay(30);
        }
        break;
      case 5:
        for(int x = 0; x < 20; x++){
        tone1.play(NOTE_E3, 30);
        tone2.play(NOTE_E4, 30);
        delay(30);
        }
        break;
      case 6:
        for(int x = 0; x < 20; x++){
        tone1.play(NOTE_F3, 30);
        tone2.play(NOTE_F4, 30);
        delay(30);
        }
        break;
      default:
        break;
    }
  }
  
  delay(100);
}



// I2C Mode setup for accelerometer

void I2C_Mode_Setup()
{
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

// A function to read pressure sensor value
bool READ_Pressure()
{
  int fsrReading;      // the analog reading from the FSR resistor divider
  fsrReading = analogRead(fsrAnalogPin);
  if (fsrReading > 50)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// A function to read accelerometer value
bool READ_Accelerometor()
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  
  if ((AcX > AcX_ + 2000) || (AcX < AcX_ - 2000) || (AcY > AcY_ + 2000) || (AcY < AcY_ - 2000) || (AcZ > AcZ_ + 2000) || (AcZ < AcZ_ - 2000))
  {
    mov = true;
  }
  else
  {
    mov =  false;
  }
  AcX_ = AcX;
  AcY_ = AcY;
  AcZ_ = AcZ;
  
  return mov;
}

// A function to read gyro sensor value
int READ_Gyro()
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  //Serial.print(", GyX: "); Serial.print(GyX);
  //Serial.print(", GyY: "); Serial.print(GyY);
  //Serial.print(", GyZ: "); Serial.println(GyZ);
  if(GyX < -15000)
  {
    pos = 1;
  }
  else if (GyX > 15000)
  {
    pos = 2;
  }
  else if (GyY < -15000)
  {
    pos = 3;
  }
  else if (GyY > 15000)
  {
    pos = 4;
  }
  else if (GyZ < -15000)
  {
    pos = 5;
  }
  else if (GyZ > 15000)
  {
    pos = 6;
  }
  return pos;
}


