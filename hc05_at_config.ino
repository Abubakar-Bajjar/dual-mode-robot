/*
 * ============================================================================
 *  HC-05 MASTER/SLAVE CONFIGURATION SKETCH
 * ============================================================================
 *  Role:    Serial passthrough between the Arduino IDE Serial Monitor and
 *           an HC-05 module in AT command mode, used to configure one
 *           HC-05 as Master (remote) and the other as Slave (car), and
 *           bind them so they auto-connect on power-up.
 *
 *  Wiring:  docs/circuit-hc05-at-config.png
 *           (HC-05 must be put into AT mode — hold its button while
 *           powering on, or per your module's AT-mode procedure — before
 *           uploading/running this sketch.)
 *
 *  Usage:   Upload this sketch, open Serial Monitor at 38400 baud with
 *           "Both NL & CR" line ending, and send the AT commands below.
 * ============================================================================
 */

#include <SoftwareSerial.h>
SoftwareSerial btSerial(2, 3); // RX | TX

void setup()
{
    Serial.begin(9600);

    btSerial.begin(38400);
    Serial.println("btSerial started at 38400");
}

void loop()
{
  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
  {
    btSerial.write(Serial.read());
  }

  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (btSerial.available())
  {
    Serial.write(btSerial.read());
  }
}

/*
Slave Command (run on the CAR's HC-05):
AT
AT+RMAAD
AT+ROLE=0
AT+UART=38400,0,0
AT+ADDR


Master Commands (run on the REMOTE's HC-05):
AT
AT+RMAAD
AT+ROLE=1
AT+UART=38400,0,0
AT+CMODE=0
AT+BIND=98D3:61:F613EA  (replace with your HC-05 Slave's address, from AT+ADDR above)
*/
