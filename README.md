[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/3MmVbb7f)
# Debugging 24/25 Exercise 1

Detailed instructions are in the exercise sheet. Following are your checkpoints:

- [x] Implement parser and evaluator
- [x] Implement a fuzzer
- [x] Generate *lots* of random instances with your fuzzer. Your evaluator and z3 must return the same result on generated instances
- [x] Provide detailed build instructions for your code so that we can evaluate it
  - clone the repository with the "--recurse-submodules" flag
  - do "mkdir build" in the root of the project and then "cd build"
  - run "cmake .." followed by "make" to build
  - the executable "generator" will generate a random expression
  - the executable "evaluate" can be called like this "./evaluate -i ./path/to/smt-file" which accepts a file with smt expressions
  - the script "fuzz.sh" can be called from the build directory ("../fuzz.sh") to continuously generate expression and compare the evalutation of the evaluator executable with z3
