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

byte recipient;
byte sender;

String SenderNode = "";
String outcoming, incoming;
String buf;

// Tracks the time since last event fired
unsigned long int currentSecs;
unsigned long int previousSecs;
unsigned long int currentMillis;
unsigned int interval = 1, seconds = 0;


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

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(SERIAL_BAUD);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Connect to WiFi and MQTT brocker
  InitWiFi();
  InitMqtt();  

  // set the message receive callback
  mqttClient.onMessage(onMqttMessage);
  
   // subscribe to a topic
  mqttClient.subscribe(node1_topic);
  mqttClient.subscribe(node2_topic);
  mqttClient.subscribe(node3_topic);
  
  // Connecting to LoRa module
  Serial.println("Attempting to connect LoRa...");
  LoRa.setPins(SS, RST, DIO0);
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
  Serial.println(buf);
  buf = "";
}


void loop() {
  // check the network connection once every 10 seconds:
  if (!wifiClient.connected()) {
    InitWiFi();
    InitMqtt();
  }

  // call poll() regularly to allow the library to send MQTT keep alive which
  // avoids being disconnected by the broker
  mqttClient.poll();

  currentMillis = millis();
  currentSecs = currentMillis / 1000;
  if ((unsigned long)(currentSecs - previousSecs) >= interval) {
    seconds = seconds + 1;
    Serial.println(seconds);
    Serial.println(recipient);
    Serial.println(sender);
    if (seconds > 12) {
      seconds = 0;
    }
    
    if (seconds <= 4) {
      //String message = "10";
      //char total[3];
      //message.toCharArray(total, 3);
      //sendMessage(total, gateway_id, node1_id);
      Serial.println(gateway_id, HEX);
      Serial.println(node1_id, HEX);
      sendMessage(gateway_id, node1_id);
    } else if (seconds <= 8) {
      //String message = "20";
      //char total[3];
      //message.toCharArray(total, 3);
      Serial.println(gateway_id, HEX);
      Serial.println(node2_id, HEX);
      sendMessage(gateway_id, node2_id);
    }
    else if (seconds <= 12) {
      //String message = "30";
      //char total[3];
      //message.toCharArray(total, 3);
      Serial.println(gateway_id, HEX);
      Serial.println(node3_id, HEX);
      sendMessage(gateway_id, node3_id);
    }
    
    previousSecs = currentSecs;
    Serial.println(incoming);
    incoming = "";
    
  }
  
  // parse for a packet, and call onReceive with the result:
  //onReceive(LoRa.parsePacket());
}


void sendMessage(byte g_id, byte node_id) {
  LoRa.beginPacket();                 // start packet
  LoRa.write(node_id);              // add destination address
  LoRa.write(g_id);                   // add sender address
  //LoRa.write(outgoing.length());    // add payload length
  //LoRa.print(outgoing);             // add payload
  LoRa.endPacket();                   // finish packet and send it
}


void onReceive(int packetSize) {
  if (packetSize == 0) return;          // if there's no packet, return

  // read four bytes for packet header:
  recipient = LoRa.read();        // recipient address
  sender = LoRa.read();            // sender address
  //byte incomingMsgId = LoRa.read();   // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length
  byte sigByte1 = LoRa.read();          // incoming sigByte1
  byte sigByte2 = LoRa.read();          // incoming sigByte2

  int sigSum = sigByte1*256 + sigByte2;

  if (sender == 0XAA)
    SenderNode = "Node1: ";
  else if (sender == 0XBB)
    SenderNode = "Node2: ";
  else if (sender == 0XCC)
    SenderNode = "Node3: ";
    
  // read the data json message
  incoming = "";
  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }

  /*  
  // check length for error
  if (incomingLength != incoming.length() ) {   
    return;  // skip rest of function
  }

  // if the recipient isn't this device(0xDD) or broadcast devices(0xAA, 0xBB, 0xCC) then error
  if (recipient != node1_id && recipient != node2_id && recipient != node2_id && recipient != gateway_id) {
    return;  // skip rest of function
  }

  if (sender == 0XAA) { 
    int msgSum = 0;
    for (int i = 0; i < incoming.length(); i++) {
        msgSum += incoming.charAt(i);
      }
    
    if (msgSum == sigSum) {
      //Serial.println(incoming);
      mqttClient.beginMessage(node1_topic);
      mqttClient.print(incoming);
      mqttClient.endMessage();
    }
  } else if (sender == 0XBB) {
    int msgSum = 0;
    for (int i = 0; i < incoming.length(); i++) {
        msgSum += incoming.charAt(i);
      }
    
    if (msgSum == sigSum) {
      mqttClient.beginMessage(node2_topic);
      mqttClient.print(incoming);
      mqttClient.endMessage();
    }
  } else if (sender == 0XCC) {
    int msgSum = 0;
    for (int i = 0; i < incoming.length(); i++) {
        msgSum += incoming.charAt(i);
      }
    
    if (msgSum == sigSum) {
      mqttClient.beginMessage(node3_topic);
      mqttClient.print(incoming);
      mqttClient.endMessage();
    }
  }
  */
}
