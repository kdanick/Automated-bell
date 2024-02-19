#include <Arduino.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <LiquidCrystal.h>

// Define the pins for the RTC, buzzer, and LCD
const int RTC_SDA = A4;
const int RTC_SCL = A5;
const int buzzerPin = 6;
const int LCD_RS = 12;
const int LCD_EN = 11;
const int LCD_D4 = 5;
const int LCD_D5 = 4;
const int LCD_D6 = 3;
const int LCD_D7 = 2;
const int buttonPin = 13;


// Create an instance of the LiquidCrystal object
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// Create an array to store the alarms
struct Alarm {
  int hour;
  int minute;
  int second;
  bool enabled;
};

// Declare Maximum number of alarms variable
const int MAX_ALARMS = 16;
Alarm alarms[MAX_ALARMS];

// Function prototypes
void initializeAlarms();
void initializeLCD();
void updateLCD();
bool isAlarmActive(int alarmNumber);
void soundAlarm(int alarmNumber);
String dayShortString(int day);

void setup() {
  // Initialize the serial port
  Serial.begin(9600);

  // Initialize the RTC
  setSyncProvider(RTC.get);
  int currentDay = weekday();

  // Initialize the alarms based on the current day
  if (currentDay == 1 || currentDay == 7) {
    initializeWeekendAlarms();
  } else if (currentDay == 4) {
    initializeWednesdayAlarms();
  } else {
    initializeWeekdayAlarms();
  }

  // Set up the LCD
  initializeLCD();
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  String dayOfWeek = dayShortString(weekday());

  // Check if any of the alarms are active
  for (int i = 0; i < MAX_ALARMS; i++) {
    if (isAlarmActive(i)) {
      soundAlarm(i);
    }
    if(digitalRead(buttonPin) == LOW){
      soundAlarm(i);
    }
    else{
      digitalWrite(buzzerPin, LOW);
    }

  }

  // Display the current time on the LCD
  updateLCD(dayOfWeek);
  delay(500);
}

void initializeWeekdayAlarms() {
  // Set the maximum number of alarms for weekday
  int maxAlarms = 6;

  // Set the alarm times
  alarms[0].hour = 10;
  alarms[0].minute = 40;
  alarms[0].enabled = true;

  alarms[1].hour = 12;
  alarms[1].minute = 34;
  alarms[1].enabled = true;

  alarms[2].hour = 13;
  alarms[2].minute = 16;
  alarms[2].enabled = true;

  alarms[3].hour = 12;
  alarms[3].minute = 36;
  alarms[3].enabled = true;

  alarms[4].hour = 12;
  alarms[4].minute = 56;
  alarms[4].enabled = true;

  alarms[5].hour = 12;
  alarms[5].minute = 12;
  alarms[5].enabled = true;

  // Disable the remaining alarms
  for (int i = maxAlarms; i < MAX_ALARMS; i++) {
    alarms[i].enabled = false;
  }
}

void initializeWeekendAlarms() {
  // Set the maximum number of alarms for weekend
  int maxAlarms = 6;

  // Set the alarm times
  alarms[0].hour = 14;
  alarms[0].minute = 42;
  alarms[0].enabled = true;

  alarms[1].hour = 14;
  alarms[1].minute = 48;
  alarms[1].enabled = true;

  alarms[2].hour = 14;
  alarms[2].minute = 50;
  alarms[2].enabled = true;

  alarms[3].hour = 15;
  alarms[3].minute = 27;
  alarms[3].enabled = true;

  alarms[4].hour = 8;
  alarms[4].minute = 39;
  alarms[4].enabled = true;

  alarms[5].hour = 13;
  alarms[5].minute = 35;
  alarms[5].enabled = true;

  // Disable the remaining alarms
  for (int i = maxAlarms; i < MAX_ALARMS; i++) {
    alarms[i].enabled = false;
  }
}

void initializeWednesdayAlarms() {
  // Set the maximum number of alarms for Wednesday
  int maxAlarms = 6;

  // Set the alarm times
  alarms[0].hour = 13;
  alarms[0].minute = 40;
  alarms[0].enabled = true;

  alarms[1].hour = 14;
  alarms[1].minute = 00;
  alarms[1].enabled = true;

  alarms[2].hour = 14;
  alarms[2].minute = 30;
  alarms[2].enabled = true;

  alarms[3].hour = 15;
  alarms[3].minute = 00;
  alarms[3].enabled = true;

  alarms[4].hour = 15;
  alarms[4].minute = 45;
  alarms[4].enabled = true;

  alarms[5].hour = 16;
  alarms[5].minute = 30;
  alarms[5].enabled = true;

  // Disable the remaining alarms
  for (int i = maxAlarms; i < MAX_ALARMS; i++) {
    alarms[i].enabled = false;
  }
}

bool isAlarmActive(int alarmNumber) {
  return alarms[alarmNumber].enabled &&
         (hour() == alarms[alarmNumber].hour &&
          minute() == alarms[alarmNumber].minute && second() <= 15);
}

void soundAlarm(int alarmNumber) {
  digitalWrite(buzzerPin, HIGH);
  tone(buzzerPin, 3000, 333); /*
  delay(200);
  digitalWrite(buzzerPin, LOW);*/ //This actually sounded worse!
}

String dayShortString(int day) {
  switch (day) {
    case 1: return "Sunday";
    case 2: return "Monday";
    case 3: return "Tuesday";
    case 4: return "Wednesday";
    case 5: return "Thursday";
    case 6: return "Friday";
    case 7: return "Saturday";
    default: return "";
  }
}

void initializeLCD() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alarm System");
  lcd.setCursor(0, 1);
  lcd.print("Initialized");
  delay(2000);
  lcd.clear();
}

void updateLCD(const String& dayOfWeek) {
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  char timeStr[9];
  sprintf(timeStr, "%02d:%02d:%02d", hour(), minute(), second());
  lcd.print(timeStr);
  lcd.setCursor(0, 1);
  lcd.print("Day: ");
  lcd.print(dayOfWeek);
}
