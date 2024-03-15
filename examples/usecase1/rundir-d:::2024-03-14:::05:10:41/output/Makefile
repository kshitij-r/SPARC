# Dynamic synthesis of generated specification
test: clean dynamicSynthesis.cpp
	g++ -std=c++14 -pthread dynamicSynthesis.cpp -o dynamicSynthesis && ./dynamicSynthesis
clean:
	rm -f dynamicSynthesis