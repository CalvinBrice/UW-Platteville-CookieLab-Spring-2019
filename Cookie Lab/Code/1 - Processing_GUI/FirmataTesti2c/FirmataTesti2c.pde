import cc.arduino.*;
import org.firmata.*;

Arduino arduino;
PFont f;

void setup() {
  size(600, 400); // Sets screen size
  f = createFont("Arial", 16, true); // Arial, 16 point, anti-aliasing on
  println(Arduino.list());
  arduino = new Arduino(this, Arduino.list()[1], 57600); // enumerates connected USB ports

}
