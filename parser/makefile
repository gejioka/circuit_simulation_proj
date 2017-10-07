all:
	cd src/.; \
	gcc -Wall -g parser.c -o parser -lm; 
	mv src/parser build/.;
	cd build/;\
	./parser /home/christos/giorgos_project/circuit_simulation_proj/parser/SimpleNetlists/Benchmark1.txt
	
gdb:
	cd build/;
	gdb;\
	file parser;\
	run ./parser /home/christos/giorgos_project/circuit_simulation_proj/parser/SimpleNetlists/Benchmark1.txt;	
