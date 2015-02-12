------------------------------------------------------------
-- Author:                  Jacob Neal
-- Date Created:            6/3/14
-- Last Modification Date:  6/3/14
-- Lab Number:              Term Project - Program 2
-- Filename:                portal.lua
--
-- Overview:
--    The purpose of this program is to have a small program
--    that demonstrates Lua being used as a scripting language
--    for my pre-existing C++ game engine. Lua is intended to 
--    be used as for lightweight scripting so I demo that 
--    here.
--
-- Input:
--    Input goes to the game itself, not these scripts.
--
-- Output:
--    The results of the scripting logic being sent to the
--    game engine.
------------------------------------------------------------

------------------------------------------------------------
-- Set Map
------------------------------------------------------------
Map:load( "Tiles/portal_demo/portal_demo.png", "Maps/portal_demo/portal", 25, 20 )

------------------------------------------------------------
-- Clear particles and effects
------------------------------------------------------------
ForegroundParticles:setColor( Color( 0, 0, 0, 0 ) )
ForegroundEffect:clear()
ForegroundEffect:set( 0, Color( 0, 0, 0, 0 ), Color( 0, 0, 0, 0 ), 10, 10 )

------------------------------------------------------------
-- Clear object layer and set to appropriate sheet
------------------------------------------------------------
ObjectLayer:clear()
ObjectLayer:setFile( "Tiles/portal_demo/portal_obj.png" )

------------------------------------------------------------
-- Create Blue Portal
------------------------------------------------------------
ObjectLayer:addObject( ksAbstract( ksRect( 128, 192, 64, 64 ), 0 ) )
ForegroundEffect:add( Vector2f( 160, 224 ), 64, Color( 0, 240, 255, 100 ), Color( 0, 240, 255, 80 ) )

------------------------------------------------------------
-- Create Red Portal
------------------------------------------------------------
ObjectLayer:addObject( ksAbstract( ksRect( 544, 416, 64, 64 ), 1 ) )
ForegroundEffect:add( Vector2f( 576, 448 ), 64, Color( 255, 245, 0, 100 ), Color( 255, 245, 0, 80 ) )