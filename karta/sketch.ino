class MyButton {

  public:
    MyButton(byte pinIN, byte pinOUT){
      _pinIN = pinIN;
      _pinOUT = pinOUT;
      pinMode(_pinIN, INPUT_PULLUP);
      digitalWrite(_pinIN, LOW);
      pinMode(_pinOUT, OUTPUT);
      digitalWrite(_pinOUT, LOW);
    }

    bool get_isOn(){
      return _isOn;
    }

    int get_pinIN(){
      return _pinIN;
    }

    void ON(){
      if (_isOn == false){
        _isOn = true;
        digitalWrite(_pinOUT, HIGH);
        Serial.print("_pinIN: ");
        Serial.print(_pinIN);
        Serial.print(", pinOUT: ");
        Serial.print(_pinOUT);
        Serial.println(" - ON");                  
      }      
    }

    void OFF(){
      if(_isOn){
      digitalWrite(_pinOUT, LOW);
      _isOn = false;
      }
    }

    bool isPressed(){
      if (digitalRead(_pinIN) == HIGH) {
        return true;
      }
      else {
        return false;
      }
    }

  private:
  byte _pinIN;
  byte _pinOUT;
  bool _isOn = false;
};

uint32_t glowTime = 3000;
uint32_t tmr1;

MyButton buttons[] = {
  MyButton(22, 23),
  MyButton(24, 25),
  MyButton(26, 27),
  MyButton(28, 29),
  MyButton(30, 31),
  MyButton(32, 33),
  MyButton(34, 35),
  MyButton(36, 37),
};

void setup() {
  Serial.begin(9600);
  Serial.println("Start");
}

void loop() {
  if (millis() - tmr1 == glowTime) {                  
    for (int k = 0; k < sizeof(buttons)/sizeof(buttons[0]); k++){
        buttons[k].OFF();
    }
  }
  for (int i = 0; i < sizeof(buttons)/sizeof(buttons[0]); i++){
    if (buttons[i].isPressed() && !buttons[i].get_isOn()){
      for (int j = 0; j < sizeof(buttons)/sizeof(buttons[0]); j++){
        buttons[j].OFF();
      }
      buttons[i].ON();
      tmr1 = millis();
    }
  }
}
