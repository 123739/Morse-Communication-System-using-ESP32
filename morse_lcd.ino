#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// -------- LCD SETUP --------
// Address usually 0x27 or 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);

// -------- PIN SETUP --------
const int bluePin = 2;    // DOT
const int greenPin = 5;   // DASH
const int buzzerPin = 23;

int dotTime = 300;

// -------- MORSE TABLE --------
String getMorse(char c) {
  switch (toupper(c)) {
    case 'A': return ".-";
    case 'B': return "-...";
    case 'C': return "-.-.";
    case 'D': return "-..";
    case 'E': return ".";
    case 'F': return "..-.";
    case 'G': return "--.";
    case 'H': return "....";
    case 'I': return "..";
    case 'J': return ".---";
    case 'K': return "-.-";
    case 'L': return ".-..";
    case 'M': return "--";
    case 'N': return "-.";
    case 'O': return "---";
    case 'P': return ".--.";
    case 'Q': return "--.-";
    case 'R': return ".-.";
    case 'S': return "...";
    case 'T': return "-";
    case 'U': return "..-";
    case 'V': return "...-";
    case 'W': return ".--";
    case 'X': return "-..-";
    case 'Y': return "-.--";
    case 'Z': return "--..";

    case '0': return "-----";
    case '1': return ".----";
    case '2': return "..---";
    case '3': return "...--";
    case '4': return "....-";
    case '5': return ".....";
    case '6': return "-....";
    case '7': return "--...";
    case '8': return "---..";
    case '9': return "----.";

    case ' ': return " ";
    default: return "";
  }
}

// -------- SIGNAL FUNCTIONS --------
void sendDot() {
  Serial.println("DOT");

  digitalWrite(bluePin, HIGH);
  tone(buzzerPin, 1000);

  delay(dotTime);

  digitalWrite(bluePin, LOW);
  noTone(buzzerPin);
}

void sendDash() {
  Serial.println("DASH");

  digitalWrite(greenPin, HIGH);
  tone(buzzerPin, 600);

  delay(dotTime * 3);

  digitalWrite(greenPin, LOW);
  noTone(buzzerPin);
}

void gap() {
  Serial.println("GAP");
  delay(dotTime);
}

void letterGap() {
  Serial.println("LETTER_GAP");
  delay(dotTime * 5);
}

void wordGap() {
  Serial.println("WORD_GAP");
  delay(dotTime * 7);
}

// -------- MORSE ENGINE --------
void sendMorse(String msg) {
  for (int i = 0; i < msg.length(); i++) {
    char c = msg[i];

    if (c == ' ') {
      wordGap();
      continue;
    }

    String morse = getMorse(c);

    for (int j = 0; j < morse.length(); j++) {
      if (morse[j] == '.') sendDot();
      else if (morse[j] == '-') sendDash();

      if (j < morse.length() - 1) gap();
    }

    letterGap();
    delay(200);
  }
}

// -------- SETUP --------
void setup() {
  Serial.begin(9600);

  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Initialize I2C with custom pins
  Wire.begin(26, 27);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Morse Ready");

  Serial.println("Type your message:");
}

// -------- LOOP --------
void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.length() > 0) {
      Serial.println("START");

      // -------- LCD DISPLAY --------
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Msg:");

      lcd.setCursor(0, 1);
      lcd.print(input.substring(0, 16)); // limit for 16 chars

      // -------- MORSE OUTPUT --------
      sendMorse(input);

      Serial.println("END");
    }
  }
}