Sensor Sen; // The solar sensor gets initialized
Motor Mo; // The motor gets initialized

void setup(){
  Mo.set_pins();
}

void loop() {
  update_running_time();
  Sen.update_status();
  switch (Sen.east_status()) {
    case lighter:   Mo.moved_right(); break;
    case unchanged: Mo.rest_ew(); break;
    case darker:    Mo.move_left(); breaK;
  }
  switch (Sen.north_status()) {
    case lighter:   Mo.moved_up(); break;
    case unchanged: Mo.rest_ns(); break;
    case darker:    Mo.move_down(); breaK;
  }
  if (Sen.is_dark()) { Mo.move_to_default(); }
  delay(step_size);
}
