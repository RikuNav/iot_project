#include <ESP8266WiFi.h>
const char* ssid = "EnGenius27EDCC";
const char* password = "ZYB3VBAF8PF2";

int valor;
int estado = 0;   
int gro;

// LED pin
void setup() {
  pinMode(2, OUTPUT);
  pinMode(0, INPUT);
  pinMode(4, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(15, OUTPUT);

  Serial.begin(1200);

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
}
void loop() {

  digitalWrite(2, LOW);
  digitalWrite(16, LOW);
  digitalWrite(15, LOW);
  delay(600);

  digitalWrite(2, HIGH);
  
  
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
}
