#include <ESP32Servo.h>
#include <WiFi.h>
#include <HTTPClient.h>

// --- WiFi Info ---
// Replace these placeholders with your WiFi credentials.
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// --- Telegram Bot Info ---
// IMPORTANT: Generate a NEW bot token with @BotFather because the token
// previously pasted into chat should be considered exposed.
String BOT_TOKEN = "YOUR_NEW_TELEGRAM_BOT_TOKEN";
String CHAT_ID = "YOUR_TELEGRAM_CHAT_ID";

// --- Ultrasonic Sensor Pins ---
#define TRIG1 5   // Lid control sensor TRIG
#define ECHO1 18  // Lid control sensor ECHO
#define TRIG2 21  // Full detection sensor TRIG
#define ECHO2 22  // Full detection sensor ECHO

// --- Servo ---
#define SERVO_PIN 19
Servo lidServo;

// --- Thresholds ---
const int DIST_THRESHOLD_LID = 10; // cm - open lid when an object is detected
const int FULL_THRESHOLD = 4;      // cm - send full-bin alert

// --- Lid close delay ---
const unsigned long CLOSE_DELAY = 5000; // 5 seconds

// --- Full alert repeat interval ---
const unsigned long ALERT_INTERVAL = 10000; // 10 seconds

// --- Variables ---
bool lidOpen = false;
unsigned long objectGoneTime = 0;
unsigned long lastFullAlertTime = 0;

// --- Function Prototypes ---
int getDistance(int trigPin, int echoPin);
void sendTelegramMessage(String message);

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");

  // Ultrasonic sensor pins
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);

  // Attach servo and start with the lid closed
  lidServo.attach(SERVO_PIN, 500, 2400);
  lidServo.write(90);
}

void loop() {
  // Read distances
  int lidDistance = getDistance(TRIG1, ECHO1);
  int fullDistance = getDistance(TRIG2, ECHO2);

  Serial.print("Lid Sensor: ");
  Serial.print(lidDistance);
  Serial.print(" cm | Full Sensor: ");
  Serial.print(fullDistance);
  Serial.println(" cm");

  // --- LID CONTROL ---
  if (lidDistance > 0 && lidDistance <= DIST_THRESHOLD_LID) {
    lidServo.write(180); // Open
    lidOpen = true;
    objectGoneTime = 0;
  } else if (lidOpen) {
    if (objectGoneTime == 0) {
      objectGoneTime = millis();
    }

    if (millis() - objectGoneTime >= CLOSE_DELAY) {
      lidServo.write(90); // Close
      lidOpen = false;
      objectGoneTime = 0;
    }
  }

  // --- FULL DETECTION ---
  if (fullDistance > 0 && fullDistance <= FULL_THRESHOLD) {
    unsigned long currentTime = millis();

    if (lastFullAlertTime == 0 ||
        currentTime - lastFullAlertTime >= ALERT_INTERVAL) {
      Serial.println("Dustbin is FULL! Sending Telegram alert...");
      sendTelegramMessage("Dustbin is FULL! Please empty it.");
      lastFullAlertTime = currentTime;
    }
  } else {
    lastFullAlertTime = 0; // Reset when the bin is no longer full
  }

  delay(1000);
}

// --- Function to measure distance ---
int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) {
    return -1; // No echo received
  }

  int distanceCm = (int)(duration * 0.034 / 2.0);
  return distanceCm;
}

// --- Function to send Telegram message over HTTPS ---
void sendTelegramMessage(String message) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected.");
    return;
  }

  // URL-encode spaces and punctuation in the message.
  message.replace("%", "%25");
  message.replace(" ", "%20");
  message.replace("\n", "%0A");
  message.replace("&", "%26");
  message.replace("?", "%3F");
  message.replace("#", "%23");

  HTTPClient https;
  String url = "https://api.telegram.org/bot" + BOT_TOKEN +
               "/sendMessage?chat_id=" + CHAT_ID +
               "&text=" + message;

  https.begin(url);
  int httpCode = https.GET();

  Serial.print("HTTP Response code: ");
  Serial.println(httpCode);

  if (httpCode > 0) {
    Serial.println("Telegram request completed.");
  } else {
    Serial.println("Failed to send Telegram message.");
  }

  https.end();
}
