# Player

The player controls a single spaceship advancing on the alien's home planet
(though this bit of detail might not be that important really). The player
starts out with 10 health and the meh machine gun, which shoots basic bullets in
whichever direction the player aims it. Anything hit by these bullets suffers 1
damage. If the player ever reaches 0 health, they die and one of their 3
respawns is used up. At this point, The screen is cleared of bullets and enemies
and the player is shoved back about 10 seconds from where they where in terms of
screen location.

This means that if they were fighting the boss, they will be starting the fight
with no powerups and with the boss back to full health (although the player will
also have full health and hopefully won't get themselves killed immediately).

## Powerups and Drops

Over the course of the game, a number of drops will spawn from enemies which
will help the player on their way to not dying. The player is able to hold onto
one NOPE! that they can use whenever they want to, but any other NOPE! picked up
will be used automatically. A complete list can be found below (along with their
relative percentage chance of dropping):

 + HP Up! - Gain 1 HP - __5%__
 + Full Health! - Gain max health - __0.5%__
 + Pew! - Your guns do 1 more damage - __0.1%__
 + Pew! Pew! - Your guns shoot faster - __0.1%__
 + NOPE! - Clear the screen of bullets (but not enemies) - __1%__

These powerups will disappear if they are not picked up within 5 seconds of
being dropped.
