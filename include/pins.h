#pragma once

// ============================================================
// ESP32 <-> TB6612FNG Motor Driver Pin Mapping
// ============================================================
//
// Motor Driver: TB6612FNG
// Board: ESP32 DevKit / ESP-WROOM-32
//
// Notes:
// - GPIO23 is intentionally not used because it physically
//   interferes with the wheel in the current chassis layout.
// - All TB6612FNG control GPIOs are routed on the right side
//   of the ESP32 to leave the left side available for sensors,
//   buzzer, LEDs, OLED, etc.

// -------------------- Motor A --------------------

#define PIN_PWMA  21
#define PIN_AIN1  18
#define PIN_AIN2  17

// -------------------- Motor B --------------------

#define PIN_PWMB  19
#define PIN_BIN1  26
#define PIN_BIN2  27

// -------------------- Driver Control --------------------

#define PIN_STBY  16