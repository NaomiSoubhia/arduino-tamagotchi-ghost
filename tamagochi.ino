//Naomi Soubhia Doi 
//2025-10-29
//Final project: Tamagochi
//Game over if the bars get 0 and win if stays alive for 1 minute

#include <LiquidCrystal.h>
#include "pitches.h"
#include "songs.h"
#include "sprites.h"

//Initialise the Serial LCD.
LiquidCrystal lcd( 12,11,5,4,7,6); //These pin numbers are hard coded in on the serial backpack board.

//Defining Pins
int buzzerPin = 9;
int button = A0; 
int button2 = 3;
int button3 = 8;
int RGBRedPin = 10;
int RGBGreenPin = 2;
int RGBBluePin = 13;


//Global variables
int shower= 8;
int rest=8;
bool clean= false;
bool action =false;
bool gameOver= false;
int z = 0;
int food=8;
bool saveTime=true;

unsigned  long current_song_time = 0; 
unsigned long prev_song_time = 0; 
int note_count = 0;  
int on_off = 0; //variables for running the song

// Define the pixels for bars
byte life[8],hungry[8],cleaning[8] = {0};

// Define the timers
unsigned long lastTimeFood = 0;
unsigned long lastTimeRest = 0;
unsigned long lastTimeBath = 0;
unsigned long lastBlink = 0;
unsigned long time=0;
unsigned long currentMillis=0;

//Music pacman
unsigned long previousMillisNote = 0;
int currentNote = 0;
bool notePlaying = false;


void setup()
{
  lcd.begin (16,2);       // Initialize the 16x2 LCD display
  pinMode(button, INPUT); // Button for feeding the ghost
  pinMode(button2, INPUT);// Button for putting the ghost to sleep
  Serial.begin(9600);     // Serial communication for debugging
  pinMode(buzzerPin, OUTPUT); // Buzzer output pin

  // RGB LED pin modes
  pinMode(RGBRedPin, OUTPUT);
  pinMode(RGBGreenPin, OUTPUT); 
  pinMode(RGBBluePin, OUTPUT);

  // Create custom LCD characters (sprites)
  lcd.createChar(0, ghost);      // Default ghost sprite
  lcd.createChar(3, ghostFood);  // Food icon
  lcd.createChar(5, hungry);     // Hunger bar icon
  lcd.createChar(4, zzzzSleep);  // Sleeping animation
  lcd.createChar(1, moon);       // Moon icon (sleep/bath)
  
  lcd.clear(); // Clear the LCD screen

  // Display the ghost in the initial position
  lcd.setCursor(8, 1);
  lcd.write(byte(0)); // Draws the ghost
}


void loop(){
  
  // Play the haunted background music continuously
  hauntedMusic();
  
  // RGB LED status indicator (green/yellow/red)
  if(food>=6 && rest>=6 && shower>=6){
    // Healthy – green LED
    analogWrite(RGBRedPin, 255);
    analogWrite(RGBGreenPin, 0);
    analogWrite(RGBBluePin, 255);
  }
  else if(food>=3 && rest>=3 && shower>=3){
    // Warning – yellow LED
analogWrite(RGBRedPin,   0);  
analogWrite(RGBGreenPin, 0);  
analogWrite(RGBBluePin,  255);    
  }
  else{
    // Danger – red LED
    analogWrite(RGBRedPin, 0);
    analogWrite(RGBGreenPin, 255);
    analogWrite(RGBBluePin, 255); 
  }
  
  unsigned long currentMillis = millis(); // Current time in milliseconds
  
  // ACTION BUTTONS
  if(digitalRead(button) == HIGH){
    eat(); // Feed method
  } 
  
  if(digitalRead(button2) == HIGH){
    sleep(); // Sleep method
  } 
  
  if(digitalRead(button3) == HIGH){
    bath(); // Bath method
  } 
  
  // If any bar hits 0 → ghost dies
  if(rest==0 || shower==0 || food==0){
    on_off = 1;       // Stop music from main game
    dead();           // Call death animation
    gameOver = true;
    clean = true;
  }
  
  // Update the LCD every 1 second or whenever an action happens
  if(time + 1000 < currentMillis || action == false){

    if(!gameOver){

      // Clear screen after each action
      if(clean == true){
        clean = false;
        action = false;
        lcd.clear();
      }

      lcd.createChar(0, ghost); // Redraw the normal ghost sprite
      
      //
      // ========== HUNGER BAR ==========
      //
      for (int i = 0; i <= 8; i++) {
        if (i < food) {
          hungry[7 - i] = B00100; // Filled block
        } else {
          hungry[7 - i] = B00000; // Empty block
        }
      }
      lcd.createChar(3, ghostFood);
      lcd.createChar(5, hungry);
      lcd.setCursor(15, 0);
      lcd.write(byte(5)); // Bar (top)
      lcd.setCursor(15, 1);
      lcd.write(byte(3)); // Food icon (bottom)
      
      //
      // ========== REST BAR ==========
      //
      for (int i = 0; i <= 8; i++) {
        if (i < rest) {
          life[7 - i] = B00100;
        } else {
          life[7 - i] = B00000;
        }
      }
      lcd.createChar(6, life);
      lcd.setCursor(14, 0);
      lcd.write(byte(6)); // Rest bar
      lcd.setCursor(14, 1);
      lcd.write(byte(4)); // Zzzz icon
      
      //
      // ========== BATH BAR ==========
      //
      for (int i = 0; i <= 8; i++) {
        if (i < shower) {
          cleaning[7 - i] = B00100;
        } else {
          cleaning[7 - i] = B00000;
        }
      }
      lcd.createChar(10, cleaning);
      lcd.setCursor(13, 0);
      lcd.write(byte(10)); // Bath bar
      
      lcd.createChar(7, moon);
      lcd.setCursor(13, 1);
      lcd.write(byte(7)); // Moon icon

      //
      // ========== GHOST ANIMATION ==========
      //

      // Open eyes
      if (currentMillis - lastBlink > 200) {
        lcd.setCursor(8, 1);
        lcd.write(byte(0));
      }

      // Blink animation
      if (currentMillis - lastBlink > 700) {
        lcd.createChar(1, ghostBlink);
        lcd.setCursor(8, 1);
        lcd.write(byte(1));
        lastBlink = millis();
      }

      //
      // ========== DECREASE STATUS OVER TIME ==========
      //

      // Hunger decreases every 2.5s
      if (currentMillis - lastTimeFood >= 2500){ 
        if (food > 0) food--;
        lastTimeFood = currentMillis;
      }

      // Rest decreases every 3.5s
      if (currentMillis - lastTimeRest >= 3500) {
        if (rest > 0) rest--;
        lastTimeRest = currentMillis;
      }

      // Hygiene decreases every 4.5s
      if (currentMillis - lastTimeBath >= 4500) {
        if (shower > 0) shower--;
        lastTimeBath = currentMillis;
      }

    } // end if !gameOver

    //
    // ========== 1 MINUTE SURVIVAL CONDITION ==========
    //
    if(currentMillis >= 60000){
      survivor();  // Winning animation
      on_off = 1;  // Stop music
    }  
  }

}
//=======================
// EAT METHOD
//=======================
void eat() {
  time = millis();             // Record the current time for action timing
  lcd.createChar(0, ghostEat); // Change ghost sprite to eating animation
  food = 8;                    // Refill the food bar to maximum
  lcd.setCursor(8, 1);         // Move cursor to ghost position
  lcd.write(byte(0));           // Draw ghost eating

  // Display food icons on the top row
  lcd.setCursor(6, 0);
  lcd.write(byte(3));
  lcd.setCursor(8, 0);
  lcd.write(byte(3));
  lcd.setCursor(10, 0);
  lcd.write(byte(3));

  clean = true;   // Flag to indicate screen needs clearing after action
  action = true;  // Flag to indicate an action is happening
}

//=======================
// SLEEP METHOD
//=======================
void sleep(){
  time = millis();             // Record current time for animation

  rest = 8;                    // Refill the rest bar
  lcd.createChar(0, ghostSleep); // Change ghost sprite to sleeping animation
  lcd.createChar(9, zzzzSleep2); // Add additional sleep animation
  lcd.createChar(1, zzzzSleep3); // Additional zzzz icon

  lcd.setCursor(8, 1);
  lcd.write(byte(0));           // Draw sleeping ghost
  lcd.setCursor(9, 0);
  lcd.write(byte(9));           // Display zzzz
  lcd.setCursor(10, 0);
  lcd.write(byte(4));           // Additional sleep bar
  lcd.setCursor(11, 0);
  lcd.write(byte(1));           // Display final zzzz/indicator

  clean = true;   // Flag to clear screen after animation
  action = true;  // Flag to indicate an action is happening
}

//=======================
// BATH METHOD
//=======================
void bath(){
  time = millis();             // Record current time

  shower = 8;                  // Refill hygiene bar
  lcd.createChar(0, ghostSleep); // Ghost shows calm/neutral during bath
  lcd.createChar(1, moon);     // Moon icon for bath

  lcd.setCursor(8, 1);
  lcd.write(byte(0));           // Draw ghost
  lcd.setCursor(3, 0);
  lcd.write(byte(1));           // Draw moon icon

  clean = true;   // Screen will need clearing after action
  action = true;  // Action in progress
}

//=======================
// GAME OVER METHOD (DIED)
//=======================
void dead(){  
  currentMillis = millis();  // Current time in ms

  //=============== PLAY DEATH MUSIC ===============
  if (currentNote < notes) {
    int noteDuration = 1000 / durations[currentNote];  // Calculate duration of the note
    int pause = noteDuration * 1.70;                  // Add pause after note

    if (!notePlaying) {
      tone(buzzerPin, melody[currentNote], noteDuration); // Play current note
      previousMillisNote = currentMillis;  // Save start time
      notePlaying = true;
    } 
    else if (currentMillis - previousMillisNote >= pause) {
      noTone(buzzerPin);  // Stop note
      currentNote++;       // Go to next note
      notePlaying = false;
    }
  } 
  else {
    noTone(buzzerPin); 
    currentNote = 0;       // Reset song
  }

  // Clear LCD once if needed
  if(saveTime == true){
    time = millis();
    saveTime = false;
    lcd.clear();  
  }

  // Draw ghost in position if z <= 7
  if(z <= 7){
    lcd.setCursor(8, 1);
    lcd.write(byte(0));
  }
    
  // Move Pac-Man like sprite across screen
  if(time + 500 < currentMillis) {
    if(z <= 16){  
      lcd.createChar(3, pacman);  
      lcd.setCursor(z, 1);
      lcd.write(byte(3));        // Draw pacman sprite
      lcd.setCursor(z-1, 1);
      lcd.write(" ");            // Clear previous position
      z++;                        // Increment position
      time = millis();            // Update last movement time
    }
    else{
      lcd.setCursor(3, 1);
      lcd.write("THE END...");   // Display end text
    }
  } 
}

//=======================
// PLAY HAUNTED MUSIC
//=======================
void hauntedMusic(){
  // Haunted song: [projecthub.arduino.cc](https://projecthub.arduino.cc/aams86/add-lights-and-spooky-music-to-your-jack-o-lantern-8dea8f)
  current_song_time = millis(); 

  if(on_off == 0) {
    if(current_song_time - prev_song_time >= 20){
      if(note_count + 1 == numTones){
        wait  = 10000;  // Long pause at end of song
        on_off++;
        on_off %= 2;
      } 
      else {
        prev_song_time = current_song_time;
        tone(buzzerPin, tones[note_count]); // Play next note
        on_off++;
        on_off %= 2;
      }
    }
  } 
  else {
    if(current_song_time - prev_song_time >= wait){
      prev_song_time = current_song_time;
      noTone(buzzerPin); // Stop note
      note_count++;
      note_count %= numTones; // Loop back to start
      on_off++;
      on_off %= 2;
      wait = 200;              // Short pause between notes
    }
  }
}

//=======================
// WIN METHOD (SURVIVOR)
//=======================
void survivor(){
  currentMillis = millis(); // Current time

  // Clear screen first time
  if(saveTime == true){
    time = millis();
    saveTime = false;
    lcd.clear();  
  }

  // If within first 3 seconds
  if(time + 3000 > currentMillis){
    gameOver = true;
    lcd.createChar(5, byteB);
    lcd.createChar(9, byteO);
  
    lcd.setCursor(8, 1);
    lcd.write(byte(0)); // Draw ghost
    lcd.setCursor(9, 0);
    lcd.write(byte(5)); // Draw letters B, O...
    lcd.setCursor(10, 0);
    lcd.write(byte(9));
    lcd.createChar(9, byteO2);
    lcd.setCursor(11, 0);
    lcd.write(byte(9));
    lcd.createChar(5, byteB2);
    lcd.setCursor(9, 0);
    lcd.write(byte(5));
    clean = true;
    action = true;
  }
  else{ 
    if(clean){  
      lcd.clear(); // Clear screen
    }

    // Sparkling stars animation
    if(lastBlink + 200 < currentMillis){  
      lcd.createChar(2, star);
      lcd.createChar(3, star3);
      lcd.setCursor(10, 0);
      lcd.write(byte(2)); 
      lcd.setCursor(15, 0);
      lcd.write(byte(2));
      lcd.setCursor(6, 0);
      lcd.write(byte(3));
      lcd.setCursor(2, 0);
      lcd.write(byte(2)); 
      lcd.setCursor(0, 1);
      lcd.write(byte(2));
      lcd.setCursor(13, 1);
      lcd.write(byte(2)); 
      lcd.setCursor(3, 1);
      lcd.write("THE END...");
    }

    // Alternate star animation
    if(lastBlink + 400 < currentMillis){
      lcd.createChar(2, star2); 
      lcd.createChar(3, star4); 
      lastBlink = currentMillis; 
      clean = false;    
    }
  }
}
