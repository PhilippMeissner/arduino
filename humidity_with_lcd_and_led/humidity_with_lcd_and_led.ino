#include <dht.h>
#include <LiquidCrystal.h>

#define DHT_PIN 7
#define LED_PIN 8

#define LCD_WIDTH 16
#define LCD_HEIGHT 2

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
dht DHT;

int old_temperature, new_temperature, old_humidity, new_humidity;

void setup() {
  Serial.begin(9600);

  welcomeMessage();

  pinMode(DHT_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void welcomeMessage() {
  lcd.begin(LCD_WIDTH, LCD_HEIGHT);
  String welcomeMessage = "Humidity/Temperature warning sensor";
  lcd.print(welcomeMessage);

  for (int positionCounter = 0; positionCounter < welcomeMessage.length(); positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(150);
  }

  lcd.clear();
}


bool sensorValuesChanged() {
  return (new_temperature != old_temperature || new_humidity != old_humidity);
}


void indicateHumidityLevel() {
  digitalWrite(LED_PIN, LOW);
  if (new_humidity < 45 || new_humidity > 60) {
    digitalWrite(LED_PIN, HIGH);
  }
}

void serialOutput() {
  old_temperature = new_temperature;
  old_humidity = new_humidity;

  Serial.print("Temperature: ");
  Serial.print(new_temperature);
  Serial.print("\t\t");
  Serial.print("Humidity: ");
  Serial.println(new_humidity);

  indicateHumidityLevel();
}

void displayToLcd() {
  lcd.setCursor(0,0); 
  lcd.print("Temp: ");
  lcd.print(new_temperature);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(new_humidity);
  lcd.print("%");
}

void loop() {
  DHT.read11(DHT_PIN);

  new_temperature = DHT.temperature;
  new_humidity = DHT.humidity;

  if (sensorValuesChanged()) {
    serialOutput();
  }

  displayToLcd();  

  delay(3000);

}

