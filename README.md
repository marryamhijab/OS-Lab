# xv6 Process Manager

Extensions to [xv6-riscv](https://github.com/mit-pdos/xv6-riscv), MIT's teaching operating system, adding process monitoring and scheduling features.

Author: Marryam Hijab
Course: Operating System

## Features

1. `ps`: lists running processes with PID, state, memory and priority
2. `trace`: prints the system calls a program makes
3. `sysinfo`: shows free memory and number of processes
4. `nice` + priority scheduler: set process priority so important processes get more CPU
5. Lazy allocation: memory is allocated only when a program actually uses it

## Build and Run

```bash
make qemu
```

R