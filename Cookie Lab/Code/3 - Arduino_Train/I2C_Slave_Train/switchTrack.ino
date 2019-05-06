void switchTrack(boolean trackDirection) { // Orientation of track: straight track on left, curved track on right
  if (trackDirection == isSwitchOnRight) return; // Does nothing if switch is already facing the correct direction
  else if (trackDirection == true) digitalWrite(switchPin, LOW); // Sets track to straight side
  else if (trackDirection == false) digitalWrite(switchPin, HIGH); // Sets track to curved side
  else Serial.println("Error switching track");
}
