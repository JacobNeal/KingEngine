slime = {}
slime[0] = "Praise Lord Cheesus!"
slime[1] = "Hail Sriracha Satan!"
slime[2] = "I'm with child."
slime[3] = "My name is Labeoufxx"
slime[4] = "Feed the crocs that feed the tigers that feed the pigs."
slime[5] = "Go with the stream"

AdventureLog:insert( "Working... -- The Slime.", Color( 255, 60, 60, 255 ) )

my_pos = random() % 6
something = slime[ my_pos ]

KingEngine:activateDialog( "Zoooom", Color( 255, 120, 120, 255 ), Vector2f( 896, 608 ) )
AdventureLog:insert( "-- Your best friend, The Slime.", Color( 255, 60, 60, 255 ) )