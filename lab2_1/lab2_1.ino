int latchPin = 4;
int clockPin = 7;
int dataPin = 8;  // SSD pins
const unsigned char ssdlut[] = { 0b00111111, 0b00000110,
                                 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101,
                                 0b00000111, 0b01111111, 0b01101111,
                                 0b01110111, 0b01111100, 0b00111001, 0b01011110, 0b01111001, 0b01110001 };
// ,0b01110111, 0b01111100, 0b00111001, 0b01011110,0b01111001,0b01110001
const unsigned char anodelut[] = { 0b00000001, 0b00000010,
                                   0b00000100, 0b00001000 };
const unsigned char digits[] = { 14, 15, 12, 13 };  // The number to be

const long long delay_time = 1;  // ms
long long last_time = 0;

const int BTN_1 = A1;
const int BTN_2 = A2;
const int BTN_3 = A3;

int num = 0;

//displayed is 1234. You can change it.
void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  // The three pins connected to
  // the shift register must be output pins

  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(BTN_3, INPUT_PULLUP);
}

void display_num(int num) {
  int copy = num;
  for (char i = 0; i <= 3; i++)  // For each of the 4 digits
  {
    unsigned char digit = copy % 10;
    unsigned char with_dot = ~(ssdlut[digit] | (1 << 7));
    unsigned char cathodes = ~ssdlut[digit];  // The
    copy /= 10;

    if (i == 2) cathodes = with_dot;

    //cathodes of the current digit, we’ll
    //negate the value from the original LUT
    digitalWrite(latchPin, LOW);  // Activate the latch to
    //allow writing
    shiftOut(dataPin, clockPin, MSBFIRST, cathodes);  //
    //shift out the cathode byte
    shiftOut(dataPin, clockPin, MSBFIRST, anodelut[3 - i]);
    // shift out the anode byte
    digitalWrite(latchPin, HIGH);  // De-activate the latch
    //signal
    delay(2);  // Short wait
  }
}

bool lastBtn1 = HIGH;
bool lastBtn2 = HIGH;
bool lastBtn3 = HIGH;

bool do_count = false;

void loop() {

  display_num(num);

  bool btn1_val = digitalRead(BTN_1);
  if (lastBtn1 == HIGH && btn1_val == LOW) {
    do_count = true;
  }
  lastBtn1 = btn1_val;

  bool btn2_val = digitalRead(BTN_2);
  if (lastBtn2 == HIGH && btn2_val == LOW) {
    do_count = false;
  }
  lastBtn2 = btn2_val;

  bool btn3_val = digitalRead(BTN_3);
  if (lastBtn3 == HIGH && btn3_val == LOW) {
    num = 0;
  }
  lastBtn3 = btn3_val;

  if (millis() - last_time >= delay_time) {
    if (do_count) {
      num = (num + 1) % 10000;
    }
    last_time += delay_time;
  }
}