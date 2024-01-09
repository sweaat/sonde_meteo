
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal_I2C.h>  // Ajout de l'inclusion de la bibliothèque LiquidCrystal_I2C

// Connection à l'API
const char *ssid = "Oppo-234z";
const char *password = "123456789";
const char *apiEndpoint = "http://192.168.252.119/apisite/post_meteo.php"; // Mettez l'adresse complète de l'API, y compris le protocole (http://)

Adafruit_BME280 bme;
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Adresse I2C, nombre de colonnes, nombre de lignes

void setup() {
  Serial.begin(9600);
  Serial.println("Debut du programme");

  Wire.begin(0, 2);

  if (!bme.begin(0x76)) {
    Serial.println("Impossible de trouver un capteur BME280, vérifiez votre câblage !");
    while (1);
  }

  // Initialisation de l'écran
  lcd.init(); // initialisation de l'afficheur

  // Efface l'écran
  lcd.clear();
  lcd.home();

  // Connexion au réseau WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au WiFi en cours...");
  }

  Serial.println("Connecté au réseau WiFi");
}

void loop() {
  Serial.println("Lecture du capteur BME280...");

  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;

  Serial.print("Température = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidité = ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Pression = ");
  Serial.print(pressure);
  Serial.println(" hPa");

  // Affichage sur l'écran LCD
  lcd.backlight(); // Allumer le rétroéclairage
  
  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(temperature);
  lcd.print("C");
  delay(2000);
  lcd.print("       ");

  
  lcd.setCursor(0, 0);
  lcd.print("H: ");
  lcd.print(humidity);
  lcd.print("%");
  delay(2000);
  lcd.print("       ");
  
  
  lcd.setCursor(0, 0);
  lcd.print("P: ");
  lcd.print(pressure);
  lcd.print("hPa");
  delay(2000);
  lcd.print("      ");
  lcd.clear();

  // Envoi des données à l'API
  sendSensorData(temperature, humidity, pressure);

  delay(2000); // Attendre 2 secondes entre les lectures
}

void sendSensorData(float temp, float hum, float pres) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient wifiClient; // Créer un objet WiFiClient

    // Préparez les données à envoyer
String data = "{\"temp\":" + String(temp) +
              ",\"hum\":" + String(hum) +
              ",\"pres\":" + String(pres) + "}";

    // Commencez la requête HTTP POST avec le client WiFi
    http.begin(wifiClient, apiEndpoint);
    http.addHeader("Content-Type", "application/json");

    // Envoyez les données
    int httpCode = http.POST(data);

    // Vérifiez le code de réponse
    if (httpCode > 0) {
      Serial.println("Données envoyées avec succès à l'API");
      Serial.print("Data to send: ");
      Serial.println(data);
      Serial.println(httpCode);
    } else {
      Serial.println("Erreur lors de l'envoi des données à l'API");
    }

    // Libérez les ressources de la requête HTTP
    http.end();
  } else {
    Serial.println("Erreur de connexion WiFi");
  }
}
