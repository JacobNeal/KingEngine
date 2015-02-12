-----------------------------------------------------------
-- Author:					Jacob Neal
-- Date Created:			2/22/14
-- Date Last Modified:		3/11/14
-- Filename:				luafile.lua
--
-- Purpose:
--		To create a test file for the lua binded functions
--		in KingEngine.
-----------------------------------------------------------

flower = {}
original_x = 0
original_y = 0
x = original_x
y = original_y

current = 0
num = 180
flower_per_line = 10

-- Generate the Flowers
for count = 0, num - 1 do
  --flower[ count ] = ksAbstract( ksRect( x, y, 32, 32 ), current )
  --ObjectLayer:addObject( flower[ count ] )
  --ObjectLayer:animate( count, current, current + 1, 30 )
  
  if ( count + 1 ) % flower_per_line == 0 then
    x = original_x
    y = y + 32
  else
    x = x + 32
  end
  
  if current == 0 then
    current = 2
  else
    current = 0
  end
end

--random_person = ksAbstract( ksRect( 96, 320, 64, 64 ), 11 )
--ObjectLayer:addObject( random_person )
--ObjectLayer:animate( num, 11, 30, 5 )

AdventureLog:insert( "This is a message from LUA!", Color( 255, 0, 0, 255 ) )