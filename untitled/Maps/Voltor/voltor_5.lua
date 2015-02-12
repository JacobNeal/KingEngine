ForegroundEffect:add( Vector2f( 816, 560 ), 64, Color( 255, 255, 0, 80 ), Color ( 255, 255, 0, 60 ) )
ObjectLayer:addObject( ksAbstract( ksRect( 800, 544, 32, 32 ), 6 ) )
ObjectLayer:animate( ObjectLayer:getCount() - 1, 6, 7, 15 )

Player:setPosition( MapView, Player:x( MapView ), Player:y( MapView ) + 64 )