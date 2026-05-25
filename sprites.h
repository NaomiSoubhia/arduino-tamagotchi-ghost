#ifndef SPRITES_H
#define SPRITES_H

// Define the pixels for a moon
byte moon[8] = {
  B00000,
  B00000,
  B01110,
  B11100,
  B11100,
  B11100,
  B01110,
  B00000
};


// Define the pixels for a ghost
byte ghost[8] = {
  B00000,
  B01110,
  B11111,
  B10101,
  B11111,
  B11111,
  B10101,
  B00000
};

// Define the pixels for a ghost blinking
byte ghostBlink[8] = {
  B00000,
  B01110,
  B11111,
  B11111,
  B11111,
  B11111,
  B10101,
  B00000
};

// Define the pixels for ghost eating
byte ghostEat[8] = {
  B00000,
  B01110,
  B10101,
  B11111,
  B11011,
  B11111,
  B10101,
  B00000
};

// Define the pixels for ghost food
byte ghostFood[8] = {
  B00000,
  B00100,
  B01110,
  B01110,
  B01110,
  B00000,
  B00000,
  B00000
};


// Define the pixels for ghost sleep
byte ghostSleep[8] = {
  B00000,
  B01110,
  B11111,
  B11111,
  B11011,
  B11111,
  B10101,
  B00000
};

// Define the pixels for pacman
byte pacman[8] = {
  B00000, 
  B01110, 
  B11111, 
  B11111, 
  B11000,
  B11111, 
  B11111, 
  B01110
};


// Define the pixels for ZZZZ
byte zzzzSleep[8] = {
  B00000,
  B01110, 
  B00010, 
  B00100, 
  B01000,  
  B01110,  
  B00000,      
  B00000       
};
byte zzzzSleep2[8] = {
  B00000, 
  B00000,  
  B11111,  
  B00010,
  B00100,  
  B01000,  
  B11111,      
  B00000      
};

byte zzzzSleep3[8] = {
  B00000,  
  B00000,     
  B00000,
  B11111,  
  B00010, 
  B00100,    
  B01000, 
  B11111  
};


// Define the pixels for BOO
byte byteB[8] = {
  B00000,
  B11110,
  B10001, 
  B10001, 
  B11110, 
  B10001,
  B10001,
  B11110     
         
};

byte byteB2[8] = {
  B00000,
  B11110,
  B11111, 
  B10001, 
  B11110, 
  B10001,
  B10001,
  B11110     
         
};
byte byteO[8] = {
  B00000,
  B01110,
  B10001,
  B10001,
  B10001,
  B10001,
  B01110,
  B00000    
};

byte byteO2[8] = {
  B00000,
  B01110,
  B11111,
  B10001,
  B10001,
  B11111,
  B01110,
  B00000
};

//Define the pixels for star
byte star[8] = {
  B00000,
  B00000,
  B00000,
  B00100,
  B00100,
  B11011,
  B00100,
  B00100
};

byte star2[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B01010,
  B00100,
  B00000
};

byte star3[8] = {
  B00100,
  B00100,
  B11011,
  B00100,
  B00100,
  B00000,
  B00000,
  B00000

};

byte star4[8] = {
  B00100,
  B01010,
  B00100,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

#endif
