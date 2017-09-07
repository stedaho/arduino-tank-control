# Arduino-Aquariensteuerung / Arduino Tank Control

## Deutsche Version

### Hardware-Komponenten
Software zur Steuerung eines Aquariums mit folgenden Komponenten:
* **Arduino Nano** als Herzstück der Steuerung
* **RTC DS1307** als Echzeituhr für den Zeitplan, angebunden per *I²C*
* **LED** zur Statusanzeige an Pin *LED_BUILTIN*
* **Schalter** zur Aktivierung des Wartungsmodus an Pin xxx
* **Giesemann PULZAR LED HO TROPIC** zur Beleuchtung des Aquariums, drei getrennt per PWM regelbare Farbkanäle:
    * *Weißer Kanal* an Pin 5
    * *Rötlicher Kanal* an Pin 9
    * *Bläulicher Kanal* an Pin 6

### Anschluss der Giesemann PULZAR LED HO
Die Aquarienbeleuchtung [Giesemann PULZAR LED HO](http://www.giesemann.de/717,1,PULZAR-LED,.html) führt ohne weitere Adapter über einen USB-Stecker die PWM-Kanäle der drei LED-Treiberbausteine (*Microchip/Micrel MIC3203*) und eine Masseleitung heraus. Die Masse liegt dabei auf der *Schirmung* des USB-Anschlusses, die PWM-Leitungen der drei Kanäle liegen auf den USB-Leitungen *VCC*, *Data+* und *Data-*. In der Lampe werden sie über einen 10k-Ohm-Widerstand auf 3V gezogen, damit die Lampe voll leuchtet, wenn das USB-Kabel nirgends angeschlossen ist. Die USB-Leitung *GND* ist nicht belegt.
Dank der kompatiblen Pegel können die entsprechenden Leitungen direkt mit den PWM-fähigen Ausgängen des Arduino Nano verbunden werden, die Masseleitung wird mit der Masse des Arduino verbunden.
Beim Anschluss ist Vorsicht geboten, da diese Ansteuerung keine offizielle Funktion darstellt und die Schaltung deshalb auch nicht vor Verpolung, Überspannung etc. geschützt ist.

### Beschreibung
*TBD*


## English version

### Hardware components
Software for controlling a fish tank with the following components:
* **Arduino Nano** as controller
* **RTC DS1307** as real time clock, connected via *I²C*
* **LED** for displaying the state at pin *LED_BUILTIN*
* **Switch** to activate the maintenance mode at pin xxx
* **Giesemann PULZAR LED HO TROPIC** for lighting the tank, three color channels to be controlled separately via PWM:
    * *White channel* at pin 5
    * *Red channel* at pin 9
    * *Blue channel* at pin 6

### Connecting the Giesemann PULZAR LED HO
The wires of the USB cable of the [Giesemann PULZAR LED HO](http://www.giesemann.de/717,2,,.html) can be connected directly to the Arduino Nano.
Ground is the USB *shield*, and the USB wires *VCC*, *Data+* und *Data-* are the PWM inputs of the three LED drivers (*Microchip/Micrel MIC3203*) which can be connected to the Arduino's PWM outputs.
The PWM wires are pulled up via a 10k-Ohm resistor to 3V to let the light shine with full brightness  when it is not connected via the USB cable.
Please be careful when connecting the wires as this is not officially supported and therefore has no protection against voltage reversal nor overvoltage.

### Description
*TBD*