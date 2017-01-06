# Fractals

## Description

This project was created to play with fractals.

# Dependencies

* Qt 5.7 (https://www.qt.io/)
* OpenGL 3.0 ES (https://www.opengl.org/)

# Compiling (Linux)

Preferred way to compile:

1. Go to main directory (it contains README.md).

2. Create two folders: `build` and `artifacts`.

3. Open terminal and go to `build` folder.

4. Run this commands in terminal:

  ```bash
  cmake ..
  make
  ```

5. Copy `shader` folder from `fractals` to `artifacts` directory.

6. Compiled application should be in `artifacts` folder.

# To do

- Insensitiveness to be run from different directories (now it cannot find shaders).
- Modes system (every mode as different dynamic library which will be loaded in runtime).
- cross stitching mode :)
