Player:setPosition( MapView, 384, 448 )

Map:load( "Tiles/Voltor/voltor.png", "Maps/Voltor/Chris_Carpenter/chris_carpenter", 25, 20 )

ForegroundParticles:setColor( Color( 0, 0, 0, 0 ) )

ForegroundEffect:clear()
ForegroundEffect:set( 0, Color( 0, 0, 0, 0 ), Color( 0, 0, 0, 0 ), 0, 0 )

ObjectLayer:clear()
ObjectLayer:setFile( "Tiles/Voltor/Chris_Carpenter/chris_carpenter.png" )
ObjectLayer:addObject( ksAbstract( ksRect( 384, 128, 64, 64 ), 0 ) )
ObjectLayer:animate( 0, 0, 2, 30 )