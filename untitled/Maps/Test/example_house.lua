AdventureLog:insert( "From example_house.lua", Color( 255, 255, 255, 255 ) )

ObjectLayer:clear()

KingEngine:loadMap( "Tiles/tilesheetsmall.png", "Tiles/olivia_and_andrew.png",
                    Effect( Color( 0, 0, 0, 0 ), Color( 0, 0, 0, 0 ), 10, 10 ),
                    Particles( Color( 0, 0, 0, 0 ), Vector2f( 0, 0 ), 0, 0, 0, 0 ),
                    "Maps/example_house", 25, 20 )

Player:setPosition( MapView, 384, 448 )

ObjectLayer:addObject( ksAbstract( ksRect( 384, 128, 64, 64 ), 0 ) )
ObjectLayer:animate( 0, 0, 2, 30 )

ForegroundParticles:setColor( Color( 0, 0, 0, 0 ) )

ForegroundEffect:clear()
ForegroundEffect:resize( 25, 20 )
ForegroundEffect:set( 0, Color( 0, 0, 0, 0 ), Color( 0, 0, 0, 0 ), 10, 0 )