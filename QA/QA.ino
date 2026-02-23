byte relay = 18;
byte led = 19;
byte button = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(relay, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(button) == LOW){
    digitalWrite(led,HIGH);
    digitalWrite(relay,HIGH);
  }
  else{
    digitalWrite(led,LOW);
    digitalWrite(relay,LOW);
  }
}
