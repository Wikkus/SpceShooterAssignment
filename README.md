# SpceShooterAssignment

Assignment for: FutureGames Computer Technology course.



Naive implementation:

Creates enemies every other second using the factory pattern.

Projectiles are created in a similar way.

Currently, the collision is checked by going through all projectiles and checking their damage type. If they can damage the player, it checks if the projectile collides with the player. If the projectile can damage enemies, it loops through all the enemies and checks if it collides with any of them. 

Since the enemies and projectiles are created at runtime, that also drains on the CPU usage.

When set so enemies spawn every 0.01 seconds, according to the performance profiler, the EnemyWizard that shoots projectiles takes up 17.77% of CPU usage, where 16.14% of it goes to the projectile creation.

The CreateEnemy function takes up 5.17% of the CPU usage, since it's done in runtime.

The ProjectileManagers update function drains 3,76%. Might not be the bottleneck here, but considering that the only thing the update does is updating movement and checking collisions, it is way higher than it can be.

Trying it with 5000 enemies made it unplayable. The fps seemed to go down to 0.4 when the enemies were shooting projectiles.



There are two ideas I have for improving this:

The first idea I have in mind is to pool both the enemies and the projectiles. So they are all created in compiling time instead of during runtime. This would result in a longer load time, but the game would run at better performance.

The other idea I have is using a quadtree to handle the collision. This way, I don't have to compare players' projectiles with every enemy and vice versa every frame. It would only compare those in the same quadtree node.

I have some idea of how they work, but haven't used it in a project before.



Pooled enemies and projectiles:

I'm pooling 10000 enemy projectiles, 2000 player projectiles and 10000 enemies, so the startup time of the project is a couple of seconds.

During playtime, it is around 7 - 15 fps for me. Which is a massive improvement compared to the earlier 0.4.

However, this is true if the player doesn't shoot. Since the players projectile check collisions against every active enemy. In this case, 10000 * the amount of active player projectiles. 



Up next is trying to implement a quadtree that handles the collision. I don't have a very good understanding of quadtree, so this will be a challenge to implement.

It was similar to my understanding of the object pool, but quadtree seems to be a bit more tricky to implement than an object pool.



Successfully created a QuadTree template that I can use when checking the collision between the players' projectile and the enemies. Before the QuadTree, I checked the projectile collision against every enemy every frame. Which made the project run at unplayable fps. It was less than 0.1 against 2500 enemies at that point. Now it runs at between 5 and 25 fps while shooting projectiles.



Next up is adding a separation behavior for the enemies. Currently, they stack up in the same position after a while when chasing the player. This results in all enemies being in the same QuadTreeNode, which drops the fps drastically.



After that, I want to create a sorting algorithm for the projectiles and enemies. When I remove an enemy, I am looping through every enemy comparing their id to the enemies id the QuadTree returns. The same goes for projectiles. Either a sorting algorithm to make it easier to find the object by index in a vector or a better way to locate the specific object.