# Snake Game

This is a classic command-line snake game I made when I first learned C++, with multiple difficulty modes and wall-piercing gameplay

## 🕹️ Controls
- **Movement**  
  `W`/`↑` : Move Up  
  `S`/`↓` : Move Down  
  `A`/`←` : Move Left  
  `D`/`→` : Move Right  

- **Menu Navigation**  
  `↑`/`↓` : Select Difficulty  
  `Enter` : Confirm and Start  

## 🌟 Features
- **Three Difficulty Modes**  
  🟢 Easy Mode - Slow movement, wall-passing enabled  
  🟠 Normal Mode - Medium speed, wall-passing enabled  
  🔴 Hard Mode - Fast movement, wall collision ends game  

- **Smart Food Generation**  
  - Food (`F`) always spawns in valid positions  
  - Automatically avoids snake body and walls  
  - Aligns with snake movement step (Y coordinate is even)  

- **Game Rules**  
  ✅ Eat food to grow (+1 point per food)  
  ❌ Game ends if snake collides with itself  
  ❌ Wall collision immediately ends game in Hard Mode  

## 📥 Installation & Running
1. **Requirements**  
   - Windows OS  
   - C++17 compatible compiler  

2. **Compile & Run**  
   ```bash
   g++ main.cpp FigureEngine.cpp -o snake.exe -std=c++17
   ./snake.exe
## 📌 Notes
Ensure console window size is at least 40x20 characters

Game Symbols:
'#' - Wall | 'O' - Snake Body | 'F' - Food

Close the window to exit the game

🎮 Start your snake adventure! See how long you can survive in Hard Mode!
