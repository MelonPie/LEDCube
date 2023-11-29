


void SetShiftReg(unsigned int value) {
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, value >> 8);   //shift out high byte, alternative: LSBFIRST / MSBFIRST
  shiftOut(DATA, CLOCK, MSBFIRST, value);        //shift out low byte, alternative: LSBFIRST / MSBFIRST
  digitalWrite(LATCH, HIGH);
}
