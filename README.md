# ProjectShard
![Alt text](/projectshardlogo.png?raw=true "Project Shard Logo")

An open-source C++ game engine!
I've created this project for learning purposes at first but I hope it will become something much more in the future.
Facebook page: [link](https://www.facebook.com/theprojectshard)

Basics
------
In the main function you must set up the basic 2D environment and the engine:
```C++
Core::Initialize();

glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glDisable(GL_DEPTH_TEST);
```
After that you create a window and add a game state to the state machine:
```C++
Window display("Shard Engine", 960, 540);

GameStateManager::PushState(new TestState());
GameStateManager::Start();
```
Game states
-----------
A state is the part of a game. The options menu, the ingame part or the main menu for example. You inherit it from the GameState class. It has 5 methods to override.
```C++
Initialize()
```
It's called when the state begins. Here you should load resources and initialize objects.
```C++
Update(float delta)
```
It's called repeatedly when the state machine is running. The parameter delta is the time in seconds that passed since the last update. You should write game logic here.
```C++
Render()
```
It's also called repeatedly just after update and a clear screen. You should render things here.
```C++
Tick()
```
This is called once every second. You can use it for debugging or to calculate FPS for example.
```C++
Deinitialize()
```
This last function is called when the state is popped (ended). This is the place for destroying, deallocating and unloading resources.
Content management
------------------
You can load resources with the ContentManager. You first specify the root (can be empty):
```C++
ContentManager content("res/");
```
After that you can load resources. For example you can load text and an image like this:
```C++
Text* textfile = content.Load<Text>("readme.txt");                  // res/readme.txt
Texture2D* player = content.Load<Texture2D>("images/soldier.png");  // res/images/soldier.png
```
You can also reference to them with their resource IDs if you prefer that. The content manager keeps track of resources and unloads them if it gets destroyed or the UnloadAll() method is called.
Rendering
---------
If you don't use layers (not recommended yet) then some extra setup is needed before drawing:
```C++
Text* file1 = content->Load<Text>("basic.vert");  // Builtin shaders
Text* file2 = content->Load<Text>("basic.frag");

GLSLProgram& shader = ShaderFactory::CreateShader(file1->GetText(), file2->GetText());
Matrix4f ortho = Matrix4f::Orthographic(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);

shader.Enable();
shader.SetUniformMat4f("pr_matrix", ortho);
static int texIDs[] =
{
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
	20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
	30, 31
};
shader.SetUniform1iv("textures", texIDs, 32);
shader.Disable();
```
This is some setup code for the basic shader. With layers you won't need any of these.
There's only one renderer so far and that is the SpriteBatch. Example usage by drawing the player:
```C++
SpriteBatch batch(100);   // Create a batch that can hold 100 sprites

// ...

batch.Begin();
batch.DrawSprite(Vector3f(10, 10, 0), *player);
batch.End();
batch.Render();
```
Input
-----
Input is very simple. You have a Keyboard and a Mouse:
```C++
if (Keyboard::IsKeyDown(Keys::W))
{
  movePlayerUp();
}

if (Mouse::IsButtonPressed(Buttons::Left))
{
  shootAt(Mouse::GetPosition());
}
```
You can also use states like in XNA which is basically a momentary state of the keyboard as an object.
Sounds
------
You can create a sound effect (even 3D) from a loaded sound source. You can play, pause, loop the effect and you can also set the volume and pitch for it. If you want doppler-effect, use a 3D sound effect. Example usage:
```C++
if (Keyboard::IsKeyDown(Keys::Space))
{
  SoundEffect shoot(*shootSound);
  shoot.Play();
}
```
So far you can only load WAV files.
