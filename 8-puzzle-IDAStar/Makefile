appname := app

CXX := g++ -std=c++11
CXXFLAGS := -Wall -O3

srcfiles := $(shell find . -name "*.cpp")
objects  := $(patsubst %.cpp, %.o, $(srcfiles))

all: $(appname)

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

depend: .depend

.depend: $(srcfiles)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	-rm -f *.o
	-rm -f $(appname)
	-rm -f $(srcfiles)/*.o
	-rm -f file.zip

dist-clean: clean
	rm -f *~ .depend

run:
	./$(appname)

runtest:
	./$(appname) < test.in

debug:
	gdb $(appname)

valgrind:
	valgrind --leak-check=full ./$(appname)

zipf:
	zip -r file.zip . -x .depend \*.zip \*.o \.vscode/ \$(appname) \.vscode/* \*.out \*.csv \*.txt \*.bin \*.csv \*.in