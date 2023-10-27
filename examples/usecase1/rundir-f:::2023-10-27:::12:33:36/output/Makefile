# Formal synthesis of generated specification
formalvalidation: klee_sim.cpp
	clang -I ~/klee/include -emit-llvm -c -g klee_sim.cpp && klee --warnings-only-to-file klee_sim.bc
clean:
	rm -f *.bc