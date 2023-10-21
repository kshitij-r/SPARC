# Dynamic Test Harness Generator
dynamicHarness: 
	python3 scripts/dynamicSimulation.py

# Formal Test Harness Generator
formalHarness: 
	python3 scripts/formalProcessing.py

# Dynamic Synthesis of Harness
synthesis_dynamic: dynamicSimulation.o
	./dynamicSimulation.o
dynamicSimulation.o: dynamicSimulation.cpp
	clang -pthread dynamicSimulation.cpp -o dynamicSimulation.o

# Formal Synthesis of Harness
synthesis_formal: formalSynthesisHarness.bc
	klee --warnings-only-to-file formalSynthesisHarness.bc
formalSynthesisHarness.bc: formalSynthesisHarness.cpp
	clang -I ~/klee/include -emit-llvm -c -g formalSynthesisHarness.cpp && klee --warnings-only-to-file formalSynthesisHarness.bc

# Remove all harnesses and executables
clean:
	rm -f dynamicSimulation.o formalTestHarness.bc dynamicSimulation.cpp formalSynthesisHarness.cpp