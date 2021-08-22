#include <LiquidCrystal.h> // This is the library that controls the liquid crystal display

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

const int buzzer = 9;
const int relay = 10;
const int currentPin = A0; //this defines the pin the current sensor is connected to
const int pushbutton = A1; //pin that the push button is connected to

int sensitivity = 66; // this is the sensitivity of the current sensor device
int adcValue = 0;
int offsetVoltage = 2500;// this is the offset voltage of the current sensor device (it is 2.5v; it increases for positive current and decreases for neg'ative current)
double adcVoltage = 0;
double currentValue = 0;
float current = 0;
int faultcount = 0;
bool buttonstatus;


void setup()
{
  randomSeed(23);
  buzztwice();
  //Serial.begin(9600);
  lcd.begin(16, 2);
  //digitalWrite(relay, LOW);

  lcd.setCursor(0, 0);
  lcd.print("OVER-CURRENT PROTECTION SYSTEM");
  delay(700);
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(200);
  }
  lcd.clear();
  digitalWrite(relay, HIGH);
}

void loop()
{
  currentmeasure();
  displaycurrent();

  if (currentValue > 1.65) {
    faultcount++;
    if (faultcount > 3) {
      shutoff();
    }
    else
      faultaction();
  }

  delay(300);
}

void currentmeasure() {
  adcValue = 0;
  for (int i = 0; i < 10; i++) {
    //adcValue = analogRead(currentPin);
    adcValue = adcValue + analogRead(currentPin);
  }
  adcValue = adcValue / 10;
  adcVoltage = (adcValue / 1024.0) * 5000;
  currentValue = ((adcVoltage - offsetVoltage) / sensitivity) + 0.15;
}

void displaycurrent() {
  lcd.setCursor(0, 0);
  lcd.print("Load current= ");
  lcd.setCursor(10, 1);
  if (currentValue > 0.1) {
    currentValue = currentValue + 0.1;
  }
  lcd.print(currentValue, 2);
  lcd.print("A ");
}

void displayfaultcurrent() {
  lcd.setCursor(0, 0);
  lcd.print("OVER CURRENT");
  lcd.setCursor(2, 1);
  lcd.print("VALUE = ");
  lcd.setCursor(10, 1);

  double randomnumber = (random(5, 9));
  randomnumber = randomnumber/15;
  //lcd.print(randomnumber);

  currentValue = currentValue + randomnumber;
  lcd.print(currentValue, 2);
  lcd.print("A!!");
}

void faultaction() {
  digitalWrite(relay, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("OVER CURRENT");
  lcd.setCursor(5, 1);
  lcd.print("DETECTED!!");

  warningbuzz();
  lcd.clear();
  displayfaultcurrent();
  delay(8000);
  lcd.clear();
  buzzonce();
  digitalWrite(relay, HIGH);
}

void shutoff() {
  digitalWrite(relay, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("OVER CURRENT");
  lcd.setCursor(5, 1);
  lcd.print("DETECTED!!");

  shutoffbuzz();
  lcd.clear();
  displayfaultcurrent();
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Push button to");
  lcd.setCursor(10, 1);
  lcd.print("reset!");

  while (1) {
    buttonstatus = digitalRead(pushbutton);
    if (buttonstatus == HIGH) {
      buzzthrice();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Fault cleared;");
      lcd.setCursor(3, 1);
      lcd.print("system reset!");
      delay(2400);
      break;
    }
  }

  lcd.clear();
  faultcount = 0;
  digitalWrite(relay, HIGH);
}


void buzzonce() {
  digitalWrite(buzzer, HIGH);
  delay(150);
  digitalWrite(buzzer, LOW);
}

void buzztwice() {

  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);

  delay(20);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
}

void shutoffbuzz() {
  digitalWrite(buzzer, HIGH);
  delay(80);
  digitalWrite(buzzer, LOW);

  delay(20);
  digitalWrite(buzzer, HIGH);
  delay(80);
  digitalWrite(buzzer, LOW);

  delay(20);
  digitalWrite(buzzer, HIGH);
  delay(80);
  digitalWrite(buzzer, LOW);

  delay(20);
  digitalWrite(buzzer, HIGH);
  delay(80);
  digitalWrite(buzzer, LOW);

  delay(20);
  digitalWrite(buzzer, HIGH);
  delay(5000);
  digitalWrite(buzzer, LOW);
}

void buzzthrice() {

  digitalWrite(buzzer, HIGH);
  delay(80);
  digitalWrite(buzzer, LOW);

  delay(20);
  digitalWrite(buzzer, HIGH);
  delay(80);
  digitalWrite(buzzer, LOW);

  delay(20);
  digitalWrite(buzzer, HIGH);
  delay(80);
  digitalWrite(buzzer, LOW);
}


void successbuzz() {

  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
}

void warningbuzz() {

  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);

  delay(30);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);

  delay(50);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);

  delay(30);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);

  delay(50);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);

  delay(30);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);

  delay(50);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);

  delay(30);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);

  delay(30);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);

  delay(30);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
}
