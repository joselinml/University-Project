#include <FirebaseESP32.h>
#include <WiFi.h>

#define WIFI_SSID "Totalplay-2.4G-6458"
#define WIFI_PASSWORD "W4hBncjktjwzWXSQ"

#define FIREBASE_HOST "https://sensortemp-9c59a-default-rtdb.firebaseio.com/" 
#define FIREBASE_AUTH "AIzaSyB2lJ9U_lItr5kZheDnUTFVqAhQLqqHL84"
const int potPin= 34;
float ph;
float Value = 0;



FirebaseData firebaseData;


void setup() // Esta es una función especial en Arduino que se ejecuta una vez al iniciar el programa.
{ 
  delay(1000);
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado a WiFi");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
 pinMode(potPin,INPUT);
  Serial.begin(9600);  // 
  delay (1000);
} 

void loop() // Esta es otra función especial en Arduino que se ejecuta en un bucle continuo después de la función setup().
{ 
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
   delay(500);
} 
