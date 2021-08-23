
#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <IRremote.h>
#include <DHT.h>
#include <SoftwareSerial.h>

SoftwareSerial EspSerial(4, 5); // RX, TX
IRsend irSend;

const char auth[] = "ldK-A7MvEnm86TkxTMKstnxfNRdi8TKt";
const char ssid[] = "DM-Wifi2";
const char pass[] = "danmich2020";

#define ESP8266_BAUD 9600
ESP8266 wifi(&EspSerial);

#define DHTPIN 8     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
#define FREQ_KHZ 38
DHT dht(DHTPIN, DHTTYPE);

const size_t signal_size = 85;
static PROGMEM const uint16_t irSignalon[signal_size] = {2000,1000, 5450,1000, 1450,550, 1500,400, 550,550, 500,450, 550,500, 500,500, 550,450, 550,450, 1550,450, 550,500, 500,500, 550,450, 550,450, 550,500, 500,550, 1500,400, 600,450, 1550,400, 600,500, 500,500, 500,500, 550,500, 500,450, 550,500, 500,450, 600,450, 550,450, 550,500, 500,500, 550,450, 550,400, 600,500, 500,500, 1550,400, 600,450, 1550,400, 1550,500, 500,550, 1450,500, 1550,400, 550};
static PROGMEM const uint16_t irSignaloff[signal_size] = {1950,1000, 5450,1000, 1500,500, 1500,450, 550,500, 550,450, 500,550, 450,550, 500,500, 500,550, 1500,500, 450,500, 550,450, 550,500, 500,500, 550,500, 450,550, 1500,500, 500,500, 1500,500, 500,500, 500,500, 500,550, 500,500, 500,500, 550,450, 500,550, 500,500, 500,500, 500,550, 450,550, 500,500, 500,500, 550,500, 450,550, 1450,500, 550,500, 1500,450, 1500,550, 500,450, 1550,500, 1450,550, 450};
static PROGMEM const uint16_t dimUp[signal_size] = {1950,1050, 5450,1000, 1500,500, 1500,450, 550,450, 550,500, 500,500, 500,500, 550,450, 550,450, 1550,450, 550,450, 550,550, 500,500, 500,500, 500,500, 500,550, 1500,500, 500,450, 550,500, 500,500, 500,550, 500,500, 500,500, 1500,450, 550,500, 500,500, 550,450, 550,500, 500,450, 600,400, 600,450, 550,450, 550,450, 550,550, 450,550, 500,500, 1500,500, 1500,450, 550,450, 550,500, 1500,500, 500};
static PROGMEM const uint16_t dimDown[signal_size] = {1950,1000, 5500,1000, 1500,450, 1500,500, 550,500, 500,500, 500,500, 500,450, 550,550, 500,450, 1550,500, 500,500, 500,500, 500,500, 550,500, 500,500, 500,450, 1550,450, 550,500, 550,500, 500,450, 550,450, 550,500, 550,500, 500,500, 1500,500, 500,500, 500,500, 550,500, 500,500, 500,500, 500,500, 550,500, 500,450, 550,450, 550,450, 600,500, 1500,500, 1500,450, 550,450, 1550,500, 500,500, 500};
static PROGMEM const uint16_t white[signal_size] = {1950,1050, 5450,1000, 1500,450, 1550,500, 500,450, 550,500, 500,500, 500,500, 500,550, 500,450, 1550,500, 500,450, 600,450, 550,500, 500,500, 500,500, 500,500, 1500,500, 500,500, 550,500, 500,500, 550,450, 550,450, 1500,550, 450,550, 500,450, 550,500, 550,450, 550,500, 500,500, 500,500, 550,450, 550,500, 500,450, 600,400, 600,450, 550,500, 1500,500, 1500,450, 1550,450, 1550,500, 1450,500, 500};

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if (pinValue == 1) {
    send_signal(irSignalon);}
  else if (pinValue == 2) {
    send_signal(irSignaloff);
    delay(1000);
    send_signal(irSignalon);}
  else if (pinValue == 3) {
    send_signal(dimDown);
    delay(1500);
    send_signal(dimDown);}
  else if (pinValue == 4) {
    send_signal(dimUp);
    delay(1500);
    send_signal(dimUp);}
  else if (pinValue == 5) {
    send_signal(white);
    delay(1500);
    send_signal(white);}
  else if (pinValue == 6) {
    send_signal(yellow);
    delay(1500);
    send_signal(yellow);}
}
BLYNK_WRITE(V2)
{
  int pinValue2 = param.asInt(); // assigning incoming value from pin V1 to a variable
  if (pinValue2 == 1) {
    Blynk.virtualWrite(V5, dht.readTemperature());
    Blynk.virtualWrite(V6, dht.readHumidity());
   }
}

BLYNK_WRITE(V3)
{
  int pinValue3 = param.asInt(); // assigning incoming value from pin V1 to a variable
  if (pinValue3 == 1) {
    send_signal(airconoff);
   }
}
void setup()
{

  // Debug console
  Serial.begin(9600);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
  delay(1000);
  dht.begin();


}

void loop()
{
  Blynk.run();
}

/* Send an IR signal from PROGMEM. */
void send_signal(const uint16_t *signal) {
    static uint16_t signal_buffer[signal_size];
    memcpy_P(signal_buffer, signal, signal_size * sizeof *signal);
    irSend.sendRaw(signal_buffer, signal_size, FREQ_KHZ);
}
