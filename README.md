Two-Node Vehicle Telemetry UART Link

A bare-metal C simulation of a two-node embedded telemetry system for a delivery robot. Node A (chassis MCU) reads sensor data and transmits framed UART messages every 200ms. Node B (head unit MCU) receives frames, validates checksums, and recovers gracefully from corruption — all without HAL abstractions or blocking loops.


Architecture

Node A (chassis MCU)                        Node B (head unit MCU)
┌─────────────────────────┐                ┌──────────────────────────────┐
│  IMU sensor (I2C sim)   │                │  Ring buffer (interrupt sim) │
│  Load sensor (SPI sim)  │── pipe() ────► │  Frame parser (state machine)│
│  Frame builder          │  (fake UART)   │  Checksum verifier           │
│  200ms timer            │                │  Error recovery              │
└─────────────────────────┘                └──────────────────────────────┘

Both nodes run as separate processes connected via a Linux pipe() which simulates the UART channel.


Frame Format

[ 0xAA ] [ length ] [ payload (16 bytes) ] [ checksum ]
   1B        1B       ax, ay, az, load          1B


0xAA — start byte, used by Node B to detect frame boundary
length — size of payload in bytes
payload — 3 IMU floats (ax, ay, az) + 1 load sensor float
checksum — XOR of all payload bytes for corruption detection



Project Structure

telemetry/
├── common/
│   ├── frame.h             # Frame and Payload struct definitions
│   ├── checksum.h          # compute_checksum declaration
│   └── checksum.c          # XOR checksum implementation
│
├── node_a/
│   ├── imu_sensor.h/c      # Simulated I2C IMU (ax=0, ay=0, az=9.8)
│   ├── load_sensor.h/c     # Simulated SPI load cell (5.0 kg)
│   ├── frame_builder.h/c   # Packs payload into UART frame
│   └── node_a_main.c       # 200ms transmit loop
│
├── node_b/
│   ├── uart_rx.h/c         # Ring buffer + ISR simulation
│   ├── frame_parser.h/c    # 4-state frame parser state machine
│   ├── checksum_verify.h/c # Checksum validation + error counter
│   └── node_b_main.c       # Node B entry point
│
└── main_sim.c              # Connects A and B via pipe(), forks two processes


Key Concepts Demonstrated


Bare-metal framing protocol — custom start byte, length, payload, checksum
XOR checksum — lightweight error detection without CRC hardware
Ring buffer — simulates interrupt-driven UART byte reception
State machine parser — 4 states: WAIT_START → READ_LENGTH → READ_PAYLOAD → READ_CHECKSUM
Struct packing — __attribute__((packed)) to eliminate compiler padding in wire format
Inter-process communication — Linux pipe() as a fake UART channel
Graceful error recovery — corrupted frames increment error counter, parser resyncs automatically



How to Build and Run

Requirements: GCC on Linux

bashgcc main_sim.c node_a/imu_sensor.c node_a/load_sensor.c node_a/frame_builder.c \
    node_b/uart_rx.c node_b/frame_parser.c node_b/checksum_verify.c \
    common/checksum.c -I common/ -I node_a/ -I node_b/ -o telemetry_sim

./telemetry_sim

Expected output:

valid frame received
valid frame received
valid frame received
...

If a frame is corrupted (e.g. on startup sync):

corrupted! error count: 1
valid frame received
valid frame received
...

Node B recovers automatically — no reset required.


Hardware Porting Notes

To port this to real hardware (STM32, ESP32):


Replace pipe() with real UART peripheral
Replace usleep(200000) with a hardware timer interrupt (TIM2, etc.)
Replace sensor stubs in imu_sensor.c / load_sensor.c with real I2C/SPI reads
Replace thread-based ring buffer push with actual UART RX ISR calling uart_rx_push()
Core logic (frame builder, parser, checksum) transfers unchanged



Author

Nithin Kumar — ECE Graduate, 2025
GitHub
