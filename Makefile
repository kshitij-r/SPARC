synthesis_dynamic: dynamicSimulation.o
	./dynamicSimulation.o
dynamicSimulation.o: dynamicSimulation.cpp
	g++ -std=c++17 -pthread dynamicSimulation.cpp -o dynamicSimulation.o

synthesis_formal: formalTestHarness.bc
	klee --warnings-only-to-file formalTestHarness.bc
formalTestHarness.bc: formalTestHarness.cpp
	clang++-9 -I ~/klee/include -I ./include_new -emit-llvm -c -g formalTestHarness.cpp && klee --warnings-only-to-file formalTestHarness.bc

clean:
	rm -f dynamicSimulation.o formalTestHarness.bc