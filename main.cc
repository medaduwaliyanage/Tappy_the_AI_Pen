#include "tappy_face.h"

// Small runnable-style example showing the core TAPPY loop.
// This file is intentionally an example, not the complete production firmware.

void setup() {
    Serial.begin(115200);
    TappyFace::GetInstance().Initialize();
}

void loop() {
    TappyFace::GetInstance().Update();
    delay(30);
}
