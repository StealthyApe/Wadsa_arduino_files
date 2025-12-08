byte button = 5;
byte relay  = 9;


void setup() {
  // put your setup code here, to run once:
  pinMode(button,INPUT_PULLUP);
  pinMode(relay,OUTPUT);
  digitalWrite(relay,LOW);
  Serial0.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  byte state = digitalRead(button);
  Serial0.println(state);
  if(state == LOW){
    digitalWrite(relay,HIGH);
  }
  else{
    digitalWrite(relay,LOW);
  }
}
