# humidityI2CLCD
Simple Arduino application to monitor humidity and temperature with sensors

I do not have experience how to document breadboard information in digital format besides taking a photo of it and listing all components.
When I have more information, I will update this accordingly.

For now, this sketch measures the humidity and temperature from DHT22 sensor and displays it on the 16x2 LCD matrix display using the I2C interface.
If humidity is below 30% or above 50% then blue LED flashing alarm will go on.
If temperature is below 20 and above 30 then red LED flashing alarm will go on.

Future things:
* Find better humidity and temperature sensor
* Integrate photosensor to control LED brightness in the darkness. If the room is dark then lower the brightness.
* Restructure the code to see if there are some sort of thread emulation or Actor pattern in place. As I understood, Arduino does not support threads for a good reason
* Add buzzer if it is not too annoying
* Add Wifi module to send data on some IoC platform which allows monitoring from the mobile phone.
