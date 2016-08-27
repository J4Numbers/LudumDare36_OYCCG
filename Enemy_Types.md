# Enemy Types

There are several different types of enemy in the game and all of them will have
different types of attacks that they can use (along with an associated
percentage chance of them actually using said attacks on the player). The file
system must therefore be designed around the needs of this data.

## Basic Brute

This is the simplest enemy and the easiest one to fight. If we assume that a
single bullet from the player does 1 damage, the basic brute has 3 health. It
will only ever fire basic bullets in a straight line in the direction of the
player (straight down the screen) and these bullets will do 1 damage to the
player.

## Tougher Trooper

The trooper has 5 health and will actively aim and shoot the player with
blistering bullets (which, once again, only do 1 damage, but are slightly faster
than their basic counterparts). Their bullets do not track the player past
firing, but will be shot in a trajectory that will hit them if they stay still.

## Superior Soldier

The hardest of the basic bunch, with 10 health and relentless rockets that deal
2 damage to the player and have a slight amount of tracking to them
post-shooting. The amount of tracking should only ever result in a deviation
margin of 15 degrees from the initial shot. This bullet is slightly slower than
the basic bullets.

## Welcoming Warship

The welcoming warship is effectively a miniboss with 100 health and will take up
position at the opposite end of the screen to the player and shoot towards them
using a mixture of all three previously seen attacks, plus one new one - this
being the lethal laser, which splits the screen in two and deals 5 damage on
hitting the player (due to its large charge time). The odds of any attack taking
place are as follows from standstill:

 + Basic bullet (volley of 5): __35%__
 + Blistering bullet (volley of 5): __35%__
 + Relentless rocket (volley of 2): __20%__
 + Lethal laser (single shot): __10%__

Repeat attacks are always less likely, with a __-10%__ penalty to it and a
__+3.3%__ increase on all other attacks - though that might not be necessary.

## Bullying Boss

The final boss has 500 health and will shoot the player with all available
attacks, having its own versions of the lethal laser that split the screen into
three parts. Minions will also be summoned during the fight to assist it. The
warship will not be summoned. The odds of any attack from standstill are:

 + Basic bullet (volley of 10): __45%__
 + Blistering bullet (volley of 5): __20%__
 + Relentless rocket (volley of 5): __20%__
 + Lethal laser (single shot): __15%__

Minions will be spawned throughout the fight during pause between volleys. Once
again, the odds of the same attack happening immediately again are decreased by
__10%__, with the other attacks gaining a share of those odds.
