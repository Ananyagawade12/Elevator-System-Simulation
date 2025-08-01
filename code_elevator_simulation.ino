// C++ code
//
int list1 = 0;
int current_floor = 1;
const int segPins[7] = {8, 7, 6, 5, 4, 3, 1};
const byte interruptPin = 2;
volatile int queue[10];      // Queue for storing requests
volatile int queueCount = 0; // Number of requests in the queue
int currentFloor = 1;        
int targetFloor = 1;
int floors[5] = {1,2,3,4,5};
const int currentFloor_ledPins[5] = {A0, A1, A2, A3, A4};

byte digitPatterns[5][7] = {
  {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW},   // 1
  {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH},  // 2
  {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH},  // 3
  {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH},  // 4
  {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH}   // 5
};

void update7SegmentDisplay(int floor) {
  if (floor >= 1 && floor <= 5) {
    for (int i = 0; i < 7; i++) {
      digitalWrite(segPins[i], digitPatterns[floor - 1][i]);
      
    }
  }
}

void setup()
{ 
  Serial.begin(9600);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);  // up led
  //pinMode(0, OUTPUT);	// down led
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], LOW);
  }
  
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), pressedtwo, RISING);
  update7SegmentDisplay(currentFloor);
}


void loop()
{
  digitalWrite(A5, LOW);
  digitalWrite(0, LOW);
  check_and_addtoQueue();
  
  if (queueCount > 0) {
    targetFloor = queue[0];  // Get the first request in the queue
	
    if (currentFloor < targetFloor) {
      // Move up 
      digitalWrite(A5, HIGH);
      //digitalWrite(0, LOW);
      for (int i = currentFloor; i < targetFloor; i++){
      	update7SegmentDisplay(currentFloor);
        digitalWrite(currentFloor_ledPins[currentFloor-1], HIGH);
      	delay(2000);
        digitalWrite(currentFloor_ledPins[currentFloor-1], LOW); 
      	currentFloor++;
      }
      digitalWrite(A5, LOW);
    } 
    
    else if (currentFloor > targetFloor) {
      digitalWrite(A5, LOW);
      //digitalWrite(0, HIGH);
      // Move down 
      for (int i = currentFloor; i > targetFloor; i--){
      	update7SegmentDisplay(currentFloor);
        digitalWrite(currentFloor_ledPins[currentFloor-1], HIGH); 
      	delay(2000); 
        digitalWrite(currentFloor_ledPins[currentFloor-1], LOW); 
      	currentFloor--;
      }
      //digitalWrite(0, LOW);
    }
    display_currentFloor(currentFloor);
    clearRequestFromQueue();
  } 
}
void pressedtwo(){
      queue[queueCount] = floors[0];
      queueCount++;
}

void check_and_addtoQueue(){
  for(int i = 9; i < 14; i++ ){
    if (digitalRead(i) == HIGH) {
      queue[queueCount] = floors[i-9];
      queueCount++;
      }
  }
}
  
void clearRequestFromQueue() {
  for (int i = 0; i < queueCount; i++) {
    queue[i] = queue[i + 1];  // Shift requests
  }
  queueCount--;  // Decrease the queue count
}
void display_currentFloor(int floor){
  update7SegmentDisplay(floor);
  digitalWrite(currentFloor_ledPins[floor-1], HIGH); 
}