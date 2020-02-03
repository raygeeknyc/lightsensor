// Light Sensor for Code Next Robotics Club
// Trinket M0, CDS Photo Resistor, Piezo Buzzer
// by Raymond Blum, 2020

#include <Adafruit_DotStar.h>
#define LIGHT_CHANGE_THRESHOLD 50
#define BUZZER_PIN 4
#define PHOTORESISTOR_PIN A2

Adafruit_DotStar strip = Adafruit_DotStar(1, INTERNAL_DS_DATA, INTERNAL_DS_CLK, DOTSTAR_BGR);
int previous_light_level;

void setup() {
  strip.begin();
  Serial.begin(115200);
  pinMode(PHOTORESISTOR_PIN, INPUT);
  previous_light_level = 0;
}

void loop() {
  int light_level = analogRead(PHOTORESISTOR_PIN);
  Serial.print("light: ");
  Serial.println(light_level);
  if ((light_level - previous_light_level) > LIGHT_CHANGE_THRESHOLD) {
    strip.setPixelColor(0, 0, 64, 0);  //green
    tone(BUZZER_PIN, 700, 100);
  } else if ((previous_light_level - light_level) > LIGHT_CHANGE_THRESHOLD) {
    strip.setPixelColor(0, 64, 0, 0);  //red
    tone(BUZZER_PIN, 200, 100);
  } else {
    strip.setPixelColor(0, 0, 0, 64);  //blue
    noTone(BUZZER_PIN);
  }
  strip.show();
  previous_light_level = light_level;
  delay(100);
}
