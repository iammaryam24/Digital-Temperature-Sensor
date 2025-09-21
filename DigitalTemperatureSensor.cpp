#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
#include <DHT.h> 

// Define I2C LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust if your LCD's address is different 

// Define DHT11 
#define DHTPIN 2       // Data pin connected to D2 
#define DHTTYPE DHT11  // DHT 11 

DHT dht(DHTPIN, DHTTYPE); 

void setup() { 
  // Initialize Serial Monitor 
  Serial.begin(9600); 
  
  // Initialize LCD 
  lcd.init();        // Initialize the LCD 
  lcd.backlight();   // Turn on the backlight 
  
  // Initialize DHT11 sensor 
  dht.begin(); 
  
  // Print a message to the LCD 
  lcd.setCursor(0, 0); 
  lcd.print("DHT11 Sensor"); 
  lcd.setCursor(0, 1); 
  lcd.print("Initializing..."); 
  delay(2000); 
  lcd.clear(); 
} 

void loop() { 
  // Read temperature and humidity 
  float humidity = dht.readHumidity(); 
  float temperature = dht.readTemperature(); 
  
  // Check if any reads failed 
  if (isnan(humidity) || isnan(temperature)) { 
    lcd.setCursor(0, 0); 
    lcd.print("Failed to read"); 
    lcd.setCursor(0, 1); 
    lcd.print("sensor data!"); 
    Serial.println("Failed to read from DHT sensor!"); 
    delay(2000); 
    return; 
  } 
  
  // Print temperature and humidity to the LCD 
  lcd.setCursor(0, 0); 
  lcd.print("Temp: "); 
  lcd.print(temperature); 
  lcd.print(" C"); 
  
  lcd.setCursor(0, 1); 
  lcd.print("Humidity: "); 
  lcd.print(humidity); 
  lcd.print(" %"); 
  
  // Print to Serial Monitor 
  Serial.print("Temperature: "); 
  Serial.print(temperature); 
  Serial.print(" *C, Humidity: "); 
  Serial.print(humidity); 
  Serial.println(" %"); 
  
  // Debug prints 
  Serial.print("Raw Temp Data: "); 
  Serial.println(temperature); 
  Serial.print("Raw Humidity Data: "); 
  Serial.println(humidity); 
  
  // Wait 5 seconds before next reading 
  delay(5000); 
} 
