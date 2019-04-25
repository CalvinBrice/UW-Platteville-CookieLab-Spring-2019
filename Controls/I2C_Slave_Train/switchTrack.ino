void switchTrack(int trackDirection) { // Orientation of track: straight track on left, curved track on right
  if (trackDirection == isTrackStraight) return;
  switch (trackDirection) {
    case false:
      // Switch track direction to straight side
      isTrackStraight = false;
      Serial.println("Track switched to straight side");
      break;
    case true:
      // Switch track direction to curved side
      isTrackStraight = true;
      Serial.println("Track switched to curved side");
      break;
    default:
      Serial.print("Unknown input: ");
      Serial.println(trackDirection);
  }
}
