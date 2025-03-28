# Assignment_08 - ECS (Part 2)

**Overall Objective for Assignment 8:** 

The overall objective for your final submission is to refactor your space invaders game to utilize components rather than having everything self-contained in your player and enemy game entities. This will involve refactoring our Sprite into both a Transform and Texture component, our Input (for our player) into an Input Component, and our Collision Logic into a Collision2D component.

I have included some starter code for this part of the assignment. It contains the Component Types, and the Component class. I have also provided you with some function implementations in the StarterCode src directory.

The starter code is just for reference, but your end result should be fairly similar to the provided starter code. That being said, some variation in your implementation is okay because you all have your own versions of your Space Invaders game.

After completing all parts, you will have the basics of a game engine that will allow you create different types of games, as well as add new functionality to existing games much more easily than with our original codebase.

**Objective for Part 2**

Create an Assignment Folder and copy your code from Assignment #7 into the Part2 Directory.

We will be creating an Input Component and moving input functionality from our Player into this component. We'll also be refactoring our code base a bit.

Also, for this assignment it is very important to compile frequently as there will be a lot of errors when refactoring the code. It may look scary at first, but you'll handle the errors one at a time. Also, when renaming things, it is very easy to miss something, so frequent compiling will allow you to make sure things are renamed correctly before moving on.

**Starter Code**

**Section 1: Create an Input Component**

* Having an input component is important because we'll be moving the input logic from our player to this component. Having different input components will allow you to slot in an input component for say, Xbox, PlayStation, Switch, Mobile, etc. You may also wonder why we would need to render if we're just handling input. You may want to display the controller to the user, for example, the joystick on a mobile device so the user knows where to move or tap.
* Create the header and source files for your input component.
* This class should look similar to the texture component minus Move() and all the setters and getters.
* Your input component will store mSpeed (currently in our Player.hpp).
* Include the header file to GameEntity.

**Section 2: Refactoring our Component Class**

* A big refactoring in Part 2 is to make our components know about the GameEntities that hold them. 
* Your component class should have a member variable that is a shared pointer to a game entity.
* Make sure your component includes the GameEntity headerfile.
* You will need to forward declare the GameEntity struct so the Component class knows about it.
* Add two functions to your Component that can set and get the GameEntity.

**Section 3: Refactoring our Game Entity**
* Move the addComponent and getComponent method implementations from the header file to the source file if you haven't already.
* In other programming languages you can use (self, or this). 'this' will return a raw pointer to the Object, but since we're working with a lot of shared pointers and a lot of our functions take shared pointers, we need a way to not use 'this', and get a shared pointer from an object.
* Because we will need our components to be able to access our game entities and their member variables, we will need our GameEntity class to inherit from "public std::enable_shared_from_this<GameEntity>". This is a utility that allows an instance of a class to create a std::shared_ptr<T> to itself. 
* Then, you can create a function in your GameEntity class that will return a shared pointer and call 'shared_from_this()'. This will return the Object as a shared pointer.
* Now that our components know about their assigned GameEntity, when we add a component in AddComponent(), we can call 
* 'c->SetGameEntity(GetThisPtr());' where the parameter is a shared pointer to our game entity.

**Section 4: Refactoring our Application Class**

* If your Application class is storing GameEntities as unique pointers, they should now store them as shared pointers. This will involve refactoring both the .hpp and .cpp files to make sure you're also creating shared pointers to these entities.

**Section 5: Input Component and Player**

* Move the logic for moving the player from the Player's Input method into the Input Component's input method. 
* Comment out the Projectile logic for now.
* When we had this logic in our Player, we had access to the input component. But now we have an input component with access to our game entity.
* auto ref = GetComponent<TextureComponent>(ComponentType::TextureComponent); This was our previous logic in the Player class, now you'll need to use the Component's member variable to the game entity to call GetComponent.

**Section 6: Add Explicit Template Instantiation**

* I have provided the code to add explicit template instantiation to your GameEntity.cpp. Just place it at the end of your file.
* The reason we need this is to avoid Linker Errors. The compiler does not generate code for templates until they are used with specific types. So, we'll make sure the compiler knows about the functions with the various component types.
* There are 4 instantiations for Add and Get that have been commented out for now since we don't have those components yet, but we'll uncomment them when we do add them.

**Section 7: Finale**

After successfully completing your refactoring, your game should compile with no errors. Because we aren't changing the functionality of our code, the game should run exactly the same as it did before. You should be able to move your player left and right but NOT fire at the moment.

**How to compile and run your program**

Your code may compile with different commands based on your architecture, but a sample compilation command may look like: g++ -std=c++20 ./src/*.cpp `pkg-config --cflags --libs sdl2` -o prog.

**Submission/Deliverables**

Submission

Commit all of your files to github, including any additional files you create.
Do not commit any binary files unless told to do so.
Do not commit any 'data' files generated when executing a binary.
