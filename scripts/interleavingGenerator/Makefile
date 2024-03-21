# Run z3 configurator to create z3Gen.py and run it to create all possible interleaving sequences.
all: run_three

run_three: run_two
	cp interleavings.txt ../

run_one:
	python3 z3Configurator.py

run_two: run_one
	python3 z3Gen.py
