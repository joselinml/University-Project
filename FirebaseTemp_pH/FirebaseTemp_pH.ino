#include <FirebaseESP32.h> 
#include <WiFi.h>
//Include para el sensor de temperatura
#include <OneWire.h>
#include <DallasTemperature.h> 
//Fin de include para el sensor de temperatura

#define WIFI_SSID "**********" // red Wi-Fi
#define WIFI_PASSWORD "***************"  //Password de wi-fi

#define FIREBASE_HOST "**************************" //Host/url de la base de datos
#define FIREBASE_AUTH "************************"  /llave o key de la base de datos

//Declaraciones para el sensor de pH
const int potPin= 34;
float ph;
float Value = 0;
//Fin de las declaraciones

//Declaraciones para el sensor de temperatura
#define ONE_WIRE_BUS 5

OneWire ourWire(ONE_WIRE_BUS);
DallasTemperature sensors(&ourWire);
//Fin de declaraciones 

FirebaseData firebaseData;

void setup() {
  delay(1000);
  Serial.begin(9600);
  //Begin para el sensor de temperatura
  sensors.begin();
  //Fin del begin
  
  //La conexión al Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado a WiFi");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

//Llamado Al sensor de pH
  pinMode(potPin,INPUT);
  Serial.begin(9600);  // 
  delay (1000);
  //Fin del llamado
}


void loop() {
  //Captura de datos del sensor de temperatura para la conexión de Firebase
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
  //Fin de la captura


//Captura de datos del sensor de pH para la conexión de Firebase
  Value = analogRead(potPin);
  float voltage = Value*(3.3/4095.0);
  ph=(3.3*voltage);
 Serial.print("pH =   ");
 Serial.print(ph);

   if (Firebase.setFloat(firebaseData, "/pH", ph)) {
    Serial.println("Datos enviados a Firebase correctamente");
  } else {
    Serial.println("Error al enviar datos a Firebase");
    Serial.println(firebaseData.errorReason());
  }
   delay(60000);
}
