-- Pink Slime!!!
-- Pink Slime!!!
-- Pink Slime!!! BURBBBB <3

Player:setPosition( MapView, Player:x( MapView ), Player:y( MapView ) + 16 )

NUM_OF_SAYINGS = 6

slime = {}
slime[0] = "Praise Lord Cheesus!"
slime[1] = "Hail Sriracha Satan!"
slime[2] = "I'm with child."
slime[3] = "My name is actually Labeoufxxxxxxxxxxxxxx"
slime[4] = "Pigs > Tigers > Crocodiles"
slime[5] = "Go with the stream"

AdventureLog:insert( "Working... -- The Slime.", Color( 255, 60, 60, 255 ) )

KingEngine:activateDialog( slime[ random() % NUM_OF_SAYINGS ], Color( 255, 120, 120, 255 ), Vector2f( 896, 608 ) )
AdventureLog:insert( "-- Your best friend, The Slime.", Color( 255, 60, 60, 255 ) )