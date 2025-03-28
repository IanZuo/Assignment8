# Assignment_07 - Projectiles and Collision

**Objective:** Add projectiles to Player and Enemies and test for collision. You will be creating a Projectile class that the Player and Enemy class will hold. Then in your Applications Update(), you'll check for collision and set a boolean to determine if the enemies should continue to be rendered.

I have provided the header files for the classes that I used for this assignment. Your code should follow these classes and functions closely but it doesn't have to be exact. I have also provided a projectile asset that you can add to your assets folder.

It is broken into three parts. You should follow this guide as closely as possible, but some minor variation is acceptable.

I have provided some goal videos at the end of the instructions as guidance.

Also, please remember, when you make a change, compile your code, and see if you introduced any bugs or errors. Implementing tons of changes and then compiling can make it more difficult to debug. For example when you create your Projectile class, implement the Constructor then compile. Move on to the next function, compile, repeat.

GRADUATE STUDENTS ONLY HAVE ADDITIONAL REQUIREMENTS LOCATED AFTER PART 3. As always, undergraduates, feel free to complete this section as well, but you will not be graded on it.

**Part 1: Adding Projectiles to the Player**

The Projectile class is a Game Entity.

Projectile() should set the time since last launched and renderable to false. We don't want all the projectiles rendered at the start of the game.

Launch() should have some mechanism to check if enough time has passed before launching a projectile. This prevents the Player and Enemy from spamming their projectiles.

Update() should check if the object is firing. If it is, check whether it should be moving up or down accordingly (up for Player, down for Enemy). It should also check for the projectiles location to decide if it should still be "firing".

Render() should only render the projectile if it is renderable.

Your Player class should be creating, resizing, and moving the projectile upon creation.

Your Player's Input() needs some modification to launch the projectile when the "Space" button is pressed.

After completing this, your player should be able to launch a projectile. Completing this will make adding projectiles to the enemies much easier.

**Part 2: Testing Collision**

GameEntities should have a renderable member variable that will help us decide if we should render something or not. If an enemy is hit with a projectile, it should no longer be rendered (neither should its projectile which will come in the next part).

I have provided a TestCollision() function for you to use in your Game Entity. It takes a rectangle and checks if it overlaps with another rectangle.

You will test collision in your Application's Update(). Think about what the source rectangle is and what the comparing rectangle will be.

You will also need to update where you render enemies to check if the enemy is renderable or not. If it is, render it.

***Game Entity***

```
bool GameEntity::TestCollision(std::shared_ptr<GameEntity> enemy) {
    SDL_FRect enemyRect = enemy->mSprite.getRectangle();
    SDL_FRect thisRect = mSprite.getRectangle();
    
    return !(enemyRect.x + enemyRect.w <= thisRect.x ||  // r1 is completely to the left of r2
             thisRect.x + thisRect.w <= enemyRect.x ||  // r1 is completely to the right of r2
             enemyRect.y + enemyRect.h <= thisRect.y ||  // r1 is completely above r2
             thisRect.y + thisRect.h <= enemyRect.y);   // r1 is completely below r2
}
```

***Part 3: Adding Projectiles to Enemies***

Your enemies will also need to create a projectile in their constructor.

Your enemies Update() should update the projectile and, if the enemy is renderable, launch the projectile.

Unlike the Player class which can launch a projectile every 1 second, we won't want all of the enemies to fire at the same time. We need some randomness.

When you create the enemy's projectile you'll want to randomize the minLaunchTime using rand(). Test around with different values to find what works best.

***GRADUATE STUDENTS ONLY***

Requirements:
* 1. Add a way to keep track of score. You should gain 1 point when you hit an enemy, and this score should be printed to the console when the player wins or loses.
* 2. A player wins when they destroy all enemies. The result should be the game exiting, and the score being printed to the console.
* 3. A player loses when they are hit by an enemies projectile.
* 4. You may have noticed in the EnemyGoal video, the enemy's projectile will disappear if the enemy is destroyed while the projectile is in transit. Implement a way to have the projectile only de-render after it has left the screen.

**Requirements**

Copy over your files from the previous assignment into the Assignment directory of this assignment. 

**How to compile and run your program**

Your code may compile with different commands based on your architecture, but a sample compilation command may look like: g++ -std=c++20 ./src/*.cpp `pkg-config --cflags --libs sdl2` -o prog.

**Submission/Deliverables**

Submission

Commit all of your files to github, including any additional files you create.
Do not commit any binary files unless told to do so.
Do not commit any 'data' files generated when executing a binary.
Submit your GitHub link on Canvas.

Found a bug?

If you found a mistake (big or small, including spelling mistakes) in this assignment, kindly send me an e-mail. It is not seen as nitpicky, but appreciated! (Or rather, future generations of students will appreciate it!)

**Goal Videos** 

Your output doesn't have to be exactly as seen in the below video, but it should be pretty close.

***Player Projectile Goal***

In this video, you'll see that the projectile is renderered at the start under the player (we will want to fix this to only render if it's firing).
The player launches the missile vertically if the space button is pressed, but there is no collision yet.

![](../Media/PlayerGoal.mov)

***Collision Goal***

In this video, you'll see that the projectile intersecting with the enemy will cause the enemy to disappear (or no longer be renderable).

![](../Media/CollisionGoal.mov)

***Enemy Projectile***

In this video, you'll see that the enemies now launch projectiles toward the player in a randomized manner.

![](../Media/EnemyGoal.mov)
