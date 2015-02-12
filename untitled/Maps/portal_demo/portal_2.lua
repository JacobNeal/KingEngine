------------------------------------------
-- CST223 Term Project - Program 2
-- Filename: portal_2.lua
------------------------------------------

------------------------------------------
-- Set player position to red portal
------------------------------------------

player_y = Player:y( MapView )

------------------------------------------
-- If player enters blue portal going up
------------------------------------------
if ( player_y <= 256 ) and ( player_y + 64 > 224 ) then
  Player:setPosition( MapView, 544, 350 )
  
------------------------------------------
-- If player enter blue portal going down
------------------------------------------
elseif ( player_y + 64 >= 192 ) and ( player_y < 224 ) then
  Player:setPosition( MapView, 544, 480 )
end