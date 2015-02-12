-- Load the new map
Map:load( "Tiles/tilesheetsmall.png", "Maps/examplemap", 25, 20 )

-- Clear the Object Layer
ObjectLayer:clear()

-- Set the Foreground Effect
ForegroundEffect:set( Color( 255, 255, 0, 80 ), Color( 0, 0, 0, 0 ), 200, 0 )

-- Set the Foreground Particles
ForegroundParticles:setColor( Color( 255, 255, 0, 100 ) )
ForegroundParticles:setNumber( 1 )
Player:setPosition( 64, 64 )

-- Notify Player
AdventureLog:insert( "Area changed.", Color( 255, 255, 255, 255 ) )