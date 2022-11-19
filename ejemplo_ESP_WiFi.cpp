#include <Arduino.h> // No incluyan esta librería es para usar arduino en vscode
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Estructura para guardar los elementos de la request de HTTP
struct ServerResponse 
{
  int HTTP_CODE = -1;
  String PAYLOAD = "__No Response From Server__";
};

// Nombre de la red WiFi y la contraseña
const char* ssid = "";
const char* pass = "";

// Dirección de nuestro servidor Ejemplo:     http://_nuestraIP_/api
 
// Esta dirección puede cambiar dependiendo de la ip que nos asigne el router
// o de como tengan configurado MAMP/XAMP y nuestro servidor así que revisen 
// que sea el mismo 
const char* host = "";

ServerResponse httpPOST(const String& JSON);
ServerResponse httpGET();

void setup() {
  Serial.begin(115200);
  
  // Pasos para conectarse a WiFi
  Serial.print("\nWifi connecting to: ");
  Serial.println(ssid);
  
  Serial.print("\nPassword: ");
  Serial.println(pass);         // Cosas inseguras xd
  
  WiFi.begin(ssid, pass);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected!!!");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());
}

void loop() {
  // Ejemplo de POST con una función que recibe una string con formato de json
  ServerResponse responsePOST = httpPOST("{\"api_key\":\"tPmAT5Ab3j7F9\",\"sensor\":\"BME280\",\"value1\":\"24.25\",\"value2\":\"49.54\",\"value3\":\"1005.14\"}");
  /* El formato es:
    "{
      "llave1":"valor1",
      "llave2":"valor2"
    }"
    
    En una sola línea y usando caracteres de escape para incluir las comillas en la cadena
    Cuando vayan a instertar los datos del sensor concatenen usando += si usan las strings de arduino
    o con std::stringstream y conviertan la string resultante a una string normal de c
    ej. con strings de arduino
      String unaString = "una string";
      unaString += "otra string o número la verdad no se";
      ...

    ej. con stringstream
      #include <string.h>
      #include <sstream>
      std::stringstream stream;
      stream << "una cadena";
      stream << 5;
      stream << "otra cadena" << 9;
      ...

      // La siguiente línea pasa lo que esté almacenado en el buffer a una string de c++ 
      // y luego la convierte a una de c, la cual si entiende arduino
      stream.str().c_str();  //-> const char* resultado = "una cadena5otra cadena9"
      // Ojalá se haya entendido bien xd
  */
  Serial.print("Message sent with response code: ");
  Serial.println(responsePOST.HTTP_CODE);
  Serial.print("Data returned from server: ");
  Serial.println(responsePOST.PAYLOAD);

  // Ejemplo de GET con una función que devuelve el código de http y los datos que regresa el servidor
  ServerResponse responseGET = httpGET();
  Serial.print("Message sent with response code: ");
  Serial.println(responseGET.HTTP_CODE);
  Serial.print("Data returned from server: ");
  Serial.println(responseGET.PAYLOAD);

  delay(2000);  // Cada 2 segundos 😺
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
