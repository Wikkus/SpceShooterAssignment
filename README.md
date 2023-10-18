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

There are two ideas I have for improving this:
The firest idea I have in mind is to pool both the enemies and the projectiles. So they are all created in compiling time instead of during runtime. This would result in a longer load time but the game would run at better performance.
The other idea I have is using a quadtree to handle the collision. This way I don't have to compare players projectile with every enemy and vice versa every frame. It would only compare those in the same quadtree node.
I have some idea of how they work, but haven't used it in a project before. So these will be the challenges of the week.

Check the folder performanceProfilerStatuses to see images from the different states of the project.