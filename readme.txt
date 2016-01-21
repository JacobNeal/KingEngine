--------------------------KingEngine--------------------------

New Features:

Currently adding in a limited 3D perspective that allows you
to view walls in front of you, above you, below you, and to
the left and right sides.

Example:
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

--------------------------------------------------------------

Engine Outline:

ksApplication
    ksWorld
        ksFile
    ksLuaLoader
    map(ksParticleEmitter *)
    ksEntityLayer
        map(ksEntity *)
    ksControlLayer
        map(ksControl *)
            ksButton
            ksText
            ksContainer
                ksControl
