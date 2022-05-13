#include <menu/TFT.h>
#include <menu/buttons.h>
#include <menu/touchscreen.h>



void setup() {
  launchTFT();
  launchButtons();
  Wire.begin();
}

void loop() {
  // Buttons
  launchControls();
  //setClock();
  // Menu
  switch (menuindex) {
    case 0: // Enviroment Menu
      loadEnviroment();
      break; 
    case 1: // Warm Hide Menu
      loadWarmHide();
      editTemperatureWarmSide();
      break;
    case 2:  // Humid Hide Menu
      loadHumidHide();
      break;
    case 3: // Cold Hide Menu
      loadColdHide();
      break;
    case 4: // Lights Control Panel Menu
      loadLightsPanel();
      editControlPanel();
      break;
    default:
      break; 
  }
}