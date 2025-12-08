/*
  Rui Santos & Sara Santos - Random Nerd Tutorials
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/  
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/

#include <esp_now.h>
#include <WiFi.h>
byte relay = 18;
byte led = 19;
byte button = 5;
byte battery = 2;
char message;
unsigned long lastMessage = 0;
const unsigned long TIMEOUT_MS = 30 * 60 * 1000; // timeout after 30 minutes!
const int cutoff = 2400;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&message, incomingData, len);
  lastMessage = millis();
  if (message == 'S') {
    digitalWrite(relay, HIGH);
    digitalWrite(led,HIGH);
  }
   else {
    digitalWrite(relay, LOW);
    digitalWrite(led,LOW);
  }
}

void handleTimeout(){ // gets called if nothing happens for 30 minutes
  WiFi.disconnect();
  esp_deep_sleep_start();
}

void setup() {
  // Initialize Serial Monitor
  Serial0.begin(115200);
  pinMode(button,INPUT_PULLUP);
  pinMode(battery, INPUT);
  while(digitalRead(button) == LOW){ // make sure the button isn't already low when the interupt is attached!
    delay(1);
  }
  esp_deep_sleep_enable_gpio_wakeup(1ULL << button, ESP_GPIO_WAKEUP_GPIO_LOW);
  int startLevel = analogRead(battery);
  if(startLevel < cutoff){ // kills the device if already below the threshold so the user doesn't see any lights
    esp_deep_sleep_start();
  }
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial0.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
  pinMode(relay, OUTPUT);

  pinMode(led,OUTPUT);
  for(byte i = 0; i < 3; i++){
    digitalWrite(led,HIGH);
    delay(50);
    digitalWrite(led,LOW);
    delay(50);
  }
  Serial0.println(analogRead(battery));
  digitalWrite(led,LOW);

}

void loop() {
  int level = analogRead(battery);
  unsigned long currentTime = millis();
  Serial0.println(analogRead(battery));
  if(level < cutoff && digitalRead(relay) != HIGH){ // if the battery level drops 3.5V it should kill the device also checks if the relay is high
    WiFi.disconnect();
    esp_deep_sleep_start();
  }
  if(currentTime - lastMessage >= TIMEOUT_MS){ // kills the device if nothing happens for 30 minutes
    WiFi.disconnect();
    esp_deep_sleep_start();
  }
  if(digitalRead(button) == LOW){
    digitalWrite(led,HIGH);
    delay(100);
    digitalWrite(led,LOW);
  }

}
