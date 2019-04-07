# arm-assembler
A work-in-progress ARM assembler

This project is intended to be an ARM assembler. It is designed to be a two pass assembler,
doing most of the work (populating symbol table, syntax & semantic analysis, etc) during the first
pass. The second pass will iterate through a collection of pre-assembled instructions and assemble
them.

Planned features:
- Output to ELF
- Macros & Directives
- "Live" mode where pre-assembled instructions can be piped into the program and assembled to stdout.
