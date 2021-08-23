#include <IRremote.h>

IRsend irsend;

void setup()
{

}

void loop() {
  int khz = 38; // 38kHz carrier frequency for the NEC protocol
  unsigned int irSignal1[33] = {2200,650, 800,1400, 800,1350, 800,650, 800,1450, 750,700, 750,650, 700,750, 800,1450, 750,1450, 750,1450, 700,1550, 700,1500, 800,1400, 750,1400, 800,650, 750}; //AnalysIR Batch Export (IRremote) - RAW
  irsend.sendRaw(irSignal1, sizeof(irSignal1) / sizeof(irSignal1[0]), khz); //Note the approach used to automatically calculate the size of the array.
  delay(2000); //In this example, the signal will be repeated every 5 seconds, approximately.
}
