# 🤖 TAPPY — The AI Pen

<p align="center"><strong>A compact AI assistant designed to fit naturally into a pen.</strong></p>

<p align="center"><img src="https://img.shields.io/badge/Platform-ESP32--S3-ff6b35?style=for-the-badge&logo=espressif"><img src="https://img.shields.io/badge/Voice-STT%20%2B%20TTS-6c5ce7?style=for-the-badge"><img src="https://img.shields.io/badge/AI-LLM-00b894?style=for-the-badge"><img src="https://img.shields.io/badge/OLED-SSD1306-0984e3?style=for-the-badge"></p>



> ## ⚠️ IMPORTANT
> **The source files in this repository are representative examples, not the complete private TAPPY production firmware.** See [`EXAMPLE_NOTICE.md`](./EXAMPLE_NOTICE.md) for the intellectual-property and example-code notice.

---

## ✨ About TAPPY

TAPPY is a student-built AI pen that brings voice conversation, intelligent assistance and a small expressive display into one portable device.

The idea is simple: instead of keeping an AI assistant on a phone or computer, TAPPY brings the interaction into a small device that can listen, respond and show emotion while you use it.

## 🚀 Features

### 🧠 AI Conversation
- Natural voice conversations
- LLM-powered responses
- Streaming conversational audio
- AI-controlled device functions

### 🎙️ Speech-to-Text and Text-to-Speech

~~~text
Your voice
   ↓
I²S microphone
   ↓
Speech-to-Text
   ↓
Language Model
   ↓
Text-to-Speech
   ↓
I²S speaker
~~~

### 👀 Animated OLED Face

TAPPY uses a **128×64 SSD1306 OLED** as its face.
- AI-selected expressions
- Automatic blinking
- Automatic eye movement
- Continuous face updates

Current expressions: **Normal, Angry, Glee, Happy, Sad, Worried, Focused, Annoyed, Surprised, Skeptic, Frustrated, Unimpressed, Sleepy, Suspicious, Squint, Furious, Scared and Awe.**

### 🌦️ Weather

TAPPY can retrieve current weather information using Open-Meteo and can save and change the weather location.

### ⏰ Time and Alarms
- Internet-synchronized local time
- Exact date/time alarms
- Relative alarms
- Persistent alarm storage
- Alarm listing and cancellation
- Audio alarm notification
- BOOT-button alarm dismissal

### 💡 Status Lighting

A WS2812/NeoPixel on **GPIO 48** provides visual status feedback.

### 🔊 Audio
- INMP441 I²S microphone input
- MAX98357A I²S speaker output
- Voice response playback
- Streaming audio
- Speaker volume control
- Built-in audio cues

## 🔌 TAPPY-S3 Hardware

| Part | Role |
|---|---|
| **ESP32-S3** | Main controller |
| **SSD1306 128×64 OLED** | Animated face |
| **INMP441** | Digital I²S microphone |
| **MAX98357A** | I²S audio amplifier |
| **WS2812 / NeoPixel** | Status indicator |
| **BOOT button** | User input |

### GPIO Map
| Device | Pins |
|---|---|
| INMP441 | WS **4**, SCK **5**, SD **6** |
| MAX98357A | BCLK **42**, LRCLK **45**, DIN **47** |
| SSD1306 | SDA **15**, SCL **7** |
| NeoPixel | Data **48** |
| BOOT | GPIO **0** |

---

# 📁 Example Firmware Structure

The repository keeps a **small example of each major part of the TAPPY firmware directly in the root source tree**, making the project easy to inspect for competition reviewers.

~~~text

└── main/
    ├── application.cc
    ├── mcp_server.cc
    ├── tappy_face.cc
    │
    ├── boards/
    │   └── tappy-s3/
    │       ├── config.h
    │       ├── config.json
    │       ├── README.md
    │       └── tappy_s3.cc
    │
    ├── audio/
    │   └── README.md
    │
    ├── time/
    │   └── README.md
    │
    ├── alarm/
    │   └── README.md
    │
    └── weather/
        └── README.md
~~~

> **Important:** the files inside `` are representative examples. They explain how the TAPPY features and firmware are organized; they are not presented as the complete production firmware.

## 🧩 What Each Example Shows

### `main/application.cc`
The central application layer. It represents where TAPPY brings together the board, display, audio system, networking and services.

### `main/mcp_server.cc`
The device-control layer. It demonstrates where AI-accessible functions such as volume, time, weather and alarms are registered.

### `main/tappy_face.cc`
The OLED face implementation example. It demonstrates SSD1306 initialization, 128×64 display configuration, emotion control, blinking, eye movement and continuous face updates.

### `main/boards/tappy-s3/`
The hardware-specific TAPPY-S3 board definition.
- `config.h` — GPIO and hardware configuration
- `config.json` — board/build information
- `tappy_s3.cc` — board initialization structure
- `README.md` — board notes

### `main/audio/`
Shows the role of the audio subsystem:

~~~text
INMP441 → STT → AI → TTS → MAX98357A
~~~

### `main/time/`
Shows the time-service location and responsibility. The production service handles internet-synchronized local time.

### `main/alarm/`
Shows the alarm-service location and responsibility. The production service handles persistent alarms, scheduling, listing and cancellation.

### `main/weather/`
Shows the weather-service location and responsibility. The production service uses Open-Meteo for current weather information.

# 👀 OLED Face Example

A simplified version of the face behavior looks like this:

~~~cpp
void initialize_face() {
    // SSD1306: SDA=15, SCL=7, 128x64
    face = new Face(128, 64, 40);

    face->RandomBehavior = false;
    face->RandomLook = true;
    face->RandomBlink = true;
    face->Behavior.GoToEmotion(Normal);
}

void update_face() {
    // The real face task updates continuously.
    face->Update();
}

void change_emotion(const char* emotion) {
    face->Behavior.GoToEmotion(ParseEmotion(emotion));
}
~~~

This is **only an example showing the feature**. The complete face implementation contains the actual task, display handling and emotion definitions.

# 🏗️ Firmware Architecture

~~~text
                    TAPPY-S3
                       │
          ┌────────────┼────────────┐
          │            │            │
          ▼            ▼            ▼
       Audio          OLED       NeoPixel
          │            │            │
          ▼            ▼            │
         STT        Face/Emotion    │
          │                         │
          ▼                         │
         LLM ────────────────► Device
          │                    Controls
          ▼
         TTS
          │
          ▼
       Speaker
~~~

The major source areas are kept separated so the hardware, AI interaction and individual services are easier to understand and maintain.

## ⚙️ Building the Full Firmware

This repository's `` directory is intended to **show the implementation and structure clearly**.

The complete TAPPY-S3 firmware contains the full source tree and GitHub Actions workflows for building the ESP32-S3 firmware.

~~~text
Target: ESP32-S3
Board:  TAPPY-S3
Build:  tappy-s3
~~~

So a reviewer can inspect the example implementation here, while the complete project contains the actual build system and production implementation.

## 🎯 Project

TAPPY is a continuing student innovation project exploring how embedded hardware, voice AI, audio and an expressive display can be combined into a small everyday device.

<p align="center"><strong>🤖 TAPPY — The AI Pen</strong></p>