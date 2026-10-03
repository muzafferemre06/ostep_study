# OSTEP Self-Study

My notes, homework solutions and projects while working through
[*Operating Systems: Three Easy Pieces*](https://pages.cs.wisc.edu/~remzi/OSTEP/) by Remzi & Andrea Arpaci-Dusseau.

## Progress

### Part I — Virtualization: CPU

| Ch | Topic | Reading | Work |
|---|---|---|---|
| 2 | [Introduction](https://pages.cs.wisc.edu/~remzi/OSTEP/intro.pdf) | ✅ | — |
| 4 | [Processes](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-intro.pdf) | ✅ | [`codes/chapter-4`](codes/chapter-4) — `process-run.py` simulator |
| 5 | [Process API](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-api.pdf) | ✅ | [`codes/chapter-5`](codes/chapter-5) — `fork`/`exec`/`wait` exercises, Q1–Q8 |
| 6 | [Limited Direct Execution](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-mechanisms.pdf) | ✅ | [`codes/chapter-6`](codes/chapter-6) — syscall & context-switch cost measurement |
| 7 | [Scheduling: Introduction](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-sched.pdf) | | |
| 8 | [Scheduling: MLFQ](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-sched-mlfq.pdf) | | |
| 9 | [Scheduling: Proportional Share](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-sched-lottery.pdf) | | |
| 10 | [Multiprocessor Scheduling](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-sched-multi.pdf) | | |

Legend: ✅ done · 🔄 in progress

## Projects

- [`projects/wish-shell`](projects/wish-shell) — a simple Unix shell (`wish`) in C.

## Layout

```
codes/chapter-N/   homework code and answers per chapter
projects/          larger projects from the OSTEP project list
```

## Build

```sh
gcc -Wall -o q1 codes/chapter-5/homework-code/q1.c
gcc -Wall -o wish projects/wish-shell/wish.c
```
