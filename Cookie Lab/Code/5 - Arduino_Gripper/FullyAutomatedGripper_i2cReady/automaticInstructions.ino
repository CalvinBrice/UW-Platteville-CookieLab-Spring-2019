// Ensure that the arm has a clear path to home the height

void automaticInstructions() {

  //Home
  setHome();
  //heightCurrent = 0;
  homeRotation();

  setRotation(800);
  setHeight(275);

  setRotation(1110);

  servoFinger.write(CLOSE);
  servoFinger.write(OPEN);
  servoFinger.write(CLOSE);

  setHeight(160); // drops arm down
  setRotation(1750);

  setHeight(27);
  setPlate(1); //forward
  delay(1000);
  servoFinger.write(OPEN);
  setHeight(70);

  digitalWrite(MIXER_PIN, MIX_ON);
  delay(5000);
  digitalWrite(MIXER_PIN, MIX_OFF);
  delay(1000);

  servoFinger.write(CLOSE);
  delay(1000);
  setPlate(0); //backward

  setHeight(160);
  setRotation(800);

  servoWrist.write(DOWN);
  setHeight(253);

  setRotation(110);

  setLinearActuator(0); //DOWN
  delay(5000);
  setLinearActuator(1); //UP
  delay(5000);

  setRotation(600);
  setHeight(160);

  servoWrist.write(UP);

  setRotation(1120);
  setHeight(290);
  servoFinger.write(OPEN);
  setHeight(100);

}
