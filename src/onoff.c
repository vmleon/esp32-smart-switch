const int relay = 26;

void setup() {
  Serial.begin(115200);
  pinMode(relay, OUTPUT);
}

void loop() {
  digitalWrite(relay, HIGH);
  Serial.println("Current Flowing");
  delay(5000);

  digitalWrite(relay, LOW);
  Serial.println("Current not Flowing");
  delay(5000);
}
