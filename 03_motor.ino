class Motor {
  unsigned long travel = 0;
  const unsigned long max_travel;
  const unsigned long min_travel;
  const int forward_pin;
  const int reverse_pin;

  public:
    Motor(int, int, unsigned long, unsigned long);
    boolean forward();
    boolean reverse();
    boolean rest();
};

Motor::Motor(int forw, int reve, unsigned long max_t, unsigned long min_t): forward_pin(forw), reverse_pin(reve), max_travel(max_t), min_travel(min_t) { }

  void Motor::init() {
    pinMode(forw, OUTPUT);
    pinMode(reve, OUTPUT);
    rest();
  }

boolean Motor::forward() {
  if ((travel + step_size) >= max_travel) return rest();
  digitalWrite(forward_pin, HIGH);
  digitalWrite(reverse_pin, LOW);
  travel += time_delta();
  return true;
}

boolean Motor::reverse() {
  if ((travel - step_size) < min_travel) return rest();
  digitalWrite(forward_pin, LOW);
  digitalWrite(reverse_pin, HIGH);
  travel -= time_delta();
  return true;
}

boolean Motor::rest() {
  digitalWrite(forward_pin, LOW);
  digitalWrite(reverse_pin, LOW);
  return false;
}
