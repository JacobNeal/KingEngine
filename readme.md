# KingEngine

<b>Description:</b>
2D and limited 3D perspective game engine created with C++ / SFML and scripted game content through Lua.

Example of the limited 3D perspective that allows you to view walls in front of you,
above you, below you, and to the left and right:
        __________________
       |\                /|
       | \ ____________ / |
       |  |            |  |
       |  |            |  |
       |  |            |  |
       |  /------------\  |
       | /              \ |
        ------------------

This feature is currently still experimental.

<b>Technologies</b>
C++, SFML and the Lua scripting language.

<b>Screenshots:</b>


--------------------------------------------------------------

<b>Engine Outline:</b>

ksApplication
    ksWorld
        ksFile
    ksLuaLoader
    ksEffect
    map(ksParticleEmitter *)
    ksEntityLayer
        map(ksEntity *)
            ksComplex
                ksComplexBehavior
                ksPathFinder
                    ksPathNode
    ksControlLayer
        map(ksControl *)
            ksButton
            ksText
            ksContainer
                ksControl
