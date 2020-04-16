#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#include <Servo.h>
Servo myServo;
const int numberPin1 = 6;
const int numberPin2 = 7;

void setup() {
  pinMode(numberPin1, INPUT);
  pinMode(numberPin2, INPUT);
  Serial.begin(9600);
  myServo.attach(9);
  myServo.write(0);
  openfeedback();


}

void loop() {
  boolean a = (digitalRead(numberPin1) == 0);
  boolean b = (digitalRead(numberPin2) == 0);
  Serial.print("button 1:");
  Serial.println(a);
  Serial.print("button 2:");
  Serial.println(b);
  if (a && b ) {
    greeting();
  } else {
    newcustomer();
  }
}





void greeting() {
  lcd.clear();
  lcd.print("Welcome to self-");
  lcd.setCursor(0, 1);
  lcd.print("service lockbox");
  delay(2000);

  lcd.clear();
  lcd.print("Press any button");
  lcd.setCursor(0, 1);
  lcd.print("to start ");
  delay(2000);

}
void newcustomer() {
  Serial.println("enter new customer");
  String password = "";
  lcd.clear();
  lcd.print("Please enter");
  lcd.setCursor(0, 1);
  lcd.print("your code:");
  delay(2000);
  while (password.length() < 4) {
    if (digitalRead(numberPin1) == 1) {
      password += "1";
      lcd.clear();
      lcd.print("code entered:");
      lcd.setCursor(0, 1);
      lcd.print(password);
      delay(1500);
    }
    else if (digitalRead(numberPin2) == 1) {
      password += "0";
      lcd.clear();
      lcd.print("code entered:");
      lcd.setCursor(0, 1);
      lcd.print(password);
      delay(1500);
    }

  }
  lcd.clear();
  lcd.print("code accepted");
  lcd.setCursor(0, 1);
  lcd.print("**unlock**");
  delay(2000);
  myServo.write(90);
  delay(2000);
}
void openfeedback() {
  lcd.begin(16, 2);
  lcd.print("Too good");
  lcd.setCursor(0, 1);

  lcd.print("to go :)");
  delay(1000);
  lcd.clear();
  lcd.print("Lockbox :)");
  lcd.setCursor(0, 1);


  delay(2000);
}
