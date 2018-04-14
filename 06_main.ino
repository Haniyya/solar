Sensor Sen; // The solar sensor gets initialized
Motor Mo; // The motor gets initialized

void setup(){
  Mo.set_pins();
  Mo.move_to_default();
}

void loop() {
  update_running_time();
  Sen.update_status();
  switch (Sen.east_status()) {
    case lighter:   Mo.move_right(); break;
    case unchanged: Mo.rest_ew(); break;
    case darker:    Mo.move_left(); break;
  }
  switch (Sen.north_status()) {
    case lighter:   Mo.move_up(); break;
    case unchanged: Mo.rest_ns(); break;
    case darker:    Mo.move_down(); break;
  }
  if (Sen.is_dark()) { Mo.move_to_default(); }
  delay(step_size);
}
