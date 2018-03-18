#include <dht.h>
#include <LiquidCrystal.h>

// HUMIDITY/TEMPERATURE SENSOR
#define DHT_PIN 7

// WARNING LED
#define LED_PIN 8

// LCD DISPLAY
#define LCD_WIDTH 16
#define LCD_HEIGHT 2

#define RS_PIN 12
#define ENABLE_PIN 11
#define D4_PIN 5
#define D5_PIN 4
#define D6_PIN 3
#define D7_PIN 2

LiquidCrystal lcd(RS_PIN, ENABLE_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);
dht DHT;

// COMMON
#define LOWEST_HUMIDITY_THRESHOLD 45
#define HIGHEST_HUMIDITY_THRESHOLD 60

int temperature = 0, humidity = 0;

void setup() {
  Serial.begin(9600);

  welcomeMessage();

  pinMode(DHT_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void welcomeMessage() {
  lcd.begin(LCD_WIDTH, LCD_HEIGHT);
  String welcomeMessage = "Humidity/Temperature + LED";
  lcd.print(welcomeMessage);

  for (int positionCounter = 0; positionCounter < welcomeMessage.length(); positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(150);
  }

  lcd.clear();
}

void indicateHumidityLevel() {
  digitalWrite(LED_PIN, LOW);
  if (humidity < LOWEST_HUMIDITY_THRESHOLD || humidity > HIGHEST_HUMIDITY_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);
  }
}

void displayToLcd() {
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");
}

void loop() {
  DHT.read11(DHT_PIN);

  temperature = DHT.temperature;
  humidity = DHT.humidity;

  indicateHumidityLevel();

  displayToLcd();

  delay(3000);

}

