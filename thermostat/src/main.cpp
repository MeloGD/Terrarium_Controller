#include <menu/TFT.h>
#include <menu/buttons.h>
#include <menu/touchscreen.h>



void setup() {
  pinMode(dhp_relay_pin, OUTPUT);
  pinMode(uvb_relay_pin, OUTPUT);
  pinMode(light_relay_pin, OUTPUT);
  launchTFT();
  launchButtons();
  Wire.begin();
  dht.begin();
}

void loop() {
  // Buttons
  launchControls();
  //setClock();
  // Menu
  switch (menuindex) {
    case 0: // Enviroment Menu
      loadEnviroment();
      // this needs to be in every while. the dhp wont work otherwise
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