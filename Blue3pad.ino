  #include <BleConnectionStatus.h>
  #include <BleGamepad.h>
  #include <BleGamepadConfiguration.h>
  
  #include <Wire.h>  // For I2C communication
  
  
  // Constants
  #define ADXL345_ADDRESS 0x53  // I2C address for accelerometer
  #define ADXL345_POWER_CTL 0x2D  // Power control register
  #define ADXL345_DATA_FORMAT 0x31  // Data format register
  #define ADXL345_DATAX0 0x32  // X-axis data register
  #define THRESHOLD 75  // Movement threshold for accelerometer
  #define X_BUTTON 23         // A
  #define CIRCLE_BUTTON 22    // B
  #define TRIANGLE_BUTTON 21  // Y
  #define SQUARE_BUTTON 19    // X
  
  // ADC pin for joystick
  const int joystickPin = 0;  // Adjust based on your ESP32 pin configuration
  
  // Variables to hold ADXL345 values
  int16_t xAccel, yAccel, zAccel;
  float xG, yG, zG;
  
  BleGamepad bleGamepad;
  // Initialize I2C for ADXL345 accelerometer
  void initADXL345() {
    Wire.begin(1,2);
    Wire.beginTransmission(ADXL345_ADDRESS);
    Wire.write(ADXL345_POWER_CTL);
    Wire.write(0x08);  // Enable measurement mode
    Wire.endTransmission();
  
    Wire.beginTransmission(ADXL345_ADDRESS);
    Wire.write(ADXL345_DATA_FORMAT);
    Wire.write(0x0B);  // Full resolution, +/- 16g
    Wire.endTransmission();
  }
  
  // Read acceleration data from ADXL345
  void readAccelData() {
    Wire.beginTransmission(ADXL345_ADDRESS);
    Wire.write(ADXL345_DATAX0);
    Wire.endTransmission(false);
    Wire.requestFrom(ADXL345_ADDRESS, 6);
  
    if (Wire.available() == 6) {
      xAccel = Wire.read() | (Wire.read() << 8);
      yAccel = Wire.read() | (Wire.read() << 8);
      zAccel = Wire.read() | (Wire.read() << 8);
    }
  
    // Convert to g values
    xG = xAccel * 0.0039;
    yG = yAccel * 0.0039;
    zG = zAccel * 0.0039;
  }
  
  void setup() {
    Serial.begin(115200);
    initADXL345();
    bleGamepad.begin();
  }
  
  void loop() {
    // Read joystick ADC value
    if (bleGamepad.isConnected()){
    int x = analogRead(joystickPin);
    int aaa = 0;int bbb = 0;int ccc = 0;int ddd = 0;
    
    if (x > 180 && x < 230)      {Serial.println("1");aaa = 1;bleGamepad.press(BUTTON_1);delay(75);bleGamepad.release(BUTTON_1);} 
    else if (x > 250 && x < 300) {Serial.println("2");bbb = 1;bleGamepad.press(BUTTON_2);delay(75);bleGamepad.release(BUTTON_2);} 
    else if (x > 360 && x < 450) {Serial.println("3");ccc = 1;bleGamepad.press(BUTTON_3);delay(75);bleGamepad.release(BUTTON_3);} 
    else if (x > 600)            {Serial.println("4");ddd = 1;bleGamepad.press(BUTTON_4);delay(75);bleGamepad.release(BUTTON_4);}
  
    readAccelData();
    int xxx = 1;
    int yyy = 1;
    if (abs(xAccel) > THRESHOLD) {if (xAccel > 0) {xxx = 2;} else if (xAccel < 0) {xxx = 0;}} else {xxx = 1;}
    if (abs(yAccel) > THRESHOLD) {if (yAccel > 0) {yyy = 2;} else if (yAccel < 0) {yyy = 0;}} else {yyy = 1;}
    /*
    if (aaa == 1){bleGamepad.press(X_BUTTON);}
    if (bbb == 1){bleGamepad.press(CIRCLE_BUTTON);}
    if (ccc == 1){bleGamepad.press(TRIANGLE_BUTTON);}
    if (ddd == 1){bleGamepad.press(SQUARE_BUTTON);}
    */
    if (xxx == 1 && yyy == 1){bleGamepad.setHat1(HAT_CENTERED);}
    if (xxx == 0){bleGamepad.setHat1(HAT_LEFT );}
    if (xxx == 2){bleGamepad.setHat1(HAT_RIGHT);}
    if (yyy == 0){bleGamepad.setHat1(HAT_DOWN );}
    if (yyy == 2){bleGamepad.setHat1(HAT_UP);} 
  //else {bleGamepad.release(BUTTON_23);bleGamepad.release(BUTTON_22);bleGamepad.release(BUTTON_21);bleGamepad.release(BUTTON_20);}
    delay(10);}}
