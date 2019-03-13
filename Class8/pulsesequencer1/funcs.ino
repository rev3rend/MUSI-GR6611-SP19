// ...helper functions...

//
// show sequence clock (view 0):
//
void shiftClock()
{
    led1 = 0;
    led2 = 0;
    if (sptr < 8) {
      bitSet(led1, sptr);
    }
    else {
      bitSet(led2, sptr - 8);
    }
    updateShiftRegister(led1, led2);  
}

//
// show programmed sequence (view 1-4):
//
void shiftSequence(boolean s[], int n)
{
    led1 = 0;
    led2 = 0;
    int i;
    for(i =0;i<n;i++)
    {
      if(i<8) {
        if(i==crsr&&cp>0) {
          bitWrite(led1, i, now%200>100);
          cp--;
        }
        else bitWrite(led1, i, s[i]);
      }
      else {
        if(i==crsr&&cp>0) {
          bitWrite(led2, i-8, now%200>100);
          cp--;
        }
        else bitWrite(led2, i-8, s[i]);
      }
    }

    updateShiftRegister(led1, led2);    
}

//
// pulse outputs:
//
void updateOutputPins()
{
  // update output pins
  digitalWrite(s1Pin, s1p > 0);
  digitalWrite(s2Pin, s2p > 0);
  digitalWrite(s3Pin, s3p > 0);
  digitalWrite(s4Pin, s4p > 0);
  s1p--;
  s2p--;
  s3p--;
  s4p--;
}

//
// update shift register LEDs:
//
void updateShiftRegister(byte _l1, byte _l2)
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, _l1);
  shiftOut(dataPin, clockPin, LSBFIRST, _l2);
  digitalWrite(latchPin, HIGH);
}

//
// debug routine:
//
void debug(int _a, int _b, int _c, int _d, int _k)
{
  Serial.print(_a);
  Serial.print(" ");
  Serial.print(_b);
  Serial.print(" ");
  Serial.print(_c);
  Serial.print(" ");
  Serial.print(_d);
  Serial.print(" ");
  Serial.println(_k);  
}
