#include <SPI.h>
#include <LoRa.h>

#ifdef ARDUINO_SAMD_MKRWAN1300
#error "This example is not compatible with the Arduino MKR WAN 1300 board!"
#endif

void setup() {
  SPI.begin();
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Receiver Callback");

  int n = 0;
  while (n<10) {
    if (!LoRa.begin(868E6)) {
      Serial.println("Starting LoRa failed!");
      //while (1);
    }
    else
      break;
    n++;
    delay(2000);
  }
  if (n < 10)
    Serial.println("Lora connected ok !!!");
  else {
      Serial.println("Starting LoRa failed!");
      while (1);
  }

  // Uncomment the next line to disable the default AGC and set LNA gain, values between 1 - 6 are supported
  // LoRa.setGain(6);
  
  // register the receive callback
  LoRa.onReceive(onReceive);

  // put the radio into receive mode
  LoRa.receive();
}

void loop() {
  
}

void onReceive(int packetSize) {
  // received a packet
  Serial.print("Received packet: ");

  // read packet
  for (int i = 0; i < packetSize; i++) {
    Serial.print((char)LoRa.read());
  }


  // print RSSI of packet
  Serial.print(" with RSSI ");
  Serial.println(LoRa.packetRssi());
}
