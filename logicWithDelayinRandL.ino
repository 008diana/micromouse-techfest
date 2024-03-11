#define m1 4  //Right Motor MA1
#define m2 5  //Right Motor MA2
#define m3 12  //Left Motor MB1
#define m4 13  //Left Motor MB2
#define e1 9  //Right Motor Enable Pin EA
#define e2 10 //Left Motor Enable Pin EB

//***5 Channel IR Sensor Connection***//
#define ir1 A0
#define ir2 A1
#define ir3 A2
#define ir4 A3
#define ir5 A4
//*****************//

void setup() {
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(e1, OUTPUT);
  pinMode(e2, OUTPUT);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);
}

void moveForward(int speed) {
  analogWrite(e1, speed);
  analogWrite(e2, speed);
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);
}

void turnFullRight(int speed) {
  analogWrite(e1, speed);
  analogWrite(e2, speed);
  digitalWrite(m1, LOW);
  digitalWrite(m2, HIGH);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);
  delay(485);
}

void turnFullLeft(int speed) {
  analogWrite(e1, speed);
  analogWrite(e2, speed);
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, HIGH);
  delay(525);
}

void stopMotors() {
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
}


void loop() {

  //declaring an array:
  char arrayDryRun[1000]; // Declare the array to store 'L', 'R', or 'F'
  int arrayIndex = 0; // Index to keep track of the array position


  //Reading Sensor Values
  int s1 = digitalRead(ir1);  //Left Most Sensor
  int s2 = digitalRead(ir2);  //Left Sensor
  int s3 = digitalRead(ir3);  //Middle Sensor
  int s4 = digitalRead(ir4);  //Right Sensor
  int s5 = digitalRead(ir5);  //Right Most Sensor



  //if only middle sensor detects white line
  //going forward with full speed 
  if((s1 == 0) && (s2 == 0) && (s3 == 1) && (s4 == 0) && (s5 == 0))
  {
    moveForward(100);
    arrayDryRun[arrayIndex] = 'F'; // Store 'R' in the array
    arrayIndex++;

  }


  // right L or T condidtion
  //if only middle, right and right extreme  sensor detects white line
  if((s1 == 0) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1))
  {

    //FORWARD DELAY:
    moveForward(100);
    delay(85);

    // T condition 
    if((s1 == 0) && (s2 == 0) && (s3 == 1) && (s4 == 0) && (s5 == 0)){
      moveForward(100); 
    }

    // L condition
    else{
        turnFullRight(100);
        arrayDryRun[arrayIndex] = 'R'; // Store 'R' in the array
        arrayIndex++;    
    }
    
  }
  
  // left L or T or end condidtion
  //if only middle, left and left extreme  sensor detects white line
  if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 0))
  {

    //FORWARD DELAY:
    moveForward(100);
    delay(200);


    // end point
    if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 0)){
          stopMotors();
          } 
    

    // T condition 
    if((s1 == 0) && (s2 == 0) && (s3 == 1) && (s4 == 0) && (s5 == 0)){
            turnFullLeft(100);
            arrayDryRun[arrayIndex] = 'L'; // Store 'R' in the array
            arrayIndex++;
    }

    // L condition
    else{
        turnFullLeft(100);
        arrayDryRun[arrayIndex] = 'L'; // Store 'R' in the array
        arrayIndex++;
    }
    
  }


  // T or + condition
  // all the sensors read white
  if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1)){


    //FORWARD DELAY:
    moveForward(100);
    delay(200);

    
    //T condition
    if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0)){
        turnFullLeft(100);
        arrayDryRun[arrayIndex] = 'L'; // Store 'R' in the array
        arrayIndex++;
    }

    //+ condition
    if((s1 == 0) && (s2 == 0) && (s3 == 1) && (s4 == 0) && (s5 == 0)){
        turnFullLeft(100);
        arrayDryRun[arrayIndex] = 'L'; // Store 'R' in the array
        arrayIndex++;
    }
 
  }


  //dead end
  if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0)){
        turnFullRight(100);
        delay(485);
        arrayDryRun[arrayIndex] = 'U'; // Store 'R' in the array
        arrayIndex++;
  }


}