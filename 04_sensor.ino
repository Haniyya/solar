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
