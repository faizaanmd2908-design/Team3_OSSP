# Demo / Viva Quick Guide

## CO1 — Linux systems programming foundation
Show:
- `make`
- `./flight_simulator`
- process IDs printed by the program
- `getpid()` / `getppid()` in the monitor

Say:
> The project is implemented as a Linux C systems-programming application. The operating system provides process and file services through system calls such as fork, pipe, open, read, write and waitpid.

## CO2 — Processes and synchronization
Show:
- simulator PID
- monitor PID
- two child processes created using `fork()`
- final message after both children finish

Say:
> The parent creates independent child processes for simulation and monitoring. The parent uses waitpid() to synchronize with and safely reap both child processes.

## CO3 — IPC and signals
Show:
- telemetry appearing in the monitor
- `pipe()` mentioned in the output
- press Ctrl+C while it is running
- final safe termination

Say:
> The simulator writes telemetry structures into an anonymous pipe. The monitor reads the same data from the read end. SIGINT and SIGTERM are handled for asynchronous termination.

## Logging
Show:
```bash
cat logs/flight.log
```

Say:
> The monitor records telemetry and detected status conditions into a log file using Linux file I/O.

## Architecture

Parent/controller
  ├── fork() → Simulator
  │              └── write() → anonymous pipe
  │
  └── fork() → Monitor
                 └── read() ← anonymous pipe
                       └── open()/dprintf() → flight.log

Parent → waitpid() → safe termination
Signals → SIGINT/SIGTERM → controlled shutdown
