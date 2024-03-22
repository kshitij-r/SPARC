# Formal synthesis of generated specification
test: clean klee_sim.cpp
	clang -I ~/klee/include -emit-llvm -c -g klee_sim.cpp && klee -solver-backend=z3 --warnings-only-to-file klee_sim.bc
clean:
	rm -f *.bc