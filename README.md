# 🚗 Automotive ECU Communication System Using CAN Protocol

A bare-metal embedded C implementation of an automotive **Electronic Control Unit (ECU) communication system** built on the **LPC2129 microcontroller**, demonstrating real-time CAN bus messaging between a transmitter (Node A) and receiver (Node B) to control automotive lighting functions.

---

## 📋 Table of Contents

- [Overview](#overview)
- [Hardware](#hardware)
- [Project Architecture](#project-architecture)
- [CAN Message Protocol](#can-message-protocol)
- [File Structure](#file-structure)
- [Getting Started](#getting-started)
- [How It Works](#how-it-works)
- [Tools & IDE](#tools--ide)

---

## Overview

This project simulates an automotive body control scenario where **Node A (Transmitter ECU)** sends CAN messages in response to physical button presses (EINT0, EINT1, EINT2), and **Node B (Receiver ECU)** decodes those messages to control LEDs representing:

- 💡 **Headlight** (High Beam)
- 🔦 **Left Indicator** (with blinking)
- 🔦 **Right Indicator** (with blinking)

UART0 is used on both nodes for serial debug output at 9600 baud.

---

## Hardware

| Component | Details |
|---|---|
| Microcontroller | NXP LPC2129 (ARM7TDMI-S, 60 MHz) |
| CAN Controller | On-chip CAN1 peripheral |
| Indicators (RX side) | 3× LEDs on P0.17, P0.18, P0.19 |
| Input (TX side) | 3× Push buttons via EINT0, EINT1, EINT2 |
| Debug | UART0 at 9600 baud |
| IDE | Keil µVision |

---

## Project Architecture

```
┌──────────────────────────────┐         CAN Bus          ┌──────────────────────────────┐
│         Node A (TX)          │ ───────────────────────► │         Node B (RX)          │
│                              │                           │                              │
│  EINT0 → Head Light toggle   │   CAN ID 0x501 (0x10/11) │  LED1 (P0.17) - Head Light   │
│  EINT1 → Left Indicator      │   CAN ID 0x502 (0x12/13) │  LED2 (P0.18) - Left Blink   │
│  EINT2 → Right Indicator     │   CAN ID 0x503 (0x14/15) │  LED3 (P0.19) - Right Blink  │
│                              │                           │                              │
│  UART0: debug print          │                           │  UART0: debug print          │
└──────────────────────────────┘                           └──────────────────────────────┘
```

---

## CAN Message Protocol

| CAN ID | Data Byte | Meaning |
|--------|-----------|---------|
| `0x501` | `0x10` | Head Light **ON** |
| `0x501` | `0x11` | Head Light **OFF** |
| `0x502` | `0x12` | Left Indicator **ON** (blink) |
| `0x502` | `0x13` | Left Indicator **OFF** |
| `0x503` | `0x14` | Right Indicator **ON** (blink) |
| `0x503` | `0x15` | Right Indicator **OFF** |

All frames are **standard data frames** (FF=0, RTR=0, DLC=1).

---

## File Structure

```
├── nodeA.uvproj          # Keil project file – Transmitter (Node A)
├── nodeA.uvopt           # Keil options – Node A
├── nodeB.uvproj          # Keil project file – Receiver (Node B)
├── nodeB.uvopt           # Keil options – Node B
│
├── can1_tx_main.c        # Node A: main loop, button events, CAN TX
├── can1_tx_driver.c      # CAN1 transmit driver
│
├── can_rx_main.c         # Node B: main loop, CAN RX, LED control
├── can_rx_driver.c       # CAN1 receive driver + ISR
│
├── Bmain.c               # Additional/boot main entry
├── uart0_driver.c        # UART0 driver (debug serial)
├── delay.c               # Software delay utility (ms-level)
├── header2.h             # Shared type definitions & function prototypes
│
├── Startup.s             # ARM7 startup assembly (stack/heap init)
└── p1.ini                # Keil debugger initialization script
```

---

## Getting Started

### Prerequisites

- **Keil µVision 4/5** with the LPC2100 device pack installed
- **Flash Magic** or **Keil ULINK** for programming the LPC2129
- Two LPC2129 boards connected via a **CAN transceiver** (e.g., MCP2551 or SN65HVD230)

### Build & Flash

1. Clone the repository:
   ```bash
   git clone https://github.com/NaveenkumarAnnadurai/Automotive-ECU-Communication-System-Using-CAN-Protocol.git
   ```

2. Open **`nodeA.uvproj`** in Keil µVision → Build → Flash to the **transmitter board**.

3. Open **`nodeB.uvproj`** in Keil µVision → Build → Flash to the **receiver board**.

4. Connect both boards via CAN bus (CANH/CANL lines through transceiver ICs).

5. Open a serial terminal (9600 8N1) on both boards to observe debug output.

---

## How It Works

### Node A — Transmitter

- Initializes CAN1 and UART0.
- Configures **EINT0, EINT1, EINT2** as external interrupt sources via the VIC.
- Each button press toggles a flag (`tx_flagH`, `tx_flagL`, `tx_flagR`).
- The main loop checks these flags and transmits the corresponding CAN frame using `can1_tx()`.

### Node B — Receiver

- Initializes CAN1 and UART0.
- Configures the **CAN1 receive interrupt** via the VIC.
- The ISR populates a `CAN1` struct (`m1`) and sets a `flag`.
- The main loop reads `m1.id` and `m1.byteA` to drive the appropriate LED.
- Left and right indicators **blink** (50 ms on/off) until turned off.

---

## Tools & IDE

| Tool | Purpose |
|------|---------|
| Keil µVision | Build, debug, and flash |
| Flash Magic | UART-based ISP flashing |
| Serial Terminal | UART debug monitoring |
| CAN Analyzer (optional) | Bus-level frame inspection |

---

## License

This project is open-source and available for educational and personal use.
