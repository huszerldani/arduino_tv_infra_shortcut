# IR Remote Control for Arduino

This project allows you to control various functions on your devices using an IR remote. When specific buttons are pressed on the remote, the Arduino sends a sequence of IR commands to execute predefined shortcuts. This can be used for tasks such as setting a sleep timer or adjusting the brightness of a screen.

## Features

- **Sleep Timer Shortcuts**: Set sleep timers of 60 or 90 minutes.
- **Screen Brightness Adjustment**: Easily darken or lighten the screen.
- **Customizable Shortcuts**: Modify or add new button sequences to suit your needs.

## Hardware Requirements

- Arduino board (e.g., Arduino Uno)
- IR receiver module
- IR LED transmitter
- Remote control (compatible with the IR receiver)

## Software Requirements

- Arduino IDE
- IRremote library by shirriff (installable via Arduino Library Manager)

## Installation

1. **Clone the Repository**
   ```bash
   git clone https://github.com/huszerldani/ir-remote-control-arduino.git
   cd ir-remote-control-arduino
