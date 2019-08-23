// ring-led-aa-sketch.cpp
// 23 August 2019  14:43 UTC

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



// make TOS pin an output
void output() {
// 111   push(TOS);
  pinMode(pop(), OUTPUT);
}



void led_off(void) {
// 226   int a = pop();
// 232   digitalWrite(a, LOW);
}

/*
223 // Toggle pin at TOS and delay(spd), repeat...
224 NAMED(_wiggle, "wiggle");
225 void wiggle() {
226   int a = pop();
227   pinMode(a, OUTPUT);
228   for (int i = 0; i < 20; i++) {
229     digitalWrite(a, HIGH);
230     defspeed();
231     delay(spd); // delay(100);
232     digitalWrite(a, LOW);
233     delay(spd); // delay(100);
234   }
235 }
*/

void setup_gpio(void) {
  output();
}

void setup(void) {
  setup_gpio();
  led_off();
}

void loop(void) {
}
