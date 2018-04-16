enum SensorStatus { dark, darker, unchanged, lighter };

class SensorArray {
  const int pos_pin;
  const int neg_pin;
  // Tolerance of measurements.
  const int tolerance = 3;
  // Threshhold for darkness
  const int darkness = 260;

  // Initialisieren der Messwertdarstellung
  // Sensoren zeigen 1000< Messwert für Dunkelheit
  int pos_value  = 1023;
  int neg_value = 1023;

  public:
    SensorArray(int, int);
    SensorStatus status();
    void update_status();
};

SensorArray::SensorArray(int pos, int neg): pos_pin(pos), neg_pin(neg) {}

void SensorArray::update_status() {
  pos_value = analogRead(pos_pin);
  neg_value = analogRead(neg_pin);
}

// Returns the status of the north radiation: 
// - dark: It is night.
// - darker: pos_pin is darker than neg_pin.
// - unchanged: Delta of pos_pin and neg_pin is too small.
// - lighter: pos_pin is lighter than neg_pin.
SensorStatus SensorArray::status() {
  if (pos_value > darkness && neg_value > darkness) return dark;
  if ((pos_value - neg_value) >= tolerance) return lighter;
  if ((neg_value - pos_value) >= tolerance) return darker;
  return unchanged;
}
