# Dual-Mode Robot — Obstacle Avoidance & Racing

A robot project with two operating modes: an autonomous **obstacle-avoidance
mode** (servo-scanning ultrasonic sensor) and a manual **racing mode**
(dual-joystick RC control over Bluetooth).

## Objective

Design and build a robot capable of switching between two modes: an
obstacle-avoiding mode for autonomous navigation, and a racing mode for
speed and maneuverability.

## Components

- Arduino Nano x2 (remote + car) for the manual RC build
- HC-05 Bluetooth module x2 (one Master, one Slave)
- L298N H-bridge motor driver
- 4x DC motors (2 left, 2 right) + wheels
- Dual analog joysticks (left stick = throttle, right stick = steering)
- HC-SR04 ultrasonic sensor + SG90 servo (obstacle-avoidance build)
- 7-12V rechargeable battery packs

## How It Works

### Racing Mode — Manual RC (`firmware/manual_rc_mode/`)

- The remote reads both joysticks, maps each axis to a 0-254 range with a
  center deadband, and streams `lx,ly,rx,ry` over HC-05 (Master) at 38400
  baud, 10ms per packet.
- The car (HC-05 Slave) parses each packet, derives throttle (left stick Y)
  and steering (right stick X), mixes them into left/right motor speeds
  (tank-style), and drives the L298N accordingly.
- If no packet is received for 1 second (connection lost), the car stops.

### Obstacle-Avoidance Mode (`firmware/obstacle_avoidance_mode/`)

- Standalone autonomous build. Drives forward until the HC-SR04 detects
  something within 25cm.
- On detection: stops, reverses briefly, then pans the servo-mounted
  ultrasonic sensor left and right, compares the two distance readings, and
  turns toward whichever side is more open.

### HC-05 Setup (`firmware/hc05_configuration/`)

- A serial-passthrough sketch for issuing AT commands to each HC-05: sets
  one as Slave (car) and reads its address, then sets the other as Master
  (remote) and binds it to that address so the pair auto-connects on
  power-up with no phone/PC needed.

## Repo Structure

```
robot-project/
├── firmware/
│   ├── manual_rc_mode/
│   │   ├── remote_transmitter/remote_transmitter.ino
│   │   └── car_receiver/car_receiver.ino
│   ├── obstacle_avoidance_mode/
│   │   └── obstacle_avoidance.ino
│   └── hc05_configuration/
│       └── hc05_at_config.ino
├── docs/
│   ├── circuit-transmitter-remote.png
│   ├── circuit-receiver-car.png
│   ├── circuit-hc05-at-config.png
│   ├── circuit-obstacle-avoidance-reference.png
│   └── wiring-table.md
└── README.md
```

## Flashing

1. Configure both HC-05 modules first (see `hc05_configuration/`).
2. Flash `remote_transmitter.ino` to the remote's Nano.
3. Flash `car_receiver.ino` to the car's Nano for RC/racing mode, **or**
   `obstacle_avoidance.ino` to the autonomous build for obstacle-avoidance
   mode.

> Note: as currently built, racing mode and obstacle-avoidance mode are two
> separate sketches/pin layouts rather than one mode-switching sketch — see
> `docs/wiring-table.md` for the pin differences if you want to merge them
> onto a single chassis with a mode-toggle switch.

## Applications

- **Search & rescue:** racing mode for fast traversal of open ground,
  obstacle-avoidance mode for navigating debris/rubble autonomously.
- **Warehouse logistics:** autonomous obstacle-avoidance for general
  transport, switchable to manual override for precise maneuvering.
