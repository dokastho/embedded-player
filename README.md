# OLED Display Music Player
 
This project is meant to showcase my skills in embedded systems development. It is a BT-connected music player with an OLED display for personalized graphics.

This project will be flashed to an RP2040 MCU with a 128x64 OLED display connected over a SPI bus.

# State Diagram

## Idle State

- Enter into bluetooth pairing mode and search for discoverable devices
- Open terminal and display info & potential items
- Prompt for input to pair or navigate info menu
- Transition to running state when a device is paired

## Running State

- Connected to a BT sink
- Streams music to that device and displays gfx
- Transitions to idle state when the sink device disconnects

## Running Inner-State Transitions

- Media controls will seek through tracks on the playlist, temporarily suspend running state on pause
