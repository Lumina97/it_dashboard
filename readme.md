# Orange Pi IT Dashboard

A small hardware/software monitoring dashboard built around an **Orange Pi 3 LTS**, an **Arduino UNO R3**, and an **LCD1602 display**.

This project was primarily built as a hands-on introduction to **hardware prototyping, wiring, embedded devices, serial communication, and integrating Linux software with physical hardware**.

> **Status:** ✅ Prototype complete / Learning project

## What It Does

The Orange Pi collects system information such as:

* CPU usage
* RAM usage
* CPU/system temperature
* Network statistics

The information is sent over USB serial to an Arduino UNO, which handles the LCD and physical button.

The button can be used to cycle between different monitoring screens.

```text
┌─────────────────┐
│    Orange Pi    │
│                 │
│ System Monitor  │
└────────┬────────┘
         │
         │ USB Serial
         ▼
┌─────────────────┐
│   Arduino UNO   │
│                 │
│ Serial Parser   │
│ Button Handler  │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│     LCD1602     │
│                 │
│ CPU     37.5%   │
└─────────────────┘
```

## Hardware

The prototype uses:

* Orange Pi 3 LTS
* Arduino UNO R3
* LCD1602 character display
* 4-pin tactile push button
* Breadboard
* Jumper wires
* USB connection between the Orange Pi and Arduino

The LCD and button are connected directly to the Arduino.

The Arduino acts as a simple hardware interface between the Linux system and the display.

## Software Architecture

The project is divided into separate C modules rather than putting everything into one source file.

```text
it_dashboard/
├── it_dashboard.c
├── cpu.c
├── cpu.h
├── ram.c
├── ram.h
├── temp.c
├── temp.h
├── arduino.c
├── arduino.h
└── build.sh
```

### System Monitoring

The Orange Pi runs a C program that reads system information from Linux.

For example, temperature information is obtained from:

```text
/sys/class/thermal/thermal_zone0/temp
```

The kernel provides the temperature in millidegrees Celsius, which the program converts into a floating-point temperature.

CPU, RAM, and temperature functionality are separated into their own modules to keep the dashboard code organized and reusable.

### Arduino Communication

The Orange Pi communicates with the Arduino through USB serial using:

```text
/dev/ttyACM0
```

at **9600 baud**.

The monitoring program formats the system statistics into a simple message:

```text
CPU=37.5,RAM=62.1,TEMP=48.2,NET=12.4
```

The Arduino receives the message, parses the values, and updates the currently selected LCD screen.

### Arduino Interface

The Arduino handles:

* LCD output
* Serial communication
* Parsing incoming system statistics
* Button input
* Switching between display screens

## Linux Service

The dashboard was also configured to run as a **systemd service** on the Orange Pi.

This provided experience with:

* Running custom programs as services
* Automatic startup
* Restart behavior
* Working directories
* Linux users/groups
* Device permissions
* Accessing `/dev/ttyACM0`

The service allows the dashboard to run independently of an interactive terminal.

## Development Process

The project started as a simple Arduino and LCD experiment.

The initial goal wasn't to build a polished commercial device. Instead, the project was intentionally used as a **learning exercise for getting into hardware and embedded development**.

The progression was roughly:

```text
Arduino + LCD
      ↓
Physical button
      ↓
Multiple display screens
      ↓
Arduino serial input
      ↓
Orange Pi → Arduino communication
      ↓
C system monitoring
      ↓
Modular C source files
      ↓
systemd service
```

Each stage introduced another part of the hardware/software interaction.

## What I Learned

This project provided hands-on experience with:

* C programming
* Modular C program design
* Header/source file organization
* Linux system interfaces
* Linux `/sys` filesystem
* File I/O with C
* Serial communication
* Arduino development
* Embedded systems
* GPIO/button input
* LCD interfacing
* USB device communication
* systemd services
* Linux permissions
* Git/GitHub
* Breadboard prototyping
* Basic hardware troubleshooting

## Project Status

The prototype is considered **complete for its intended purpose**.

### Working

* ✅ Arduino/LCD communication
* ✅ Physical button input
* ✅ Multiple LCD screens
* ✅ Orange Pi system monitoring
* ✅ CPU monitoring
* ✅ RAM monitoring
* ✅ Temperature monitoring
* ✅ Orange Pi → Arduino serial communication
* ✅ C-based dashboard
* ✅ systemd integration

### Not Planned Right Now

The original idea included eventually designing a custom PCB and enclosure. That is **not currently part of the project's active scope**.

The prototype can be revisited in the future if I want to explore:

* Custom PCB design
* Embedded microcontrollers
* More advanced sensors
* Improved power management
* Custom enclosures

For now, this project is being kept as a record of the hardware/software concepts learned while building it.
