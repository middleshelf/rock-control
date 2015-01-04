
#include <SPI.h>
#include <WiFi.h>

//Wifi Info
char ssid[] = "Galaxy Alpha 4337"; //  your network SSID (name) 
char pass[] = "kock1944";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

//
int status = WL_IDLE_STATUS;
char server[] = "www.google.com";    // name address for Google (using DNS)
char driveServer[] = "70.165.248.69:40890";    // name address for AT&T Drive APIs (using DNS)
char digitalHomeServer[] = "https://systest.digitallife.att.com:443";    // name address for AT&T Connected Home APIs (using DNS)
WiFiClient client;

//Sensors
int touch = 6;   //attach a button to digital pin 6
int LED = 13;      //on board
int speakerPin = 3; //Piezo pickup on digital pin 3

//Touch count
int touchCount = 0;
int timer = 0;
boolean ignore = false;


void setup()
{
  pinMode(touch, INPUT);  //define button an INPUT device
  pinMode(LED, OUTPUT);    //define LED an OUTPUT device
  pinMode(speakerPin, OUTPUT); //Define speaker an OUTPUT Device

  //Initialize serial and wait for port to open:
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  }

  String fv = WiFi.firmwareVersion();
  if( fv != "1.1.0" )
    Serial.println("Please upgrade the firmware");

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  } 
  Serial.println("Connected to wifi");
  printWifiStatus();
}

void loop()
{

  /*
  // if there are incoming bytes available 
   // from the server, read them and print them:
   while (client.available()) {
   char c = client.read();
   Serial.write(c);
   }
   
   // if the server's disconnected, stop the client:
   if (!client.connected()) {
   Serial.println();
   Serial.println("disconnecting from server.");
   client.stop();
   
   // do nothing forevermore:
   while(true);
   }
   */


  int buttonState = digitalRead(touch);  //read the status of the button
  if(buttonState == 1){

    //Count how many touches
    ++touchCount;
    Serial.println("\nTouch Count = ");
    Serial.print(touchCount);
    //Start Timer
    //TBD

    int pitch = random(0,8);
    int freq[] = { 
      3830, 3400, 3038, 2684, 2550, 2272, 2028, 1912                };
    tone(3, freq[pitch], 100);


  }
  else{
    digitalWrite(LED,0);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(1200);

    //Open Garage door
    if((touchCount == 3) && (!ignore)){
      //Connect to Digital Life Connected Home API
      Serial.println("\nStarting connection to server...");
      // if you get a connection, report back via serial:
      if (client.connect(digitalHomeServer, 80)) {
        Serial.println("connected to AT&T Digital Home");
        // Make a HTTP request:
        client.println("POST /penguin/api/FFB4D699E0E64AE3A0142EC6A0E2D6F2/devices/DL00000004/lock HTTP/1.1");
        client.println("Host: https://systest.digitallife.att.com:443");
        client.println("Connection: close");
        client.println();
        //Send signal to open garage door
        Serial.println("\nPosting /api/{gatewayGUID}/devices/{deviceGUID}/{action}");
        
        
        //Clear inputs
        resetTouchInput();      

      }
    }

    //Unlock car door
    if(touchCount >= 7){
      //Connect to AT&T Drive API
      Serial.println("\nStarting connection to AT&T Drive API...");
      // if you get a connection, report back via serial:
      if (client.connect(driveServer, 80)) {
        Serial.println("connected to AT&T Drive");
        // Make a HTTP request to open lock car door
        client.println("POST /remoteservices/v1/vehicle/lock/1xacr15x0tta00033 HTTP/1.1");
        client.println("Host: 70.165.248.69:40890");
        client.println("Connection: close");
        client.println();


        //Clear inputs
        resetTouchInput();      

      }
    }

    /*
    // if the server's disconnected, stop the client:
    if (!client.connected()) {
      Serial.println();
      Serial.println("disconnecting from server.");
      client.stop();

      // do nothing forevermore:
      while(true);
    }
    
    */

  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void resetTouchInput(){
  touchCount = 0;
  timer = 0;
  ignore = true;
  Serial.println("\nReset Touch Input");
  Serial.println("Ignore = ");
  Serial.print(ignore);

}




