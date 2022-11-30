
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
const char* ssid = "COM-818";
const char* password = "";

const char* host = "http://192.168.10.100/api";

String data;
String preview;

int valor;
int estado = 0;   
int gro;
int led = 12;   // the pin that the LED is atteched to
int sensor = 5; // 
int state = LOW;             // by default, no motion detected
int val = 0; 
int push = 13;
int led2 = 14;
int value = 0;

// Estructura para guardar los elementos de la request de HTTP
struct ServerResponse 
{
  int HTTP_CODE = -1;
  String PAYLOAD = "__No Response From Server__";
};
ServerResponse httpPOST(const String& JSON);
ServerResponse httpGET();


// LED pin
void setup() {
  pinMode(2, OUTPUT);
  pinMode(0, INPUT);
  pinMode(4, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(sensor, INPUT);
  pinMode(push, INPUT);
  pinMode(led2, OUTPUT);

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

  digitalWrite(2, LOW); // D4 internal LED
  digitalWrite(16, LOW); // Pin D0 in ESP if connected to WiFi
  digitalWrite(15, LOW); // Pin D8 LED if not connected to WiFi
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
  //Serial.println(gro);
  digitalWrite(4, estado); 
  valor = digitalRead(0);
  if (valor == HIGH){
    digitalWrite(4, !estado); 
  }

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
      
  value = digitalRead(push);
  if (value == HIGH) {
    digitalWrite(led2, !estado);
  }
  else {
    digitalWrite(led2, estado);
  }

  preview = data;
  if (val == HIGH && valor == HIGH && value == HIGH){
    data = "{\"salon_id\":\"3101\",\"estado\":\"1\",\"luz\":\"1\"}";
  }
  else if (val == HIGH && valor == HIGH && value == LOW){
    data = "{\"salon_id\":\"3101\",\"estado\":\"1\",\"luz\":\"0\"}";
  }
  else if (value == HIGH && (val == LOW || valor == LOW)){
    data = "{\"salon_id\":\"3101\",\"estado\":\"0\",\"luz\":\"1\"}";   
  }
  else{
    data = "{\"salon_id\":\"3101\",\"estado\":\"0\",\"luz\":\"0\"}";    
  }

  ServerResponse respuesta;
  respuesta = httpPOST(data);
  Serial.println(respuesta.PAYLOAD); 
  Serial.println(respuesta.HTTP_CODE);

  delay(15000);         
  


}

/*
  Función que toma una string con formato de JSON y la envia a la url que definimos arriba
  hace un POST de http y regresa lo que envió el servidor.
  Si el código de respuesta es -1 entondes la request no se envió.

  @param const String& JSON
  @return ServerResponse
*/
ServerResponse httpPOST(const String& JSON) 
{
  ServerResponse response;
  if(WiFi.status() == WL_CONNECTED)
  {
    WiFiClient client;
    HTTPClient http;  
    http.begin(client, host);
    http.addHeader("Content-Type", "application/json");

    response.HTTP_CODE = http.POST(JSON);

    if(response.HTTP_CODE > 0)
      response.PAYLOAD = http.getString();
    else
      Serial.println("Error al enviar el mensaje");

    http.end();
  }
  return response;
}

/*
  Función que hace un GET de http y regresa lo que envió el servidor.
  Si el código de respuesta es -1 entondes la request no se envió.

  @return ServerResponse
*/
ServerResponse httpGET()
{
  ServerResponse response;
  if (WiFi.status() == WL_CONNECTED) 
  {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, host);

    response.HTTP_CODE = http.GET();

    if(response.HTTP_CODE > 0)
      response.PAYLOAD = http.getString();
    else
      Serial.println("Error al enviar el mensaje");

    http.end();
  }
  return response;

}

