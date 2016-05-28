#CXX = clang++
CXX = g++
SFML = -framework sfml-window -framework sfml-graphics -framework sfml-audio -framework sfml-system
LUA = -I/usr/local/Cellular/lua51/5.1.5_3/include -L/usr/local/Cellular/lua51/5.1.5_3/lib -lua
BOOST = -I/usr/local/Cellular/boost/1.60.0/include -L/usr/local/Cellular/boost/1.60.0/lib -boost
LUABIND = -I/usr/local/Cellular/luabind/0.9.1_1/include -L/usr/local/Cellular/luabind/0.9.1_1/lib -luabind
ENGINE = /Users/pigman/Documents/KingEngine_2/src

# You may instead want to change to -std=c++0x instead of -std=c++11 for older compiler
CXXFLAGS = -Wall -I$(ENGINE) -c -std=c++11 -ggdb
LDFLAGS = $(SFML)
EXE = KingEngine

all: $(EXE)

$(EXE): main.o ksComplex.o ksComplexBehavior.o ksApplication.o ksAudioTrack.o ksImageControl.o ksContainer.o ksLabel.o ksParticleEmitter.o ksLightSystem.o ksWorld.o ksPathFinder.o ksEffect.o ksControlLayer.o ksButton.o ksEntityLayer.o ksEntity.o ksVector2D.o
	$(CXX) $(LDFLAGS) main.o ksComplex.o ksComplexBehavior.o ksApplication.o ksAudioTrack.o ksImageControl.o ksContainer.o ksLabel.o ksParticleEmitter.o ksLightSystem.o ksWorld.o ksPathFinder.o ksEffect.o ksControlLayer.o ksButton.o ksEntityLayer.o ksEntity.o ksVector2D.o -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $@

ksComplex.o: $(ENGINE)/ksComplex.cpp
	$(CXX) $(CXXFLAGS) $(ENGINE)/ksComplex.cpp -o $@

ksComplexBehavior.o: $(ENGINE)/ksComplexBehavior.cpp
	$(CXX) $(CXXFLAGS) $(ENGINE)/ksComplexBehavior.cpp -o $@

ksApplication.o: $(ENGINE)/ksApplication.cpp
	$(CXX) $(CXXFLAGS) $(ENGINE)/ksApplication.cpp -o $@

ksAudioTrack.o: $(ENGINE)/ksAudioTrack.cpp
	$(CXX) $(CXXFLAGS) $(ENGINE)/ksAudioTrack.cpp -o $@

ksImageControl.o: $(ENGINE)/ksImageControl.cpp
	$(CXX) $(CXXFLAGS) $(ENGINE)/ksImageControl.cpp -o $@

ksContainer.o: $(ENGINE)/ksContainer.cpp
	$(CXX) $(CXXFLAGS) $(ENGINE)/ksContainer.cpp -o $@

ksLabel.o: $(ENGINE)/ksLabel.cpp
	$(CXX) $(CXXFLAGS) $(ENGINE)/ksLabel.cpp -o $@

ksParticleEmitter.o: $(ENGINE)/ksParticleEmitter.cpp
	$(CXX) $(CXXFLAGS) $(ENGINE)/ksParticleEmitter.cpp -o $@

ksLightSystem.o: $(ENGINE)/ksLightSystem.cpp
	$(CXX) $(CXXFLAGS) $(ENGINE)/ksLightSystem.cpp -o $@

ksWorld.o: $(ENGINE)/ksWorld.cpp
	$(CXX) $(CXXFLAGS) $(ENGINE)/ksWorld.cpp -o $@

ksPathFinder.o: $(ENGINE)/ksPathFinder.cpp
	$(CXX) $(CXXFLAGS) $(ENGINE)/ksPathFinder.cpp -o $@

ksEffect.o: $(ENGINE)/ksEffect.cpp
	$(CXX) $(CXXFLAGS) $(ENGINE)/ksEffect.cpp -o $@

ksControlLayer.o: $(ENGINE)/ksControlLayer.cpp
	$(CXX) $(CXXFLAGS) $(ENGINE)/ksControlLayer.cpp -o $@

ksButton.o: $(ENGINE)/ksButton.cpp
	$(CXX) $(CXXFLAGS) $(ENGINE)/ksButton.cpp -o $@

ksEntityLayer.o: $(ENGINE)/ksEntityLayer.cpp
	$(CXX) $(CXXFLAGS) $(ENGINE)/ksEntityLayer.cpp -o $@

ksEntity.o: $(ENGINE)/ksEntity.cpp
	$(CXX) $(CXXFLAGS) $(ENGINE)/ksEntity.cpp -o $@

ksVector2D.o: $(ENGINE)/ksVector2D.cpp
	$(CXX) $(CXXFLAGS) $(ENGINE)/ksVector2D.cpp -o $@

clean:
	rm *.o && rm $(EXE)
