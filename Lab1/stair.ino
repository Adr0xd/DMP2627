// Read status of buttons and display it on LEDs connected to
//PORTA
// Variables for reading the status of the buttons connected
//to the
// digital pins 4, 5, 6, 7
int b1;
int lastB1;
// variable for the LED status
unsigned char stat = (1<<3);
  int direction = 0;
void setup() {
  // configure digital pins as inputs
  pinMode(6, INPUT_PULLUP);
  // activate PORTA, as output,
  DDRA = 0b11111111;
}
void loop() {
  // read BTNs status
  b1 = digitalRead(6);

  if (b1 == 0) {
    direction = 1 - direction;
    delay(100);
  }

  if (direction == 1) {
    // up    
    if (stat == 1) {
      stat = 16;
      // direction = 1 - direction;
    }
    stat = stat >> 1;

  } else {
    //down
    stat = stat << 1;
    if (stat == 16){
      // direction = 1 - direction;
      stat = 1;
    }
  }
  // Display status on the LEDs connected to port A
  PORTA = stat;
  // delay 50 ms
  _delay_ms(250);
}