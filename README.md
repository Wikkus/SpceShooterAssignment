# SpceShooterAssignment
Assignment for FutureGames course Computer Technology.

Naive implementation:
Creates enemies every other second using the factory pattern.
Projectiles are created in a similar way.
Currently the collision is checked by going through all projectiles and check their damagetype. If they can damage the player, it checks if the projectile collides with the player. If the projectile can damage enemies, it loops through all the enemies and checks if it collides with any of them. 
Since the enemies and projectiles are created in runtime, that also drains on the CPU usage.
When set so enemies spawn ever 0.01 seconds, according to the performance profiler the EnemyWizard that shoots projectiles takes up 17.77% of CPU usage where 16.14% of it goes to the projectile creation.
The CreateEnemy function takes up 5.17% of the CPU usage, since it's done in runtime.
ProjectileManagers update function drains 3,76%. Might not be the bottleneck here, but considering that the only thing the update does is updating movement and checking collision it is way higher than it can be.
Trying it with 5000 enemies made it unplayable. The fps seamed to go down to 0.4 when the enemies were shooting projectiles.

There are two ideas I have for improving this:
The firest idea I have in mind is to pool both the enemies and the projectiles. So they are all created in compiling time instead of during runtime. This would result in a longer load time but the game would run at better performance.
The other idea I have is using a quadtree to handle the collision. This way I don't have to compare players projectile with every enemy and vice versa every frame. It would only compare those in the same quadtree node.
I have some idea of how they work, but haven't used it in a project before.

Check the folder performanceProfilerStatuses to see images from the different states of the project.


Pooled enemies and projectiles:
I'm pooling 10000 enemy projectiles, 2000 player projectiles and 10000 enemies, so the startup time of the project is a couple of seconds.
During the playtime, it is around 7 - 15 fps for me. Which is a massive improvement compared to the earlier 0.4.
However, this is true if the player doesn't shoot. Since the player projectiles checks collision against every active enemy. In this case 10000*amount of active player projectiles. 

Up next is trying to implement a quadtree that handles the collision. I don't have very good understanding of quadtree, so this will be a challenge to implement.
It was similar for the object pool, however quadtree seams to be a bit more tricky to implement than an object pool.

Another thing I want to do better later on is the way I handle types of enemies and projectiles, currently I have a separate vector for enemy and player projectiles. However I want to have them all in the same container and be able to fast and easy pick out an element based on the wanted type. Currently I don't have a support for enemy types, it's all in a vector and every other enemy is a different type.
However, quadtree first.