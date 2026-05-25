# 🐾 Arduino Tamagotchi Ghost

A creative Arduino-based virtual pet project inspired by the classic Tamagotchi experience.  
This project simulates a digital pet with interactive gameplay using an Arduino microcontroller, LCD display, buttons, and sound.

The goal is simple: keep your Tamagotchi alive for as long as possible by managing its needs and avoiding game over conditions.

---

## 🎮 Project Concept

The **Tamagotchi Ghost** is a virtual pet system where the player must take care of the pet’s basic needs (such as happiness, hunger, and energy).  
If any of the vital stats reach zero, the game ends.  
If the pet survives for **1 minute or more**, you win the game.

This project is inspired by retro handheld gaming and aims to combine hardware programming, interaction design, and embedded systems logic.

---

## 🔧 Hardware Used

- Arduino board (Uno / Nano compatible)
- LCD Display (16x2 with LiquidCrystal library)
- Push buttons for interaction
- Buzzer for sound effects
- Wires and basic prototyping components

---

## 💻 How It Works

- The LCD displays the pet status and game interface
- Buttons allow the user to interact with the pet
- The system continuously updates:
  - Hunger
  - Happiness
  - Energy
- A buzzer provides audio feedback and alerts
- Game ends when any stat reaches zero or win condition is met

---

## 🌐 Online Simulations

You can test and explore this project without physical hardware using online simulators:

- 🧪 Tinkercad Version:  
  https://www.tinkercad.com/things/bHfNINRddrh-tamagochi/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard&sharecode=XYEf0IpX_7FSIBnPaklVufV5Q13Zy3oFIzrG9if8ur4

- 🔬 Wokwi Simulation:  
  https://wokwi.com/projects/464843126234221569

---

## 🎥 Demo Video

Add your demo video here:

👉 ...


---

## 📁 Repository Structure

```

arduino-tamagotchi-ghost/
├── Tamagotchi.ino
├── pitches.h
├── songs.h
└── sprites.h

````

---

## 🚀 Getting Started

1. Clone this repository:
```bash
git clone https://github.com/NaomiSoubhia/arduino-tamagotchi-ghost.git
````

2. Open the project in Arduino IDE

3. Install required libraries:

   * LiquidCrystal

4. Upload the code to your Arduino board

---

## ✨ Features

* Virtual pet logic system
* LCD-based user interface
* Button interaction system
* Sound effects via buzzer
* Win/Lose game conditions
* Lightweight embedded system design

---

## 📌 Future Improvements

* Add more animations on LCD
* Improve AI behavior of the pet
* Add EEPROM saving system (pet survives after reset)
* Add multiple difficulty levels
* Improve sound/music system

---

## 👩‍💻 Author

**Naomi Soubhia Doi**
Computer Programming Student
GitHub: [https://github.com/NaomiSoubhia](https://github.com/NaomiSoubhia)

---

## 📜 License

This project is open-source and free to use for educational purposes.

