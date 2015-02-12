------------------------------------------------------------
-- Author:                 Jacob Neal
-- Date Created:           XX/XX/XX
-- Last Modification Date: XX/XX/XX
-- Project:                Regime of Darkness
-- Filename:               Maps/Hello.lua
--
-- Overview:
--    The purpose of this script is to ...
------------------------------------------------------------

Player:setPosition( MapView, 368, 288 )

Map:load( "Tiles/tilesheetsmall.png", "Maps/Hello", 25, 20 )

ObjectLayer:clear()
ObjectLayer:setFile( "Tiles/Voltor/voltor_obj.png" )

-- AudioTrack set to sorrow.ogg by default
AudioTrack:transition( "sorrow.ogg" )

-- Background Particles are the blood, transparent by default
BackgroundParticles:setColor( Color( 0, 0, 0, 0 ) )

-- Foreground Particles ( Weather / Rain ) set to transparent by default
ForegroundParticles:setColor( Color( 0, 0, 0, 0 ) )

-- Foreground Particles, Size: 6 is default size for rain drops
ForegroundParticles:setSize( 6 )

-- Foreground Particles, Number: 10 is the number of drops created per second
ForegroundParticles:setNumber( 10 )

-- Foreground Particles, Velocity: 20 is the default speed for drops to fall
ForegroundParticles:setVelocity( 20 )

-- Foreground Particles, Reach: 70 is the default for drops time to live before being deallocated
ForegroundParticles:setReach( 70 )

-- Foreground Effect, Sized to the size of the area
ForegroundEffect:clear()
ForegroundEffect:resize( 20, 25 )

-- Foreground Effect Number 0 ( Main background lighting ) set to transparent by default
ForegroundEffect:set( 0, Color( 0, 0, 0, 0 ), Color( 0, 0, 0, 0 ), 0, 0 )
------------------------------------------------------------
-- How to add Object animations
--
-- Add Object takes two parameters, one being the abstract object
-- which takes a x,y position and width and height, and then a tile number
-- from the object sheet.
--
-- ObjectLayer:addObject( ksAbstract( ksRect( 0, 0, 32, 32 ), 6 ) )
--
-- Animate takes four parameters,
-- 1) Number of object to be animated
-- 2) Starting frame of animation off object sheet
-- 3) Ending frame of animation off object sheet
-- 4) Speed of animation in frames ( 30 frames per second )
--
-- ObjectLayer:animate( 0, 6, 7, 15 )
------------------------------------------------------------

------------------------------------------------------------
-- How to add Foreground effects
--
-- Adding a foreground effect takes four parameters,
-- 1) The vector position of the center of the light
-- 2) The diameter of the light in pixels
-- 3) The first color of the light, with rgba values
-- 4) The second color of the light, with rgba values
--
-- ForegroundEffect:add( Vector2f( 0, 0 ), 64, Color( 255, 255, 0,  80 ), Color( 255, 255, 0, 60 ) )
------------------------------------------------------------

