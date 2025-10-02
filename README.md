# ESP32 Web Server for LED Control

This project hosts a web server on an ESP32 board. It allows a user on the same Wi-Fi network to turn the ESP32's built-in blue LED on and off using buttons on a simple webpage.

## Hardware
* ESP32 Development Board

## How to Use
1.  Open the `.ino` file in the Arduino IDE.
2.  Change the `ssid` and `password` variables to your Wi-Fi network credentials.
3.  Upload the sketch to your ESP32.
4.  Open the Arduino Serial Monitor (baud rate 115200) and press the ESP32's reset button to see its IP address.
5.  Enter that IP address into any web browser on the same network to control the LED.
