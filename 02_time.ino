// Returns the time passed since this function was last invoked
unsigned long time_delta() {
  unsigned long delta = millis() - time_running;
  if (delta > (10 * step_size)) return step_size; // we assume we are on time
  return delta;
}

// To be called at the end of the loop. Update running time.
void update_running_time() {
  time_running = millis();
}
