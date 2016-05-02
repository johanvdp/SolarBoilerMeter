# SolarBoilerMeter
An Arduino based solar water boiler energy meter.
Used to gain insight into the energy balance of our solar water boiler.

## Measurements
* electric current [A]
* electric voltage [V]
* water temperature [&deg;C]

## Calculations
* energy consumption [J] by the electric motor and electronics
* energy content [J] the volume and temperature of the water contained
* energy storage [J] the energy in flow from solar heated water
* energy release [J] the energy out flow to heating exchanger 
* energy loss [J] the energy out flow from stored water to ambient temperature. 

## Components
* WeMos D1mini (ESP8266) development board
* INA219 current and voltage sensor
* DS18B20 one wire temperature sensor

Using an object oriented approach to divide the application into components.
Reducing complexity by making all components similar in structure and usage.
* Component
* Wattmeter
* Thermometer
* Boiler
* WebServer

## Physics

### Q = m&times;C&times;&Delta;T
* Q: heat [J]
* m: mass [kg]
* C: heat capacity [J/kg&times;K] for water this is 4184 [J/kg&times;K] 
* &Delta;T: temperature change [K]

### P = U&times;I
* P: power [W]
* U: voltage [V]
* I: current [A]

### Conversion
* 1 Ws = 1 J
* 1 kWh = 3.6 MJ
* &Delta;1 &deg;C = &Delta;1 K 
