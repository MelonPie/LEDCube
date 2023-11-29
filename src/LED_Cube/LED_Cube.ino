
#define BUTTON1 4
#define BUTTON2 5

#define ULN1 16
#define ULN2 17
#define ULN3 18
#define ULN4 19

#define LATCH 12
#define CLOCK 13
#define DATA 14

unsigned int layer[4] = {0, 0, 0, 0};   //65535 filled layer
byte active_layer = 0; 
bool start = true;
unsigned long delay_time;
int speed_time = 0;
int count;

void setup() {
  // Init shift register pins
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  // Init ULN2003
  pinMode(ULN1, OUTPUT);
  pinMode(ULN2, OUTPUT);
  pinMode(ULN3, OUTPUT);
  pinMode(ULN4, OUTPUT);
  digitalWrite(ULN1, LOW);
  digitalWrite(ULN2, LOW);
  digitalWrite(ULN3, LOW);
  digitalWrite(ULN4, LOW);
  // Buttons
  pinMode(BUTTON1, INPUT_PULLUP);
  // Not used yet
  pinMode(BUTTON2, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BUTTON1), PushButton, FALLING);
  delay_time = millis();
}

byte patternNum = 28;
byte pattern = patternNum - 1;

void loop() {
  if (start) {
    detachInterrupt(digitalPinToInterrupt(BUTTON1));
    delay(500);   //wait for releasing PushButton
    pattern++; 
    if (pattern > patternNum) pattern = 1;
    attachInterrupt(digitalPinToInterrupt(BUTTON1), PushButton, FALLING);
    count = 0;
  }
  if (((millis() - delay_time) > speed_time) || start) { 
    switch (pattern) {
      case 1: LayersUpDown(); break;
      case 2: FallingDot(); break;
      case 3: Rain(); break;
      case 4: AllCube(); break;
      case 5: Cut(); break;
      case 6: Cube(); break;
      case 7: Diagonal(); break;
      case 8: Mixer(); break;
      case 9: Random(); break;
      case 10: FallingLayer(); break;
      case 11: LayerCut(); break;
      case 12: Circle(); break;
      case 13: RandomWay(); break;
      case 14: SmallCube(); break;
      case 15: RandomWayCube(); break;
      case 16: GrowingCube(); break;
      case 17: FallingLayers(); break;
      case 18: GrowingLine(); break;
      case 19: CircleEdges(); break;
      case 20: CircleSide(); break;
      case 21: RandomWayLine(); break;
      case 22: RandomWaySide(); break;
      case 23: DJCube(); break;
      case 24: FillingCube(); break;
      case 25: NanoBuilding(); break;
      case 26: Curve(); break;
      case 27: Snake(); break;
      case 28: BDay(); break;
      default: break;
    }
    delay_time = millis();
  }

  //this part displays layers as they are set in functions
  SetShiftReg(layer[active_layer]);    //send layer data to shift registers
  if(active_layer == 0) {
    digitalWrite(ULN1, HIGH);
  } else if (active_layer == 1) {
    digitalWrite(ULN2, HIGH);
  } else if (active_layer == 2) {
    digitalWrite(ULN3, HIGH);
  } else if (active_layer == 3) {
    digitalWrite(ULN4, HIGH);
  }
  delay(2);                 //important for brightness of leds
  digitalWrite(ULN1, LOW);
  digitalWrite(ULN2, LOW);
  digitalWrite(ULN3, LOW);
  digitalWrite(ULN4, LOW);       //turn OFF layers
  active_layer++; if (active_layer > 3) active_layer = 0;    //take another layer in the loop
}

void PushButton() {
  start = true;
}
