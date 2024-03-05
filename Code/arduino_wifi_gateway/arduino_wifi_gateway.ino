#include <WiFiS3.h>
#include <ArduinoMqttClient.h>
#include <LoRa.h>
#include <NTPClient.h>
#include <time.h>
#include "arduino_secrets.h" 

#define SERIAL_BAUD   115200

#define SS    10  // D10
#define RST   9   // D9
#define DIO0   2  // D2

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int status = WL_IDLE_STATUS;
bool flag = false;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Mqtt connection
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

// MQTT parameters
const char broker[] = "zograf4lyk.lserveradmin.gr";
const int port = 1883;
const char node1_topic[] = "topic/node1";
const char node2_topic[] = "topic/node2";
const char node3_topic[] = "topic/node3";

// Nodes identifiers
byte gateway_id = 0xDD;
byte node1_id = 0xAA;
byte node2_id = 0xBB;
byte node3_id = 0xCC;

String SenderNode, buf = "", incoming = "";
String rssi_buf;

// Tracks the time since last event fired
unsigned long int currentSecs;
unsigned long int previousSecs;
unsigned long int currentMillis;
unsigned int interval = 1, seconds = 0;


void InitLoRa() {
  // Connecting to LoRa module
  Serial.println("Attempting to connect LoRa...");

  int n = 0;
  while (n < 10) {
    if (!LoRa.begin(868E6)) {
      Serial.println("Starting LoRa failed!");
    }
    else
    {
      Serial.println("Initializing LoRa Ok!");
      delay(2000);
      break;
    }
    delay(1000);
    n++;
  }
  if (n >= 10) {
      Serial.println("Failed to connect LoRa module.");
      while (true);
  }
}

void InitWiFi() {
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.print("\nConnected to Access Point with IP: ");
  Serial.println(WiFi.localIP());
}


void InitMqtt() {
  // Attempting to establish a connection to the given MQTT brocker
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);
  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    while (1);
  }
  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}


void onReceive(int packetSize) {
  if (packetSize == 0) return;

  // read four bytes for packet header:
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  //byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length
  byte sigByte1 = LoRa.read();          // incoming sigByte1
  byte sigByte2 = LoRa.read();          // incoming sigByte2

  incoming = "";
  rssi_buf = "";
  // read json data
  for (int i = 0; i < packetSize-5; i++) {
    incoming += (char)LoRa.read();
  }

  // print RSSI of packet
  rssi_buf += " with RSSI ";
  rssi_buf += String(LoRa.packetRssi());
  flag = true;
}

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(SERIAL_BAUD);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Connect LoRa, WiFi and MQTT brocker
  InitLoRa();
  InitWiFi();
  InitMqtt();  

  // set the message receive callback
  mqttClient.onMessage(onMqttMessage);
  
   // subscribe to a topic
  mqttClient.subscribe(node1_topic);
  mqttClient.subscribe(node2_topic);
  mqttClient.subscribe(node3_topic);
   
  // LoRaNow definitions
  // register the receive callback
  LoRa.onReceive(onReceive);
  // put the radio into receive mode
  LoRa.receive();
}


void onMqttMessage(int messageSize) {
  // we received a message, print out the topic and contents
  while (mqttClient.available()) {
    char ch = mqttClient.read();
    buf += ch;
  } 
  //Serial.println(buf);
  buf = "";
}


void loop() {
  // check the network connection once every 10 seconds:
  if (!wifiClient.connected()) {
    InitWiFi();
    InitMqtt();
  }

  if (flag) {
    Serial.print(incoming);
    Serial.println(rssi_buf);
    
    mqttClient.beginMessage(node1_topic);
    mqttClient.print(incoming);
    mqttClient.endMessage();
    
    flag = false;
  }

  // call poll() regularly to allow the library to send MQTT keep alive which
  // avoids being disconnected by the broker
  mqttClient.poll();
  delay(1000);
}


