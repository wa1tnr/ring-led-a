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



// return top of stack
int pop() {
  int n = TOS;
  p = (p - 1)& STKMASK;
  return n;
}


void setup(void) {
}

void loop(void) {
}
