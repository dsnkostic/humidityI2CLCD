#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

#define HUMIDITYWARNING 3
#define TEMPERATUREWARNING 4

#define HUM_LOW_TH 30
#define HUM_HIGH_TH 60
#define TEMP_LOW_TH 20
#define TEMP_HIGH_TH 30

#define DEBUG false

boolean humWarning = false;
boolean tempWarning = false;

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(HUMIDITYWARNING, OUTPUT);
  pinMode(TEMPERATUREWARNING, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(HUMIDITYWARNING, LOW);
  digitalWrite(TEMPERATUREWARNING, LOW);
  
  lcd.init();
  lcd.backlight();

  dht.begin();

  debugSerial(); 
}

void debugSerial() 
{
  if (DEBUG)
  {
    Serial.begin(9600);
    Serial.println("DHT22 test");
  }
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  debugSensoryData(h, t);

  if (isnan(t) || isnan(h)) 
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Can't get reading");
    lcd.setCursor(0, 1);
    lcd.print("from DHT");
  } else {
    engageWarnings(h, t);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Humidity ");
    lcd.print(h, 1);
    lcd.print("%");
    if (humWarning)
    {
      lcd.setCursor(15, 0);
      lcd.print("!");
    }
    lcd.setCursor(0, 1);
    lcd.print("Temperat.");
    lcd.print(t, 1);
    lcd.print("C");        
    if (tempWarning)
    {
      lcd.setCursor(15, 1);
      lcd.print("!");
    }
  }
  delay(1000);
}

void engageWarnings(float h, float t)
{
  if (!humWarning && (h < HUM_LOW_TH || h > HUM_HIGH_TH))
  {
    digitalWrite(HUMIDITYWARNING, HIGH);
    humWarning = true;
  }
  if (humWarning && (h > HUM_LOW_TH && h < HUM_HIGH_TH))
  {
    digitalWrite(HUMIDITYWARNING, LOW);
    humWarning = false;
  }

  if (!tempWarning && (t < TEMP_LOW_TH || t > TEMP_HIGH_TH))
  {
    digitalWrite(TEMPERATUREWARNING, HIGH);
    tempWarning = true;
  }
  if (tempWarning && (t > TEMP_LOW_TH && t < TEMP_HIGH_TH))
  {
    digitalWrite(TEMPERATUREWARNING, LOW);
    tempWarning = false;
  }
        
  debugWarningData();
}

void debugWarningData()
{
  if (DEBUG)
  {
    if (humWarning)
      Serial.println("Humidity alert is ON!");
    if (tempWarning)
      Serial.println("Temperature alert is ON!");
  }
}

void debugSensoryData(float h, float t) 
{
  if (DEBUG)
  {
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
  
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    Serial.println();
  }
}
