# SolarBoilerMeter
An Arduino based solar water boiler energy meter.
Used to gain insight into the energy balance of our solar water boiler.

## Measurements
* electric current [A]
* electric voltage [V]
* water temperature [&deg;C]

## Calculations
* energy consumption [J]
* energy content [J]
* energy storage [J]
* energy release [J]
* energy loss [J]

## Components
* WeMos D1mini (ESP8266) development board
* INA219 current and voltage sensor
* DS18B20 one wire temperature sensor

Using an object oriented approach to divide the application into components.
Reducing complexity by making all components similar in structure and usage.
* Component
* PowerMeter
* TemperatureMeter
* Boiler
* WebServer

## Physics

### Q = m&times;C&times;&Delta;T
* Q: heat [J]
* m: mass [kg]
* C: heat capacity [J/kg&times;K] (water: 4184 [J/kg&times;K])
* &Delta;T: temperature change [K]

### P = U&times;I
* P: power [W]
* U: voltage [V]
* I: current [A]

### Conversion
* 1 Ws = 1 J
* 1 kWh = 3.6 MJ
* &Delta;1 &deg;C = &Delta;1 K 
