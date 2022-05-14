#include <menu/TFT.h>
#include <menu/buttons.h>
#include <menu/touchscreen.h>
#include <devices/relay.h>

void setup() {
  pinMode(dhp_relay_pin, OUTPUT);
  pinMode(uvb_relay_pin, OUTPUT);
  pinMode(light_relay_pin, OUTPUT);
  launchTFT();
  launchButtons();
  Wire.begin();
  dht_env.begin();
  dht_hum.begin();
}

void loop() {
  // Buttons
  launchControls();
  // Menu
  switch (menu_index) {
    case 0: // Enviroment Menu
      loadEnviroment();
      // Both getWarmData() and relayControlLights() need to be in every
      //  while and case option. The temperature control wont work otherwise
      getWarmData();
      relayControlLights();
      break; 
    case 1: // Warm Hide Menu
      loadWarmHide();
      editTemperatureWarmSide();
      break;
    case 2:  // Humid Hide Menu
      loadHumidHide();
      getWarmData();
      relayControlLights();
      break;
    case 3: // Cold Hide Menu
      loadColdHide();
      getWarmData();
      relayControlLights();
      break;
    case 4: // Lights Control Panel Menu
      loadLightsPanel();
      editControlPanel();
      break;
    default:
      break; 
  }
}