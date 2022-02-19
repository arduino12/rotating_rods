# rotating_rods
Rotating Rods - 22 large vertical rods (X aluminum profiles) rotates to create visual patterns.  
Based on Dan Reisinger's artwork.  

Built by Didi and Drora Vardi  
Wired by Shy Vardi  
HW & SW development by Arad :)  

### Software
* Same code for all Arduinos! - the role (slave / master) is determined on runtime by reading D2-D4 that encodes the Arduino index.
* Uses [AccelStepper](https://github.com/waspinator/AccelStepper.git) library for smoth non-blocking control of the motors.
* Serial debug output and well commented code blocks.

### Hardware
* [22pcs](https://www.aliexpress.com/item/1005001505181292.html) NEMA23 stepper motors.
* [22pcs](https://www.aliexpress.com/item/1000001730872.html) TB6600 stepper motor drivers.
* [22pcs](https://www.aliexpress.com/item/32866503339.html) LJ12A3 NPN proximity sensors (we bought the 6-36V version but it seems to work with 5V so we used it).
* [6pcs](https://www.aliexpress.com/item/32831857729.html) Arduino UNO (better use Nano next time..).
* [6pcs](https://www.aliexpress.com/item/1766431287.html) Wiring shields.
* [1pcs](https://www.aliexpress.com/item/1005003723735938.html) 100V-240V to 24V 25A 600W switching power supply.
* [1pcs](https://www.aliexpress.com/item/4001107349411.html) 24V to 5V 3A DC-DC converter (to power proximity sensors and Arduinos).
* [2pcs](https://www.aliexpress.com/item/1005003478209377.html) 2KOhm resistors (for I2C pullup).
* Lots of wires and connectors to wire it all up..!

#### Wiring
| Axis   | Driver |    |      |      |      |      | Sensor |  |      |
|--------|------|------|------|------|------|------|-----|-----|------|
|        | PUL+ | PUL- | DIR+ | DIR- | ENA+ | ENA- | BLU | BRN | BLK  |
|     00 | 0D04 | -5V  | 0D03 | -5V  | 0D02 | -5V  | -5V | +5V | 0A00 |
|     01 | +5V  | 0D07 | 0D06 | -5V  | 0D05 | -5V  | -5V | +5V | 0A01 |
|     02 | +5V  | 0D10 | 0D09 | -5V  | 0D08 | -5V  | -5V | +5V | 0A02 |
|     03 | +5V  | 0D13 | 0D12 | -5V  | 0D11 | -5V  | -5V | +5V | 0A03 |
|     04 | 1D04 | -5V  | 1D03 | -5V  | +5V  | 1D02 | -5V | +5V | 1A00 |
|     05 | +5V  | 1D07 | 1D06 | -5V  | 1D05 | -5V  | -5V | +5V | 1A01 |
|     06 | +5V  | 1D10 | 1D09 | -5V  | 1D08 | -5V  | -5V | +5V | 1A02 |
|     07 | +5V  | 1D13 | 1D12 | -5V  | 1D11 | -5V  | -5V | +5V | 1A03 |
|     08 | 2D04 | -5V  | +5V  | 2D03 | 2D02 | -5V  | -5V | +5V | 2A00 |
|     09 | +5V  | 2D07 | 2D06 | -5V  | 2D05 | -5V  | -5V | +5V | 2A01 |
|     10 | +5V  | 2D10 | 2D09 | -5V  | 2D08 | -5V  | -5V | +5V | 2A02 |
|     11 | +5V  | 2D13 | 2D12 | -5V  | 2D11 | -5V  | -5V | +5V | 2A03 |
|     12 | 3D04 | -5V  | +5V  | 3D03 | +5V  | 3D02 | -5V | +5V | 3A00 |
|     13 | +5V  | 3D07 | 3D06 | -5V  | 3D05 | -5V  | -5V | +5V | 3A01 |
|     14 | +5V  | 3D10 | 3D09 | -5V  | 3D08 | -5V  | -5V | +5V | 3A02 |
|     15 | +5V  | 3D13 | 3D12 | -5V  | 3D11 | -5V  | -5V | +5V | 3A03 |
|     16 | +5V  | 4D04 | 4D03 | -5V  | 4D02 | -5V  | -5V | +5V | 4A00 |
|     17 | +5V  | 4D07 | 4D06 | -5V  | 4D05 | -5V  | -5V | +5V | 4A01 |
|     18 | +5V  | 4D10 | 4D09 | -5V  | 4D08 | -5V  | -5V | +5V | 4A02 |
|     19 | +5V  | 4D13 | 4D12 | -5V  | 4D11 | -5V  | -5V | +5V | 4A03 |
|     20 | +5V  | 5D04 | 5D03 | -5V  | +5V  | 5D02 | -5V | +5V | 5A00 |
|     21 | +5V  | 5D07 | 5D06 | -5V  | 5D05 | -5V  | -5V | +5V | 5A01 |
|     22 | +5V  | 5D10 | 5D09 | -5V  | 5D08 | -5V  | -5V | +5V | 5A02 |
|     23 | +5V  | 5D13 | 5D12 | -5V  | 5D11 | -5V  | -5V | +5V | 5A03 |

## See [docs](https://docs.google.com/presentation/d/1KEq_qDWCliBDza_pi2NsCsC85T2rr4le3yrmxQ1LMs4/edit).

## Enjoy!
A.E.TECH 2022
