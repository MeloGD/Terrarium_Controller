#include <menu/TFT.h>
#include <menu/buttons.h>
#include <menu/touchscreen.h>
#include <devices/relay.h>
#include <devices/dimmer.h>

void setup() {
  pinMode(uva_relay_pin, OUTPUT);
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
    case 0: // Summary Menu
      // Both getWarmData() and relayControlLights() need to be in every
      //  while and case option. The temperature control wont work otherwise
      // TODO: CHANGE getWarmData for ControlWarmTemp() and just control the
      // temperature, not doing both controlling and reporting the temp
      loadSummary();
      controlWarmTemp();
      relayControlLights();
      break; 
    case 1: // Warm Hide Menu
      loadWarmHide();
      editTemperatureWarmSide();
      controlWarmTemp();
      relayControlLights();
      break;
    case 2: // Lights Control Panel Menu
      loadLightsPanel();
      editControlPanel();
      controlWarmTemp();
      relayControlLights();
      break;
  }
}