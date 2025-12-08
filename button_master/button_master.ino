#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x34,0xcd,0xb0,0x4e,0x90,0xf4};

// Structure example to send data
// Must match the receiver structure
byte button = 19;
byte led = 5;
char payload;

// Create a struct_message called myData

esp_now_peer_info_t peerInfo;

 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  pinMode(button,INPUT_PULLUP);
  pinMode(led,OUTPUT);
}
 bool state = false;
 bool change = false;
void loop() {

  // Send message via ESP-NOW
  if(digitalRead(button) == LOW && state == false){
    payload = 'S';
    state = true;
    change = true;
    digitalWrite(led,HIGH);
  }
  if(digitalRead(button) == HIGH && state == true && change == false){
    payload = 'K';
    state = false;
    change = true;
    digitalWrite(led,LOW);
  }
  if(change == true){
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &payload, sizeof(payload));
    Serial.println(payload);
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
      }
    }
  change = false;
  delay(10);
}