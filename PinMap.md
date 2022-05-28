# Arduino Mega

- Pin  2 (PWM/INT4)   -> Encoder Right A
- Pin  3 (PWM/INT5)   -> Encoder Right B

- Pin  4 (+ GND)      -> Tirette
- Pin  5 (+ GND)      -> Switch Side Select (Yellow/Purple)

- Pin  6 (PWM)        -> Vacuum Pump Right
- Pin  7 (PWM)        -> Vacuum Pump Left

- Pin  8 (PWM)        -> Motor Right Forward
- Pin  9 (PWM)        -> Motor Right Backward
- Pin 10 (PWM)        -> Motor Right PWM

- Pin 11 (PWM)        -> Motor Left Forward
- Pin 12 (PWM)        -> Motor Left Backward
- Pin 13 (PWM)        -> Motor Left PWM

- Pin 14 (TX3)        -> (<-> Nano 8 (SoftwareSerial RX))
- Pin 15 (RX3)        -> (<-> Nano 9 (SoftwareSerial TX))
- Pin 16 (TX2)        -> Data XL320
- Pin 17 (RX2)        ->
- Pin 18 (TX1)        -> Data AX-12A
- Pin 19 (RX1)        ->

- Pin 20 (SDA/INT1)   -> Encoder Left A
- Pin 21 (SCL/INT0)   -> Encoder Left B

- Pin 54/A0 (ADC)     -> Status Led Red
- Pin 55/A1 (ADC)     -> Status Led Green
- Pin 56/A2 (ADC)     -> Status Led Blue

- Pin 57/A3 (ADC)     -> Current Shunt Vaccum Pump Right
- Pin 58/A4 (ADC)     -> Current Shunt Vaccum Pump Left

GPIO with GND & 5V:
59/A5
  |
69/A15

# Arduino Nano

- Pin  0 (RX)         ->
- Pin  1 (TX)         ->
- Pin  2 (INT0)       ->
- Pin  3 (INT1/PWM)   ->
- Pin  4              -> Sonar 0 Trigger
- Pin  5 (PWM)        -> Sonar 0 Echo
- Pin  6 (PWM)        -> Sonar 1 Trigger
- Pin  7              -> Sonar 1 Echo
- Pin  8              -> Sonar 2 Trigger
- Pin  9 (PWM)        -> Sonar 2 Echo
- Pin 10 (SS/PWM)     -> Sonar 3 Trigger
- Pin 11 (MOSI/PWM)   -> Sonar 3 Echo
- Pin 12 (MISO)       ->
- Pin 13 (SCK)        ->
- Pin 14/A0 (ADC)     -> SoftwareSerial RX (<-> Mega 14 (TX3))
- Pin 15/A1 (ADC)     -> SoftwareSerial TX (<-> Mega 15 (RX3))
- Pin 16/A2 (ADC)     ->
- Pin 17/A3 (ADC)     ->
- Pin 18/A4 (ADC/SDA) -> SDA LCD Display
- Pin 19/A5 (ADC/SCL) -> SCL LCD Display
- Pin A6 (ADC only)   ->
- Pin A7 (ADC only)   ->
