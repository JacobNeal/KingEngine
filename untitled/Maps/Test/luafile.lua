Player:setPosition( MapView, Player:x( MapView ), Player:y( MapView ) + 100 )

Map:load( "Tiles/tilesheetsmall.png", "Maps/example", 25, 20 )

ObjectLayer:clear()
ObjectLayer:setFile( "Tiles/objecttiles.png" )

BackgroundParticles:setColor( Color( 0, 0, 0, 0 ) )

ForegroundParticles:setColor( Color( 0, 0, 255, 80 ) )
ForegroundParticles:setSize( 6 )



--ForegroundParticles:setNumber( 15 )
ForegroundParticles:setNumber( 10 )

ForegroundParticles:setVelocity( 20 )
ForegroundParticles:setReach( 70 )

ForegroundEffect:set( 0, Color( 0, 0, 255, 120 ), Color( 0, 0, 255, 120 ), 10, 10 )

AdventureLog:insert( "From luafile.lua", Color( 255, 255, 0, 255 ) )
AdventureLog:insert( "Press {ENTER} to clear", Color( 0, 255, 0, 255 ) )

y = 0
num = 20

water = {}
ripple_vel = 30

-- Generate the Water Ripples
for count = 0, num - 1 do
  water[ count ] = ksAbstract( ksRect( 0, y, 32, 32 ), 4 )
  ObjectLayer:addObject( water[ count ] )
  ObjectLayer:animate( count, 4, 11, 15 )
  
  y = y + 32
end

x = 0

for count = num, num + 24 do
  water[ count ] = ksAbstract( ksRect( x, 0, 32, 32 ), 4 )
  ObjectLayer:addObject( water[ count ] )
  ObjectLayer:animate( count, 4, 11, 15 )
  
  x = x + 32
end

-- Create House Fire example
ForegroundEffect:add( Vector2f( 368, 272 ), 64, Color( 255, 255, 0, 80 ), Color ( 255, 255, 0, 60 ) )
ObjectLayer:addObject( ksAbstract( ksRect( 352, 256, 32, 32 ), 12 ) )
ObjectLayer:animate( num + 25, 12, 13, 15 )
ObjectLayer:addObject( ksAbstract( ksRect( 352, 224, 32, 32 ), 14 ) )
ObjectLayer:animate( num + 26, 14, 17, 7 )


ForegroundEffect:add( Vector2f( 528, 336 ), 64, Color( 255, 255, 0, 80 ), Color ( 255, 255, 0, 60 ) )
ObjectLayer:addObject( ksAbstract( ksRect( 512, 320, 32, 32 ), 12 ) )
ObjectLayer:animate( num + 27, 12, 13, 15 )
ObjectLayer:addObject( ksAbstract( ksRect( 512, 288, 32, 32 ), 14 ) )
ObjectLayer:animate( num + 28, 14, 17, 7 )


ForegroundEffect:add( Vector2f( 592, 240 ), 64, Color( 255, 255, 0, 80 ), Color ( 255, 255, 0, 60 ) )
ObjectLayer:addObject( ksAbstract( ksRect( 576, 224, 32, 32 ), 12 ) )
ObjectLayer:animate( num + 29, 12, 13, 15 )
ObjectLayer:addObject( ksAbstract( ksRect( 576, 192, 32, 32 ), 14 ) )
ObjectLayer:animate( num + 30, 14, 17, 7 )


--ForegroundEffect:add( Vector2f( 368, 400 ), 64, Color( 255, 255, 0, 80 ), Color( 255, 255, 0, 60 ) )
--ObjectLayer:addObject( ksAbstract( ksRect( 368, 384 ), 






