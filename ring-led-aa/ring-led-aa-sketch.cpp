// ring-led-aa-sketch.cpp
// 23 August 2019  14:43 UTC

// test platform: ItsyBitsyM4

#include <Arduino.h>
#define LED 13 // D13


const int STKSIZE = 8;
const int STKMASK = 7;
int stack[STKSIZE];
int p = 0;

/* TOS is Top Of Stack */
#define TOS stack[p]



// push n to top of data stack
void push(int n) {
  p = (p + 1)& STKMASK;
  TOS = n;
}



// return top of stack
int pop() {
  int n = TOS;
  p = (p - 1)& STKMASK;
  return n;
}


int spd = 44;

/*
 86 // Global delay timer
 87 // int spd = 100; // 15;
 88 int spd = 44;
*/




// make TOS pin an output
void output() {
  push(LED);
  pinMode(pop(), OUTPUT);
}



void led_off(void) {
  push(LED);
  int a = pop();
  digitalWrite(a, LOW);
}


void delay(void) {}
void defspeed(void) {}

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
void wiggle(void) {
  int a = pop();
  pinMode(a, OUTPUT);
  for (int i = 0; i < 20; i++) {
    digitalWrite(a, HIGH);
    defspeed();
    delay(spd); // delay(100);
    digitalWrite(a, LOW);
    delay(spd); // delay(100);
  }
}

void setup_gpio(void) {
  output();
}

void setup(void) {
  setup_gpio();
  led_off();
}

void loop(void) {
}
