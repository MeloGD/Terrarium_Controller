#ifndef buttons
#define buttons

#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <menu/touchscreen.h>


// Variables
bool load_edit_menu = false;
bool load_edit_temp = false;
bool load_edit_bulb = false;
bool load_edit_uvb = false;
bool load_edit_plants = false;
bool down;

//relay
byte dhp_relay_pin = 40;
byte uvb_relay_pin = 42;
byte light_relay_pin = 44;

// Buttons 
Adafruit_GFX_Button previous, next, edit, increase, decrease, home;
Adafruit_GFX_Button heatswitch, uvbswitch, plantswitch , timeheatbulb, timeuvbbulb, timeplantsbulb;
Adafruit_GFX_Button incrhour1, decrhour1, incrmin1, decrmin1, incrhour2, decrhour2, incrmin2, decrmin2;

void launchButtons(void) {
  previous.initButton(&tft, 300, 290, 100, 40, WHITE, RED, BLACK, "Previous", 2);
  next.initButton(&tft, 420, 290, 100, 40, WHITE, GREEN, BLACK, "Next", 2);
  edit.initButton(&tft, 60, 290, 100, 40, WHITE, YELLOW, BLACK, "Edit", 2);
  increase.initButton(&tft, 420, 290, 100, 40, WHITE, GREEN, BLACK, "+", 2);
  decrease.initButton(&tft, 300, 290, 100, 40, WHITE, RED, BLACK, "-", 2);
  home.initButton(&tft, 60, 290, 100, 40, WHITE, YELLOW, BLACK, "Return", 2);
  heatswitch.initButton(&tft, 320, 90, 90, 40, WHITE, YELLOW, BLACK, "Switch", 2);
  uvbswitch.initButton(&tft, 320, 140, 90, 40, WHITE, YELLOW, BLACK, "Switch", 2);
  plantswitch.initButton(&tft, 320, 190, 90, 40, WHITE, YELLOW, BLACK, "Switch", 2);
  timeheatbulb.initButton(&tft, 410, 90, 70, 40, WHITE, BLUE, BLACK, "Time", 2);
  timeuvbbulb.initButton(&tft, 410, 140, 70, 40, WHITE, BLUE, BLACK, "Time", 2);
  timeplantsbulb.initButton(&tft, 410, 190, 70, 40, WHITE, BLUE, BLACK, "Time", 2);
  decrhour1.initButton(&tft, 220, 110, 30, 30, WHITE, RED, BLACK, "-", 2);
  incrhour1.initButton(&tft, 310, 110, 30, 30, WHITE, GREEN, BLACK, "+", 2);
  decrmin1.initButton(&tft, 360, 110, 30, 30, WHITE, RED, BLACK, "-", 2);
  incrmin1.initButton(&tft, 450, 110, 30, 30, WHITE, GREEN, BLACK, "+", 2);
  decrhour2.initButton(&tft, 220, 210, 30, 30, WHITE, RED, BLACK, "-", 2);
  incrhour2.initButton(&tft, 310, 210, 30, 30, WHITE, GREEN, BLACK, "+", 2);
  decrmin2.initButton(&tft, 360, 210, 30, 30, WHITE, RED, BLACK, "-", 2);
  incrmin2.initButton(&tft, 450, 210, 30, 30, WHITE, GREEN, BLACK, "+", 2);
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
    if (menuindex < 4) {
      menuindex++;  
    } else if (menuindex == 4){
      menuindex = 0;
    }
  }
  if (previous.justPressed()) {
    tft.fillScreen(BLACK);
    previous.drawButton();
    next.drawButton();
    if (menuindex > 0) {
      menuindex--;  
    } else if (menuindex == 0) {
      menuindex = 4;
    }
  }
}

void relayControlLights(void) {
  DateTime now =  rtc.now();
  // DHP
  int hour = now.hour();
  int minute = now.minute();
  if ((hour == on_dhp_hour) && (minute == on_dhp_minute)) {
    digitalWrite(dhp_relay_pin, LOW);
  } else if ((hour == off_dhp_hour) && (minute == off_dhp_minute)){
    digitalWrite(dhp_relay_pin, HIGH);
  }
  // UVB
  if ((hour == on_uvb_hour) && (minute == on_uvb_minute)) {
    digitalWrite(uvb_relay_pin, LOW);
  } else if ((hour == off_uvb_hour) && (minute == off_uvb_minute)){
    digitalWrite(uvb_relay_pin, HIGH);
  }
  // Plants Light
  if ((hour == on_plants_hour) && (minute == on_plants_minute)) {
    digitalWrite(light_relay_pin, LOW);
  } else if ((hour == off_plants_hour) && (minute == off_plants_minute)){
    digitalWrite(light_relay_pin, HIGH);
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
      targettemperature += 0.5;
      loadEditTempMenu();
      increase.drawButton();
      decrease.drawButton();
      home.drawButton();
      delay(200);
    }
    if (decrease.justPressed()) {
      targettemperature -= 0.5;
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
        if (menuindex < 4) {
          menuindex++;  
        }
      }  
      if (previous.justPressed()) {
        load_edit_menu = false;
        tft.fillScreen(BLACK);
        previous.drawButton();
        next.drawButton();
        if (menuindex > 0) {
          menuindex--;  
        }
      }
    }  
  }
}

// DHP
bool switch_press_heat = false;
void switchHeatBulb(void) {
  if (switch_press_heat == true){
    heatswitch.drawButton();
    switch_press_heat = false;
    digitalWrite(dhp_relay_pin, LOW);
  } else {
    heatswitch.drawButton(true);
    switch_press_heat = true;
    digitalWrite(dhp_relay_pin, HIGH);
  }
}

void timeDrawButtons(void) {
  home.drawButton();
  incrhour1.drawButton();
  decrhour1.drawButton();
  incrmin1.drawButton();
  decrmin1.drawButton();
  incrhour2.drawButton();
  decrhour2.drawButton();
  incrmin2.drawButton();
  decrmin2.drawButton();
}

void timePressButtons(void) {
  down = Touch_getXY();
  home.press(down && home.contains(pixel_x, pixel_y)); 
  incrhour1.press(down && incrhour1.contains(pixel_x, pixel_y)); 
  decrhour1.press(down && decrhour1.contains(pixel_x, pixel_y)); 
  incrmin1.press(down && incrmin1.contains(pixel_x, pixel_y)); 
  decrmin1.press(down && decrmin1.contains(pixel_x, pixel_y)); 
  incrhour2.press(down && incrhour2.contains(pixel_x, pixel_y)); 
  decrhour2.press(down && decrhour2.contains(pixel_x, pixel_y)); 
  incrmin2.press(down && incrmin2.contains(pixel_x, pixel_y)); 
  decrmin2.press(down && decrmin2.contains(pixel_x, pixel_y)); 
}

void timeHeatBulb(void) {
  tft.fillScreen(BLACK);
  loadEditTimeHeatMenu();
  timeDrawButtons();
  bool time_heat_menu = true;
  while (time_heat_menu) {
    timePressButtons();
    if (incrhour1.justPressed()) {
      on_dhp_hour++;
      loadEditTimeHeatMenu();
      delay(100);
    }
    if (decrhour1.justPressed()) {
      on_dhp_hour--;
      loadEditTimeHeatMenu();
      delay(100);
    }
    if (incrmin1.justPressed()) {
      on_dhp_minute++;
      loadEditTimeHeatMenu();
      delay(100);
    }
    if (decrmin1.justPressed()) {
      on_dhp_minute--;
      loadEditTimeHeatMenu();
      delay(100);
    }
    if (incrhour2.justPressed()) {
      off_dhp_hour++;
      loadEditTimeHeatMenu();
      delay(100);
    }
    if (decrhour2.justPressed()) {
      off_dhp_hour--;
      loadEditTimeHeatMenu();
      delay(100);
    }
    if (incrmin2.justPressed()) {
      off_dhp_minute++;
      loadEditTimeHeatMenu();
      delay(100);
    }
    if (decrmin2.justPressed()) {
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
    uvbswitch.drawButton();
    switch_press_uvb = false;
    digitalWrite(uvb_relay_pin, LOW);
  } else {
    uvbswitch.drawButton(true);
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
    if (incrhour1.justPressed()) {
      on_uvb_hour++;
      loadEditTimeUvbMenu();
      delay(100);
    }
    if (decrhour1.justPressed()) {
      on_uvb_hour--;
      loadEditTimeUvbMenu();
      delay(100);
    }
    if (incrmin1.justPressed()) {
      on_uvb_minute++;
      loadEditTimeUvbMenu();
      delay(100);
    }
    if (decrmin1.justPressed()) {
      on_uvb_minute--;
      loadEditTimeUvbMenu();
      delay(100);
    }
    if (incrhour2.justPressed()) {
      off_uvb_hour++;
      loadEditTimeUvbMenu();
      delay(100);
    }
    if (decrhour2.justPressed()) {
      off_uvb_hour--;
      loadEditTimeUvbMenu();
      delay(100);
    }
    if (incrmin2.justPressed()) {
      off_uvb_minute++;
      loadEditTimeUvbMenu();
      delay(100);
    }
    if (decrmin2.justPressed()) {
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
    plantswitch.drawButton();
    switch_press_plants = false;
    digitalWrite(light_relay_pin, LOW);
  } else {
    plantswitch.drawButton(true);
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
    if (incrhour1.justPressed()) {
      on_plants_hour++;
      loadEditTimePlantsMenu();
      delay(100);
    }
    if (decrhour1.justPressed()) {
      on_plants_hour--;
      loadEditTimePlantsMenu();
      delay(100);
    }
    if (incrmin1.justPressed()) {
      on_plants_minute++;
      loadEditTimePlantsMenu();
      delay(100);
    }
    if (decrmin1.justPressed()) {
      on_plants_minute--;
      loadEditTimePlantsMenu();
      delay(100);
    }
    if (incrhour2.justPressed()) {
      off_plants_hour++;
      loadEditTimePlantsMenu();
      delay(100);
    }
    if (decrhour2.justPressed()) {
      off_plants_hour--;
      loadEditTimePlantsMenu();
      delay(100);
    }
    if (incrmin2.justPressed()) {
      off_plants_minute++;
      loadEditTimePlantsMenu();
      delay(100);
    }
    if (decrmin2.justPressed()) {
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
  heatswitch.drawButton();
  timeheatbulb.drawButton();
  uvbswitch.drawButton();
  timeuvbbulb.drawButton();
  plantswitch.drawButton();
  timeplantsbulb.drawButton();
  while (load_edit_bulb) {
    // this needs to be in every while. the dhp wont work otherwise
    getWarmData();
    relayControlLights();
    down = Touch_getXY();
    previous.press(down && previous.contains(pixel_x, pixel_y));
    next.press(down && next.contains(pixel_x, pixel_y));
    heatswitch.press(down && heatswitch.contains(pixel_x, pixel_y)); 
    timeheatbulb.press(down && timeheatbulb.contains(pixel_x, pixel_y)); 
    uvbswitch.press(down && uvbswitch.contains(pixel_x, pixel_y)); 
    timeuvbbulb.press(down && timeuvbbulb.contains(pixel_x, pixel_y)); 
    plantswitch.press(down && plantswitch.contains(pixel_x, pixel_y));
    timeplantsbulb.press(down && timeplantsbulb.contains(pixel_x, pixel_y));
    if (heatswitch.justPressed()) {
      switchHeatBulb();
      delay(200);
    } else if (timeheatbulb.justPressed()) {
      timeHeatBulb();
      tft.fillScreen(BLACK);
      next.drawButton();
      previous.drawButton();
    } else if (uvbswitch.justPressed()) {
      switchUvbBulb();
      delay(200);
    } else if (timeuvbbulb.justPressed()) {
      timeUvbBulb();
      tft.fillScreen(BLACK);
      next.drawButton();
      previous.drawButton();
    } else if (plantswitch.justPressed()) {
      switchPlantsBulb();
      delay(200);
    } else if (timeplantsbulb.justPressed()) {
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
        if (menuindex < 4) {
          menuindex++;  
        } else if (menuindex == 4) {
          menuindex = 0;  
        }
      }  
      if (previous.justPressed()) {
        load_edit_bulb = false;
        tft.fillScreen(BLACK);
        previous.drawButton();
        next.drawButton();
        if (menuindex > 0) {
          menuindex--;  
        } else if (menuindex == 0) {
          menuindex = 4;  
        }
      } 
    }
  }
}

#endif