# Philosophers

Implementation of the classic Dining Philosophers concurrency problem, developed as part of the 42 curriculum. The goal is to coordinate multiple philosophers around a table so that they can eat, think, and sleep without causing deadlocks or data races.

This repository’s mandatory implementation lives in the `philo/` directory.

## Table of Contents
- Overview
- Rules and Arguments
- Build
- Run
- Output Format
- Design Notes
- Edge Cases and Validation
- Testing Tips
- Troubleshooting
- License

## Overview

Five philosophers sit around a round table with a fork between each pair. Each philosopher alternates between thinking, eating, and sleeping. To eat, a philosopher must pick up the two forks adjacent to them. The program must:
- Avoid deadlocks.
- Detect and report when a philosopher dies (fails to eat within `time_to_die` ms).
- Use millisecond precision timestamps starting at program start.
- Ensure thread-safe logging without interleaving or garbled output.

The mandatory version uses threads and mutexes (one mutex per fork, plus additional mutexes for shared state).

Directory layout:
- `philo/` — mandatory implementation (Makefile, sources, headers, etc.)

## Rules and Arguments

Program usage:
```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Arguments:
- `number_of_philosophers` (int > 0): number of philosophers and forks.
- `time_to_die` (ms, > 0): time after which a philosopher dies if they haven’t started eating.
- `time_to_eat` (ms, > 0): time it takes for a philosopher to eat.
- `time_to_sleep` (ms, > 0): time a philosopher spends sleeping.
- `[number_of_times_each_philosopher_must_eat]` (optional, int > 0): if specified, the simulation stops when every philosopher has eaten at least this many times.

Rules:
- Philosophers are numbered starting at 1.
- Each philosopher alternates: think → take forks → eat → drop forks → sleep → think…
- If any philosopher dies, the simulation ends and no further state changes are logged.

## Build

From the repository root, build the mandatory target inside `philo/`:

```
cd philo
make
```

Common Make targets:
- `make` — build the `philo` executable.
- `make clean` — remove object files.
- `make fclean` — remove objects and the executable.
- `make re` — rebuild from scratch.

The project generally compiles with:
- `cc` (or `gcc`)
- Flags: `-Wall -Wextra -Werror`

## Run

After building, run from `philo/`:

```
./philo 5 800 200 200
```

Example with an eat count limit:
```
./philo 5 800 200 200 5
```

Example with many philosophers:
```
./philo 200 800 200 200
```

Notes:
- Use reasonable timing values; too small values may cause immediate deaths on slower machines.
- The program prints logs to stdout.

## Output Format

Each log line follows:
```
<timestamp_ms> <philosopher_id> <action>
```

Common actions:
- `has taken a fork`
- `is eating`
- `is sleeping`
- `is thinking`
- `died`

Example:
```
12 1 has taken a fork
13 1 has taken a fork
13 1 is eating
214 1 is sleeping
415 1 is thinking
723 2 died
```

Guarantees:
- Timestamps are relative to the simulation start.
- Logs are serialized to avoid overlapping lines.

## Design Notes

Typical mandatory design (threads + mutexes):
- One thread per philosopher.
- One mutex per fork (array of `N` mutexes).
- A dedicated mutex for printing/logging.
- Shared state tracking last meal time and meal counts (protected by mutex(es)).
- Death monitor:
  - Either a separate monitoring thread, or periodic checks within philosopher threads protected by synchronization primitives.
- Deadlock avoidance:
  - Common strategies include ordering fork acquisition (e.g., lower-indexed fork first, except for one philosopher), or staggering start times.

Timing:
- Sleep and wait functions should aim for millisecond accuracy.
- Use small usleeps in loops to reduce CPU spin while maintaining responsiveness.

## Edge Cases and Validation

Input validation:
- Reject non-numeric or out-of-range arguments.
- All times must be positive (> 0).
- Philosopher count must be positive (> 0).

Edge scenarios to consider:
- `number_of_philosophers == 1` (can never acquire two forks; should die after `time_to_die`).
- Very small `time_to_die` relative to `time_to_eat` or `time_to_sleep`.
- Large philosopher counts (stress on scheduling and locks).
- Optional eat-count provided: simulation ends only after all philosophers meet the quota (and no one has died).

## Testing Tips

Quick runs:
```
./philo 5 800 200 200
./philo 5 800 200 200 7
```

Stress tests:
- Many philosophers:
  ```
  ./philo 200 610 200 200
  ```
- Tight timings (expect possible deaths, validate correct detection):
  ```
  ./philo 5 310 200 200
  ```

Memory and thread leaks:
- Use Valgrind (Linux):
  ```
  valgrind --leak-check=full --show-leak-kinds=all ./philo 5 800 200 200
  ```

Behavioral checks:
- Ensure no deadlocks occur (simulation progresses or terminates properly).
- Ensure no interleaved or corrupted log lines.
- Verify that no further logs appear after a death is printed.

## Troubleshooting

- Immediate deaths:
  - Increase `time_to_die` or reduce `time_to_eat/time_to_sleep`.
  - Ensure the system clock and sleep functions are accurate enough.
- Jittery timestamps:
  - Prefer monotonic clocks for timing.
  - Avoid long critical sections around sleeps and time checks.
- Hangs or no output:
  - Check for potential deadlocks (fork acquisition ordering, lock inversion).
  - Verify logging mutex usage.

## License

This project is for educational purposes as part of the 42 curriculum. Refer to your school’s policies on code sharing and plagiarism before reusing or distributing.
