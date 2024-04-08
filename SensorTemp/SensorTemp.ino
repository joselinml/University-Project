
#include <FirebaseESP32.h>
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>




#define WIFI_SSID "Tu red de wifi"
#define WIFI_PASSWORD "tu contraseña"

#define FIREBASE_HOST "Host de firebase" 
#define FIREBASE_AUTH "La Key/llave de tu base de datos"

#define ONE_WIRE_BUS 5

OneWire ourWire(ONE_WIRE_BUS);
DallasTemperature sensors(&ourWire);

FirebaseData firebaseData;


void setup() {
  delay(1000);
  Serial.begin(9600);
  sensors.begin();
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado a WiFi");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);

  Serial.print("Temperatura =  ");
  Serial.print(temp);
  Serial.println(" °C");

  if (Firebase.setFloat(firebaseData, "/temperatura", temp)) {
    Serial.println("Datos enviados a Firebase correctamente");
  } else {
    Serial.println("Error al enviar datos a Firebase");
    Serial.println(firebaseData.errorReason());
  }

  delay(60000); // Envía datos cada 1 minuto
}
