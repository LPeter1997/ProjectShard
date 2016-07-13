#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include "src\Shard.h"
#include "src\Gfx\Window.h"
#include "src\Input\Input.h"
#include "src\Resources\ContentManager.h"
#include "src\Gfx\Shader\ShaderFactory.h"
#include "src\Maths\Matrix.h"
#include "src\Gfx\Buffers\VertexArray.h"
#include "src\Gfx\Buffers\IndexBuffer.h"
#include "src\Gfx\Renderers\SpriteBatch.h"
#include "src\Gfx\ColorUtils.h"
#include "src\Gfx\Layer2D.h"
#include "src\Components\Component.h"
#include "src\Logic\GameStateManager.h"
#include "src\Logic\GameState.h"
#include "src\GUI\GUILayer.h"
#include "src\Sfx\AudioListener.h"
#include "src\Sfx\SoundEffect.h"
#include "src\Sfx\SoundEffect3D.h"
#include "src\Physics\BroadPhase.h"
#include "src\Physics\NarrowPhase.h"
#include "src\Physics\CollisionResolver.h"
#include "src\Physics\Shape\Circle.h"

using namespace Shard;
using namespace Gfx;
using namespace Maths;
using namespace Input;
using namespace Resources;
//using namespace Components;
using namespace Logic;
using namespace GUI;
using namespace Sfx;
using namespace Physics;

#if 0
#define SUBSYS_USE

#ifdef SUBSYS_USE

class EntitySystem
{
public:
	virtual void Update(float delta) = 0;
	virtual void Render(Renderer2D& renderer) = 0;
};

template <typename T>
class EntitySubSystem : public EntitySystem
{
private:
	std::vector<T*> m_Components;

public:
	inline void AddComponent(T* c)
	{
		m_Components.push_back(c);
	}

	inline void Update(float delta) override
	{
		for (T* c : m_Components)
			c->Update(delta);
	}

	inline void Render(Renderer2D& renderer) override
	{
		for (T* c : m_Components)
			c->Render(renderer);
	}
};

class SubLayer
{
private:
	Renderer2D* m_Renderer;
	std::vector<EntitySystem*> m_Systems;
	const GLSLProgram& m_Shader;
	Maths::Matrix4f m_ProjectionMatrix;

public:
	SubLayer(Renderer2D* renderer, const GLSLProgram& shader, const Maths::Matrix4f& prMat)
		: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(prMat)
	{
		m_Shader.Enable();

		m_Shader.SetUniformMat4f("pr_matrix", m_ProjectionMatrix);

		static int texIDs[] =
		{
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
			10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
			20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
			30, 31
		};

		m_Shader.SetUniform1iv("textures", texIDs, 32);

		m_Shader.Disable();
	}

	virtual ~SubLayer()
	{
		delete m_Renderer;
	}

	void Render()
	{
		m_Shader.Enable();
		m_Renderer->Begin();

		for (EntitySystem *sys : m_Systems)
			sys->Render(*m_Renderer);

		m_Renderer->End();
		m_Renderer->Render();
		m_Shader.Disable();
	}

	void Update(float delta)
	{
		for (EntitySystem *sys : m_Systems)
			sys->Update(delta);
	}

	template <typename T>
	inline EntitySubSystem<T>* GetSystem()
	{
		for (EntitySystem* comp : m_Systems)
		{
			EntitySubSystem<T>* c2 = dynamic_cast<EntitySubSystem<T>*>(comp);
			if (c2)
				return c2;
		}

		return nullptr;
	}

	template <typename T>
	inline T* Add(T* comp)
	{
		EntitySubSystem<T>* sys = GetSystem<T>();
		if (!sys)
		{
			sys = new EntitySubSystem<T>();
			m_Systems.push_back(sys);
		}

		sys->AddComponent(comp);
		return comp;
	}
};

class SubActor;
struct SubComponent
{
	SubActor& m_Actor;

	SubComponent(SubActor& a)
		: m_Actor(a)
	{
	}

	virtual ~SubComponent() {}
};

class SubActor
{
private:
	std::vector<SubComponent*> m_Components;
	Transform m_Transform;

public:
	SubActor(const Maths::Vector3f& pos)
	{
		m_Transform.SetPosition(pos);
	}

	~SubActor()
	{
		for (SubComponent* c : m_Components)
			delete c;
	}

	inline Transform& GetTransform() { return m_Transform; }

	template <typename T>
	inline T* AddComponent()
	{
		T* c = new T(*this);
		m_Components.push_back(c);
		return c;
	}

	template <typename T>
	inline T* GetComponent()
	{
		for (SubComponent* comp : m_Components)
		{
			T* c2 = dynamic_cast<T*>(comp);
			if (c2)
				return c2;
		}

		return nullptr;
	}

	template <typename T>
	inline std::vector<T*> GetComponents()
	{
		std::vector<T*> comps;

		for (SubComponent* comp : m_Components)
		{
			T* c2 = dynamic_cast<T*>(comp);
			if (c2)
				comps.push_back(c2);
		}

		return comps;
	}
};

class DrawTextureComponent : public SubComponent
{
public:
	Transform& Position;
	Texture2D* Texture;

public:
	DrawTextureComponent(SubActor& a)
		: SubComponent(a), Position(a.GetTransform())
	{
	}

	inline void Update(float delta) {}

	inline void Render(Renderer2D& renderer)
	{
		renderer.GetTransformationStack().Push(Position.GetTransformationMatrix());
		renderer.DrawTexture(Vector3f(0, 0, 0), *Texture);
		renderer.GetTransformationStack().Pop();
	}
};

class ColliderComponent : public SubComponent
{
private:
	static std::vector<ColliderComponent*> s_Colliders;

public:
	Transform& Position;
	AABBf CollisionBox;

public:
	ColliderComponent(SubActor& a)
		: SubComponent(a), Position(a.GetTransform())
	{
		s_Colliders.push_back(this);
	}

	inline void Update(float delta)
	{
		const Vector3f& pos = Position.GetPosition();
		CollisionBox.x = pos.x;
		CollisionBox.y = pos.y;
	}

	inline void Render(Renderer2D& renderer) {}

	bool Collides() const
	{
		for (ColliderComponent* col : s_Colliders)
		{
			if (col == this)
				continue;

			if (col->CollisionBox.Intersects(CollisionBox))
				return true;
		}

		return false;
	}
};
std::vector<ColliderComponent*> ColliderComponent::s_Colliders;

class PlayerInputComponent : public SubComponent
{
public:
	Transform& Position;
	ColliderComponent& Collider;

public:
	PlayerInputComponent(SubActor& a)
		: SubComponent(a), Position(a.GetTransform()), Collider(*a.GetComponent<ColliderComponent>())
	{
	}

	void Update(float delta)
	{
		float dx = 0.0f;
		float dy = 0.0f;

		if (Keyboard::IsKeyDown(Keys::Up)) dy -= 200;
		if (Keyboard::IsKeyDown(Keys::Down)) dy += 200;
		if (Keyboard::IsKeyDown(Keys::Left)) dx -= 200;
		if (Keyboard::IsKeyDown(Keys::Right)) dx += 200;

		dx *= delta;
		dy *= delta;

		Move(dx, dy);
	}

	inline void Render(Renderer2D& renderer) {}

	void Move(float xp, float yp)
	{
		if (xp != 0 && yp != 0)
		{
			Move(xp, 0);
			Move(0, yp);
			return;
		}

		float px = Collider.CollisionBox.x;
		float py = Collider.CollisionBox.y;

		Collider.CollisionBox.x += xp;
		Collider.CollisionBox.y += yp;

		if (Collider.Collides())
		{
			Collider.CollisionBox.x = px;
			Collider.CollisionBox.y = py;
		}
		else
			Position.AddPosition(Vector3f(xp, yp, 0));
	}
};

SubActor* MakeActor(SubActor* ac = nullptr)
{
	if (ac == nullptr)
	{
		ac = new SubActor(Vector3f(0, 0, 0));
	}
	return ac;
}

SubActor* MakeTexturedActor(SubLayer* layer, Texture2D* tex, SubActor* ac = nullptr)
{
	ac = MakeActor(ac);
	DrawTextureComponent* dt = ac->AddComponent<DrawTextureComponent>();
	dt->Texture = tex;
	layer->Add<DrawTextureComponent>(dt);
	return ac;
}

SubActor* MakeColliderActor(SubLayer* layer, const AABBf& aabb, SubActor* ac = nullptr)
{
	ac = MakeActor(ac);
	ColliderComponent* dt = ac->AddComponent<ColliderComponent>();
	dt->CollisionBox = aabb;
	layer->Add<ColliderComponent>(dt);
	return ac;
}

SubActor* RepositionActor(SubActor* ac, const Vector3f& pos)
{
	ac->GetTransform().SetPosition(pos);
	return ac;
}

#else

class DrawTextureComponent : public Component
{
public:
	Transform& Position;
	Texture2D* Texture;

public:
	DrawTextureComponent(Actor& a)
		: Component(a), Position(a.GetTransform())
	{
	}

	void Render(Renderer2D& renderer) override
	{
		renderer.DrawTexture(Vector3f(0, 0, 0), *Texture);
	}
};

class ColliderComponent : public Component
{
private:
	static std::vector<ColliderComponent*> s_Colliders;

public:
	Transform& Position;
	AABBf CollisionBox;

public:
	ColliderComponent(Actor& a)
		: Component(a), Position(a.GetTransform())
	{
		s_Colliders.push_back(this);
	}

	void Update(float delta) override
	{
		const Vector3f& pos = Position.GetPosition();
		CollisionBox.x = pos.x;
		CollisionBox.y = pos.y;
	}

	bool Collides() const
	{
		for (ColliderComponent* col : s_Colliders)
		{
			if (col == this)
				continue;

			if (col->CollisionBox.Intersects(CollisionBox))
				return true;
		}

		return false;
	}
};
std::vector<ColliderComponent*> ColliderComponent::s_Colliders;

class PlayerInputComponent : public Component
{
public:
	Transform& Position;
	ColliderComponent& Collider;

public:
	PlayerInputComponent(Actor& a)
		: Component(a), Position(a.GetTransform()), Collider(*a.GetComponent<ColliderComponent>())
	{
	}

	void Update(float delta) override
	{
		float dx = 0.0f;
		float dy = 0.0f;

		if (Keyboard::IsKeyDown(Keys::Up)) dy -= 200;
		if (Keyboard::IsKeyDown(Keys::Down)) dy += 200;
		if (Keyboard::IsKeyDown(Keys::Left)) dx -= 200;
		if (Keyboard::IsKeyDown(Keys::Right)) dx += 200;

		dx *= delta;
		dy *= delta;

		Move(dx, dy);
	}

	void Move(float xp, float yp)
	{
		if (xp != 0 && yp != 0)
		{
			Move(xp, 0);
			Move(0, yp);
			return;
		}

		float px = Collider.CollisionBox.x;
		float py = Collider.CollisionBox.y;

		Collider.CollisionBox.x += xp;
		Collider.CollisionBox.y += yp;

		if (Collider.Collides())
		{
			Collider.CollisionBox.x = px;
			Collider.CollisionBox.y = py;
		}
		else
			Position.AddPosition(Vector3f(xp, yp, 0));
	}
};

Actor* MakeActor(Actor* ac = nullptr)
{
	if (ac == nullptr)
	{
		ac = new Actor(Vector3f(0, 0, 0));
	}
	return ac;
}

Actor* MakeTexturedActor(Texture2D* tex, Actor* ac = nullptr)
{
	ac = MakeActor(ac);
	DrawTextureComponent* dt = ac->AddComponent<DrawTextureComponent>();
	dt->Texture = tex;
	return ac;
}

Actor* MakeColliderActor(const AABBf& aabb, Actor* ac = nullptr)
{
	ac = MakeActor(ac);
	ColliderComponent* dt = ac->AddComponent<ColliderComponent>();
	dt->CollisionBox = aabb;
	return ac;
}

Actor* RepositionActor(Actor* ac, const Vector3f& pos)
{
	ac->GetTransform().SetPosition(pos);
	return ac;
}

#endif

class TestState : public GameState
{
private:
	ContentManager* content;
	SpriteBatch* batch;
#ifdef SUBSYS_USE
	SubLayer* layer;
#else
	Layer2D* layer;
#endif

public:
	TestState() {}

protected:
	void Initialize() override
	{
		content = new ContentManager("res");

		Text* file1 = content->Load<Text>("basic.vert");
		Text* file2 = content->Load<Text>("basic.frag");

		Texture2D* playertex = content->Load<Texture2D>("sprite1.png");
		Texture2D* grndtex = content->Load<Texture2D>("sprite2.png");

		GLSLProgram& shader = ShaderFactory::CreateShader(file1->GetText(), file2->GetText());
		Matrix4f ortho = Matrix4f::Orthographic(0.0f, 960.0f, 540.0f, 0.0f, -1.0f, 1.0f);

		batch = new SpriteBatch(50000);
#ifdef SUBSYS_USE
		layer = new SubLayer(batch, shader, ortho);

		SubActor* player = RepositionActor(MakeColliderActor(layer, AABBf(128, 128), MakeTexturedActor(layer, playertex)), Vector3f(100, 100, 0));
		PlayerInputComponent* pic = player->AddComponent<PlayerInputComponent>();
		layer->Add(pic);

		for (int i = 0; i < 4000; i++) {
		RepositionActor(MakeColliderActor(layer, AABBf(128, 128), MakeTexturedActor(layer, grndtex)), Vector3f(300, 300, 0));
		RepositionActor(MakeColliderActor(layer, AABBf(128, 128), MakeTexturedActor(layer, grndtex)), Vector3f(300 + 128, 300, 0));
		RepositionActor(MakeColliderActor(layer, AABBf(128, 128), MakeTexturedActor(layer, grndtex)), Vector3f(300 + 256, 300, 0));
		RepositionActor(MakeColliderActor(layer, AABBf(128, 128), MakeTexturedActor(layer, grndtex)), Vector3f(300 + 256, 300 - 128, 0));
		RepositionActor(MakeColliderActor(layer, AABBf(128, 128), MakeTexturedActor(layer, grndtex)), Vector3f(300 + 256, 300 - 256, 0));
		}
#else
		layer = new Layer2D(batch, shader, ortho);

		Actor* player = RepositionActor(MakeColliderActor(AABBf(128, 128), MakeTexturedActor(playertex)), Vector3f(100, 100, 0));
		player->AddComponent<PlayerInputComponent>();
		layer->Add(player);

		for (int i = 0; i < 4000; i++) {
			layer->Add(RepositionActor(MakeColliderActor(AABBf(128, 128), MakeTexturedActor(grndtex)), Vector3f(300, 300, 0)));
			layer->Add(RepositionActor(MakeColliderActor(AABBf(128, 128), MakeTexturedActor(grndtex)), Vector3f(300 + 128, 300, 0)));
			layer->Add(RepositionActor(MakeColliderActor(AABBf(128, 128), MakeTexturedActor(grndtex)), Vector3f(300 + 256, 300, 0)));
			layer->Add(RepositionActor(MakeColliderActor(AABBf(128, 128), MakeTexturedActor(grndtex)), Vector3f(300 + 256, 300 - 128, 0)));
			layer->Add(RepositionActor(MakeColliderActor(AABBf(128, 128), MakeTexturedActor(grndtex)), Vector3f(300 + 256, 300 - 256, 0)));
		}
#endif
	}

	inline void Tick() override
	{
		std::cout << "FPS: " << m_FPS << std::endl;
	}

	inline void Update(float delta) override
	{
		layer->Update(delta);
	}

	inline void Render() override
	{
		layer->Render();
	}

	void Deinitialize() override
	{
		content->UnloadAll();
		delete content;
	}
};

struct Foo
{
	int a;

	Foo()
	{
		a = 0;
	}

	virtual void doStuff() = 0;
};

struct Bar : public Foo
{
	Bar()
		: Foo()
	{
	}

	void doStuff() override
	{
		a++;
		if (a % 2)
			a *= 2;
		a -= 3;
	}
};

struct Bar2 : public Foo
{
	Bar2()
		: Foo()
	{
	}

	void doStuff() override
	{
		a--;
		if (a % 2 == 0)
			a /= 2;
		a += 3;
	}
};

int main(void)
{
	Core::Initialize();

	Window display("Shard Engine", 960, 540);

	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	GameStateManager::PushState(new TestState());
	GameStateManager::Start();

	display.Dispose();
	Core::Deinitialize();

	/*
	Timer t;
	t.Start();

	Bar b;
	Foo *f = &b;
	for (uint i = 0; i < 0xffffffff; i++)
		f->doStuff();

	std::cout <<"Elapsed: " << t.Reset() << std::endl;
	system("PAUSE");
	*/

	return 0;
}
#endif

RigidBody* CreateCircle(int x, int y)
{
	Material mat(0.1f, 0.7f, 0.8f, 0.6f);
	RigidBody* bdy = new RigidBody(Maths::Vector2f(x, y), new Circle(Maths::Vector2f(x, y), 32), mat);
	return bdy;
}

RigidBody* CreateBox(int x, int y, int w, int h)
{
	Material mat(0.1f, 0.7f, 0.2f, 0.1f);
	RigidBody* bdy = new RigidBody(Maths::Vector2f(x, y), new AABB(Maths::Vector2f(x, y), Maths::Vector2f(w, h)), mat);
	return bdy;
}

int main(void)
{
	Core::Initialize();

	Window display("Shard Engine", 960, 540);
	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	ContentManager content("res");

	Text* file1 = content.Load<Text>("basic.vert");  // Builtin shaders
	Text* file2 = content.Load<Text>("basic.frag");

	Texture2D* ball = content.Load<Texture2D>("circle.png");

	GLSLProgram& shader = ShaderFactory::CreateShader(file1->GetText(), file2->GetText());
	Matrix4f ortho = Matrix4f::Orthographic(0.0f, 960.0f, 540.0f, 0.0f, -1.0f, 1.0f);

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

	SpriteBatch batch(1000);

	std::vector<RigidBody*> bodies;
	
	//bodies.push_back(CreateBox(0, 0, 10, 540, true));
	//bodies.push_back(CreateBox(0, 0, 960, 10, true));
	//bodies.push_back(CreateBox(950, 0, 10, 540, true));
	//bodies.push_back(CreateBox(0, 530, 960, 10, true));

	//uint sz = bodies.size();
	//for (uint i = sz; i < sz + 6; i++) {
		//bodies.push_back(CreateBox(70 + i * 70, 70 + i * 70, 64, 64));
		//bodies[i]->Velocity = Vector2f(((0.01f + (i % 5) * 0.3f) * (i % 2 ? 1 : -1)) * 1000.0f, ((0.01f + (i % 5) * 0.3f) * (i >> 1 % 2 ? 1 : -1)) * 1000.0f);
	//}

	bodies.push_back(CreateBox(600, 140, 64, 64));
	bodies.push_back(CreateBox(300, 400, 500, 80));

	bodies[0]->Velocity.x = 0;
	bodies[0]->Velocity.y = 0;

	bodies[1]->BodyMaterial.Restitution = 0.0f;
	bodies[1]->BodyMaterial.StaticFriction = 0.4f;
	bodies[1]->BodyMaterial.DynamicFriction = 0.1f;
	bodies[1]->SetInfiniteMass();

	//bodies.push_back(CreateCircle(100, 100));
	//bodies.push_back(CreateCircle(400, 100));
	//bodies.push_back(CreateCircle(100, 100, 0.01f));
	//bodies.push_back(CreateCircle(400, 100, 0.1f));

	//bodies[0]->Velocity.x = 0.01f;
	NarrowCollision::Initialize();

	uint frames = 0;
	Timer t;
	t.Start();

	Timer deltat;
	deltat.Start();

	while (!display.IsCloseRequested())
	{
		// Gravity
		bodies[0]->Velocity += Maths::Vector2f(0, 0.0098f);

		// Collision
		std::vector<BroadCollision::ColliderPair> colliders = BroadCollision::GenerateColliderPairs(bodies);
		for (BroadCollision::ColliderPair cp : colliders)
		{
			NarrowCollision::Mainfold mf;
			mf.A = cp.A;
			mf.B = cp.B;
			
			if (NarrowCollision::Collide(&mf))
			{
				std::cout << "COLLISION " << mf.Penetration << " " << mf.Normal << std::endl;
				CollisionResolver::ResolveCollision(&mf);
				CollisionResolver::PositionalCorrection(&mf);
			}
		}

		// Integration
		float delta = deltat.Reset();
		for (RigidBody* b : bodies)
		{
			b->Position += Vector2f(delta * b->Velocity.x, delta * b->Velocity.y);
			if (b->BodyShape->Type == ShapeType::Circle)
				((Circle*)b->BodyShape)->Origin = b->Position;
			else
				((AABB*)b->BodyShape)->Position = b->Position;

			// Bounds
			if (b->Position.x < 0 && b->Velocity.x < 0)
				b->Velocity = Maths::Vector2f(-b->Velocity.x, b->Velocity.y);
			else if (b->Position.x >= 960 - 64 && b->Velocity.x > 0)
				b->Velocity = Maths::Vector2f(-b->Velocity.x, b->Velocity.y);

			if (b->Position.y < 0 && b->Velocity.y < 0)
				b->Velocity = Maths::Vector2f(b->Velocity.x, -b->Velocity.y);
			else if (b->Position.y >= 540 - 64 && b->Velocity.y > 0)
				b->Velocity = Maths::Vector2f(b->Velocity.x, -b->Velocity.y);
		}

		// Draw the bodies
		display.Clear();
		
		batch.Begin();
		for (RigidBody* b : bodies)
		{
			if (b->BodyShape->Type == ShapeType::Circle)
			{
				AABB sh = b->BodyShape->ComputeAABB();
				//batch.DrawRectangle(Vector3f(sh.Position.x, sh.Position.y, 0), sh.Size, 0xff0000ff);
				batch.DrawTexture(Vector3f(sh.Position.x, sh.Position.y, 0), *ball);
			}
			else
			{
				// Rect
				AABB sh = b->BodyShape->ComputeAABB();
				//batch.DrawRectangle(Vector3f(sh.Position.x, sh.Position.y, 0), sh.Size, 0xff0000ff);
				batch.DrawRectangle(Vector3f(sh.Position.x, sh.Position.y, 0), sh.Size, 0xff0000ff);
			}
		}
		batch.End();
		shader.Enable();
		batch.Render();
		shader.Disable();

		display.Update();
		frames++;

		if (t.GetElapsedTime() > 1)
		{
			//std::cout << "FPS: " << frames << std::endl;
			frames = 0;
			t.Reset();
		}
	}

	content.UnloadAll();

	display.Dispose();
	Core::Deinitialize();

	return 0;
}