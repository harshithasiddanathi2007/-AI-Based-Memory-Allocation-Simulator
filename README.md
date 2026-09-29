# AI-Based Memory Allocation Simulator

Menu-driven C program that simulates First Fit, Best Fit and Worst Fit,
measures fragmentation and efficiency, compares them, and recommends a
strategy using a rule-based weighted scoring module (not machine learning).

Build: `make` or `gcc main.c memory.c firstbest.c worstcomp.c ai.c -o sim`

Usage: create blocks (1), create processes (2), run 4, 5 and 6, then 7, 8, 9.

Test: blocks `100 500 200 300`, processes `180 250 90 400` -> Best Fit recommended.

See `MEMBER_WORK.md` for the team work division.
