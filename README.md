# nice!view Press Start

The nice!view Press Start is a retro-themed ZMK module based on https://github.com/kevinpastor/nice-view-elemental

What has been changed compared to Elemental : 
- Canvases were moved to make more room for **new animations**;
- **New custom font** to match retro theme;
- Provides a **fully vertical UI**;
- **New animations** based on Pokemon Gold from GBC and Wild Gunmen from NES (Pegasus). 

Didn't change things that were already perfect like battery and connectivity icons - **big big kudos** to https://github.com/kevinpastor for creating such good project. 
I'm no developer, but it allowed me to learn enough coding to make this happen. 

## Gallery

![Animation Preview](./assets/Animations.gif)

## Installation

Few changes are needed to your keyboard configuration's build setup, rebuild and flash your keyboard firmware.

1. In the `config/west.yml` file, add a new remote and its related project. 

```diff
manifest:
  remotes:
    - name: zmkfirmware
      url-base: https://github.com/zmkfirmware
+   - name: Ziembski
+     url-base: https://github.com/Ziembski
  projects:
    - name: zmk
      remote: zmkfirmware
      revision: main
      import: app/west.yml
+   - name: nice-view-press-start
+     remote: Ziembski
+     revision: main
  self:
    path: config
```

2. In the `build.yaml` file, replace the `nice_view` shield with `nice_view_press_start`.

```diff
---
include:
  - board: nice_nano_v2
-   shield: corne_left nice_view_adapter nice_view
+   shield: corne_left nice_view_adapter nice_view_press_start
  - board: nice_nano_v2
-   shield: corne_right nice_view_adapter nice_view
+   shield: corne_right nice_view_adapter nice_view_press_start
```

3. Build the firmware, flash it to your keyboard, and enjoy!

## Features

### Layer Name

Since nice!view screens are actually horizontal, layer name had to be rotated to make it horizontal from users perspective.

### Battery

Displays the battery remaining power and status. **Kudos** to https://github.com/kevinpastor for creating them.

| Pictogram                                            | Description                             |
| ---------------------------------------------------- | --------------------------------------- |
| ![Battery](./assets/battery.png)                     | Displayed on normal battery use.        |
| ![Battery - Charging](./assets/battery_charging.png) | Displayed when the battery is charging. |

### Connectivity

Displays the connectivity status for both the central and peripheral halves. **Kudos** to https://github.com/kevinpastor for creating them.

#### Output

| Pictogram                                                        | Description                                                                                                                                                                            |
| ---------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| ![Connectivity - Bluetooth](./assets/connectivity_bluetooth.png) | Displayed when the keyboard output is sent via Bluetooth (e.g., when unplugged from USB). On the central half, a number will be displayed representing the selected Bluetooth profile. |
| ![Connectivity - USB](./assets/connectivity_usb.png)             | Displayed when the keyboard output is sent to USB (e.g., when plugged via USB). Only displayed on the central half.                                                                    |

#### Bluetooth

| Pictogram                                                        | Description                                                                                                                                                                       |
| ---------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| ![Bluetooth - Connected](./assets/bluetooth_connected.png)       | On the central half, displayed when the currently selected profile is connected to the host.<br />On the peripheral half, displayed when connected to the central half.           |
| ![Bluetooth - Disconnected](./assets/bluetooth_disconnected.png) | On the central half, displayed when the currently selected profile is disconnected from the host.<br />On the peripheral half, displayed when disconnected from the central half. |
| ![Bluetooth - Searching](./assets/bluetooth_searching.png)       | Displayed when the currently selected profile is not bound to any host (e.g., when `&bt BT_CLR` was just called). Only displayed on the central half.                             |

## Configuration

| Config                                          | Type | Description                                                                                                       | Default |
| ----------------------------------------------- | ---- | ----------------------------------------------------------------------------------------------------------------- | ------- |
| `CONFIG_NICE_VIEW_PRESS_START_ANIMATION`          | bool | Enables the background animation.                                                                                 | y       |
| `CONFIG_NICE_VIEW_PRESS_START_ANIMATION_FRAME_MS` | int  | Frame delay for the animation, in milliseconds.                                                                   | 250     |
| `CONFIG_NICE_VIEW_PRESS_START_BACKGROUND`         | bool | Displays a background.                                                                                            | y       |
<!--
| `CONFIG_NICE_VIEW_ELEMENTAL_CAPITALIZATION`     | bool | Enables full capitalization for the layer name.                                                                   | y       | 
-->

## Playing on your split?

Wild Gunmen can actually be "played" - try to press reset button when gunmen reach for the gun (his eyes shine) and see if you make it before flash! Almost like on NES.

## What's next?

In future I plan to add :
- more retro animations from games like Battletoads x Double Dragon, Duck Hunt and other, 
- add randomization of animations,
- change Wild Gunmen animation in a way that gun draw timing and firing speed is also randomized.
