// Print IR Buttons to Serial Monitor
// TheGeekPub.com
 
#include <IRremote.h>
 
// Define the pin for the IR Receiver
const int IR_RECV_PIN = 7;
 
// Create the IR object
IRrecv gpirrecv(IR_RECV_PIN);
decode_results results;
 
void setup(){
  Serial.begin(9600);
  gpirrecv.enableIRIn();
  gpirrecv.blink13(true);
  Serial.println("READY.");
}
 
void loop(){
  if (gpirrecv.decode(&results)){
  Serial.println(results.value, HEX);
  gpirrecv.resume();
}
}
