// ...main functions...

//
// setup:
//
void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(aPin, INPUT);
  pinMode(bPin, INPUT);
  pinMode(cPin, INPUT);
  pinMode(dPin, INPUT);
  pinMode(s1Pin, OUTPUT);
  pinMode(s2Pin, OUTPUT);
  pinMode(s3Pin, OUTPUT);
  pinMode(s4Pin, OUTPUT);
  if(db) Serial.begin(9600);
}

//
// main loop:
//
void loop()
{
  // read input pins:
  boolean a = digitalRead(aPin);
  boolean b = digitalRead(bPin);
  boolean c = digitalRead(cPin);
  boolean d = digitalRead(dPin);
  int k = analogRead(kPin);

  if(db) debug(a, b, c, d, k); // debug

  // buttons:

  // A: CHANGE "VIEW"
  if (a == 1 & a_o == 0)
  {
    view = (view + 1) % 5;
    crsr = 0; // reset cursor
    cp = crsrtime;
  }
  a_o = a;
  
  // B: CURSOR LEFT
  if (b == 1 & b_o == 0)
  {
    crsr--;
    cp = crsrtime;
    if(crsr<0) crsr=15;
  }
  b_o = b;
  
  // C: CURSOR RIGHT
  if (c == 1 & c_o == 0)
  {
    crsr++;
    cp = crsrtime;
    if(crsr>15) crsr=0;
  }
  c_o = c;
  
  // D: FLIP VALUE
  if (d == 1 & d_o == 0)
  {
    if(view==1) s1[crsr] = !s1[crsr];
    else if(view==2) s2[crsr] = !s2[crsr];
    else if(view==3) s3[crsr] = !s3[crsr];
    else if(view==4) s4[crsr] = !s4[crsr];
  }
  d_o = d;

  updateOutputPins(); // fire triggers

  // fire shift registers (LEDs):
  if(view == 0) shiftClock();
  else if(view == 1) shiftSequence(s1, 16);
  else if(view == 2) shiftSequence(s2, 16);
  else if(view == 3) shiftSequence(s3, 16);
  else if(view == 4) shiftSequence(s4, 16);

  // clock:
  now = millis();
  if (now - then >= interval) {
    then = now; // reset time
    interval = (k+1)*4; // update sequence speed

    sptr = (sptr + 1) % 16; // increment sequence

    // pull triggers high:
    s1p = s1[sptr] * ptime;
    s2p = s2[sptr] * ptime;
    s3p = s3[sptr] * ptime;
    s4p = s4[sptr] * ptime;
  }

}
