
#include <Wire.h>
int ArduinoLED = 13;

#include "ScioSense_ENS160.h"  // ENS160 library
ScioSense_ENS160      ens160(ENS160_I2CADDR_1);

#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

#include "Multichannel_Gas_GMXXX.h"

GAS_GMXXX<TwoWire> gas;                               // Multichannel gas sensor v2

#define target              0                         // target label 0: alcohol, 1: paint thinner, 2: unidentifiable, 3: ambient

void setup() {
    Serial.begin(115200);

    while (!Serial) {}
    unsigned status;
    gas.begin(Wire, 0x08);
    status = bme.begin();  
        // You can also pass in a Wire library object like &Wire2
        // status = bme.begin(0x76, &Wire2)
        if (!status) {
            Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
            Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
            Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
            Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
            Serial.print("        ID of 0x60 represents a BME 280.\n");
            Serial.print("        ID of 0x61 represents a BME 680.\n");
            while (1) delay(10);
        }
        
        Serial.println("-- Default Test --");

    //Switch on LED for init
    pinMode(ArduinoLED, OUTPUT);
    digitalWrite(ArduinoLED, LOW);

    Serial.println("------------------------------------------------------------");
    Serial.println("ENS160 - Digital air quality sensor");
    Serial.println();
    Serial.println("Sensor readout in standard mode");
    Serial.println();
    Serial.println("------------------------------------------------------------");
    delay(1000);

    Serial.print("ENS160...");
    ens160.begin();
    Serial.println(ens160.available() ? "done." : "failed!");
    if (ens160.available()) {
        // Print ENS160 versions
        Serial.print("\tRev: "); Serial.print(ens160.getMajorRev());
        Serial.print("."); Serial.print(ens160.getMinorRev());
        Serial.print("."); Serial.println(ens160.getBuild());
    
        Serial.print("\tStandard mode ");
        Serial.println(ens160.setMode(ENS160_OPMODE_STD) ? "done." : "failed!");
    }
}

void loop() {
    float gm_no2_v;
    float gm_eth_v;
    float gm_voc_v;
    float gm_co_v;
    float ens_TVOC;
    float ens_CO2;
    float bme_temp;
    float bme_pressure;
    float bme_altitude;
    float bme_humidity;

    // Serial.println("gm_voc_v, gm_no2_v, gm_eth_v, gm_co_v, ens_tvoc, ens_co2, bme_temp, bme_pressure, bme_altitude, bme_humidity, target");

    // Read from sensors
    gm_no2_v = gas.calcVol(gas.getGM102B());
    gm_eth_v = gas.calcVol(gas.getGM302B());
    gm_voc_v = gas.calcVol(gas.getGM502B());
    gm_co_v = gas.calcVol(gas.getGM702B());
    ens160.measure(0);
    ens_TVOC = ens160.getTVOC();
    ens_CO2 = ens160.geteCO2();
    bme_temp = bme.readTemperature();
    bme_pressure = bme.readPressure();
    bme_altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
    bme_humidity = bme.readHumidity();


    Serial.print(timestamp);
    Serial.print(",");
    Serial.print(gm_voc_v);
    Serial.print(",");
    Serial.print(gm_no2_v);
    Serial.print(",");
    Serial.print(gm_eth_v);
    Serial.print(",");
    Serial.print(gm_co_v);
    Serial.print(",");
    Serial.print(ens_TVOC);
    Serial.print(",");
    Serial.print(ens_CO2);
    Serial.print(",");
    Serial.print(bme_temp);
    Serial.print(",");
    Serial.print(bme_pressure);
    Serial.print(",");
    Serial.print(bme_altitude);
    Serial.print(",");
    Serial.print(bme_humidity);
    Serial.print(",");
    Serial.print(target);
    Serial.println();
    delay(100);
}

