// Define the IR sensor pins
const int irSensorPins[] = {A0, A1, A2, A3, A4}; // Analog pins for the IR sensors
const int numSensors = 5; // Number of IR sensors

// Define the threshold values for each sensor to distinguish between white and black
const int thresholds[numSensors] = {500, 500, 500, 500, 500}; // Adjust these values based on your sensors and conditions

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read values from all IR sensors
  int irSensorValues[numSensors];
  int s[numSensors];

  for (int i = 0; i < numSensors; i++) {
    irSensorValues[i] = analogRead(irSensorPins[i]);
  }

  // Classify the output of each sensor based on its threshold
  for (int i = 0; i < numSensors; i++) {
    if (irSensorValues[i] > thresholds[i]) {
      Serial.print("Sensor ");
      Serial.print(i);
      Serial.print(": White : "); // Object detected (black)
      Serial.println(irSensorValues[i]);
      s[i]=1;



    } else {
      Serial.print("Sensor ");
      Serial.print(i);
      Serial.print(": Black : "); // No object detected (white)
      Serial.println(irSensorValues[i]);
      s[i]=0;


    }
  }


  for (int i = 0; i < numSensors; i++) {

      Serial.print(s[i]);

  }

    

  // Add a short delay to avoid flooding the serial monitor
  delay(1000);
}