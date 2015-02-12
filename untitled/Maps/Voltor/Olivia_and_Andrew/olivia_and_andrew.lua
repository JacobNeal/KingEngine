Player:setPosition( MapView, 384, 448 )

Map:load( "Tiles/Voltor/voltor.png", "Maps/Voltor/Olivia_and_Andrew/olivia_and_andrew", 25, 20 )

ForegroundParticles:setColor( Color( 0, 0, 0, 0 ) )

ForegroundEffect:clear()
ForegroundEffect:set( 0, Color( 0, 0, 0, 0 ), Color( 0, 0, 0, 0 ), 10, 10 )

ObjectLayer:clear()
ObjectLayer:setFile( "Tiles/Voltor/Olivia_and_Andrew/olivia_and_andrew.png" )
ObjectLayer:addObject( ksAbstract( ksRect( 384, 128, 64, 64 ), 0 ) )
ObjectLayer:animate( 0, 0, 2, 45 )

ObjectLayer:addObject( ksAbstract( ksRect( 384, 192, 64, 64 ), 3 ) )
ObjectLayer:animate( 1, 3, 5, 10 )