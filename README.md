# simple-fluid

A simple 2d pressureless (e.g. smoke) real-time fluid. Using sfml for visualisation and can be interacted with via the mouse. Supports periodic, wall and free boundary conditions.

# Controls

| Key | Action |
|:----|:-------|
| Left click + drag | Inject velocity |
| Right click + drag | Inject mass |
| v | Draw velocity lines |
| g | Draw grid lines |
| space | pause fluid |

# Compiling

simple-fluid is compiled using cmake. An out-of-source build can be accomplished with the following commands:

```
mkdir build
cd build
cmake ..
make
```

Then run the created ```simple-fluid``` binary.

# Requirements
* C++11
* cmake
* sfml

# TODO
* Implement ease way to add persistent sources
* Replace ```const``` with ```constexpr``` where appropriate and benchmark difference