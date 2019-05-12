#include <Wire.h>
#include <MPU6050.h>
#include <OneButton.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2); // RX, TX

#define xres 1366
#define yres 768

OneButton button1(A0, true);
OneButton button2(A1, true);

MPU6050 mpu;

// Timers
unsigned long timer = 0;
float timeStep = 0.1;

// Pitch, Roll and Yaw values
int pitch = 0;
int roll=0;
int yaw = 0;
int m_pitch=0;
int m_yaw=0;

const int uint_sw=A7;

const int mode_sw=A3;

String lc="N",rc="N",uc,data;

void setup() 
{
  Serial.begin(9600);
  mySerial.begin(9600); 
  
  button1.attachClick(click1);
  button1.attachDoubleClick(doubleclick1);
  button1.attachLongPressStart(longPressStart1);
  button1.attachLongPressStop(longPressStop1);
  button1.attachDuringLongPress(longPress1);

  button2.attachClick(click2);
  button2.attachDoubleClick(doubleclick2);
  button2.attachLongPressStart(longPressStart2);
  button2.attachLongPressStop(longPressStop2);
  button2.attachDuringLongPress(longPress2);
  
  pinMode(mode_sw,INPUT_PULLUP);
  pinMode(uint_sw,INPUT);
  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    //Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  mpu.setThreshold(3);
}

void loop()
{
  timer = millis();
  lc="N";
  rc="N";
  button1.tick();
  button2.tick();
  
  // Read normalized values
  Vector norm = mpu.readNormalizeGyro();

  // Calculate Pitch, Roll and Yaw
  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;
  
  m_yaw=map(yaw,30,-25,0,xres);
  m_pitch=map(pitch,30,-25,0,yres);
  
  if(m_yaw<0)
  {
    m_yaw=0;
  }
  if(m_yaw>xres)
  {
    m_yaw=xres;
  }

  if(m_pitch<0)
  {
    m_pitch=0;
  }
  if(m_pitch>yres)
  {
    m_pitch=yres;
  }
  
  String p = String(m_pitch);
  String y = String(m_yaw);

  if(analogRead(uint_sw)>500)
  {
    uc="1";
  }
  else
  {
    uc="0";
  }
  
  String data = y + ',' + p + ',' + lc + ',' + rc + ',' + uc + ',';
  
  if (yaw > 30)
  {
    data += 'L';
  }
  else if (yaw < -20)
  {
    data += 'R';
  }

  else if (pitch > 30)
  {
    data += 'E';
  }
  else if (pitch < -20)
  {
    data += 'E';
  }

  else if (roll > 40)
  {
    data += 'B';
  }
  else if (roll < -30)
  {
    data += 'C';
  }
  else
  {
    data += 'N';
  }

  data += ',';
  
  if(analogRead(mode_sw)>500)
  {
    data += 'M';
  }
  else
  {
    data += 'P';
  }

  data += ',';
  data += '.';
 mySerial.println(data);
 // Serial.println(data);
  // Wait to full timeStep period
  delay((timeStep*1000) - (millis() - timer));
}

void click1() 
{
  lc="S";
}

void doubleclick1() 
{
  lc="D";
}

void longPressStart1() 
{
  lc="L";
}

void longPress1() 
{
  lc="L";
}

void longPressStop1() 
{
  lc="N";
}

void click2() 
{
  rc="S";
}

void doubleclick2() 
{
  rc="D";
}

void longPressStart2() 
{
  rc="L";
}

void longPress2() 
{
  rc="L";
}

void longPressStop2() 
{
  rc="N";
