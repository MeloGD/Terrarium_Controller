#ifndef buttons
#define buttons

#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <menu/touchscreen.h>
#include <devices/relay.h>

// Variables
bool load_edit_menu = false;
bool load_edit_temp = false;
bool load_edit_bulb = false;
bool load_edit_uvb = false;
bool load_edit_plants = false;
bool down;

// Buttons 
Adafruit_GFX_Button previous, next, edit, increase, decrease, home;
Adafruit_GFX_Button heat_switch, uvb_switch, plant_switch , time_heat_bulb, time_uvb_bulb, time_plants_bulb;
Adafruit_GFX_Button incr_hour_1, decr_hour_1, incr_min_1, decr_min_1, incr_hour_2, decr_hour_2, incr_min_2, decr_min_2;

void launchButtons(void) {
  previous.initButton(&tft, 300, 290, 100, 40, WHITE, RED, BLACK, "Previous", 2);
  next.initButton(&tft, 420, 290, 100, 40, WHITE, GREEN, BLACK, "Next", 2);
  edit.initButton(&tft, 60, 290, 100, 40, WHITE, YELLOW, BLACK, "Edit", 2);
  increase.initButton(&tft, 420, 290, 100, 40, WHITE, GREEN, BLACK, "+", 2);
  decrease.initButton(&tft, 300, 290, 100, 40, WHITE, RED, BLACK, "-", 2);
  home.initButton(&tft, 60, 290, 100, 40, WHITE, YELLOW, BLACK, "Return", 2);
  heat_switch.initButton(&tft, 320, 90, 90, 40, WHITE, YELLOW, BLACK, "Switch", 2);
  uvb_switch.initButton(&tft, 320, 140, 90, 40, WHITE, YELLOW, BLACK, "Switch", 2);
  plant_switch.initButton(&tft, 320, 190, 90, 40, WHITE, YELLOW, BLACK, "Switch", 2);
  time_heat_bulb.initButton(&tft, 410, 90, 70, 40, WHITE, BLUE, BLACK, "Time", 2);
  time_uvb_bulb.initButton(&tft, 410, 140, 70, 40, WHITE, BLUE, BLACK, "Time", 2);
  time_plants_bulb.initButton(&tft, 410, 190, 70, 40, WHITE, BLUE, BLACK, "Time", 2);
  decr_hour_1.initButton(&tft, 220, 110, 30, 30, WHITE, RED, BLACK, "-", 2);
  incr_hour_1.initButton(&tft, 310, 110, 30, 30, WHITE, GREEN, BLACK, "+", 2);
  decr_min_1.initButton(&tft, 360, 110, 30, 30, WHITE, RED, BLACK, "-", 2);
  incr_min_1.initButton(&tft, 450, 110, 30, 30, WHITE, GREEN, BLACK, "+", 2);
  decr_hour_2.initButton(&tft, 220, 210, 30, 30, WHITE, RED, BLACK, "-", 2);
  incr_hour_2.initButton(&tft, 310, 210, 30, 30, WHITE, GREEN, BLACK, "+", 2);
  decr_min_2.initButton(&tft, 360, 210, 30, 30, WHITE, RED, BLACK, "-", 2);
  incr_min_2.initButton(&tft, 450, 210, 30, 30, WHITE, GREEN, BLACK, "+", 2);
  previous.drawButton();
  next.drawButton();
}

void launchControls(void) {
  load_edit_menu = true;
  load_edit_temp = true;
  load_edit_bulb = true;
  load_edit_uvb = true;
  load_edit_plants = true;
  down = Touch_getXY();
  previous.press(down && previous.contains(pixel_x, pixel_y));
  next.press(down && next.contains(pixel_x, pixel_y)); 
  if (next.justPressed()) {
    tft.fillScreen(BLACK);
    next.drawButton();
    previous.drawButton();
    if (menu_index < 2) {
      menu_index++;  
    } else if (menu_index == 2) {
      menu_index = 0;
    }
  }
  if (previous.justPressed()) {
    tft.fillScreen(BLACK);
    previous.drawButton();
    next.drawButton();
    if (menu_index > 0) {
      menu_index--;  
    } else if (menu_index == 0) {
      menu_index = 2;
    }
  }
}

void editTargetTemp(void) {
  tft.fillScreen(BLACK);
  loadEditTempMenu();
  increase.drawButton();
  decrease.drawButton();
  home.drawButton();
  load_edit_temp= true;
  while (load_edit_temp) {
    down = Touch_getXY();
    increase.press(down && increase.contains(pixel_x, pixel_y));
    decrease.press(down && decrease.contains(pixel_x, pixel_y)); 
    home.press(down && home.contains(pixel_x, pixel_y)); 
    if (increase.justPressed()) {
      target_temperature += 0.5;
      loadEditTempMenu();
      increase.drawButton();
      decrease.drawButton();
      home.drawButton();
      delay(200);
    }
    if (decrease.justPressed()) {
      target_temperature -= 0.5;
      loadEditTempMenu();
      increase.drawButton();
      decrease.drawButton();
      home.drawButton();
      delay(200);
    } 
    if (home.justPressed()){
      load_edit_temp = false;
    }
  }
  load_edit_menu = false;
}

void editTemperatureWarmSide() {
  edit.drawButton();
  while (load_edit_menu) { 
    // lights control
    relayControlLights();
    down = Touch_getXY();
    previous.press(down && previous.contains(pixel_x, pixel_y));
    next.press(down && next.contains(pixel_x, pixel_y));
    edit.press(down && edit.contains(pixel_x, pixel_y)); 
    // imprimir reloj
    printTFTClock(); 
    // sacar temperatura
    tft.setTextColor(WHITE, BLACK);
    tft.setCursor(70,150);
    tft.setTextSize(3);
    tft.print(getWarmData());
    tft.print(" C");

    if (edit.justPressed()) {
      editTargetTemp();
      tft.fillScreen(BLACK);
      previous.drawButton();
      next.drawButton();
    } else {
      if (next.justPressed()) {
        load_edit_menu = false;
        tft.fillScreen(BLACK);
        next.drawButton();
        previous.drawButton();
        if (menu_index < 2) {
          menu_index++;  
        }
      }  
      if (previous.justPressed()) {
        load_edit_menu = false;
        tft.fillScreen(BLACK);
        previous.drawButton();
        next.drawButton();
        if (menu_index > 0) {
          menu_index--;  
        }
      }
    }  
  }
}

// DHP
bool switch_press_heat = false;
void switchHeatBulb(void) {
  if (switch_press_heat == true){
    heat_switch.drawButton();
    switch_press_heat = false;
    digitalWrite(dhp_relay_pin, LOW);
  } else {
    heat_switch.drawButton(true);
    switch_press_heat = true;
    digitalWrite(dhp_relay_pin, HIGH);
  }
}

void timeDrawButtons(void) {
  home.drawButton();
  incr_hour_1.drawButton();
  decr_hour_1.drawButton();
  incr_min_1.drawButton();
  decr_min_1.drawButton();
  incr_hour_2.drawButton();
  decr_hour_2.drawButton();
  incr_min_2.drawButton();
  decr_min_2.drawButton();
}

void timePressButtons(void) {
  down = Touch_getXY();
  home.press(down && home.contains(pixel_x, pixel_y)); 
  incr_hour_1.press(down && incr_hour_1.contains(pixel_x, pixel_y)); 
  decr_hour_1.press(down && decr_hour_1.contains(pixel_x, pixel_y)); 
  incr_min_1.press(down && incr_min_1.contains(pixel_x, pixel_y)); 
  decr_min_1.press(down && decr_min_1.contains(pixel_x, pixel_y)); 
  incr_hour_2.press(down && incr_hour_2.contains(pixel_x, pixel_y)); 
  decr_hour_2.press(down && decr_hour_2.contains(pixel_x, pixel_y)); 
  incr_min_2.press(down && incr_min_2.contains(pixel_x, pixel_y)); 
  decr_min_2.press(down && decr_min_2.contains(pixel_x, pixel_y)); 
}

void timeHeatBulb(void) {
  tft.fillScreen(BLACK);
  loadEditTimeHeatMenu();
  timeDrawButtons();
  bool time_heat_menu = true;
  while (time_heat_menu) {
    timePressButtons();
    if (incr_hour_1.justPressed()) {
      on_dhp_hour++;
      loadEditTimeHeatMenu();
      delay(100);
    }
    if (decr_hour_1.justPressed()) {
      on_dhp_hour--;
      loadEditTimeHeatMenu();
      delay(100);
    }
    if (incr_min_1.justPressed()) {
      on_dhp_minute++;
      loadEditTimeHeatMenu();
      delay(100);
    }
    if (decr_min_1.justPressed()) {
      on_dhp_minute--;
      loadEditTimeHeatMenu();
      delay(100);
    }
    if (incr_hour_2.justPressed()) {
      off_dhp_hour++;
      loadEditTimeHeatMenu();
      delay(100);
    }
    if (decr_hour_2.justPressed()) {
      off_dhp_hour--;
      loadEditTimeHeatMenu();
      delay(100);
    }
    if (incr_min_2.justPressed()) {
      off_dhp_minute++;
      loadEditTimeHeatMenu();
      delay(100);
    }
    if (decr_min_2.justPressed()) {
      off_dhp_minute--;
      loadEditTimeHeatMenu();
      delay(100);
    }
    if (home.justPressed()){
      time_heat_menu = false;
    }
  }
  load_edit_bulb = false;
}

// UVB
bool switch_press_uvb = false;
void switchUvbBulb(void) {
  if (switch_press_uvb == true){
    uvb_switch.drawButton();
    switch_press_uvb = false;
    digitalWrite(uvb_relay_pin, LOW);
  } else {
    uvb_switch.drawButton(true);
    switch_press_uvb = true;
    digitalWrite(uvb_relay_pin, HIGH);
  }
}

void timeUvbBulb(void) {
  tft.fillScreen(BLACK);
  loadEditTimeUvbMenu();
  timeDrawButtons();
  bool time_heat_menu = true;
  while (time_heat_menu) {
    timePressButtons();
    if (incr_hour_1.justPressed()) {
      on_uvb_hour++;
      loadEditTimeUvbMenu();
      delay(100);
    }
    if (decr_hour_1.justPressed()) {
      on_uvb_hour--;
      loadEditTimeUvbMenu();
      delay(100);
    }
    if (incr_min_1.justPressed()) {
      on_uvb_minute++;
      loadEditTimeUvbMenu();
      delay(100);
    }
    if (decr_min_1.justPressed()) {
      on_uvb_minute--;
      loadEditTimeUvbMenu();
      delay(100);
    }
    if (incr_hour_2.justPressed()) {
      off_uvb_hour++;
      loadEditTimeUvbMenu();
      delay(100);
    }
    if (decr_hour_2.justPressed()) {
      off_uvb_hour--;
      loadEditTimeUvbMenu();
      delay(100);
    }
    if (incr_min_2.justPressed()) {
      off_uvb_minute++;
      loadEditTimeUvbMenu();
      delay(100);
    }
    if (decr_min_2.justPressed()) {
      off_uvb_minute--;
      loadEditTimeUvbMenu();
      delay(100);
    }
    if (home.justPressed()){
      time_heat_menu = false;
    }
  }
  load_edit_bulb = false;
}

// Plants
bool switch_press_plants = false;
void switchPlantsBulb(void) {
  if (switch_press_plants == true){
    plant_switch.drawButton();
    switch_press_plants = false;
    digitalWrite(light_relay_pin, LOW);
  } else {
    plant_switch.drawButton(true);
    switch_press_plants = true;
    digitalWrite(light_relay_pin, HIGH);
  }
}

void timePlantsBulb(void) {
  tft.fillScreen(BLACK);
  loadEditTimePlantsMenu();
  timeDrawButtons();
  bool time_heat_menu = true;
  while (time_heat_menu) {
    timePressButtons();
    if (incr_hour_1.justPressed()) {
      on_plants_hour++;
      loadEditTimePlantsMenu();
      delay(100);
    }
    if (decr_hour_1.justPressed()) {
      on_plants_hour--;
      loadEditTimePlantsMenu();
      delay(100);
    }
    if (incr_min_1.justPressed()) {
      on_plants_minute++;
      loadEditTimePlantsMenu();
      delay(100);
    }
    if (decr_min_1.justPressed()) {
      on_plants_minute--;
      loadEditTimePlantsMenu();
      delay(100);
    }
    if (incr_hour_2.justPressed()) {
      off_plants_hour++;
      loadEditTimePlantsMenu();
      delay(100);
    }
    if (decr_hour_2.justPressed()) {
      off_plants_hour--;
      loadEditTimePlantsMenu();
      delay(100);
    }
    if (incr_min_2.justPressed()) {
      off_plants_minute++;
      loadEditTimePlantsMenu();
      delay(100);
    }
    if (decr_min_2.justPressed()) {
      off_plants_minute--;
      loadEditTimePlantsMenu();
      delay(100);
    }
    if (home.justPressed()){
      time_heat_menu = false;
    }
  }
  load_edit_bulb = false;
}

void editControlPanel(void) {
  heat_switch.drawButton();
  time_heat_bulb.drawButton();
  uvb_switch.drawButton();
  time_uvb_bulb.drawButton();
  plant_switch.drawButton();
  time_plants_bulb.drawButton();
  while (load_edit_bulb) {
    // this needs to be in every while. the dhp wont work otherwise
    getWarmData();
    relayControlLights();
    down = Touch_getXY();
    previous.press(down && previous.contains(pixel_x, pixel_y));
    next.press(down && next.contains(pixel_x, pixel_y));
    heat_switch.press(down && heat_switch.contains(pixel_x, pixel_y)); 
    time_heat_bulb.press(down && time_heat_bulb.contains(pixel_x, pixel_y)); 
    uvb_switch.press(down && uvb_switch.contains(pixel_x, pixel_y)); 
    time_uvb_bulb.press(down && time_uvb_bulb.contains(pixel_x, pixel_y)); 
    plant_switch.press(down && plant_switch.contains(pixel_x, pixel_y));
    time_plants_bulb.press(down && time_plants_bulb.contains(pixel_x, pixel_y));
    if (heat_switch.justPressed()) {
      switchHeatBulb();
      delay(200);
    } else if (time_heat_bulb.justPressed()) {
      timeHeatBulb();
      tft.fillScreen(BLACK);
      next.drawButton();
      previous.drawButton();
    } else if (uvb_switch.justPressed()) {
      switchUvbBulb();
      delay(200);
    } else if (time_uvb_bulb.justPressed()) {
      timeUvbBulb();
      tft.fillScreen(BLACK);
      next.drawButton();
      previous.drawButton();
    } else if (plant_switch.justPressed()) {
      switchPlantsBulb();
      delay(200);
    } else if (time_plants_bulb.justPressed()) {
      timePlantsBulb();
      tft.fillScreen(BLACK);
      next.drawButton();
      previous.drawButton();
    } else {
      if (next.justPressed()) {
        load_edit_bulb = false;
        tft.fillScreen(BLACK);
        next.drawButton();
        previous.drawButton();
        if (menu_index < 2) {
          menu_index++;  
        } else if (menu_index == 2) {
          menu_index = 0;  
        }
      }  
      if (previous.justPressed()) {
        load_edit_bulb = false;
        tft.fillScreen(BLACK);
        previous.drawButton();
        next.drawButton();
        if (menu_index > 0) {
          menu_index--;  
        } else if (menu_index == 0) {
          menu_index = 2;  
        }
      } 
    }
  }
}

#endif