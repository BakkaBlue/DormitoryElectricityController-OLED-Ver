# Dormitory Electricity Controller (OLED Version)

[English Version](./README_ENG.md) | 中文版本

![Project Banner]()

A compact and efficient electricity management solution for dormitories, featuring an OLED display, user-friendly interface, and advanced functionality.

## Features

- [x] **OLED Display**: Provides dormitory information and real-time clock display.
- [ ] **Bluetooth Connectivity**: Supports simple configuration and status monitoring via a mobile app.
- [ ] **User Interaction**: Equipped with buttons for local control and navigation.
- [ ] **Expandable Design**: Supports additional modules such as accelerometer sensors.

## Hardware Requirements

1. **ESP32-S3 Development Board**
2. **0.96-inch OLED Display (SSD1306)**
3. **Buttons**: At least 4 GPIO-based buttons for navigation.
4. **Optional Modules**:
   - Temperature and Humidity Sensor AHT10
   - Passive Buzzer (for annoying music)

## Software Requirements

- VS Code
- PlatformIO

## Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/BakkaBlue/DormitoryElectricityController-OLED-Ver.git
   cd DormitoryElectricityController-OLED-Ver
   ```
2. **Install Dependencies**:
   - Add the required libraries via PlatformIO.

3. **Configure the Code**:
   - Update the pin configuration or communication speed in the code to match your hardware setup.

4. **Upload the Code**:
   - Connect the ESP32-S3 board and upload the code using your IDE.

## Usage

### OLED Navigation
- **Left/Right Buttons**: Navigate through the menu.
- **Confirm Button**: Select an option.
- **Back Button**: Return to the previous menu.

### Bluetooth Control - Under Construction
1. Open the companion app on your phone.
2. Pair with the ESP32-S3 device.
3. Access real-time data and configure settings remotely.

### Alarm Clock
- Wake up every morning to ***annoying buzzer music***, on time.

## Contribution

We welcome contributions! Please follow these steps:

1. Fork the repository.
2. Create a feature branch:
   ```bash
   git checkout -b feature-name
   ```
3. Commit your changes and push:
   ```bash
   git push origin feature-name
   ```
4. Create a pull request.

## Acknowledgments

This project was developed with assistance from OpenAI's ChatGPT for coding and conceptual guidance. All content has been reviewed and finalized by Cyren. Contributions are welcome, provided they comply with the project's AGPL-3.0 license.

## License

This project is licensed under the GNU Affero General Public License v3.0. See the [LICENSE](./LICENSE) file for details.

This license ensures that any modifications or derivatives of this project are also open-sourced under AGPL, and prohibits the use of this project for commercial purposes without proper licensing.

## Contact

For questions, feel free to contact the author:
- **GitHub**: [BakkaBlue](https://github.com/BakkaBlue)
- **Email**: chip06balabala@gmail.com

---

Enjoy using the Dormitory Electricity Controller (OLED Version)! 🚀
