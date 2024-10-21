
# Coin Collect Game using OpenGL

 This is a 2D coin collect game using OpenGL specification and building with GLFW3, SOIL, Freetype2.
 


## Demo
![LINK](Demo.gif)
[LINK](https://imgur.com/a/nxJM0bd)


## Environment

To run this project, you will need to compile in g++ or clang++ -std=c++17.
Futhermore, because the pre-compiled dynamic libararies are OS-dependent, it should be ran in the __MAC OS__ in the __Visual Studio Code__.

(Unfortunately, if TAs are not using MAC, then you are not able to use the following command to run this project. However, it is possible to install the Windows/Linux version of GLFW, SOIL Freetype2 to compile the project.)

In the Visual Studio Code, just simply compile with `Command + Shift + B` or in the menu bar `Terminal -> Run Build task`.
Only by doing so, the arguments in the `.vscode/task.json` wil be properly added. 

After successfully compiled, you will see an execution file `Game`, and simply type `./Game` in the terminal, the game should be executed!


## Features

- Using many textures
- Using several fonts from the internet
- Enabling blending in OpenGL
- Not modern OpenGL and no shader is used
