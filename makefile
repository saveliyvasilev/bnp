CXX=g++
CPPFLAGS=-std=c++2a -g
LDFLAGS=-Wl,-stack_size,0x640000

OBJ=main.o dummy_sum_problem.o dummy_sum_action.o
DEPS=

main: $(OBJ)
	$(CXX) $(OBJ) -o $@ $(CPPFLAGS) $(LDFLAGS)

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CPPFLAGS)

.PHONY: clean

clean:
	rm -f ./*.o main