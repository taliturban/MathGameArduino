#include <LiquidCrystal.h> 

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12,11,5, 4, 3, 2);


const int incorrectAttempts = 3; // create an intenger to calculate the wrong answer limit to game over
const int correctAttempts = 2; // create an intenger to calculate the correct answer limit to pass the level
int buttonPin = 7; //create an intenger declaring the button is connected to pin 7
int manPosition = 0; //create an intenger of the man position starting with 0
bool gameOn = true; //create an intenger to return true or false of game over
int correctAnsLevel4 = 0; //create an intenger to end the game if the user get two correct answers in the level 4
int redLed = 8; //connect the red led
int greenLed = 9; //connect the green led

//create the man character in the screen
byte man[] = { 
	B01110, 
	B01110, 
	B00100, 
	B01110, 
	B10101, 
	B00100, 
	B01010, 
	B10001, 
};

//initialize arduino and the LCD, declare the button as an input
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(redLed,OUTPUT);
  pinMode(greenLed,OUTPUT);
  pinMode(buttonPin, INPUT);
  displayWelcomeScreen();
  lcd.createChar(0, man); 
}

//create a main game void loop
void loop() {
  
  //if the user press the button the led turn on
  if (digitalRead(buttonPin) == HIGH && gameOn) {
    lcd.clear();
    
    //print the level 1
    lcd.setCursor(4, 0);
    lcd.print("LEVEL 1");
    delay(2000);  
    gameOn = level1();
    
    //print the level 2
    if (gameOn) {
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("LEVEL 2");
      delay(2000);
      gameOn = level2();
    }

    //print the level 3
    if (gameOn) {
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("LEVEL 3");
      delay(2000);
      gameOn = level3();
    }

   //print the level 4
    if (gameOn) {
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("LEVEL 4");
      delay(2000);
      gameOn = level4();
    }

    //print game over and keep the screen clear while the user don't press the button
    if (!gameOn) {
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("Game Over");
      lcd.setCursor(0,1);
      lcd.print("Press the button");
      delay(2000); 
      lcd.noDisplay(); 
      while (digitalRead(buttonPin) == LOW) {
        
      }
      lcd.display();   
    }
    
    //if the user press the button then the game start
  } else if (digitalRead(buttonPin) == HIGH && !gameOn) {
   
    //if the game is on the man position goes to the beggining and display the content of welcome screen
   gameOn = true;
   manPosition = 0;
   lcd.clear();
   displayWelcomeScreen();
 }
}
 
//create a method to display press the button + start game in the welcome screen
void displayWelcomeScreen() {
  lcd.setCursor(0,0);
  lcd.print("PRESS THE BUTTON");
  lcd.setCursor(3,1);
  lcd.print("START GAME");
}

//create a boolean to get true or false in the correct and incorrect answers
bool level1() {
  int attemptsIncorrect = 0;
  int attemptsCorrect = 0;
  
  //while the user is in level 1 and didn't get more than 3 incorrect answers + did not get more than 2 correct answers
  //display random questions of addition
  while (attemptsIncorrect < incorrectAttempts && attemptsCorrect < correctAttempts) {
    int num1 = random(100, 500);
  	int num2 = random(600, 900);
    int correctAnswer = num1 + num2;
    lcd.setCursor(0, 1); 

    //print this message in the screen
  	lcd.clear(); 
  	lcd.print("What is ");
 	lcd.print(num1);
 	lcd.print("+");     
  	lcd.print(num2);
 	lcd.print("?");
    
    //change man position
	updateManPosition(); 
    
    //create an intenger to get the user answer
    int userAnswer = getUserInput(); 
    

    //if the user get the correct answer
    if (userAnswer == correctAnswer) {
      
      //print this message if the user type the correct answer + change the man position + turn on the led 
      digitalWrite(greenLed, HIGH);
      delay (1000);
      digitalWrite(greenLed, LOW);
     Serial.println("Correct!");
      attemptsCorrect++;
      manPosition += 1;
      delay(500); 
         
    } 
    
    //if the user type the incorrect answer print this message
    else {
    digitalWrite(redLed, HIGH);
    delay (1000);
    digitalWrite(redLed, LOW);  
    Serial.println("Incorrect!");
      attemptsIncorrect++;
      delay(500); 
      
    }
  }
  //check if the user get at least 2 correct answers
  return attemptsCorrect >= correctAttempts;
  
  }

//create a boolean to get true or false in the correct and incorrect answers
  bool level2() {
  int attemptsIncorrect = 0;
  int attemptsCorrect = 0;
  
   //while the user is in level 2 and didn't get more than 3 incorrect answers + did not get more than 2 correct answers
  //display random questions of subtraction
  while (attemptsIncorrect < incorrectAttempts && attemptsCorrect < correctAttempts) {
    int num1 = random(600, 900);
  	int num2 = random(100, 500);
    int correctAnswer = num1 - num2;
    lcd.setCursor(0, 1); 

    //print this message in the screen
  	lcd.clear(); 
  	lcd.print("What is ");
 	lcd.print(num1);
 	lcd.print("-");     
  	lcd.print(num2);
 	lcd.print("?");
    
    //change man position
    updateManPosition(); 
    
    //get the user answer
    int userAnswer = getUserInput(); 
    

    // if the user get the correct print this message + change man position 
    if (userAnswer == correctAnswer) {
     digitalWrite(greenLed, HIGH);
      delay (1000);
      digitalWrite(greenLed, LOW); 
     Serial.println("Correct!");
      attemptsCorrect++;
      manPosition += 1;
      delay(500); 
    
    } 
    
    // if the user don't get the answer print this message
    else {
      digitalWrite(redLed, HIGH);
      delay (1000);
      digitalWrite(redLed, LOW);  
      Serial.println("Incorrect!");
      attemptsIncorrect++;
      delay(500); 
      
    }
  }
  
   // if the user get 3 incorrect answers, display game over message + clear the screen
  if (attemptsIncorrect == incorrectAttempts){
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Game Over");
  lcd.setCursor(0,1);
  lcd.print("Press the button");
  delay(3000); 
  }
    
 return attemptsCorrect >= correctAttempts;

}
 
 //create a boolean to get true or false in the correct and incorrect answers
  bool level3() {
  int attemptsIncorrect = 0;
  int attemptsCorrect = 0;
  
   //while the user is in level 3 and didn't get more than 3 incorrect answers + did not get more than 2 correct answers
  //display random questions of multiplication  
   while (attemptsIncorrect < incorrectAttempts && attemptsCorrect < correctAttempts) {
    int num1 = random(50, 100);
  	int num2 = random(20, 80);
    int correctAnswer = num1 * num2;
    lcd.setCursor(0, 1); 

    //print this message in the screen
  	lcd.clear(); 
  	lcd.print("What is ");
 	lcd.print(num1);
 	lcd.print("*");     
  	lcd.print(num2);
 	lcd.print("?");
    
    //change man position
	updateManPosition(); 

   //get the user answer
    int userAnswer = getUserInput(); 
    

     //check the user answer
    if (userAnswer == correctAnswer) {
    
      //print this message if the user get the correct answer + change the man position + turn on the led
      digitalWrite(greenLed, HIGH);
      delay (1000);
      digitalWrite(greenLed, LOW); 
      Serial.println("Correct!");
      attemptsCorrect++;
      manPosition += 1;
      delay(500); 
        
    } 
     
    else {
   
     //print this message if the user get the incorrect answer + turn on the led
      digitalWrite(redLed, HIGH);
      delay (1000);
      digitalWrite(redLed, LOW);  
      Serial.println("Incorrect!");
      attemptsIncorrect++;
      delay(500); 
      
    }
  }

 // if the user get 3 incorrect answers, display game over message + clear the screen
  if (attemptsIncorrect == incorrectAttempts){
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Game Over");
  lcd.setCursor(0,1);
  lcd.print("Press the button");
  delay(3000); 
  }

}

  //create a boolean to get true or false in the correct and incorrect answers
  bool level4() {
  int attemptsIncorrect = 0;
  int attemptsCorrect = 0;
  
  //while the user is in level 4 and didn't get more than 3 incorrect answers + did not get more than 2 correct answers
  //display random questions of division
  while (attemptsIncorrect < incorrectAttempts && attemptsCorrect < correctAttempts) {
    int num1 = random(100, 300);
  	int num2 = random(20, 80);
    int correctAnswer = num1 / num2;
    lcd.setCursor(0, 1); 

    
    //print this message in the screen
  	lcd.clear(); 
  	lcd.print("What is ");
 	lcd.print(num1);
 	lcd.print("/");     
  	lcd.print(num2);
 	lcd.print("?");
    
    //change man position
	updateManPosition(); 

    //get the user answer
    int userAnswer = getUserInput(); 
    
    
    //check the user answer
    if (userAnswer == correctAnswer) {
      
    //print this message if the user get the correct answer + change the man position + turn on the led
    digitalWrite(greenLed, HIGH);
    delay (1000);
    digitalWrite(greenLed, LOW); 
    Serial.println("Correct!");
    attemptsCorrect++;
    manPosition += 1;
    correctAnsLevel4++;  
    delay(500);
}
    else {
   
      //print this message if the user get the incorrect answer and turn on the led
      digitalWrite(redLed, HIGH);
      delay (1000);
      digitalWrite(redLed, LOW);
      Serial.println("Incorrect!");
      attemptsIncorrect++;
      delay(500); 
      
    }
  }

   // if the user get 3 incorrect answers, display game over message + clear the screen  
  if (attemptsIncorrect == incorrectAttempts){
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Game Over");
  lcd.setCursor(1,0);
  lcd.print("Press the button");
  delay(3000); 
}
  
  //if the user get 2 or more correct answers in level 4 display the congratulations content  
  if (correctAnsLevel4 >= 2) {
  displayCongratulations();
  correctAnsLevel4 = 0;  
} 
  return attemptsCorrect >= correctAttempts;
}
 
 //create a method to display the congratulation message
  void displayCongratulations() {
  for (int i = 0; i < 16; ++i) {
    lcd.clear();
 	lcd.setCursor(0, 0);
  	lcd.print("Congratulations!");

    lcd.setCursor(i, 1);
    lcd.write((byte)0);
    delay(300);
  }

  delay(2000); 
}
  
  //create a intenger to get the user input so it display a message while wait for the user answer
  int getUserInput() {
  while (!Serial.available()) {
    Serial.println("Type your answer");
    Serial.println("You have 10 seconds");
    delay(10000);
    break;
  }
    
  //read an integer value from the Serial input and return it from the function
  return Serial.parseInt();
}


    // create a method to update the man position
    void updateManPosition(){
	lcd.setCursor(manPosition,1);
    lcd.write((byte)0);
  
}
