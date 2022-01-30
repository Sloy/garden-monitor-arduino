
/*

*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int MAX_HUMID = 1000;
const int MIN_HUMID = 200;
const int HUMID_PIN = A0;

const int PHOTORES_PIN = A1;
const int TMP_PIN = A2;

void setup() {
    Serial.begin(9600);
    Serial.println("Reading From the Sensor ...");
    lcd.begin(16, 2);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    int humidity = readHumidity();
    int light = readLight();
    float temperature = readTemp();
    printValues(humidity, light, temperature);
    blink();
    delay(1000);
}

void printValues(int humidity, int light, float temperature) {
    //Serial.println("Printing values: Humidity=" + humidity);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Agua ");
    lcd.print(humidity);
    lcd.print("% Luz ");
    lcd.print(light);
    lcd.print("% ");
    lcd.setCursor(0, 1);
    lcd.print("Temp ");
    lcd.print(temperature, 1);
    lcd.print((char)223);
    lcd.print("C");
}

/**
 * Returns the ground humidity value in percentage, from 0 (mid air) to 100 (submerged in water).
*/
int readHumidity() {
    int humidityValue = analogRead(HUMID_PIN);
    delay(5);
    Serial.println("");
    Serial.print("Humidity value: ");
    Serial.print(humidityValue);

    int percentage = 100 - map(humidityValue, 250, 1023, 0, 100);
    return percentage;
}

int readLight() {
    int lightValue = analogRead(PHOTORES_PIN);
    delay(5);
    Serial.println("");
    Serial.print("Light value: ");
    Serial.print(lightValue);

    int percentage = map(lightValue, 0, 1023, 0, 100);
    return percentage;
}

float readTemp() {
    int tempValue = analogRead(TMP_PIN);
    delay(5);
    Serial.print("\nTemperature value: ");
    Serial.print(tempValue);
    float voltage = (tempValue / 1024.0) * 5.0;
    Serial.print("\tVoltage: ");
    Serial.print(voltage);
    float temperature = (voltage - .5) * 100;
    Serial.print("\tTemperature: ");
    Serial.print(temperature);
    Serial.print("oC");
    return temperature;
}

void blink() {
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(50);                        // wait for a second
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    delay(50);
}
