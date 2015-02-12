------------------------------------------------------------
-- Author:                 Jacob Neal
-- Date Created:           5/28/14
-- Last Modification Date: 8/31/14
-- Project:                Regime of Darkness
-- Filename:               Maps/Voltor/voltor.lua
--
-- Overview:
--    The purpose of this script is to set up the area for
--    Voltor Village during the day time and experiment
--    with Lua's capabilities, leading up to more emphasis
--    on content development.
------------------------------------------------------------

Map:load( "Tiles/Voltor/voltor.png", "Maps/Voltor/voltor", 75, 40 )

ObjectLayer:clear()
ObjectLayer:setFile( "Tiles/Voltor/voltor_obj.png" )

AudioTrack:transition( "the_honeymoon.ogg" )

BackgroundParticles:setColor( Color( 0, 0, 0, 0 ) )

ForegroundParticles:setColor( Color( 0, 0, 255, 0 ) )
ForegroundParticles:setSize( 6 )

ForegroundParticles:setNumber( 15 )
ForegroundParticles:setNumber( 10 )

ForegroundParticles:setVelocity( 20 )
ForegroundParticles:setReach( 70 )

ForegroundEffect:clear()
ForegroundEffect:resize( 75, 40 )
ForegroundEffect:set( 0, Color( 255, 255, 0, 40 ), Color( 255, 255, 0, 40 ), 10, 0 )

y = 0
num = 40

water = {}
ripple_vel = 30

-- Generate the Water Ripples
for count = 0, num - 1 do
  water[ count ] = ksAbstract( ksRect( 0, y, 32, 32 ), 33 )
  ObjectLayer:addObject( water[ count ] )
  ObjectLayer:animate( count, 33, 40, 15 )
  
  y = y + 32
end

x = 0

for count = num, num + 74 do
  water[ count ] = ksAbstract( ksRect( x, 0, 32, 32 ), 33 )
  ObjectLayer:addObject( water[ count ] )
  ObjectLayer:animate( count, 33, 40, 15 )
  
  x = x + 32
end

-- Create Trees
ObjectLayer:addObject( ksAbstract( ksRect( 800, 512, 64, 128 ), 0 ) )
ObjectLayer:addObject( ksAbstract( ksRect( 864, 448, 64, 128 ), 0 ) )
ObjectLayer:addObject( ksAbstract( ksRect( 928, 512, 64, 128 ), 0 ) )
ObjectLayer:addObject( ksAbstract( ksRect( 1536, 448, 64, 128 ), 0 ) )
ObjectLayer:addObject( ksAbstract( ksRect( 1472, 512, 64, 128 ), 0 ) )

-- Pink Slime
ObjectLayer:addObject( ksAbstract( ksRect( 864, 576, 64, 64 ), 4 ) )
ObjectLayer:animate( num + 80, 4, 5, 15 )

KingEngine:activateDialog( "I have been summoned by the guards...", Color( 50, 255, 50, 255 ), Vector2f( Player:x( MapView ) + 32, Player:y( MapView ) + 32 ) )
AdventureLog:insert( "What could they want?", Color( 50, 255, 50, 255 ) )