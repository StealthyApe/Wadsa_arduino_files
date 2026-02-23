#include <WiFi.h>
#include <esp_wifi.h>
byte button = 5;
void readMacAddress(){
  uint8_t baseMac[6];
  esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
  if (ret == ESP_OK) {
    Serial0.printf("0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x\n",
                  baseMac[0], baseMac[1], baseMac[2],
                  baseMac[3], baseMac[4], baseMac[5]);
  } else {
    Serial0.println("Failed to read MAC address");
  }
}

void setup(){
  Serial0.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.STA.begin();
  pinMode(button,INPUT_PULLUP);
  pinMode(2,INPUT);
}
 
void loop(){
Serial0.print("[DEFAULT] ESP32 Board MAC Address: ");
readMacAddress();
Serial0.println(analogRead(2));
delay(2000);

}