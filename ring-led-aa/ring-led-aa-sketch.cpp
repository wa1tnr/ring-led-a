// ring-led-aa-sketch.cpp
// 23 August 2019  14:43 UTC

#include <Arduino.h>


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


/*
 69 // return top of stack
 70 int pop() {
 71   int n = TOS;
 72   p = (p - 1)& STKMASK;
 73   return n;
 74 }
*/

void setup(void) {
}

void loop(void) {
}
