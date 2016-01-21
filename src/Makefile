CXX = clang++
SFML = -framework sfml-window -framework sfml-graphics -framework sfml-system

# You may instead want to change to -std=c++0x instead of -std=c++11 for older compiler
CXXFLAGS = -Wall -c -std=c++11
LDFLAGS = $(SFML)
EXE = KingEngine

all: $(EXE)

$(EXE): main.o ksApplication.o ksWorld.o ksControlLayer.o ksButton.o ksEntityLayer.o ksEntity.o ksVector2D.o
	$(CXX) $(LDFLAGS) main.o ksApplication.o ksWorld.o ksControlLayer.o ksButton.o ksEntityLayer.o ksEntity.o ksVector2D.o -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $@

ksApplication.o: ksApplication.cpp
	$(CXX) $(CXXFLAGS) ksApplication.cpp -o $@

ksWorld.o: ksWorld.cpp
	$(CXX) $(CXXFLAGS) ksWorld.cpp -o $@

ksControlLayer.o: ksControlLayer.cpp
	$(CXX) $(CXXFLAGS) ksControlLayer.cpp -o $@

ksButton.o: ksButton.cpp
	$(CXX) $(CXXFLAGS) ksButton.cpp -o $@

ksEntityLayer.o: ksEntityLayer.cpp
	$(CXX) $(CXXFLAGS) ksEntityLayer.cpp -o $@

ksEntity.o: ksEntity.cpp
	$(CXX) $(CXXFLAGS) ksEntity.cpp -o $@

ksVector2D: ksVector2D.cpp
	$(CXX) $(CXXFLAGS) ksVector2D.cpp -o $@

clean:
	rm *.o && rm $(EXE)
