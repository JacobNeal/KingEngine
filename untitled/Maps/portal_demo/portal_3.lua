------------------------------------------
-- CST223 Term Project - Program 2
-- Filename: portal_3.lua
------------------------------------------

------------------------------------------
-- Set player position to blue portal
------------------------------------------

player_y = Player:y( MapView )

------------------------------------------
-- If player enters red portal going up
------------------------------------------
if ( player_y <= 480 ) and ( player_y + 64 > 448 ) then
  Player:setPosition( MapView, 128, 126 )
  
------------------------------------------
-- If player enters red portal going down
------------------------------------------
elseif ( player_y + 64 >= 416 ) and ( player_y < 448 ) then
  Player:setPosition( MapView, 128, 258 )
end