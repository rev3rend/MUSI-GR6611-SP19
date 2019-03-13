
int stuff = 0;
int pot = 0;
int photocell = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // turn on serial line
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  pot = analogRead(A0);
  photocell = analogRead(A1);
  Serial.println(photocell); // send the value of 'stuff' back to the computer
  digitalWrite(2, stuff);
  analogWrite(3, photocell/4);
  stuff = 1-stuff;
  delay(pot);
}
