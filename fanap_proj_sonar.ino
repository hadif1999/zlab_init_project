class SonarDist {
  public:
    SonarDist(int trigPin = 9, int echoPin = 10, bool toinch = false) {
      this->trigPin = trigPin;
      this->echoPin = echoPin;
      this->toinch = toinch;
      pinMode(trigPin, OUTPUT);
      pinMode(echoPin, INPUT);
    }

    float calc_dist() {
      long duration;
      float distance;

      // clears the trigPin
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);

      // Sets the trigPin on HIGH state for 10 microseconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      duration = pulseIn(echoPin, HIGH);

      // Calculating the distance
      distance = duration * 0.034 / 2; 

      if (toinch) {
        distance /= 2.54; // Convert cm to inches
      }

      return distance;
    }

    bool isInRange(float range) {
      float distance = calc_dist();
      return distance <= range;
    }

    float mean_calc_dist() {
      const int duration = 100; 
      unsigned long startTime = millis();
      float sum = 0;
      int count = 0;

      while (millis() - startTime < duration) {
        sum += calc_dist();
        count++;
        delay(10); 
      }

      return sum / count;
    }

    bool getToInch() const {
      return toinch;
    }

  private:
    int trigPin;
    int echoPin;
    bool toinch;
};

SonarDist sonar(9, 10, true);

void setup() {
  Serial.begin(9600); 
}

void loop() {
  float distance = sonar.calc_dist(); 
  float meanDistance = sonar.mean_calc_dist(); 

  Serial.print("Distance: ");
  Serial.print(distance);
  if (sonar.getToInch()) {
    Serial.println(" inches");
  } else {
    Serial.println(" cm");
  }

  Serial.print("Mean Distance: ");
  Serial.print(meanDistance);
  if (sonar.getToInch()) {
    Serial.println(" inches");
  } else {
    Serial.println(" cm");
  }

  
  bool inRange = sonar.isInRange(10.0);
  Serial.print("Is in range (10 units): ");
  Serial.println(inRange ? "Yes" : "No");

  delay(1000); 
}
