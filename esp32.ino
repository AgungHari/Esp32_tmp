#include <WiFi.h>
#include <Arduino.h>

//WiFi Configuration
const char* ssid = "Agung-Ganteng-Banget";
const char* password = "123456789";

WiFiServer server(80);

//Motor pins
#define pwmpin1 5
#define dir1 18
#define dir2 19
#define pwmpin2 25
#define dir3 32
#define dir4 33

//PWM configuration
#define pwmChannel1 0
#define pwmChannel2 1
#define freq 15000
#define res 8

//Motor states and speed variables
int stdir[4];
int PWM1_DutyCycle = 0;
int maxspeed = 40;
int turnspeed = 40;

//Variable to track the last direction
String lastDirection = "";

void setup() {
  Serial.begin(115200);
  Serial.print("Setting AP (Access Point) ...");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("ESP32 AP IP Address : ");
  Serial.println(IP);

  server.begin();

  //Motor pin setup
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(dir3, OUTPUT);
  pinMode(dir4, OUTPUT);

  //PWM setup
  ledcSetup(pwmChannel1, freq, res);
  ledcSetup(pwmChannel2, freq, res);
  ledcAttachPin(pwmpin1, pwmChannel1);
  ledcAttachPin(pwmpin2, pwmChannel2);
}

void loop() {
  WiFiClient client = server.available();
  if(client){
    while(client.connected()){
      if(client.available()){
        String arah = client.readStringUntil('\n');
        // Compare the current direction with the last direction
        if(arah != lastDirection) {
          Serial.print("Arah : ");
          Serial.println(arah);
          lastDirection = arah; // Update the last direction to the current direction

        if(arah == "A"){
          while(PWM1_DutyCycle <= turnspeed){
            stdir[0] = LOW;
            stdir[1] = LOW;
            stdir[2] = HIGH;
            stdir[3] = LOW;

            digitalWrite(dir1, stdir[0]);
            digitalWrite(dir2, stdir[1]);
            digitalWrite(dir3, stdir[2]);
            digitalWrite(dir4, stdir[3]);
            ledcWrite(pwmChannel1, PWM1_DutyCycle++);
            ledcWrite(pwmChannel2, PWM1_DutyCycle++);
            delay(10);
          }
          Serial.println("Kiri");
        }
        else if(arah == "B"){
          while(PWM1_DutyCycle <= maxspeed){
            stdir[0] = HIGH;
            stdir[1] = LOW;
            stdir[2] = HIGH;
            stdir[3] = LOW;

            digitalWrite(dir1, stdir[0]);
            digitalWrite(dir2, stdir[1]);
            digitalWrite(dir3, stdir[2]);
            digitalWrite(dir4, stdir[3]);
            ledcWrite(pwmChannel1, PWM1_DutyCycle++);
            ledcWrite(pwmChannel2, PWM1_DutyCycle++);
            delay(10);
          }
          Serial.println("Maju");
        }
        else if(arah == "C"){
          while(PWM1_DutyCycle >= 0){
            digitalWrite(dir1, stdir[0]);
            digitalWrite(dir2, stdir[1]);
            digitalWrite(dir3, stdir[2]);
            digitalWrite(dir4, stdir[3]);
            ledcWrite(pwmChannel1, PWM1_DutyCycle--);
            ledcWrite(pwmChannel2, PWM1_DutyCycle--);
            delay(10);
          }
          Serial.println("Stop");
        }
        else if(arah == "D"){
          while(PWM1_DutyCycle <= turnspeed){
            stdir[0] = LOW;
            stdir[1] = HIGH;
            stdir[2] = LOW;
            stdir[3] = HIGH;

            digitalWrite(dir1, stdir[0]);
            digitalWrite(dir2, stdir[1]);
            digitalWrite(dir3, stdir[2]);
            digitalWrite(dir4, stdir[3]);
            ledcWrite(pwmChannel1, PWM1_DutyCycle++);
            ledcWrite(pwmChannel2, PWM1_DutyCycle++);
            delay(10);
          }
          Serial.println("Mundur");
        }
        else if(arah == "E"){
          while(PWM1_DutyCycle <= turnspeed){
            stdir[0] = HIGH;
            stdir[1] = LOW;
            stdir[2] = LOW;
            stdir[3] = LOW;

            digitalWrite(dir1, stdir[0]);
            digitalWrite(dir2, stdir[1]);
            digitalWrite(dir3, stdir[2]);
            digitalWrite(dir4, stdir[3]);
            ledcWrite(pwmChannel1, PWM1_DutyCycle++);
            ledcWrite(pwmChannel2, PWM1_DutyCycle++);
            delay(10);
          }
          Serial.println("Kanan");
        }
      }
    }
  }
}
}
