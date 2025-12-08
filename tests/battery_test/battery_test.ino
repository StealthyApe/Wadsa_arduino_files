byte battery = 2;

void setup() {
  // put your setup code here, to run once:
  Serial0.begin(115200);
  delay(100);
  pinMode(battery,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial0.println(analogRead(battery));
  delay(100);
}
