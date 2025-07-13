#include <LiquidCrystal.h>

// Pin Definitions
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
const int analogChannel1 = 0;
const int analogChannel2 = 1;
#define BUZZER_PIN 8
#define RELAY_PIN 9

// Sensor Parameters
const int sensitivity1 = 100;
const int sensitivity2 = 100;
const int offsetVoltage1 = 2500;
const int offsetVoltage2 = 2500;

// Variables
float adcValue1 = 0;
float adcValue2 = 0;
double voltage1 = 0;
double voltage2 = 0;
double current1 = 0;
double current2 = 0;
double differentialCurrent = 0;

void setup() {
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(RELAY_PIN, OUTPUT);
    lcd.begin(16, 2);

    lcd.setCursor(0, 0);
    lcd.print("Power Theft");
    lcd.setCursor(0, 1);
    lcd.print("   Detection");
    delay(2000);
    lcd.clear();
}

void loop() {
    unsigned int temp1 = 0;
    unsigned int temp2 = 0;
    float maxPoint1 = 0;
    float maxPoint2 = 0;

    // Read analog values and determine the maximum
    for (int i = 0; i < 500; i++) {
        temp1 = analogRead(analogChannel1);
        if (temp1 > maxPoint1) {
            maxPoint1 = temp1;
        }

        temp2 = analogRead(analogChannel2);
        if (temp2 > maxPoint2) {
            maxPoint2 = temp2;
        }
    }

    // Convert analog values to voltage
    adcValue1 = maxPoint1;
    voltage1 = (adcValue1 / 1024.0) * 5000;
    current1 = ((voltage1 - offsetVoltage1) / sensitivity1) / sqrt(2);

    adcValue2 = maxPoint2;
    voltage2 = (adcValue2 / 1024.0) * 5000;
    current2 = ((voltage2 - offsetVoltage2) / sensitivity2) / sqrt(2);

    // Calculate differential current
    differentialCurrent = voltage1 - voltage2;

    // Check for power theft
    if (differentialCurrent >= 50) {
        lcd.clear();
        delay(100);
        lcd.setCursor(0, 0);
        lcd.print(" POWER THEFT !!");
        lcd.setCursor(0, 1);
        lcd.print(" -Disconnected-");
        
        while (true) {
            digitalWrite(RELAY_PIN, HIGH);
            digitalWrite(BUZZER_PIN, HIGH);
            delay(1500);
            digitalWrite(BUZZER_PIN, LOW);
            delay(1000);
        }
    }

    // Display current readings and differential voltage
    lcd.setCursor(0, 0);
    lcd.print("I1=");
    lcd.print(current1, 2);
    lcd.print(" I2=");
    lcd.print(current2, 2);
    lcd.print("A");

    lcd.setCursor(0, 1);
    lcd.print("Vd=");
    lcd.print(differentialCurrent);

    delay(2500);
}
