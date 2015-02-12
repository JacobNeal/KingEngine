Map:load( "Tiles/portal_demo/portal_demo.png", "Maps/Maze/maze", 25, 20 )
Player:setPosition( MapView, 672, 320 )

------------------------------------------------------------
------------------------------------------------------------
AdventureLog:insert( "Try to get to the flag.", Color( 255, 100, 100, 255 ) )
AdventureLog:insert( "Use WASD to move.", Color( 200, 200, 255, 255 ) )

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
-- Create a portal
------------------------------------------------------------

-- Portal 02
ObjectLayer:addObject( ksAbstract( ksRect( 320, 256, 64, 64 ), 0 ) )
ForegroundEffect:add( Vector2f( 352, 288 ), 64, Color( 0, 240, 255, 100 ), Color( 0, 240, 255, 80 ) )

-- Portal 03
ObjectLayer:addObject( ksAbstract( ksRect( 64, 160, 64, 64 ), 0 ) )
ForegroundEffect:add( Vector2f( 96, 192 ), 64, Color( 0, 240, 255, 100 ), Color( 0, 240, 255, 80 ) )

-- Portal 04
ObjectLayer:addObject( ksAbstract( ksRect( 704, 160, 64, 64 ), 0 ) )
ForegroundEffect:add( Vector2f( 736, 192 ), 64, Color( 0, 240, 255, 100 ), Color( 0, 240, 255, 80 ) )

-- Portal 05
ObjectLayer:addObject( ksAbstract( ksRect( 32, 256, 64, 64 ), 0 ) )
ForegroundEffect:add( Vector2f( 64, 288 ), 64, Color( 0, 240, 255, 100 ), Color( 0, 240, 255, 80 ) )

-- Portal 06
ObjectLayer:addObject( ksAbstract( ksRect( 192, 544, 64, 64 ), 0 ) )
ForegroundEffect:add( Vector2f( 224, 576 ), 64, Color( 0, 240, 255, 100 ), Color( 0, 240, 255, 80 ) )