/* File: ColorSorter.ino
   Automated Color Sorting Machine
*/

#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <Servo.h>

// === Pin Definitions ===
const int TRIG_PIN = 9;
const int ECHO_PIN = 10;
const int SERVO_PIN = 6;

// === Thresholds & Positions ===
const float DIST_THRESHOLD = 5.0;   // cm to detect object
const int POS_RED    = 0;           // degrees
const int POS_GREEN  = 90;
const int POS_BLUE   = 180;
const int POS_NEUTRAL= 90;

// === Globals ===
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Servo sorterServo;

void setup() {
  Serial.begin(9600);

  // Ultrasonic pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Servo init
  sorterServo.attach(SERVO_PIN);
  sorterServo.write(POS_NEUTRAL);

  // Color sensor init
  if (!tcs.begin()) {
    Serial.println("TCS34725 not found!");
    while (1);
  }
  Serial.println("Color sorter ready");
}

void loop() {
  if (objectDetected()) {
    uint16_t r, g, b, c;
    tcs.getRawData(&r, &g, &b, &c);

    // Normalize RGB
    float sum = r + g + b;
    float nr = r / sum, ng = g / sum, nb = b / sum;

    // Determine dominant color
    int targetPos = POS_NEUTRAL;
    if (nr > ng && nr > nb)      targetPos = POS_RED;
    else if (ng > nr && ng > nb) targetPos = POS_GREEN;
    else if (nb > nr && nb > ng) targetPos = POS_BLUE;

    // Debug
    Serial.print("R: "); Serial.print(nr,2);
    Serial.print(" G: "); Serial.print(ng,2);
    Serial.print(" B: "); Serial.println(nb,2);

    // Move servo
    sorterServo.write(targetPos);
    delay(1000);                 // allow object to pass
    sorterServo.write(POS_NEUTRAL);
    delay(500);                  // debounce before next read
  }
}

// Returns true if an object is within DIST_THRESHOLD cm
bool objectDetected() {
  // Trigger pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo
  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // timeout 30 ms
  float distance = duration * 0.0343 / 2.0;       // cm

  return (distance > 0 && distance <= DIST_THRESHOLD);
}
