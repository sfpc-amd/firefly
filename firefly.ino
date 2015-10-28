int sensorPin = A1;
int ceilCalibratePin = 13;
int floorCalibratePin = 12;
int ledPin = 11;

bool bCeilCalibrated = false;
bool bFloorCalibrated = false;

int sensorVal;
int sensorCeil;
int sensorFloor;

int pulseAt = 240;

unsigned long currentTime;

void setup() {
  // inputs
  pinMode(sensorPin, INPUT);
  pinMode(ceilCalibratePin, INPUT);
  pinMode(floorCalibratePin, INPUT);

  // outputs
  pinMode(ledPin, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Here we go!");
}

void loop() {

    currentTime = millis();
    sensorVal = analogRead(sensorPin);

    if(digitalRead(ceilCalibratePin) == HIGH) {
      Serial.print("Ceil: ");
      Serial.println(sensorVal);
      sensorCeil = sensorVal;
      bCeilCalibrated = true;
      blink(50);
    } else if(digitalRead(floorCalibratePin) == HIGH) {
      Serial.print("Floor: ");
      Serial.println(sensorVal);
      sensorFloor = sensorVal;
      bFloorCalibrated = true;
      blink(50);
    } else if(bCeilCalibrated && bFloorCalibrated) {
      int ledOut = constrain(floor(map(sensorVal, sensorFloor, sensorCeil, 255, 0)), 0, 255);
      if(ledOut < pulseAt) {
//        Serial.println(ledOut);
        analogWrite(ledPin, ledOut); 
      } else {
        Serial.println(ledOut);
        pulse(0.005);
      }

    } else {
      blink(200);
    }

    delay(10);

}

void blink(int d) {
  analogWrite(ledPin, 255);
  delay(d);
  analogWrite(ledPin, 0);
  delay(d);
}

void pulse(float p) {
  int l = int(abs(sin(currentTime*p)*255));
//  Serial.println(l);
  analogWrite(ledPin, l);
}



