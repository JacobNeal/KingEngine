CXX = clang++
SFML = -framework sfml-window -framework sfml-graphics -framework sfml-system
LUA = -I/usr/local/Cellular/lua51/5.1.5_3/include -L/usr/local/Cellular/lua51/5.1.5_3/lib -lua
BOOST = -I/usr/local/Cellular/boost/1.60.0/include -L/usr/local/Cellular/boost/1.60.0/lib -boost
LUABIND = -I/usr/local/Cellular/luabind/0.9.1_1/include -L/usr/local/Cellular/luabind/0.9.1_1/lib -luabind

# You may instead want to change to -std=c++0x instead of -std=c++11 for older compiler
CXXFLAGS = -Wall -c -std=c++11
LDFLAGS = $(SFML)
EXE = KingEngine

all: $(EXE)

$(EXE): main.o ksComplex.o ksComplexBehavior.o ksApplication.o ksWorld.o ksPathFinder.o ksEffect.o ksControlLayer.o ksButton.o ksEntityLayer.o ksEntity.o ksVector2D.o
	$(CXX) $(LDFLAGS) main.o ksComplex.o ksComplexBehavior.o ksApplication.o ksWorld.o ksPathFinder.o ksEffect.o ksControlLayer.o ksButton.o ksEntityLayer.o ksEntity.o ksVector2D.o -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $@

ksComplex.o: ksComplex.cpp
	$(CXX) $(CXXFLAGS) ksComplex.cpp -o $@

ksComplexBehavior.o: ksComplexBehavior.cpp
	$(CXX) $(CXXFLAGS) ksComplexBehavior.cpp -o $@

ksApplication.o: ksApplication.cpp
	$(CXX) $(CXXFLAGS) ksApplication.cpp -o $@

ksWorld.o: ksWorld.cpp
	$(CXX) $(CXXFLAGS) ksWorld.cpp -o $@

ksPathFinder.o: ksPathFinder.cpp
	$(CXX) $(CXXFLAGS) ksPathFinder.cpp -o $@

ksEffect.o: ksEffect.cpp
	$(CXX) $(CXXFLAGS) ksEffect.cpp -o $@

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
