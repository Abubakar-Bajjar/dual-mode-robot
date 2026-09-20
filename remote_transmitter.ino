/*
 * ============================================================================
 *  MANUAL RC MODE — REMOTE / TRANSMITTER
 * ============================================================================
 *  Board:   Arduino Nano (remote)
 *  Role:    Reads the Left and Right analog joysticks, maps each axis to a
 *           0-254 range (127 = center / deadband), and streams them as a
 *           CSV packet ("lx,ly,rx,ry\n") to the car over HC-05 (Master).
 *
 *  Wiring:  docs/circuit-transmitter-remote.png
 * ============================================================================
 */

#include <SoftwareSerial.h>

SoftwareSerial btSerial(2, 3); // RX | TX

struct PacketData
{
  byte lxAxisValue;
  byte lyAxisValue;
  byte rxAxisValue;
  byte ryAxisValue;
};
PacketData data;

void setup()
{
  btSerial.begin(38400);
}

// This function is used to map 0-1023 joystick value to 0-254. hence 127 is the center value which we send.
// It also adjusts the deadband in the joystick.
// Joystick values range from 0-1023. But its center value is not always 511. It is a little different.
// So we need to add some deadband around center. In our case 500-530. Any value in this deadband range is mapped to center 127.
int mapAndAdjustJoystickDeadBandValues(int value, bool reverse)
{
  if (value >= 530)
  {
    value = map(value, 530, 1023, 127, 254);
  }
  else if (value <= 500)
  {
    value = map(value, 500, 0, 127, 0);
  }
  else
  {
    value = 127;
  }

  if (reverse)
  {
    value = 254 - value;
  }
  return value;
}

void loop()
{
  data.lxAxisValue = mapAndAdjustJoystickDeadBandValues(analogRead(A0), false);
  data.lyAxisValue = mapAndAdjustJoystickDeadBandValues(analogRead(A1), false);
  data.rxAxisValue = mapAndAdjustJoystickDeadBandValues(analogRead(A2), false);
  data.ryAxisValue = mapAndAdjustJoystickDeadBandValues(analogRead(A3), false);

  String dataString;
  dataString = dataString
               + data.lxAxisValue + ","
               + data.lyAxisValue + ","
               + data.rxAxisValue + ","
               + data.ryAxisValue + "\n";

  btSerial.print(dataString);
  delay(10);
}
