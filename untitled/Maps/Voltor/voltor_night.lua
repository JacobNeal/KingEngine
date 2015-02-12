------------------------------------------------------------
-- Author:                  Jacob Neal
-- Date Created:            5/28/14
-- Last Modification Date:  2/11/15
-- Project:	                Term Project - Program 1
-- Filename:                voltor_night.lua
--
-- Overview:
--    The purpose of this script is to display the state of
--	  Voltor Village at night time.
------------------------------------------------------------

Player:setPosition( MapView, 368, 388 )

Map:load( "Tiles/Voltor/voltor.png", "Maps/Voltor/voltor", 75, 40 )

ObjectLayer:clear()
ObjectLayer:setFile( "Tiles/Voltor/voltor_obj.png" )

AudioTrack:transition( "sorrow.ogg" )

BackgroundParticles:setColor( Color( 0, 0, 0, 0 ) )

ForegroundParticles:setColor( Color( 0, 0, 255, 80 ) )
ForegroundParticles:setSize( 6 )

ForegroundParticles:setNumber( 15 )
ForegroundParticles:setNumber( 10 )

ForegroundParticles:setVelocity( 20 )
ForegroundParticles:setReach( 70 )

ForegroundEffect:clear()
ForegroundEffect:resize( 75, 40 )
ForegroundEffect:set( 0, Color( 0, 0, 255, 120 ), Color( 255, 255, 0, 60 ), 240, 10 )

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

-- Create House Fire example
ForegroundEffect:add( Vector2f( 368, 272 ), 64, Color( 255, 255, 0, 80 ), Color ( 255, 255, 0, 60 ) )
ObjectLayer:addObject( ksAbstract( ksRect( 352, 256, 32, 32 ), 6 ) )
ObjectLayer:animate( num + 75, 6, 7, 15 )
ObjectLayer:addObject( ksAbstract( ksRect( 352, 224, 32, 32 ), 11 ) )
ObjectLayer:animate( num + 76, 11, 14, 7 )


ForegroundEffect:add( Vector2f( 528, 336 ), 64, Color( 255, 255, 0, 80 ), Color ( 255, 255, 0, 60 ) )
ObjectLayer:addObject( ksAbstract( ksRect( 512, 320, 32, 32 ), 6 ) )
ObjectLayer:animate( num + 77, 6, 7, 15 )
ObjectLayer:addObject( ksAbstract( ksRect( 512, 288, 32, 32 ), 11 ) )
ObjectLayer:animate( num + 78, 11, 14, 7 )


ForegroundEffect:add( Vector2f( 592, 240 ), 64, Color( 255, 255, 0, 80 ), Color ( 255, 255, 0, 60 ) )
ObjectLayer:addObject( ksAbstract( ksRect( 576, 224, 32, 32 ), 6 ) )
ObjectLayer:animate( num + 79, 6, 7, 15 )
ObjectLayer:addObject( ksAbstract( ksRect( 576, 192, 32, 32 ), 11 ) )
ObjectLayer:animate( num + 80, 11, 14, 7 )

-- Create Trees
ObjectLayer:addObject( ksAbstract( ksRect( 800, 512, 64, 64 ), 0 ) )
ObjectLayer:addObject( ksAbstract( ksRect( 864, 448, 64, 128 ), 0 ) )
ObjectLayer:addObject( ksAbstract( ksRect( 928, 512, 64, 128 ), 0 ) )
ObjectLayer:addObject( ksAbstract( ksRect( 1536, 448, 64, 128 ), 0 ) )
ObjectLayer:addObject( ksAbstract( ksRect( 1472, 512, 64, 128 ), 0 ) )

KingEngine:activateDialog( "I have been summoned by the guards...", Color( 200, 200, 80, 255 ), Vector2f( Player:x( MapView ) + 32, Player:y( MapView ) + 32 ) )
AdventureLog:insert( "What could they want?", Color( 200, 200, 80, 255 ) )