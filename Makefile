dynamicHarness: 
	python3 dynamicSimulation.py

formalHarness: 
	python3 formalProcessing.py

synthesis_dynamic: dynamicSimulation.o
	./dynamicSimulation.o
dynamicSimulation.o: dynamicSimulation.cpp
	g++ -std=c++17 -pthread dynamicSimulation.cpp -o dynamicSimulation.o

synthesis_formal: formalSynthesisHarness.bc
	klee --warnings-only-to-file formalSynthesisHarness.bc
formalSynthesisHarness.bc: formalSynthesisHarness.cpp
	clang++-9 -I ~/klee/include -I ./include_new -emit-llvm -c -g formalSynthesisHarness.cpp && klee --warnings-only-to-file formalSynthesisHarness.bc

clean:
	rm -f dynamicSimulation.o formalTestHarness.bc dynamicSimulation.cpp formalSynthesisHarness.cpp