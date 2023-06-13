README.MD
# ESP32_Bluetooth_Page_Turner

The ESP32 Bluetooth Page Turner is a programmable controller designed for tablets and e-readers. It allows precise control over your device, acting as a versatile page turner. The software runs on Arduino, simulating mouse and keyboard actions for effective interaction.

One of the core features of this software is the customization it offers to the users. It acknowledges the diversity in resolution among different tablets and e-readers. By modifying the defined parameters WIDTH and HEIGHT, you can adjust the software according to your device's resolution, ensuring maximum compatibility and effectiveness.

## Features
Resolution Adjustment: Tailor the page turner to your specific device by adjusting the WIDTH and HEIGHT parameters in the code. This allows for smooth operation on devices with various screen sizes and resolutions.

Mode Switching: Switch between three operational modes (MODE1, MODE2, MODE3) by clicking the MODE button. Each mode carries different functionalities for the left and right buttons.

Mouse Control: In MODE1 or MODE3, the mouse behavior is controlled by the left or right buttons. MODE1 guides the mouse to either side of the screen and clicks, while MODE3 drags across the screen, simulating a page-turning gesture.

Keyboard Control: In MODE2, simulate the left or right arrow keys on the keyboard by clicking the left or right button respectively.

## Usage
Cycle through the modes by clicking the MODE button. Each click will switch the mode in the following order: MODE1 > MODE2 > MODE3 > MODE1.
Depending on the current mode, execute corresponding operations by clicking the left or right button.

## Customization
Customize the behavior of the mouse and keyboard for each mode by altering the code. For instance, if you wish to simulate the action of a space bar when the left button is clicked in MODE2, modify the leftButtonMode2Action() function. Notably, the WIDTH and HEIGHT parameters can be adjusted to match your specific device's resolution, offering a customized and enhanced reading experience.

## Hardware Configuration
LED_OUTPUT_PIN -> GPIO2
BUTTON_MODE_INPUT_PIN  -> GPIO5
BUTTON_LEFT_INPUT_PIN -> GPIO18
BUTTON_RIGHT_INPUT_PIN -> GPIO19

## Libraries Used
This program uses the [ESP32-BLE-Combo](https://github.com/blackketter/ESP32-BLE-Combo) library to simulate Bluetooth mouse and keyboard behavior. Please ensure that this library is properly installed before running the program.
