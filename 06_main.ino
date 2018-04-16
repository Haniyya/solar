SensorArray UdSensors = SensorArray(0, 3);
SensorArray RlSensors = SensorArray(2, 1);
Motor UdMotor         = Motor(9, 10, 30000, 500);
Motor RlMotor         = Motor(7, 8, 33000, 800);

void setup(){
  // If you change the pin setup, change this as well.
  UdMotor.init();
  RlMotor.init();
}

void loop() {
  UdSensors.update_status();
  RlSensors.update_status();
  switch (UdSensors.status()) {
    case lighter:   UdMotor.forward(); break;
    case unchanged: UdMotor.rest(); break;
    case darker:
    case dark:      UdMotor.reverse(); break;
  };
  switch (RlSensors.status()) {
    case lighter:   RlMotor.forward(); break;
    case unchanged: RlMotor.rest(); break;
    case darker:
    case dark:      RlMotor.reverse(); break;
  };
  update_running_time();
  delay(step_size);
}
