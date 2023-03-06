# FAQ (Frequently Asked Questions)
Here is the latest, up to date FAQ.
This file was autogenerated by running 'node scripts/getcommands.js' in the repository.
All questions/answers were taken from json file.

**Question:** *What is channel?*<br>**A:** Channel is like variable, but in case of most simple devices, you can think about channels like about relay slots. If you have two relays and two buttons, and you want to link relay with button, then you just set the same channel index for given relay and button. That way you can have many buttons and relays on the same device.<br>Futhermore, channels are used to index the PWM outputs for LEDs. The expected PWM order is RGBCW (Red,Green,Blue,Cool,Warm), so you should make sure your channels order is correct if you have mixed colors.<br>Our firmware supports both numbering of channels starting with 0 and with 1.<br>Channels are set on per-pin basis in the basic Module Pins Configuration panel.<br> Some special pins might support setting two channels, for example, a Button role can have two channels set, first channel is toggled on click, second on double click.<br>


**Question:** *What is channel type?*<br>**A:** Channel types are required usually only on TuyaMCU devices.<br> Channel type determines the way the channel value is displayed on GUI. Channels are like variables, so they might contain anything, including data mapped from TuyaMCU, so for example, to display temperature data you might need to set Temperature channel type for the channel you linked to temperature dpID of your device. The same goes for TuyaMCU fan speeds (OffLowMidHigh,etc), dimmers, toggles, etc


**Question:** *I entered wrong SSID and my device is not accessible. How to recover?*<br>**A:** Do five short power on/power off cycles (but not too short, because device might have capacitors and they need to discharge every time). Device will go back to AP mode (aka Safe Mode). Remember that in Safe Mode, pins are disabled, drivers are also not run, so don't worry if you see your device seemingly not responding to buttons, etc, etc.


**Question:** *How do I enable more logging? How to make more logs visible?*<br>**A:** First type 'loglevel x' in console, where x is 0 to 7, default value is 3 (log all up to info), value 4 will also log debug logs, and value 5 will include 'extradebug'. Then, on online panel, also switch filter to 'All' (both steps must be done for logs to show up)


**Question:** *How to make device discoverable by Windows?*<br>**A:** OpenBeken devices will show up in Windows Network if you run SSDP driver. This driver must be run at each startup. You could just do 'startDriver SSDP' in console but that will not run again after reboot, so either use Short Startup Command or autoexec.bat to run that command with each reboot


**Question:** *How to make device discoverable by Alexa?*<br>**A:** Just like with SSDP, but in this case you MUST run both SSDP and Wemo drivers. So, use that command for startup: backlog startDriver SSDP; startDriver Wemo


**Question:** *I somehow lost my MAC address and I am unable to change it in Options! My MAC ends with 000000, how to fix?*<br>**A:** You have most likely overwrote the TLV header of RF partition of BK7231. For BK7231T, we have a way to restore it - open Web App, go to Flash tab, and press 'Restore RF Config'


**Question:** *How do I setup single button to control two relays (first on click, second on double click)?*<br>**A:** If you set a pin role to 'Button', you will get a second textbox after saving pins. First checkbox is a channel to toggle on single click, and second textbox is a channel to toggle on double click.


**Question:** *My wall touch switch reacts slowly! It's laggy, how to make it react instantly?*<br>**A:** It's like with Tasmota - go to our Options/General-Flags and set flag '6 - [BTN] Instant touch reaction instead of waiting for release (aka SetOption 13)'


**Question:** *How to setup device with two relays and two buttons?*<br>**A:** Determine which IO pins are used for relays and buttons, then for first relay and button set channel 1, and for second relay and button set channel 2


**Question:** *How to setup RGB LED?*<br>**A:** Determine whether this LED is using 'I2C' LED driver like SM2135, or is it using PWMs. If it's using PWMs, just check which 3 GPIO pins are used for colours, and set PWM roles for them, keep channels in RGB order - Red is 1, Green is 2, Blue is 3 (altough firmware will also support indexing started from 0)


**Question:** *How to setup RGB LED which is using 'I2C' LED driver like SM2135?*<br>**A:** In case of SM2135 and similiar LED drivers, you need to figure out two pins - SDA and SCL lines of that driver. Set their roles for pins, then reboot. Then the LED driver will start, but you may also need to remap the order of colours with appropriate Map function, for example with SM2135_Map 0 2 1 3 4


**Question:** *How to enter multiple startup commands? For example, to start both NTP and BL0942 drivers?*<br>**A:** Use backlog - like in Tasmota. Open Config->Short startup command, and enter, for example: backlog startDriver BL0942; startDriver NTP; ntp_setServer 217.147.223.78.<br> Second option would to be open the Web Application, go to LittleFS tab, and just create autoexec.bat and enter commands there, each in new line.


**Question:** *How to configure ping watchdog to do a relay cycle when given IP does not respond for a given amount of time?*<br>**A:** See the following example there: https://www.elektroda.com/rtvforum/viewtopic.php?p=20368812#20368812


**Question:** *How to set relay state on device boot? (PowerOnState)?*<br>**A:** There are two ways. <br> First way is to use Config -> Startup state and set it from GUI here. <br> Second way is to use short startup command from Options or create 'autoexec.bat' in LittleFS file system in web panel and execute commands from there.<br>For example, for RGBCW LED, to set 100% dimmer and red color on start, you can do startup command:<br> ```backlog led_dimmer 100; led_basecolor_rgb #FF0000; led_enableAll 1```<br>For simple relay, in this example on channel number 5, you can do:<br>```backlog SetChannel 5 1```<br>

