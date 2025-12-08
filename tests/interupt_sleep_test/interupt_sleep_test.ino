const byte led = 19;
const byte button = 5;
const unsigned long awakeDuration = 5000;
const byte relay = 18;

void setup() {
  pinMode(button,INPUT_PULLUP);
  pinMode(relay,OUTPUT);
  pinMode(led,OUTPUT);
  pinMode(2,INPUT);
  digitalWrite(led,HIGH);
  digitalWrite(relay,HIGH);
  Serial0.begin(115200);
  Serial0.println("I am awake");
  while(digitalRead(button) == LOW){
    delay(1);
    Serial0.println(digitalRead(button));
  }
  Serial0.println(digitalRead(button));
  delay(1000);
  Serial0.println(analogRead(2));
  digitalWrite(led,LOW);
  digitalWrite(relay,LOW);
  esp_deep_sleep_enable_gpio_wakeup(1ULL << button, ESP_GPIO_WAKEUP_GPIO_LOW);
  // Go to deep sleep
  esp_deep_sleep_start();
}

void loop() {

}
