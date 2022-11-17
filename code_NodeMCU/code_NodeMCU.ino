/*
#include <ESP8266WiFi.h>
const char* ssid = "EnGenius27EDCC";
const char* password = "ZYB3VBAF8PF2";
*/
int valor;
int estado = 0;   
int gro;
int led = 12;   // the pin that the LED is atteched to
int sensor = 5; // 
int state = LOW;             // by default, no motion detected
int val = 0; 

// LED pin
void setup() {
  pinMode(2, OUTPUT);
  pinMode(0, INPUT);
  pinMode(4, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(sensor, INPUT);

  Serial.begin(1200);
/*
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");    
  }
  
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Mac Address: ");
  Serial.println(WiFi.macAddress());
*/
}

void loop() {

  digitalWrite(2, LOW); // D4 internal LED
  digitalWrite(16, LOW); // Pin D0 in ESP if connected to WiFi
  digitalWrite(15, LOW); // Pin D8 LED if not connected to WiFi
  delay(600);

  digitalWrite(2, HIGH);
  
  /*
  if(WiFi.status() == WL_CONNECTED){
    digitalWrite(16, HIGH);
    delay(600);
  }
  else{
    digitalWrite(15, HIGH);
    delay(600);
  }

  gro = analogRead(A0);
  Serial.println(gro);
  digitalWrite(4, estado); 
  valor = digitalRead(0);
  if (valor == HIGH){
    digitalWrite(4, !estado); 
  }
*/
  //===============================
  //@sensor
  //
  //===============================
  val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(led, HIGH);   // turn LED ON
    delay(100);                // delay 100 milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
    }
  } 
  else {
      digitalWrite(led, LOW); // turn LED OFF
      delay(200);             // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }
  } 
}
