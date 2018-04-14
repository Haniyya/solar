class Motor {
  unsigned long moved_right  = 0;
  unsigned long moved_up     = 0;
  // Motor pins
  int final motor_EW         = 7;
  int final motor_EW_Reverse = 8;
  int final motor_NS         = 9;
  int final motor_NS_Reverse = 10;

  public:
    void    set_pins();
    boolean move_left();
    boolean move_right();
    void    rest_ew();
    boolean move_up();
    boolean move_down();
    void    rest_ns();
    void    move_to_default();
}

void Motor::rest_ew() {
  digitalWrite(motor_EW,         LOW);
  digitalWrite(motor_EW_Reverse, LOW);
}

void Motor::rest_ns() {
  digitalWrite(motor_NS,         LOW);
  digitalWrite(motor_NS_Reverse, LOW);
}

void Motor::set_pins() {
  motor_EW         = ew;
  motor_EW_Reverse = ew_rev;
  motor_NS         = ns;
  motor_NS_Reverse = ns_rev
  pinMode(motor_EW,         OUTPUT);
  pinMode(motor_EW_Reverse, OUTPUT);
  pinMode(motor_NS,         OUTPUT);
  pinMode(motor_NS_Reverse, OUTPUT);
  rest_ew();
  rest_ns();
}

// The move functions return true if the motor can be set to move
// this way and false otherwise.
boolean Motor::move_right() {
  if ((moved_right + step_size) >= max_ew) { return false; }
  digitalWrite(motor_EW,         HIGH);
  digitalWrite(motor_EW_Reverse, LOW);
  move_right += time_delta();
  return true;
}

boolean Motor::move_left() {
  if ((moved_right - step_size) < min_ew) { return false; }
  digitalWrite(motor_EW,         LOW);
  digitalWrite(motor_EW_Reverse, HIGH);
  move_right -= time_delta();
  return true;
}

boolean Motor::move_up() {
  if ((moved_up + step_size) >= max_ns) { return false; }
  digitalWrite(motor_NS,         LOW);
  digitalWrite(motor_NS_Reverse, HIGH);
  move_up += time_delta();
  return true;
}

boolean Motor::move_down() {
  if ((moved_up - step_size) < min_ns) { return false; }
  digitalWrite(motor_NS,         HIGH);
  digitalWrite(motor_NS_Reverse, LOW);
  move_up -= time_delta();
  return true;
}

void Motor::move_to_default() {
  while (move_left() || move_down()) { delay(step_size); }
}
