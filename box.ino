//this is a self-service lockbox for the user of 'too good to go' App in grocery store Coop Mega
//it examine the user's input, if the entered code is correct, then the box will be lock/unlock


//setting up the lcd
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins, using some of the anolog pins as digital pins
LiquidCrystal lcd(12, 11, 10, 9, A1, A2);
#include <Servo.h>

//innitialize the motor
Servo myServo;

//setting up the keypad
#define Password_Length 4
#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
//if using pin 0 and 1, then should not use Serial print. 
byte rowPins[ROWS] = {7, 6, 5, 4}; 
byte colPins[COLS] = {3, 2, 1, 0}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

//set a password, can be changed
char Data[Password_Length]; 
char Master[Password_Length] = "238C"; 
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;


void setup() {
  myServo.attach(8);
  myServo.write(0);
  //this is a greeting message that prints on the screen
  greeting();
  //clear the screen
  lcd.clear();


}

void loop() {
  //if user input is activated, then add it to the data
    customKey = customKeypad.getKey();
    if (customKey){
    Serial.println(customKey);
    Data[data_count] = customKey; 
    lcd.setCursor(data_count,1); 
    lcd.print(Data[data_count]); 
    data_count++; 
    
   
    }
  // when the length of the user input is same as our password, compare to see if the password is correct
  if(data_count == Password_Length){
     delay(2000);
    lcd.clear();
   // lcd.print(Data);
   // lcd.setCursor(0,1);
    //lcd.print(Master);
    delay(2000);
    
    
    //if the password is correct, print to the screen and unlock, rotate motor 90 degrees
    if(!strcmp(Data[0,3], Master[0,3])){
      lcd.print("Correct");
      lcd.clear();
      lcd.print("code accepted");
      lcd.setCursor(0, 1);
      if (locked == true){
        lcd.print("**unlock**");
        delay(2000);
        myServo.write(90);
        delay(2000);
      }else{
        lcd.print("**locked**");
        delay(2000);
        myServo.write(90);
        delay(2000);
      }
     }
    //if the password is not correct, give user feedback
    else{
      lcd.print("Incorrect");
      data_count=0;
      delay(1000);
      greeting();
      }
    //clear the data
    lcd.clear();
    clearData();  
   
  }
}
//the method to clear the data, so it wont mess up with new user input
void clearData(){
  while(data_count !=0){
    Data[data_count--] = 0; 
  }
  return;
}


void greeting() {
  lcd.begin(16, 2);
  lcd.print("Too good");
  lcd.setCursor(0, 1);

  lcd.print("to go :)");
  delay(3000);
  lcd.clear();

  lcd.print("Welcome to self-");
  lcd.setCursor(0, 1);
  lcd.print("service lockbox");
  delay(2000);
   lcd.clear();

}
