
#define SENSOR_LEFT_SEN     5
#define SENSOR_LEFT_REC     6
#define SENSOR_MIDDLE_SEN   7
#define SENSOR_MIDDLE_REC   8
#define SENSOR_RIGHT_SEN    9
#define SENSOR_RIGHT_REC    10

#define MOTOR_LEFT1     1
#define MOTOR_LEFT2     2
#define MOTOR_RIGHT1    3
#define MOTOR_RIGHT2    4

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_LEFT1,OUTPUT);
  pinMode(MOTOR_LEFT2,OUTPUT);
  pinMode(MOTOR_RIGHT1,OUTPUT);
  pinMode(MOTOR_RIGHT2,OUTPUT);
}

long left,middle,right;
long least;
int leastSensor;

void loop() {
  left = readPing(SENSOR_LEFT_SEN,SENSOR_LEFT_REC);
  middle = readPing(SENSOR_MIDDLE_SEN,SENSOR_MIDDLE_REC);
  right = readPing(SENSOR_RIGHT_SEN,SENSOR_RIGHT_REC);
  calc_least();
  if(leastSensor == SENSOR_LEFT_SEN){
    rotate_left();
    while(!isAhead(least)){
    }
  }else if(leastSensor == SENSOR_RIGHT_SEN){
    rotate_right();
    while(!isAhead(least)){
      
    }
  }else{
    forward();
  }
  
}

void forward(){
  digitalWrite(MOTOR_LEFT1,HIGH);
  digitalWrite(MOTOR_LEFT2,LOW);
  digitalWrite(MOTOR_RIGHT1,HIGH);
  digitalWrite(MOTOR_RIGHT2,LOW);
}

void rotate_left(){
  digitalWrite(MOTOR_LEFT1,LOW);
  digitalWrite(MOTOR_LEFT2,HIGH);
  digitalWrite(MOTOR_RIGHT1,HIGH);
  digitalWrite(MOTOR_RIGHT2,LOW);
}
void rotate_right(){
  digitalWrite(MOTOR_LEFT1,HIGH);
  digitalWrite(MOTOR_LEFT2,LOW);
  digitalWrite(MOTOR_RIGHT1,LOW);
  digitalWrite(MOTOR_RIGHT2,HIGH);
}

void calc_least(){
  least = left;
  leastSensor = SENSOR_LEFT_SEN;
  if(middle<least){
    least = middle;
    leastSensor = SENSOR_MIDDLE_SEN;
  }
  if(right<least){
    least = right;
    leastSensor = SENSOR_RIGHT_SEN;
  }
}

bool isAhead(long dist){
  long md = readPing(SENSOR_MIDDLE_SEN,SENSOR_MIDDLE_REC)-dist;
  if(dist<0)dist = -dist;
  if(dist < 1160)return true;
  else return false;
}

long readPing(int senPin,int recPin){
  digitalWrite(senPin, LOW);
  delayMicroseconds(2);
  digitalWrite(senPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(senPin, LOW);

  return pulseIn(recPin, HIGH);
  //cm = microsecondsToCentimeters(duration);
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
