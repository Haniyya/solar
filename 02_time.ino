// Returns the time passed since this function was last invoked
unsigned long time_delta() {
  return (millis() - time_running);
}

// To be called at the end of the loop. Update running time.
void update_running_time() {
  time_running = millis();
}
