/*
 *  Simple sketch for reading BME280 sensor values
 */
#include <Adafruit_BME280.h>

// BME280 sensor
Adafruit_BME280 bme;

// BME280 sensor values
#define SEALEVELPRESSURE_HPA (1013.25)

// delay between output in ms
long DELAY = 1000;

// set this to true to use weather profile + force mode sensor query
boolean SET_PROFILE_WEATHER = true;

void setup() {
    Serial.begin(115200);

    // init sensor i2c
    bme.begin(0x76);

    // enable weather profile?
    if (SET_PROFILE_WEATHER) {
        // apply BME280 to weather monitoring settings
        // see https://github.com/adafruit/Adafruit_BME280_Library/blob/master/examples/advancedsettings/advancedsettings.ino for details

        // weather monitoring
        Serial.println("-- Weather Station Scenario --");
        Serial.println("forced mode, 1x temperature / 1x humidity / 1x pressure oversampling,");
        Serial.println("filter off");
        bme.setSampling(Adafruit_BME280::MODE_FORCED,
                        Adafruit_BME280::SAMPLING_X1,  // temperature
                        Adafruit_BME280::SAMPLING_X1,  // pressure
                        Adafruit_BME280::SAMPLING_X1,  // humidity
                        Adafruit_BME280::FILTER_OFF);

        // recommended delay for weather monitoring
        DELAY = 60000;
    }
}

// ##########################################
// Main Loop ################################
// ##########################################

void loop() {
    if (SET_PROFILE_WEATHER) {
        // Only needed in forced mode! In normal mode, you can remove the next line.
        boolean measureOk = bme.takeForcedMeasurement();  // has no effect in normal mode
        Serial.print("measure ok: ");
        Serial.println(measureOk);
    }

    Serial.print("temp: ");
    Serial.println(bme.readTemperature());

    Serial.print("humidity: ");
    Serial.println(bme.readHumidity());

    Serial.print("pressure: ");
    Serial.println((bme.readPressure() / 100.0F));

    Serial.print("altitude: ");
    Serial.println(bme.readAltitude(SEALEVELPRESSURE_HPA));

    delay(DELAY);
}
