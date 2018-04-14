# Tracking software for arduino microcontroller

## Architecture

This program consists of 2 classes and 2 global helper functions:

### `Motor` class

This class handles motor communication and prevents the dc-motors from
overturning. The class tracks the its position via the time it has moved in
certain directions. 

### `Sensor` class
This class provides a querying interface for the solar sensor.
It has functions to analyze  the current status of the sensors and whether it is
dark or not.

### `update_running_time`
Sets a marker to the point where the last loop ran in milliseconds.
So the running time might be `10000` if the last loop ran 10 seconds after the
program was started.

### `delta_time`
Returns the time since the last loop ran. This way there is an accurate
measurement for the motor to track its progress.


## Configuration
The file `01_variables.ino` holds configuration for the maxima and minima for
the two dc-motors.
- `max_ew` is the maximum time the motor can travel right (so the time it takes
    to move from 0 to full swing).
- `max_ns` is the maximum time the motor can travel up (so the time it takes
    to move from 0 to full height).
- `min_ew` is the minimum time the motor can travel left (a buffer to not
    overstear to the left).
- `min_ns` is the minimum time the motor can travel down (a buffer to not
    overstear to downward).

It also holds two important varialbes for time-keeping
- `step_size` the time between loops in milliseconds.
- `time_running` should always be 0 at the start and is increased every loop.

The `Motor` and `Sensor` classes hold configuration for their pins and custom
threshholds.

## Running
The `concat.sh` script concatenates all partials into one script which can
compiled to an arduino program.


## TBD
* Validations/Tests
* Debug mode with serial output
* Maybe a `Clock` class to keep the time helpers scoped
* **CRITICAL:** Add validation for `millis` overflow. Otherwise the machine will
    randomly reset.
