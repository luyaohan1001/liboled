# liboled

`liboled` is a C library designed for controlling framebuffer-based OLED screens in Linux embedded systems. It provides a simple and efficient API to interact with OLED displays using the SSD1306 driver.

## Features

- **Simple API**: Easy-to-use functions for initializing, controlling, and updating OLED displays.
- **Flexible**: Supports various operations such as drawing text, graphics, and managing display settings.
- **Cross-Platform**: Works on any Linux-based embedded system with appropriate system adaptations.
- **Examples Included**: Includes example code to help you get started quickly.

## Installation

To install `liboled`, follow these steps:

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/luyaohan1001/liboled 

2. **Build:**

  ```bash
  mkdir build && cd build
  make -j4 ..

3. **Test:**
   ```bash
   cd build 
   ./test
