// ring-led-aa-sketch.cpp
// 23 August 2019  14:43 UTC

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

void setup_gpio(void) {
  push(LED); // say which port pin's mode is to be set as an output, now
  output();
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
}

void loop(void) {
  // everything is done in setup() at the moment
}
