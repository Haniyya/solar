// Motor maxima and minima
const unsigned long max_ew = 33000;
const unsigned long max_ns = 30000;
const unsigned long min_ew = 500;
const unsigned long min_ns = 500;

// Time management
const unsigned long step_size = 300;
unsigned long time_running = 0;
// Returns the time passed since this function was last invoked
unsigned long time_delta() {
  return (millis() - time_running);
}

// To be called at the end of the loop. Update running time.
void update_running_time() {
  time_running = millis();
}
class Motor {
  unsigned long moved_right  = 0;
  unsigned long moved_up     = 0;
  // Motor pins
  const int motor_EW         = 7;
  const int motor_EW_Reverse = 8;
  const int motor_NS         = 9;
  const int motor_NS_Reverse = 10;

  public:
    void    set_pins();
    boolean move_left();
    boolean move_right();
    void    rest_ew();
    boolean move_up();
    boolean move_down();
    void    rest_ns();
    void    move_to_default();
};

void Motor::rest_ew() {
  digitalWrite(motor_EW,         LOW);
  digitalWrite(motor_EW_Reverse, LOW);
}

void Motor::rest_ns() {
  digitalWrite(motor_NS,         LOW);
  digitalWrite(motor_NS_Reverse, LOW);
}

void Motor::set_pins() {
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
  moved_right += time_delta();
  return true;
}

boolean Motor::move_left() {
  if ((moved_right - step_size) < min_ew) { return false; }
  digitalWrite(motor_EW,         LOW);
  digitalWrite(motor_EW_Reverse, HIGH);
  moved_right -= time_delta();
  return true;
}

boolean Motor::move_up() {
  if ((moved_up + step_size) >= max_ns) { return false; }
  digitalWrite(motor_NS,         LOW);
  digitalWrite(motor_NS_Reverse, HIGH);
  moved_up += time_delta();
  return true;
}

boolean Motor::move_down() {
  if ((moved_up - step_size) < min_ns) { return false; }
  digitalWrite(motor_NS,         HIGH);
  digitalWrite(motor_NS_Reverse, LOW);
  moved_up -= time_delta();
  return true;
}

void Motor::move_to_default() {
  while (move_left() || move_down()) { delay(step_size); }
}
enum SensorStatus { darker, unchanged, lighter };

class Sensor {
  // Benötigte PINS
  // Für einlesen der Spannungen
  const int east_pin  = 2; // grün
  const int south_pin = 3; // blau
  const int west_pin  = 1; // grbl
  const int north_pin = 0; // braun

  // Tolerance of measurements.
  const int tolerance = 3;

  // Threshhold for darkness
  const int darkness = 260;

  // Initialisieren der Messwertdarstellung
  // Sensoren zeigen 1000< Messwert für Dunkelheit
  int current_east  = 1023;
  int current_south = 1023;
  int current_west  = 1023;
  int current_north = 1023;

  public:
    void update_status();
    SensorStatus east_status();
    SensorStatus north_status();
    boolean is_dark();
};

void Sensor::update_status() {
  current_east  = analogRead(east_pin);
  current_south = analogRead(south_pin);
  current_west  = analogRead(west_pin);
  current_north = analogRead(north_pin);
}

// Returns the status of the north radiation: 
// - darker: North is darker than South
// - unchanged: Delta of North and South is too small or it is dark.
// - lighter: North is lighter than south
SensorStatus Sensor::north_status() {
  if (is_dark())                                    { return unchanged;}
  if ((current_north - current_south) >= tolerance) { return lighter;}
  if ((current_south - current_north) >= tolerance) { return darker;}
  return unchanged;
}

// Returns the status of the east radiation: 
// - darker: East is darker than West
// - unchanged: Delta of East and West is too small or it is dark.
// - lighter: East is lighter than south
SensorStatus Sensor::east_status() {
  if (is_dark())                                  { return unchanged;}
  if ((current_east - current_west) >= tolerance) { return lighter;}
  if ((current_west - current_east) >= tolerance) { return darker;}
  return unchanged;
}

// When all sensors are above threshhold, it is dark.
boolean Sensor::is_dark() {
  return ((current_east > darkness)
            && (current_west > darkness)
            && (current_south > darkness)
            && (current_north > darkness));
}
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
