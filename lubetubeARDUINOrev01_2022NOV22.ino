// ** Parameters ** //

// Button //
const int button1Pin = 6;  // Button constant defined as pin #2// IS THIS NEEDED WITH ABOVE

// Potentiators //
const int pot1Pin = A2;  // Potmeter 1 pinA2 //
const int pot2Pin = A3;  // Potmeter 2 pinA3 //
const int pot3Pin = A4;  // Potmeter 3 pinA4 //

// ** Constants ** //

// Actuator1 //
#define ACT1RELAY07extend 7  //ACT1RELAY07extend is defined as pin #7//
#define ACT1RELAY08rtract 8  //ACT1RELAY08rtract is defined as pin #8//
// Actuator2 //
#define ACT2RELAY09extend 4  //ACT2RELAY09extend is defined as pin #9// REDEFINED AT #4
#define ACT2RELAY10rtract 5  //ACT2RELAY10rtract is defined as pin #10// REPINNED TO #5
// Actuator3 //
#define ACT3RELAY11extend 11  //ACT3RELAY11extend is defined as pin #11//
#define ACT3RELAY12rtract 12  //ACT3RELAY12rtract is defined as pin #12//

// ** Variables ** //

// Button //
int buttonState = 0;  // initialize variable for reading the pushbutton status //

// Potentiators //
int pot1CURRENT = 0;  // Potmeter 1's value (0 by default)
int pot2CURRENT = 0;  // Potmeter 2's value (0 by default)
int pot3CURRENT = 0;  // Potmeter 3's value (0 by default)
//  Previous pot value to track DIFF ('floating')//
int pot1PREVIOUS = 0;  // Potmeter 1's float (0 to start)
int pot2PREVIOUS = 0;  // Potmeter 2's float (0 to start)
int pot3PREVIOUS = 0;  // Potmeter 3's float (0 to start)

// Millisecond time marker at movement //
unsigned long timePREVIOUS;

// Millisecond lapsed from movement to calculation //
unsigned long elapsed;

// Relay count downs DIFF //
int ACT1rtractCOUNTER = 0;  //move in coutdown
int ACT1extendCOUNTER = 0;  //move out countdown
int ACT2rtractCOUNTER = 0;  //move in coutdown
int ACT2extendCOUNTER = 0;  //move out countdown
int ACT3rtractCOUNTER = 0;  //move in coutdown
int ACT3extendCOUNTER = 0;  //move out countdown


void setup() {  // put your setup code here, to run once:

  //Init Button
  pinMode(button1Pin, INPUT);  // initialize the pushbutton pin as an input:

  //Init LED pin
  pinMode(LED_BUILTIN, OUTPUT);

  //Init Serial USB
  Serial.begin(9600);                      // Setup Serial Monitor to display information//
  Serial.println(F("Initialize System"));  // Display bootup information//

  //Init Potentiometer
  pinMode(pot1Pin, INPUT);
  pinMode(pot2Pin, INPUT);
  pinMode(pot3Pin, INPUT);

  //Init Relays
  pinMode(ACT1RELAY07extend, OUTPUT);  //Set ACT1RELAY07extend as an output
  pinMode(ACT1RELAY08rtract, OUTPUT);  //Set ACT1RELAY08rtract as an output
  pinMode(ACT2RELAY09extend, OUTPUT);  //Set ACT2RELAY09extend as an output
  pinMode(ACT2RELAY10rtract, OUTPUT);  //Set ACT2RELAY10rtract as an output
  pinMode(ACT3RELAY11extend, OUTPUT);  //Set ACT3RELAY11extend as an output
  pinMode(ACT3RELAY12rtract, OUTPUT);  //Set ACT3RELAY12rtract as an output

  //Initilaze the pot values
  pot1PREVIOUS = analogRead(pot1Pin);
  pot2PREVIOUS = analogRead(pot2Pin);
  pot3PREVIOUS = analogRead(pot3Pin);
  pot1CURRENT = analogRead(pot1Pin);
  pot2CURRENT = analogRead(pot2Pin);
  pot3CURRENT = analogRead(pot3Pin);
}



void loop() {  // put your main code here, to run repeatedly:

  //Read Potentiometer Values:
  // TO DO HERE -  the map fuction will re scale the analoge input map(value, fromLow, fromHigh, toLow, toHigh)
  // Use this to eventuall ramp up or down the pot1CURRENT, to up the DIFF values to increase the movement timings
  pot1CURRENT = analogRead(pot1Pin);
  //pot1CURRENT = map(pot1CURRENT, 0, 1023, 0, 179); *** SCALAR FOR POT VALUE - massage this to scale (in our case to conver to MS)
  //Serial.print("Pot1 Raw val : ");Serial.println(pot1CURRENT); // uncomment this to put back in serial monitor raw potentiometer
  pot2CURRENT = analogRead(pot2Pin);
  //pot2CURRENT = map(pot2CURRENT, 0, 1023, 0, 179);
  //Serial.print("Pot2 Raw val : ");Serial.println(pot2CURRENT);
  pot3CURRENT = analogRead(pot3Pin);
  //pot2CURRENT = map(pot3CURRENT, 0, 1023, 0, 179);
  //Serial.print("Pot3 Raw val : ");Serial.println(pot3CURRENT);

  // Read Pushbutton Value:
  buttonState = digitalRead(button1Pin);  // read the state of the pushbutton value
  Serial.print("Button1 Raw val : ");
  Serial.println(button1Pin);

  // Main logic
  // button pressed - no movement and potentiometers free to calibrate,
  // Button released - checks for potentiometer movement and then opens relays based on movement scalar
  if (buttonState == HIGH) {
    digitalWrite(LED_BUILTIN, HIGH);  //LED on - button pressed

    // when pressed, set the float always equal to the value, thus no DIFF and no relay action:
    //this might need cleanup******
    pot1PREVIOUS = analogRead(pot1Pin);
    pot2PREVIOUS = analogRead(pot2Pin);
    pot3PREVIOUS = analogRead(pot3Pin);
    pot1CURRENT = analogRead(pot1Pin);
    pot2CURRENT = analogRead(pot2Pin);
    pot3CURRENT = analogRead(pot3Pin);

  } else {
    digitalWrite(LED_BUILTIN, LOW);  //LED off - button released

    //beggining of loop - set Pot1 current values
    pot1CURRENT = analogRead(pot1Pin);
    pot2CURRENT = analogRead(pot2Pin);
    pot3CURRENT = analogRead(pot3Pin);

// Check for change in movement
#define TOLERANCE 18  //this is set as a variable and should be a constant, cleanup later
    int diffabs1 = abs(pot1CURRENT - pot1PREVIOUS);
    int diffabs2 = abs(pot2CURRENT - pot2PREVIOUS);
    int diffabs3 = abs(pot3CURRENT - pot3PREVIOUS);
    int diff1 = (pot1CURRENT - pot1PREVIOUS);
    int diff2 = (pot2CURRENT - pot2PREVIOUS);
    int diff3 = (pot3CURRENT - pot3PREVIOUS);

    Serial.print("diff1 val : ");
    Serial.println(diff1);
    Serial.print("diff2 val : ");
    Serial.println(diff2);
    Serial.print("diff3 val : ");
    Serial.println(diff3);

    //if the absolute difference from potentiometers is less than the tolerance, ignore to avoid slow drifting
    if (diffabs1 < TOLERANCE) {
      pot1PREVIOUS = analogRead(pot1Pin);
    }
    if (diffabs2 < TOLERANCE) {
      pot2PREVIOUS = analogRead(pot2Pin);
    }
    if (diffabs3 < TOLERANCE) {
      pot3PREVIOUS = analogRead(pot3Pin);
    }

    //if absolute difference from potentiometers is greater than the tolerance, add to the counters
    if (diffabs1 > TOLERANCE) {  // run relay7or8 when potentiator moves more than tolderance

      if (diff1 > 0) {                                     //if diff1 is positive, PULL LENS UP (slider moved up, pull actuator in)
        ACT1extendCOUNTER = 0;                             // sets ACT1extendCOUNTER counter to zero, stopping any PUSH
        ACT1rtractCOUNTER = ACT1rtractCOUNTER + diffabs1;  // adds to the ACT1rtractCOUNTER counter, adding PULL for diffabs1 in MilliS
        digitalWrite(ACT1RELAY07extend, LOW);              //Relay 7 stops//
        digitalWrite(ACT1RELAY08rtract, HIGH);             //Relay8 ON, PULL actuator1 //
      }
      if (diff1 < 0) {                                     //if diff1 is negative, PUSH LENS DOWN (slider moved DOWN, PUSH actuator out)
        ACT1rtractCOUNTER = 0;                             // sets ACT1rtractCOUNTER counter to zero, stopping any PULL
        ACT1extendCOUNTER = ACT1extendCOUNTER + diffabs1;  // adds to the ACT1extendCOUNTER counter, adding PUSH for diffabs1 in MilliS
        diffabs1 = 0;                                      //zero diffabs1 going into next loop
        digitalWrite(ACT1RELAY08rtract, LOW);              //Relay 8 stops//
        digitalWrite(ACT1RELAY07extend, HIGH);             //Relay7 ON, PUSH actuator1  //
      }
      Serial.print("ACT1rtractCOUNTER val : ");
      Serial.println(ACT1rtractCOUNTER);
      Serial.print("ACT1extendCOUNTER val : ");
      Serial.println(ACT1extendCOUNTER);
    }
    if (diffabs2 > TOLERANCE) {  // run relay9or10 when potentiator moves more than tolderance

      if (diff2 > 0) {                                     //if diff2 is positive, PULL LENS UP (slider moved up, pull actuator in)
        ACT2extendCOUNTER = 0;                             // sets ACT2extendCOUNTER counter to zero, stopping any PUSH
        ACT2rtractCOUNTER = ACT2rtractCOUNTER + diffabs2;  // adds to the ACT2rtractCOUNTER counter, adding PULL for diffabs2 in MilliS
        digitalWrite(ACT2RELAY09extend, LOW);              //Relay 9 stops//
        digitalWrite(ACT2RELAY10rtract, HIGH);             //Relay10 ON, PULL actuator2 //
      }
      if (diff2 < 0) {                                     //if diff1 is negative, PUSH LENS DOWN (slider moved DOWN, PUSH actuator out)
        ACT2rtractCOUNTER = 0;                             // sets ACT1rtractCOUNTER counter to zero, stopping any PULL
        ACT2extendCOUNTER = ACT2extendCOUNTER + diffabs2;  // adds to the ACT2extendCOUNTER counter, adding PUSH for diffabs2 in MilliS
        digitalWrite(ACT2RELAY10rtract, LOW);              //Relay 10 stops//
        digitalWrite(ACT2RELAY09extend, HIGH);             //Relay9 ON, PUSH actuator2  //
      }
      Serial.print("ACT2rtractCOUNTER val : ");
      Serial.println(ACT2rtractCOUNTER);
      Serial.print("ACT2extendCOUNTER val : ");
      Serial.println(ACT2extendCOUNTER);
    }
    if (diffabs3 > TOLERANCE) {                            // run relay11or12 when potentiator moves more than tolderance
      if (diff3 > 0) {                                     //if diff3 is positive, PULL LENS UP (slider moved up, pull actuator in)
        ACT3extendCOUNTER = 0;                             // sets ACT3extendCOUNTER counter to zero, stopping any PUSH
        ACT3rtractCOUNTER = ACT3rtractCOUNTER + diffabs3;  // adds to the ACT3rtractCOUNTER counter, adding PULL for diffabs3 in MilliS
        digitalWrite(ACT3RELAY11extend, LOW);              //Relay 11 stops//
        digitalWrite(ACT3RELAY12rtract, HIGH);             //Relay12 ON, PULL actuator3 //
      }
      if (diff3 < 0) {                                     //if diff1 is negative, PUSH LENS DOWN (slider moved DOWN, PUSH actuator out)
        ACT3rtractCOUNTER = 0;                             // sets ACT1rtractCOUNTER counter to zero, stopping any PULL
        ACT3extendCOUNTER = ACT3extendCOUNTER + diffabs3;  // adds to the ACT1extendCOUNTER counter, adding PUSH for diffabs1 in MilliS
        digitalWrite(ACT3RELAY12rtract, LOW);              //Relay 12 stops//
        digitalWrite(ACT3RELAY11extend, HIGH);             //Relay11 ON, PUSH actuator2  //
      }
      Serial.print("ACT3rtractCOUNTER val : ");
      Serial.println(ACT3rtractCOUNTER);
      Serial.print("ACT3extendCOUNTER val : ");
      Serial.println(ACT3extendCOUNTER);
      // this sytax works but currently the relays are haywire and dont enguage, seem to light up correctly though
    }

    // Turn off relays when counters expire //
    
    // Pull current time, declare millis
    unsigned long timeCURRENT = millis();
    
    // Calculate defference between last interation and this one (timePREVIOUS and timeCURRENT)
    elapsed = (timeCURRENT - timePREVIOUS);

    // Shave off elapesed time from each counter to count
    ACT1rtractCOUNTER = ACT1rtractCOUNTER - elapsed;
    ACT1extendCOUNTER = ACT1extendCOUNTER - elapsed;
    ACT2rtractCOUNTER = ACT2rtractCOUNTER - elapsed;
    ACT2extendCOUNTER = ACT2extendCOUNTER - elapsed;
    ACT3rtractCOUNTER = ACT3rtractCOUNTER - elapsed;
    ACT3extendCOUNTER = ACT3extendCOUNTER - elapsed;

    // If counter is less than or equal to 0, stop respective relay and set COUNTERS to zero
    if (ACT1rtractCOUNTER <= 0) {
      digitalWrite(ACT1RELAY08rtract, LOW);
      ACT1rtractCOUNTER = 0;
    }
    if (ACT1extendCOUNTER <= 0) {
      digitalWrite(ACT1RELAY07extend, LOW);
      ACT1extendCOUNTER = 0;
    }
    if (ACT2rtractCOUNTER <= 0) {
      digitalWrite(ACT2RELAY10rtract, LOW);
      ACT2rtractCOUNTER = 0;
    }
    if (ACT2extendCOUNTER <= 0) {
      digitalWrite(ACT2RELAY09extend, LOW);
      ACT2extendCOUNTER = 0;
    }
    if (ACT3rtractCOUNTER <= 0) {
      digitalWrite(ACT3RELAY12rtract, LOW);
      ACT3rtractCOUNTER = 0;
    }
    if (ACT3extendCOUNTER <= 0) {
      digitalWrite(ACT3RELAY11extend, LOW);
      ACT3extendCOUNTER = 0;
    }

    pot1PREVIOUS = pot1CURRENT;
    pot2PREVIOUS = pot2CURRENT;
    pot3PREVIOUS = pot3CURRENT;

    timePREVIOUS = millis();  //marks the system millisecond at the counter start

    //delay(0); //this is for debugging to verify counter ect//
  }
}


//todo



//check the drift, and motion drift to see how its doing? can tolerance be 7-10ish?
//setup a second button to do near identical as regular motion, but max add to counter is 50ms or 100ms


//Might need to tweek MAP for DIFF calibration
//pot1CURRENT = map(pot1CURRENT, 0, 1023, 0, 179);*****massage this and lean map() function
//current thoughts or potential issues
//polling and rapid potentiometer movements - DIFF, COUNTERS, counters with elapsed espessially
//what happens when you move up then down, need to make sure a second movment in another directions resets/overites existing relay command



