#include <ir_Lego_PF_BitStreamEncoder.h>
#include <boarddefs.h>
#include <IRremoteInt.h>
#include <IRremote.h>

// If one keypress results in multiple codes being output, then
// change in IRremoteInt.h:
// #define _GAP 50000
// This sketchThis sketch was obtained from:
//  For more info:
//  jason welsh
//   https://www.youtube.com/watch?v=eR8sQq3pl20
//  https://docs.google.com/document/d/1QgmFbFlB0aI3swrhQkacRe3C-cIS0p1t0TV36-i2lLo/edit

//   http://www.instructables.com/id/Arduino-Remote-Control-Less-10/?ALLSTEPS
/////////////////////////////////
//  I made a few small changes

#include <IRremote.h>

int RECV_PIN = 9;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

int c = 0;

void dump(decode_results *results) {
  int count = results->rawlen;
  Serial.println(c);
  c++;
  Serial.println("For IR Scope: ");
  for (int i = 1; i < count; i++) {
   
    if ((i % 2) == 1) {
      Serial.print("+");
      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
    }
    else {
      Serial.print(-(int)results->rawbuf[i]*USECPERTICK, DEC);
    }
    Serial.print(" ");
  }
  Serial.println("");
  Serial.println("For Arduino sketch: ");
  Serial.print("unsigned int raw");
  Serial.print(c);
   Serial.print("[");
  Serial.print(count, DEC);
  Serial.print("] = {");
  for (int i = 1; i < count; i++) {
   
    if ((i % 2) == 1) {
      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
    }
    else {
      Serial.print((int)results->rawbuf[i]*USECPERTICK, DEC);
    }
    Serial.print(",");
  }
  Serial.print("};");
  Serial.println("");
  Serial.print("irsend.sendRaw(");
  Serial.print("raw");
  Serial.print(c);
  Serial.print(",");
  Serial.print(count, DEC);
  Serial.print(",38);");
  Serial.println("");
  Serial.println("");
}

void loop() {
  if (irrecv.decode(&results)) {
    dump(&results);
    irrecv.resume(); // Receive the next value
  }
}
