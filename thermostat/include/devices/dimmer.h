int dimmerpin = 46;

void setPWM(int pwmvalue) {
  analogWrite(dimmerpin, pwmvalue);
  //delay(5);
}