#include <iostream>
#include "Device.h"
#include "SmartHome.h"
#include "Light.h"
#include "Speaker.h"
#include "Thermostat.h"
#include "VentilationSystem.h"

int main() {
    auto thermostat = new Thermostat("abc", "thermostat_ime");

    thermostat->setTemp(Rooms::Bathroom, 25);
    thermostat->setTemp(Rooms::Living_room, 23);
    thermostat->setTemp(Rooms::Office, 0);

    SmartHome home("home_Ime");

    home.addDevice(new Device("abc", "device_ime"));
    home.addDevice(new Light("abc", "light_ime", false));
    home.addDevice(new Speaker("abc", "speaker_ime", 64));
    home.addDevice(new VentilationSystem("abc", "ventilationSystem_ime", 123, 123));
    home.addDevice(thermostat);

    std::cout << home.toString();

    return 0;
}
