// Moisture Sensor
int pin1 = A0;
int pin2 = A1;
int pin3 = A2;

// LED
int gled = 8;
int bled = 9;
int rled = 10;

// Relay
int relay = 3;

// Last watering time
long last = -1;
boolean isWatering = false;
long timeout = 0;

void setup() {
  Serial.begin(115200);
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
  pinMode(pin3, INPUT);
  pinMode(gled, OUTPUT);
  pinMode(bled, OUTPUT);
  pinMode(rled, OUTPUT);
  pinMode(relay, OUTPUT);

  digitalWrite(rled, HIGH);
  digitalWrite(bled, HIGH);
  digitalWrite(gled, HIGH);
  digitalWrite(relay, HIGH);
  delay(1000);

  digitalWrite(rled, LOW);
  digitalWrite(bled, LOW);
  digitalWrite(gled, LOW);
  digitalWrite(relay, LOW);
  delay(1000);

  digitalWrite(rled, HIGH);
  delay(1000);
  digitalWrite(rled, LOW);
  digitalWrite(bled, HIGH);
  delay(1000);
  digitalWrite(bled, LOW);
  digitalWrite(gled, HIGH);
  delay(1000);
  digitalWrite(gled, LOW);
  delay(1000);

  digitalWrite(rled, HIGH);
  digitalWrite(bled, HIGH);
  digitalWrite(gled, HIGH);
  digitalWrite(relay, HIGH);
  delay(1000);

  digitalWrite(rled, LOW);
  digitalWrite(bled, LOW);
  digitalWrite(gled, LOW);
  digitalWrite(relay, LOW);
  delay(1000);

}

void loop() {
  int a = analogRead(pin1);
  int b = analogRead(pin2);
  int c = analogRead(pin3);
  int avg = (a + b + c) / 3;
  Serial.println(avg);

  long current = millis() / 1000;
  if (timeout > 0) timeout = timeout - 1;
//  Serial.println(timeout);
  if (avg > 950) {
    digitalWrite(rled, HIGH);
    digitalWrite(bled, LOW);
    if (digitalRead(relay) == HIGH) {
      digitalWrite(gled, HIGH);
      //      Serial.println("Water CONTINUE");
    } else {
      digitalWrite(gled, LOW);
    }
    if (!isWatering && timeout < 1) {
      isWatering = true;
      last = current;
      digitalWrite(relay, HIGH);
//      Serial.println("Water started");
    } else if (last > 0 && current - last > 15) {
      digitalWrite(relay, LOW);
      isWatering = false;
      //      Serial.println("Water Timeout");
      if (timeout == 0)
        timeout = 30;
    }
    //    Serial.println("Water required");
  } else if (avg > 800) {
    digitalWrite(rled, LOW);
    digitalWrite(bled, HIGH);
    digitalWrite(gled, LOW);
    digitalWrite(relay, LOW);
    isWatering = false;
    //    Serial.println("Water moderate");
  } else if (avg > 400) {
    digitalWrite(rled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(gled, HIGH);
    digitalWrite(relay, LOW);
    isWatering = false;
    //    Serial.println("Water sufficient");
  } else {
    digitalWrite(rled, HIGH);
    digitalWrite(bled, HIGH);
    digitalWrite(gled, HIGH);
    digitalWrite(relay, LOW);
    isWatering = false;
    //    Serial.println("Sensor error");
  }
  delay(1000);
}
