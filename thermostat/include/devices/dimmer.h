int dimmer_pin = 38;

void setPWM(int pwmvalue) {
  analogWrite(dimmer_pin, pwmvalue);
}