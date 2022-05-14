int dimmer_pin = 46;

void setPWM(int pwmvalue) {
  analogWrite(dimmer_pin, pwmvalue);
}