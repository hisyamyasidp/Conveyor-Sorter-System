#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_NeoPixel ring(12, 6, NEO_GRB + NEO_KHZ800);
Servo servoMerah, servoHijau;

const int btnStart = 2, btnStop = 3, btnEMG = 4;
const int potPin = A0, enA = 9, in1 = 8, in2 = 7;

bool mesinAktif = false;
bool modeEMG = false;

void setup() {
  lcd.init(); 
  lcd.backlight();
  ring.begin(); 
  ring.show();
  servoMerah.attach(10);
  servoHijau.attach(11);
  
  pinMode(btnStart, INPUT_PULLUP);
  pinMode(btnStop, INPUT_PULLUP);
  pinMode(btnEMG, INPUT_PULLUP);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  servoMerah.write(0);
  servoHijau.write(0);
  updateLCD("SYSTEM READY", "PRESS START");
  delay(2000);
}

void loop() {
  // 1. Cek Tombol Emergency
  if (digitalRead(btnEMG) == LOW) {
    modeEMG = true;
    mesinAktif = false;
  }

  // 2. Cek Reset Emergency
  if (digitalRead(btnStop) == LOW) {
    modeEMG = false;
    mesinAktif = false;
    matikanNeo();
  }

  // 3. Logika Mode Emergency
  if (modeEMG) {
    kontrolMotor(0);
    updateLCD("EMERGENCY STOP", "PRESS STOP RESET");
    kedipMerahEMG();
    return;
  }

  // 4. Logika Normal
  if (digitalRead(btnStart) == LOW) mesinAktif = true;

  if (mesinAktif) {
    kontrolMotor(120);
    updateLCD("CONVEYOR RUN", "SCANNING...");
    animasiNeo(0, 0, 255); 

    int nilaiWarna = analogRead(potPin);
    if (nilaiWarna > 100 && nilaiWarna < 400) sortirBarang(1); 
    else if (nilaiWarna > 600 && nilaiWarna < 900) sortirBarang(2);
  } else {
    kontrolMotor(0);
    updateLCD("MACHINE OFF", "STANDBY");
    matikanNeo();
  }
}

void kontrolMotor(int speed) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, speed);
}

void kedipMerahEMG() {
  static unsigned long lastMillis = 0;
  static bool ledState = false;
  if (millis() - lastMillis > 100) {
    ledState = !ledState;
    if (ledState) warnaNeo(255, 0, 0);
    else matikanNeo();
    lastMillis = millis();
  }
}

void sortirBarang(int tipe) {
  kontrolMotor(0);
  if (tipe == 1) {
    updateLCD("OBJECT: RED", "SORTING...");
    warnaNeo(255, 0, 0);
    servoMerah.write(90);
    delay(2000);
    servoMerah.write(0);
  } else {
    updateLCD("OBJECT: GREEN", "SORTING...");
    warnaNeo(0, 255, 0);
    servoHijau.write(90);
    delay(2000);
    servoHijau.write(0);
  }
}

void updateLCD(String b1, String b2) {
  lcd.setCursor(0,0); lcd.print("                ");
  lcd.setCursor(0,0); lcd.print(b1);
  lcd.setCursor(0,1); lcd.print("                ");
  lcd.setCursor(0,1); lcd.print(b2);
}

void warnaNeo(int r, int g, int b) {
  for(int i=0; i<12; i++) ring.setPixelColor(i, r, g, b);
  ring.show();
}

void animasiNeo(int r, int g, int b) {
  static int i = 0;
  ring.clear();
  ring.setPixelColor(i, r, g, b);
  ring.show();
  i = (i + 1) % 12;
  delay(50);
}

void matikanNeo() {
  ring.clear();
  ring.show();
}
