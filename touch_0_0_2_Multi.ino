// TONES  ==========================================
// Start by defining the relationship between 
//       note, period, &  frequency. 
int  c = 3830;    // 261 Hz 
#define  d     3400    // 294 Hz 
#define  e     3038    // 329 Hz 
#define  f     2864    // 349 Hz 
#define  g     2550    // 392 Hz 
#define  a     2272    // 440 Hz 
#define  b     2028    // 493 Hz 
#define  C     1912    // 523 Hz 
// Define a special note, 'R', to represent a rest
#define  R     0


int touch = 6;   //attach a button to digital pin 6
int touch2 = 8;   //attach a button to digital pin 6
int LED = 13;      //attach an LED to digital pin 13
int speakerPin = 3;
int speakerPitch = c; //Set speaker pitch to C


void setup()
{
  pinMode(touch, INPUT);  //define button an INPUT device
  pinMode(LED, OUTPUT);    //define LED an OUTPUT device
  pinMode(speakerPin, OUTPUT); //Define speaker an OUTPUT Device
}

void loop()
{
    Serial.println("\nTouch = ");
    Serial.print(touch);
    Serial.println("\nTouch2 = ");
    Serial.print(touch2);
  //int buttonState = digitalRead(touch);  //read the status of the button
  //if(buttonState == 1){
    if(digitalRead(touch) || digitalRead(touch2)){
    //digitalWrite(LED,1);
    //digitalWrite(speakerPin, HIGH);
    //delayMicroseconds(6000);
    int pitch = random(0,8);
    int freq[] = { 
      3830, 3400, 3038, 2684, 2550, 2272, 2028, 1912    };
    tone(3, freq[pitch], 100);
  }
  else
    digitalWrite(LED,0);
  digitalWrite(speakerPin, LOW);
  delayMicroseconds(speakerPitch);
}

