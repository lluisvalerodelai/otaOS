# ToyKernel

A minimal educational kernel designed to explore low-level operating system concepts such as memory management, interrupt handling, hardware interaction, and device drivers.
I implemented this kernel while reading through the book [operating systems: 3 pieces](https://pages.cs.wisc.edu/~remzi/OSTEP/)

## Features

- **Bootable with GRUB**: kernel is grub bootable
- **Memory Layout**: A General Descriptor Table (GDT) for memory management setup.
- **Interrupt Handling**: Full interrupt setup, including a basic interrupt handler.
- **PS/2 Keyboard Driver**
- **VGA Driver**: 
  - **80x50 Text Mode** for basic text output.
  - **320x200 Color Mode** for graphics display.
- **PCI Prober**: Detects and interacts with PCI devices, equivalent to lspci command on linux
- **PIT driver** for multi-tasking

## Getting Started

### Prerequisites
To build and run the kernel, you need the following tools:
- **NASM** some assembly required. ¯\\\_(ツ)_/¯
- **QEMU** for emulating the kernel.
- **GCC** for compiling the kernel code.
- **Make** for building the project.
- **GRUB** for bootloading the kernel.

### Installation

#### 1. Clone the Repository
```bash
git clone https://github.com/lluisvalerodelai/otaOS
cd otaOS
```

#### 2. Build with Make
NOTE: if you want to see the 320x200 vga graphics mode demo, uncomment the first line in src/kernel.c
```bash
make build
make run
```
