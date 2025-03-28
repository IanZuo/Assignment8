# Assignment_08 - ECS (Part 3)

**Overall Objective for Assignment 8:** 

The overall objective for your final submission is to refactor your space invaders game to utilize components rather than having everything self-contained in your player and enemy game entities. This will involve refactoring our Sprite into both a Transform and Texture component, our Input (for our player) into an Input Component, and our Collision Logic into a Collision2D component.

The starter code is just for reference, but your end result should be fairly similar to the provided starter code. That being said, some variation in your implementation is okay because you all have your own versions of your Space Invaders game.

After completing all parts, you will have the basics of a game engine that will allow you create different types of games, as well as add new functionality to existing games much more easily than with our original codebase.

**Objective for Part 3**

Create an Assignment Folder and copy your code from Assignment #8 into the Part3 Directory.

We will be creating a Transform Component. We'll also be refactoring our code base a bit.

Part3 is fairly straight forward, it just requires some careful refactoring. Basically, we're moving all movement capabilities from the Texture Component and putting it into the Transform Component. We'll be adding a default transform component to every game entity. Then we need to refactor our code so that anywhere we previously used our Texture Component to move, we now access the Transform Component.

Also, for this assignment it is very important to compile frequently as there will be a lot of errors when refactoring the code. It may look scary at first, but you'll handle the errors one at a time. Also, when renaming things, it is very easy to miss something, so frequent compiling will allow you to make sure things are renamed correctly before moving on.

**Starter Code**

I have provided a revamped Resource Manager to deal with segmentation faults. Feel free to use it in its entirety or use it a reference for refactoring your Resource Manager.

**Section 1: Create an Transform Component Class**

* We will be moving the ability to move from our Texture Component to our Transform Component class. This includes all the setters and getters, getRectangle, as well as the member variable mRectangle. (Your function and variable names may be different and that's okay.)
* Make sure to add setters and getters for X, Y, W, and H.
* We want our texture to be just a texture rendered on the GPU and the transform to control all movement.
* The Transform Component will inherit from the Component class and will need to implement GetType().
* We also want input, update, and render. Though we won't be implementing them, they're nice to have for debugging later.

**Section 2: Visiting the GameEntity Class**

* Each GameEntity will have a default transform component added to it. 
* Create a function that will create a shared pointer to a Transform Component and add it to the game entity. It could be called AddDefaultTransform().
* Uncomment the Explicit Template Instantiations for the transform component.
* We will want an explicit GetTransform() function that will return: return GetComponent<TransformComponent>(ComponentType::TransformComponent);
* This will make is easier to position our transform.
* Modify the collision code to get the TransformComponent instead of a TextureComponent. (We'll modify this again when we create our Collision2D Component in Part4.)

**Section 3: Quick Refactor of our Enemy Class and Player**
* Make sure you add a default transform component to the projectile you create in both Player and Enemy classes.
* Refactor any movement in the enemy class that previously used the TextureComponent to now utilize the TransformComponent. (This is a simple renaming.)

**Section 4: Refactoring our InputComponent and Projectile**

* Again, refactor any movement reference that previously used the TextureComponent to now utilize the TransformComponent. (This is a simple renaming.)

**Section 5: Refactoring the TextureComponent**

* We no longer have the rectangle associated with the TextureComponent, it is now associated with the TransformComponent.
* In our update function, we will now need to find a way to access the rectangle.
* Create a variable to access the GameEntity associated with the TextureComponent.
* Create a variable that uses the previous variable to call GetTransform() and then GetRectangle().
* Use this new variable as the rectangle that you pass into SDL_RenderDrawRectF() and SDL_RenderCopyF();

**Section 6: Refactoring our Application Class**

* For our enemy creation, after we create an enemy, we want to add the default transform.
* Then, when we want to position the enemy, we'll call GetTransform() on the enemy and then move the enemy to its position. The positioning logic is the same, but the way we access Move() or SetX()/SetY() now needs to be through the Transform Component which controls movement.

* Do the same thing for the Player. Make sure to create the default transform first, then move the player to its position.

**Section 7: Finale**

After successfully completing your refactoring, your game should compile with no errors. Because we aren't changing the functionality of our code, the game should run exactly the same as it did before. You should be able to move your player left and right but NOT fire at the moment.

**How to compile and run your program**

Your code may compile with different commands based on your architecture, but a sample compilation command may look like: g++ -std=c++20 ./src/*.cpp `pkg-config --cflags --libs sdl2` -o prog.
