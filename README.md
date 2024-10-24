
# Coin Collect Game using OpenGL

Coin Collect Game is a 3D game developed using C++ and OpenGL. The game features intuitive controls, simple mechanics, and fun graphics created using OpenGL.

## Demo
![LINK](Demo.gif)

[Demo Video](https://imgur.com/a/nxJM0bd)

## Features

- **2D Graphics**: The game utilizes OpenGL for rendering 2D objects, environments, and animations.
- **Player Controls**: The player can move the character in the 2D world, collecting coins along the way.
- **Coin Collection**: Collect as many coins as possible to achieve a high score.
- **Camera and Lighting**: Basic camera control and lighting techniques are applied to improve visual appeal.

## How It Works

The player can move the character using keyboard inputs. The camera follows the character, providing an immersive 3D experience. The game world contains various coins, and the objective is to collect them to increase your score.

## Prerequisites

- **C++ Compiler**: You need a C++ compiler that supports modern C++ standards.
- **OpenGL**: Ensure OpenGL libraries are installed on your system.
- **GLFW**: The game uses GLFW for creating windows and handling inputs.
- **GLAD**: The GLAD library is used for loading OpenGL functions.
- **GLM**: OpenGL Mathematics (GLM) is used for matrix and vector operations.

## Getting Started

### Clone the Repository
```bash
git clone https://github.com/Yoppman/Coin-Collect-Game-using-OpenGL.git
cd Coin-Collect-Game-using-OpenGL
```

### Building the Game

1. **Install Dependencies**: Ensure you have the required libraries (GLFW, GLAD, GLM) installed on your system.
   - On Ubuntu:
     ```bash
     sudo apt-get install libglfw3-dev libglm-dev
     ```
   - On Windows:
     Download and install the necessary dependencies.

2. **Build the Game**:
   - Use `g++` to compile the game:
     ```bash
     g++ -o CoinCollectGame main.cpp -lglfw -lGL -lGLU -ldl
     ```
   - This command compiles the `main.cpp` file and links the necessary OpenGL, GLFW, and GLU libraries.

3. **Run the Game**:
   ```bash
   ./CoinCollectGame
   ```

### Controls

- **A**: Move Left
- **D**: Move Right
- **ESC**: Quit the game

## Project Structure

```

```

## Dependencies

- OpenGL
- GLFW
- GLAD
- GLM

