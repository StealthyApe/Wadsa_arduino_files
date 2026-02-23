#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xe4,0xb0,0x63,0x01,0x4b,0x00};

// Structure example to send data
// Must match the receiver structure
byte button = 19;
byte led = 2;
char payload;

// Create a struct_message called myData

esp_now_peer_info_t peerInfo;

 
void setup() {
  // Init Serial Monitor
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    return;
  }
   esp_now_peer_info_t peerInfo;
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    return;
  }
  pinMode(button,INPUT_PULLUP);
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);
}
 bool state = false;
 bool change = false;
void loop() {

  // Send message via ESP-NOW
  if(digitalRead(button) == LOW && state == false){
    payload = 'S';
    state = true;
    change = true;
    digitalWrite(led,LOW);
  }
  if(digitalRead(button) == HIGH && state == true && change == false){
    payload = 'K';
    state = false;
    change = true;
    digitalWrite(led,HIGH);
  }
  if(change == true){
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &payload, sizeof(payload));

    }
  change = false;
  delay(10);
}