// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define TRIGGER_PIN  4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 350 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define mountingheight 206

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int current_measurement = 0;
int last_measurement = 0;
int travel_time = 0;
int delta = 0;

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(A1, OUTPUT);
}

void loop() {
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  int measuredDistance = sonar.ping_cm(); // Send ping, get distance in cm and print result (0 = outside set distance range)
  
  last_measurement = current_measurement;
  travel_time = sonar.ping_median(5);
  current_measurement = sonar.convert_cm(travel_time);
  int person_height = mountingheight - current_measurement;
  delta = current_measurement - last_measurement;
  //Serial.println(measuredDistance);
  
  /* if(person_height < 10)
  {
     digitalWrite(A1, LOW);
  }
  else
  {
     digitalWrite(A1, HIGH);
     Serial.print("Person's Height: ");
     Serial.print(person_height);
     Serial.println("cm");
  } */

  if(delta < 3 && person_height > 10)
  {
     //digitalWrite(A1, HIGH);
     Serial.print("Person's Height: ");
     Serial.print(person_height);
     Serial.println("cm");
  }

}
