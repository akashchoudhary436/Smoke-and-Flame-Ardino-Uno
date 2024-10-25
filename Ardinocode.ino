// Pin Definitions
#define smoke 11  // MQ2 sensor digital pin no. 11
#define flame 2   // Flame sensor digital pin no. 2
#define buzzer 3
#define g_led 4
#define r_led 5
int smoke_detect;
int flame_detect;

void setup() {
  pinMode(smoke, INPUT);
  pinMode(flame, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(g_led, OUTPUT);
  pinMode(r_led, OUTPUT);

  digitalWrite(buzzer, LOW);
  Serial.begin(9600); // Initialize serial communication with ESP32
}

void loop() {
  digitalWrite(g_led, HIGH);

  
  smoke_detect = digitalRead(smoke); // smoke_detect=1 (no smoke); smoke_detect=0 (smoke present)
  flame_detect = digitalRead(flame); // flame_detect=1 (no flame); flame_detect=0 (flame present)

  if ((!smoke_detect) || (!flame_detect)) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(r_led, HIGH);

    if (!smoke_detect) {
      Serial.println("smoke detected");
    }
    if (!flame_detect) {
      Serial.println("flame detected");
    }
  } else {
    digitalWrite(buzzer, LOW);
    digitalWrite(r_led, LOW);
  }

  delay(1000);  // Delay for 1 second before the next check
}
