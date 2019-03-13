// RTSKED

unsigned long now = 0; // this is a variable that's gonna hold milliseconds
unsigned long then = 0; // this is a variable that's gonna hold milliseconds

int interval = 0; // timing value
int trigger = 0; // pulse out pin 2
int pot = 0; // analog read in A0 -> speed of pulse
int photocell = 0; // analog read in A1 -> voltage out pin 3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // turn on serial line
  // both of these pins are outputs:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  // clock:
  now = millis();
  Serial.print(now);
  Serial.print(" ");
  Serial.print(then);
  Serial.print(" ");
  Serial.print(interval);
  Serial.print(" ");
  Serial.print(trigger);
  Serial.print(" "); // send the value back to the computer
  Serial.print(photocell); // send the value back to the computer
  Serial.println();
  
  if (now - then >= interval) {
    then = now; // reset time
    interval = pot; // update sequence speed
    trigger = 1;
  }
  else {
    trigger = 0;
  }

  digitalWrite(2, trigger); // digitalWrite takes 0 or 1
  
  // put your main code here, to run repeatedly:
  // analogRead is a 10-bit value -> 0-1023
  pot = analogRead(A0); // what's the value of the pot?
  photocell = analogRead(A1); // what's the value of the photocell?
  
  analogWrite(3, photocell/4); // analogWrite takes 0-255
}
