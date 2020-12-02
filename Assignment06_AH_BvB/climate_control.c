/*
August Ho und Benjamin von Behren

Compile: make climate_control
Run: ./climate_control
*/

#include "base.h"

/*
Eine Klimaanlage soll bei Temperaturen unter 21 °C heizen, bei 21-23.7 °C nichts tun und bei Temperaturen ab 23.7 °C kühlen. Entwickeln Sie eine Funktion zur Regelung der Klimaanlage, die abhängig von der Temperatur heizt, ausschaltet oder kühlt.
*/

const double HEAT_LIMIT = 21;
const double COOL_LIMIT = 23.7;

enum OperatingMode {
    HEATING,
    OFF,
    COOLING
};

typedef enum OperatingMode OperatingMode; // optional, could use the enum keyword each time

// double -> OperatingMode
// Return the operating mode of the climate control unit given the temperature.
OperatingMode climate_control(double temperature);

static void climate_control_test() {
    test_equal_i(climate_control(17.1), HEATING);
    // todo: add futher tests, at least:
    // - one for each interval boundary
    // - one within each interval
    test_equal_i(climate_control(23.5), OFF);
    test_equal_i(climate_control(30), COOLING);
    test_equal_i(climate_control(HEAT_LIMIT), OFF);
    test_equal_i(climate_control(COOL_LIMIT), OFF);
}

// Return the operating mode of the climate control unit given the temperature.
OperatingMode climate_control(double temperature) {
    // todo: implement
	// temperature is lower than 21°C, set too heating
	if (temperature < HEAT_LIMIT) {
		return HEATING;
	// temperature is within HEAT_LIMIT and COOL_LIMIT boundaries, turn off
	}else if (temperature >= HEAT_LIMIT && temperature <= COOL_LIMIT) {
		return OFF;
	// temperature is higher than 23.7°C, set to cooling
	}else{
		return COOLING;
	}
}

int main(void) {
    climate_control_test();
    return 0;
}
