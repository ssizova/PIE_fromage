
// Include Libraries
#include "Arduino.h"
#include "DCMDriverL298.h"
#include "DHT.h"
#include "FSR.h"
#include "Adafruit_NeoPixel.h"


// Pin Definitions
#define DCMOTORDRIVERL298_PIN_INT1	2
#define DCMOTORDRIVERL298_PIN_ENB	6
#define DCMOTORDRIVERL298_PIN_INT2	3
#define DCMOTORDRIVERL298_PIN_ENA	5
#define DCMOTORDRIVERL298_PIN_INT3	4
#define DCMOTORDRIVERL298_PIN_INT4	7
#define DHT_PIN_DATA	8
#define FSRSQUARE_PIN_1	A3
#define IRPROXIMITY_PIN_VOUT	A1
#define LEDRGB_1_PIN_DIN	9
#define TCS230_PIN_S1	12
#define TCS230_PIN_S0	11
#define TCS230_PIN_S3	A5
#define TCS230_PIN_S2	13
#define TCS230_PIN_OUT	10



// Global variables and defines
#define LedRGB_1_NUMOFLEDS 2
// object initialization
DCMDriverL298 dcMotorDriverL298(DCMOTORDRIVERL298_PIN_ENA,DCMOTORDRIVERL298_PIN_INT1,DCMOTORDRIVERL298_PIN_INT2,DCMOTORDRIVERL298_PIN_ENB,DCMOTORDRIVERL298_PIN_INT3,DCMOTORDRIVERL298_PIN_INT4);
DHT dht(DHT_PIN_DATA);
FSR fsrSquare(FSRSQUARE_PIN_1);
irProximity irProximity(IRPROXIMITY_PIN_VOUT);
Adafruit_NeoPixel LedRGB_1(LEDRGB_1_PIN_DIN);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    dht.begin();
    LedRGB_1.begin(); // This initializes the NeoPixel library.
    LedRGB_1.show(); // Initialize all leds to 'off'
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // L298N Motor Driver with Dual Hobby DC motors - Test Code
    //Start both motors. note that rotation direction is determined by the motors connection to the driver.
    //You can change the speed by setting a value between 0-255, and set the direction by changing between 1 and 0.
    dcMotorDriverL298.setMotorA(200,1);
    dcMotorDriverL298.setMotorB(200,0);
    delay(2000);
    //Stop both motors
    dcMotorDriverL298.stopMotors();
    delay(2000);

    }
    else if(menuOption == '2') {
    // DHT22/11 Humidity and Temperature Sensor - Test Code
    // Reading humidity in %
    float dhtHumidity = dht.readHumidity();
    // Read temperature in Celsius, for Fahrenheit use .readTempF()
    float dhtTempC = dht.readTempC();
    Serial.print(F("Humidity: ")); Serial.print(dhtHumidity); Serial.print(F(" [%]\t"));
    Serial.print(F("Temp: ")); Serial.print(dhtTempC); Serial.println(F(" [C]"));

    }
    else if(menuOption == '3') {
    // Force Sensitive Resistor - Square - Test Code
    // Read FSR resistance value. try also fsrSquare.getResistance()
    // For more information see Sparkfun website - www.sparkfun.com/products/9375
    // Note, the default Vcc and external resistor values for FSR calculations are 5V ang 3300Okm, if you are not 
    //       using these default valuse in your circuit go to FSR.cpp and change default values in FSR constructor
    float fsrSquareForce = fsrSquare.getForce();
    Serial.print(F("Force: ")); Serial.print(fsrSquareForce); Serial.println(F(" [g]"));

    }
    else if(menuOption == '4')
    {
    // Disclaimer: The Infrared Proximity Sensor Long Range - Sharp GP2Y0A02YK0F is in testing.
    float irProximityDistance = irProximity.getDistance();
    Serial.print(F("Distance: ")); Serial.print(irProximityDistance); Serial.println(F(" [m]"));

    }
    else if(menuOption == '5') {
    // LED - RGB Addressable, PTH, 5mm Diffused (5 Pack) #1 - Test Code
    for(int i=0 ; i <= LedRGB_1_NUMOFLEDS ; i++){
    for (int k = 0 ; k <= 255 ; k++) {
    // set leds Color to RGB values, from 0,0,0 up to 255,255,255
    LedRGB_1.setPixelColor(i, LedRGB_1.Color(255-k,k,100)); // turn on green color on led #i.
    if (i > 0)
    LedRGB_1.setPixelColor(i-1, LedRGB_1.Color(0,0,0)); // turn off last led
    LedRGB_1.show(); //update led color to the hardware.
    delay(1);
    }
    }

    }
    else if(menuOption == '6')
    {
    // TCS230 Color RGB Sensor
    // Setting red filtered photodiodes to be read
    digitalWrite(TCS230_PIN_S2,LOW);
    digitalWrite(TCS230_PIN_S3,LOW);
    // Reading the output frequency
    frequency = pulseIn(TCS230_PIN_OUT, LOW);
    // Printing the value on the serial monitor
    Serial.print("R= ");//printing name
    Serial.print(frequency);//printing RED color frequency
    Serial.print("  ");
    delay(100);
    // Setting Green filtered photodiodes to be read
    digitalWrite(TCS230_PIN_S2,HIGH);
    digitalWrite(TCS230_PIN_S3,HIGH);
    // Reading the output frequency
    frequency = pulseIn(TCS230_PIN_OUT, LOW);
    // Printing the value on the serial monitor
    Serial.print("G= ");//printing name
    Serial.print(frequency);//printing RED color frequency
    Serial.print("  ");
    delay(100);
    // Setting Blue filtered photodiodes to be read
    digitalWrite(TCS230_PIN_S2,LOW);
    digitalWrite(TCS230_PIN_S3,HIGH);
    // Reading the output frequency
    frequency = pulseIn(TCS230_PIN_OUT, LOW);
    // Printing the value on the serial monitor
    Serial.print("B= ");//printing name
    Serial.print(frequency);//printing RED color frequency
    Serial.println("  ");
    delay(100);
    
    
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) L298N Motor Driver with Dual Hobby DC motors"));
    Serial.println(F("(2) DHT22/11 Humidity and Temperature Sensor"));
    Serial.println(F("(3) Force Sensitive Resistor - Square"));
    Serial.println(F("(4) Infrared Proximity Sensor Long Range - Sharp GP2Y0A02YK0F"));
    Serial.println(F("(5) LED - RGB Addressable, PTH, 5mm Diffused (5 Pack) #1"));
    Serial.println(F("(6) TCS230 Color RGB Sensor"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing L298N Motor Driver with Dual Hobby DC motors"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing DHT22/11 Humidity and Temperature Sensor"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing Force Sensitive Resistor - Square"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing Infrared Proximity Sensor Long Range - Sharp GP2Y0A02YK0F - note that this component doesn't have a test code"));
    		else if(c == '5') 
    			Serial.println(F("Now Testing LED - RGB Addressable, PTH, 5mm Diffused (5 Pack) #1"));
    		else if(c == '6') 
    			Serial.println(F("Now Testing TCS230 Color RGB Sensor - note that this component doesn't have a test code"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

/*******************************************************
*    Modified by Clément CAPORAL

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/