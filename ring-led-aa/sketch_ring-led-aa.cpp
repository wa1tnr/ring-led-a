// ring-led-aa-sketch.cpp
// 23 August 2019  14:43 UTC

// recent update:
// Fri Aug 23 19:49:29 UTC 2019

// CURRENT platform: ItsyBitsyM4, Adafruit

// (future test platform: Metro M4 Express, Adafruit - SOON)

#include <Arduino.h>
#define LED 13 // D13 // Metro vs ItsyBitsy here - TODO
#define WIGGLE_COUNT 12 // full on-off cycle count

// swap these two lines, as required:
#undef  NO_WIGGLE
#define NO_WIGGLE


// STKSIZE is always a power of two; STKMASK is one less than STKSIZE
const int STKSIZE = 8;
const int STKMASK = 7;
int stack[STKSIZE];
int p = 0;

/* TOS is Top Of Stack */
#define TOS stack[p]

// Note: TOS can by any element of the stack[] array!
// In particular, it is often not the same as stack[0] (as one might expect).

// push n to top of data stack
void push(int n) {
  p = (p + 1)& STKMASK;
  TOS = n;
}

// return top of stack
int pop(void) {
  int n = TOS;
  p = (p - 1)& STKMASK;
  return n;
}


// Global delay timer
int spd = 1044; // int spd = 44;


// set the pin named in the TOS (top of stack) to OUTPUT (push-pull) mode
void output(void) { // ( n -- )
  pinMode(pop(), OUTPUT);
}


void led_off(void) { // ( -- )
  push(LED);
  int a = pop();
  digitalWrite(a, LOW);
}

void led_on(void) { // ( -- )
  push(LED);
  int a = pop();
  digitalWrite(a, HIGH);
}

/*
void del(void) {
  delay(pop());
}
*/

// normalize spd to a reasonable value of 100, if it is outside 2 thru 22333
void defspeed(void) { // ( -- )
  if ((spd < 2) || (spd > 22333) ) { spd = 100; }
}

/*
213 // delay TOS # of milliseconds
214 NAMED(_delay, "delay");
215 void del() {
216   delay(pop());
217 }
218 
219 void defspeed() {
220     if ((spd < 2) || (spd > 22333) ) { spd = 100; }
221 }
*/

// Toggle pin at TOS and delay(spd), repeat...
void wiggle(void) { // ( n -- )
  int a = pop(); // which gpio pin?
  pinMode(a, OUTPUT);
  for (int i = 0; i < WIGGLE_COUNT; i++) {
    digitalWrite(a, HIGH);
    defspeed();
    delay(spd); // delay(100);
    digitalWrite(a, LOW);
    delay(spd); // delay(100);
  }
}

// - - - -   populate stack sample values   - - -
void populate_stack_for_test(void) {
  int n = -299;
/*
  push(n); // can push initial value n, here
*/

/*
  n = -200; push(n);
*/

  n = -107; push(n);
  n = -106; push(n);
  n = -105; push(n);
  n = -104; push(n);
  n = -103; push(n);
  n = -102; push(n);
  n = -101; push(n);
  n = -100; push(n);
}

// - - - -   printing   - - - -
void print_stack(void) {
  int a = -99; // debug
  for (int i=0; i<STKSIZE; i++) {
    Serial.print("element: ");
    Serial.print(i);
    Serial.print("  value: ");
    a = pop(); // harmless as long as entire stack gets iterated.
    Serial.println(a);
  }
  
}

// - - - -   setups   - - - -

void setup_gpio(void) {
  push(LED); // say which port pin's mode is to be set as an output, now
  output();
}

#undef WAIT_SERIAL
#define WAIT_SERIAL

void setup_serial(void) {
  Serial.begin(9600);

#ifdef WAIT_SERIAL
  while (!Serial); // hold for activity
#endif

  delay(500);
  Serial.println("Serial active.");
}

void stack_demo(void) {
}

void setup(void) {
  setup_gpio();
  led_off(); // initially off

#ifdef NO_WIGGLE
  delay(200);
  led_on(); delay(200); led_off(); delay(200);
  led_on(); delay(200); led_off(); delay(200);
#endif

#ifndef NO_WIGGLE
  delay(2500);
  push(LED);
  wiggle(); // let them know
#endif

  setup_serial();

// stack_demo();
  populate_stack_for_test();
  print_stack();
  Serial.println(" - - -");
  int n = -705; push(n); print_stack(); Serial.println(" - - -");
  n = -605;     push(n); print_stack(); // Serial.println(" - - -");

}

void loop(void) {
  // everything is done in setup() at the moment
}
