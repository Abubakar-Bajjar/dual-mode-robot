# Wiring Reference

Derived from the Fritzing diagrams in this folder — open the PNGs alongside
this table for the full picture.

## Remote / Transmitter (`circuit-transmitter-remote.png`)

| Component | Pin | Arduino Nano Pin |
|---|---|---|
| HC-05 (Master) | TXD | D2 |
| HC-05 (Master) | RXD | D3 |
| HC-05 (Master) | GND | GND |
| HC-05 (Master) | VCC | 5V |
| Left Joystick | VRx | A0 |
| Left Joystick | VRy | A1 |
| Right Joystick | VRx | A2 |
| Right Joystick | VRy | A3 |
| Both Joysticks | GND / +5V | shared GND / 5V bus |
| 7-12V Rechargeable Battery | + / − | VIN / GND |

## Car / Receiver (`circuit-receiver-car.png`)

| Component | Pin | Arduino Nano Pin |
|---|---|---|
| HC-05 (Slave) | TXD | D2 |
| HC-05 (Slave) | RXD | D3 |
| HC-05 (Slave) | GND | GND |
| HC-05 (Slave) | VCC | 5V |
| L298N | ENA (right motors) | D5 |
| L298N | IN1 | D7 |
| L298N | IN2 | D8 |
| L298N | ENB (left motors) | D6 |
| L298N | IN3 | D9 |
| L298N | IN4 | D10 |
| L298N | OUT1 / OUT2 | Right Motor 1 + Right Motor 2 (paralleled) |
| L298N | OUT3 / OUT4 | Left Motor 1 + Left Motor 2 (paralleled) |
| L298N | +12V / GND | Battery pack |
| L298N | +5V out | Powers the Nano + HC-05 |

## HC-05 AT-Mode Configuration (`circuit-hc05-at-config.png`)

Simple passthrough wiring for configuring either HC-05 module:

| Component | Pin | Arduino Nano Pin |
|---|---|---|
| HC-05 | TXD | D2 |
| HC-05 | RXD | D3 |
| HC-05 | GND | GND |
| HC-05 | VCC | 5V |

Run `firmware/hc05_configuration/hc05_at_config.ino`, open Serial Monitor at
38400 baud, and issue the AT commands in the sketch's header comment — once
on the Slave (car) HC-05 to get its address, then on the Master (remote)
HC-05 to bind to that address.

## Obstacle-Avoidance Reference Build (`circuit-obstacle-avoidance-reference.png`)

This is a separate, standalone autonomous build (no Bluetooth) — a servo
pans an HC-SR04 ultrasonic sensor left/right to pick the clearer direction
when an obstacle is detected.

| Component | Pin |
|---|---|
| HC-SR04 TRIG | D3 |
| HC-SR04 ECHO | D2 |
| Servo (ultrasonic pan) | D5 |
| L298N ENA | D11 |
| L298N IN1 | D10 |
| L298N IN2 | D9 |
| L298N ENB | D6 |
| L298N IN3 | D8 |
| L298N IN4 | D7 |
| Push button | mode/start trigger |
| 3x 18650 battery pack | L298N +12V / GND |

**Note:** this build uses a different pin layout than the manual-RC car
(it was wired independently, board-agnostic Uno/Nano). If you combine both
modes onto a single car chassis and controller, reconcile the two pin maps
before merging the sketches.
