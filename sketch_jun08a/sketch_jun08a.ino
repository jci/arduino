#include <Wire.h> 
#include <Adafruit_BMP085.h>

// Connect Vcc pin of the BMP085 to the Arduino pin 3.3V (5.0V NOT USE!) 
// Connect GND pin module to the Arduino GND 
// Connect the SCL pin module to analog pin 5 Arduino 
// Connect pin SDA module to pin 4 of analog Arduino 
// pin EOC (end of conversion) unused 
// XCLR pin is a reset pin is not used

Adafruit_BMP085 bmp;

void setup ()
{
   Serial.println ( "Sensor BMP085" );
  Serial.begin ( 9600 );
   if (bmp.begin ()) {
  Serial.println ( "Sensor BMP085 not found, check the connections!" );
   while ( 1 ) {}
  }
}

void loop ()
{
  Serial.println ( "Sensor BMP085 000" );
    Serial.print ( "Temperature =" );
    Serial.print (bmp.readTemperature ());
    Serial.println ( "C *" );

    Serial.print ( "Pressure =" );
    Serial.print (bmp.readPressure ());
    Serial.println ( "Pa" );

    // Calculate the elevation using the barometric pressure pattern 
    // of 1013.25 millibar = 101325 Pascal 
    Serial.print ( "Altitude =" );
    Serial.print (bmp.readAltitude ());
    Serial.println ( "m" );

  // It is possible to draw a more accurate measurement if you know 
  // the pressure at sea level, which varies with time / climate. 
  // If it is 1015 millibars, equals 101,500 Pascals.

    Serial.print ( "real Altitude =" );
    Serial.print (bmp.readAltitude ( 101500 ));
    Serial.println ( "m" );
    Serial.println ();

    delay ( 100 );
}
