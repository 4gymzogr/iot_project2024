#include <LoRa.h>
#include "bsec.h"

// Helper functions declarations
void checkIaqSensorStatus(void);
void errLeds(void);

// Create an object of the class Bsec
Bsec iaqSensor;

String output;

int counter = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  //pinMode(LED_BUILTIN, OUTPUT);
  iaqSensor.begin(BME68X_I2C_ADDR_HIGH, Wire);
  output = "\nBSEC library version " + String(iaqSensor.version.major) + "." + String(iaqSensor.version.minor) + "." + String(iaqSensor.version.major_bugfix) + "." + String(iaqSensor.version.minor_bugfix);
  Serial.println(output);
  checkIaqSensorStatus();

  bsec_virtual_sensor_t sensorList[13] = {
    BSEC_OUTPUT_IAQ,
    BSEC_OUTPUT_STATIC_IAQ,
    BSEC_OUTPUT_CO2_EQUIVALENT,
    BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
    BSEC_OUTPUT_RAW_TEMPERATURE,
    BSEC_OUTPUT_RAW_PRESSURE,
    BSEC_OUTPUT_RAW_HUMIDITY,
    BSEC_OUTPUT_RAW_GAS,
    BSEC_OUTPUT_STABILIZATION_STATUS,
    BSEC_OUTPUT_RUN_IN_STATUS,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
    BSEC_OUTPUT_GAS_PERCENTAGE
  };

  iaqSensor.updateSubscription(sensorList, 13, BSEC_SAMPLE_RATE_LP);
  checkIaqSensorStatus();

  Serial.println("LoRa Sender");
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
}


void loop() {

  if (iaqSensor.run()) { // If new data is available
   
    //Serial.print("Sending packet: ");
  
    // send packet
    LoRa.beginPacket();
  
    LoRa.print("Pressure: ");
    LoRa.print(iaqSensor.pressure);
    LoRa.print(" Pa, ");

    LoRa.print("Temperature: ");
    LoRa.print(iaqSensor.temperature);
    LoRa.print(" *C, ");

    LoRa.print("Humidity: ");
    LoRa.print(iaqSensor.humidity);
    LoRa.print(" %, ");

    LoRa.print("IAQ: ");
    LoRa.print(iaqSensor.iaq);
    LoRa.print(" PPM, ");

    LoRa.print("CO2: ");
    LoRa.print(iaqSensor.co2Equivalent);
    LoRa.print(" PPM");

    LoRa.write('-');
    LoRa.print(counter);
    LoRa.endPacket();  
  }
  counter++;
  delay(1000);
}

// Helper function definitions
void checkIaqSensorStatus(void)
{
  if (iaqSensor.bsecStatus != BSEC_OK) {
    if (iaqSensor.bsecStatus < BSEC_OK) {
      output = "BSEC error code : " + String(iaqSensor.bsecStatus);
      Serial.println(output);
      for (;;)
        errLeds(); /* Halt in case of failure */
    } else {
      output = "BSEC warning code : " + String(iaqSensor.bsecStatus);
      Serial.println(output);
    }
  }

  if (iaqSensor.bme68xStatus != BME68X_OK) {
    if (iaqSensor.bme68xStatus < BME68X_OK) {
      output = "BME68X error code : " + String(iaqSensor.bme68xStatus);
      Serial.println(output);
      for (;;)
        errLeds(); /* Halt in case of failure */
    } else {
      output = "BME68X warning code : " + String(iaqSensor.bme68xStatus);
      Serial.println(output);
    }
  }
}

void errLeds(void)
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}
