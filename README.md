# GalacticNova

## Overview
GalacticNova (GN) is - besides being a boss from Kirby - an interactive Solar System visualization application. 

Coded in c++ using the OpenGL library, this projects was made for my Image Synthesis course. 

## Usage

### Requiered

To compile GN it is mendatory to have those libraries installed on your computer :

- cmake min. 3.26
- OpenGL
- SDL
- GLEW

Compilation errors will occur if those are not found. 

### Compile and execute

In the project root folder :

**1 - Create ``build`` folder if it doesn't exists**
```
mkdir build
```
**2 - Place yourself in the ``build`` folder**
```
cd build
```
**3 - Generate makefile from ``CMakeLists.txt``**
```
cmake ..
```
**4 - Compile**
```
make
```
**5 - Launch application**
```
./GN/GN_visualizer
```

## Contact

For any question, please contact me at lysandre.macke@edu.univ-eiffel.fr


