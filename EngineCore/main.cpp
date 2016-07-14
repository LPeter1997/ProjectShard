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
#include "src\Physics\NarrowPhase.h"
#include "src\Physics\Shape\Circle.h"
#include "src\Physics\Shape\Polygon.h"
#include "src\Physics\PhysicsScene.h"
#include "src\Gfx\Particles\ParticleEmitter.h"
#include "src\Gfx\SpriteSheet.h"

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

RigidBody* CreateBox(int x, int y, int w, int h, PhysicsScene& scene)
{
	Material mat(0.01f, 0.2f, 0.5f, 0.3f);
	Polygon* sh = new Polygon();
	sh->SetBox(w, h);
	RigidBody* body = scene.Add(Maths::Vector2f(x, y), sh, mat);
	return body;
}

RigidBody* CreateCircle(int x, int y, int r, PhysicsScene& scene)
{
	Material mat(0.01f, 0.2f, 0.5f, 0.3f);
	Circle* sh = new Circle(r);
	RigidBody* body = scene.Add(Maths::Vector2f(x, y), sh, mat);
	return body;
}

static Vector2f rot(const Vector2f& a, float angle)
{
	float s = std::sin(angle);
	float c = std::cos(angle);
	float xnew = a.x * c - a.y * s;
	float ynew = a.x * s + a.y * c;
	return Vector2f(xnew, ynew);
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

	Texture2D* tex = content.Load<Texture2D>("tatlas.png");
	Texture2D* tex2 = content.Load<Texture2D>("sprite1.png");

	SpriteSheet sheet(*tex, 2, 2);

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

	std::srand(std::time(NULL));

	SpriteBatch batch(10000);

	PhysicsScene scene(Maths::Vector2f(0, 500.0f));
	std::vector<RigidBody*> bodies;
	
	RigidBody* platform = CreateBox(500, 400, 600, 64, scene);
	platform->SetStatic();
	bodies.push_back(platform);

	//bodies.push_back(CreateCircle(400, 400 - 32, 32, scene));
	//bodies.push_back(CreateCircle(400 + 32, 400 - 32, 32, scene));
	//bodies.push_back(CreateCircle(400 + 64, 400 - 32, 32, scene));

	//RigidBody* abdd = CreateCircle(400 + 256, 400 - 32, 32, scene);
	//abdd->ApplyImpulse(Maths::Vector2f(-10000, 0), Maths::Vector2f(0, -32));
	//bodies.push_back(abdd);

	NarrowCollision::Initialize();

	uint frames = 0;
	Timer t;
	t.Start();

	Timer deltat;
	deltat.Start();

	float sz = 0.0f;
	float ori = 0.0f;

	float rots = 0;

	// Particles
	ParticleEmitter emitter(Maths::Vector2f(300, 300), 1000, 200, 1);

	while (!display.IsCloseRequested())
	{
		float delta = deltat.Reset();
		scene.Update(delta);
		//emitter.Update(delta);
		Maths::Vector2d __mp = Mouse::GetPosition();
		//emitter.SetPosition(Maths::Vector2f(__mp.x, __mp.y));

		if (Mouse::IsButtonDown(Buttons::Left) || Mouse::IsButtonDown(Buttons::Right))
		{
			if (sz == 0)
			{
				ori = (float)std::rand() / (float)RAND_MAX;
			}
			sz += delta * 50.0f;
		}

		if (Mouse::IsButtonReleased(Buttons::Left))
		{
			RigidBody* box = CreateBox(Mouse::GetX(), Mouse::GetY(), sz, sz, scene);
			box->SetOrientation(ori);
			bodies.push_back(box);
			sz = 0.0f;
		}
		else if (Mouse::IsButtonReleased(Buttons::Right))
		{
			RigidBody* box = CreateCircle(Mouse::GetX(), Mouse::GetY(), sz / 2, scene);
			box->SetOrientation((float)std::rand() / (float)RAND_MAX);
			bodies.push_back(box);
			sz = 0.0f;
		}
		
		InputDevices::Update();

		// Draw the bodies
		display.Clear();
		
		batch.Begin();
		for (RigidBody* b : bodies)
		{
			if (b->BodyShape->Type == ShapeType::Circle)
			{
				Circle* circle = (Circle*)b->BodyShape;
				const uint k_segments = 20;
				float theta = b->Orientation;
				float inc = Constants::Pi * 2.0f / (float)k_segments;
				Maths::Vector2f p0;
				for (uint i = 0; i < k_segments + 1; ++i)
				{
					theta += inc;
					Maths::Vector2f p(std::cos(theta), std::sin(theta));
					p *= Maths::Vector2f(circle->Radius, circle->Radius);
					p += b->Position;

					if (i > 0)
						batch.DrawLine(p, p0, 3, 0xff000000);

					p0 = p;
				}

				p0.x = circle->Radius;
				p0.y = 0;

				Maths::Vector2f end = rot(p0, b->Orientation);
				batch.DrawLine(end + b->Position, b->Position, 3, 0xff0000ff);
			}
			else
			{
				// Poly
				Polygon* poly = (Polygon*)b->BodyShape;
				// Draw line loop
				for (uint i = 0; i < poly->Vertices.size(); i++)
				{
					uint j = i + 1 < poly->Vertices.size() ? i + 1 : 0;

					Vector2f& av = rot(poly->Vertices.at(i), b->Orientation);
					Vector2f& bv = rot(poly->Vertices.at(j), b->Orientation);
					Vector2f del = Maths::Vector2f(b->Position.x, b->Position.y);
					batch.DrawLine(av + del, bv + del, 3, 0xff000000);
				}
				//batch.DrawRectangle(Vector3f(poly->Position.x, sh.Position.y, 0), sh.Size, 0xff0000ff);
			}
		}

		if (sz > 0)
		{
			Vector2d mp = Mouse::GetPosition();
			if (Mouse::IsButtonDown(Buttons::Right))
			{
				// Circle
				const uint k_segments = 20;
				float theta = 0.0f;
				float inc = Constants::Pi * 2.0f / (float)k_segments;
				Maths::Vector2f p0;
				for (uint i = 0; i < k_segments + 1; ++i)
				{
					theta += inc;
					Maths::Vector2f p(std::cos(theta), std::sin(theta));
					p *= Maths::Vector2f(sz / 2, sz / 2);
					p += Maths::Vector2f((float)mp.x, (float)mp.y);

					if (i > 0)
						batch.DrawLine(p, p0, 3, 0xff00ff00);

					p0 = p;
				}
			}
			else
			{
				Maths::Vector2f ampe((float)mp.x, (float)mp.y);
				
				Maths::Vector2f a(ampe - rot(Maths::Vector2f(sz / 2, sz / 2), ori));
				Maths::Vector2f b(ampe - rot(Maths::Vector2f(-sz / 2, sz / 2), ori));
				Maths::Vector2f c(ampe - rot(Maths::Vector2f(-sz / 2, -sz / 2), ori));
				Maths::Vector2f d(ampe - rot(Maths::Vector2f(sz / 2, -sz / 2), ori));

				batch.DrawLine(a, b, 3, 0xff00ff00);
				batch.DrawLine(b, c, 3, 0xff00ff00);
				batch.DrawLine(c, d, 3, 0xff00ff00);
				batch.DrawLine(d, a, 3, 0xff00ff00);
			}
		}

		//batch.DrawRectangle(Maths::Vector3f(100, 100, 0), Maths::Vector2f(100, 100), 0xffffffff);
		rots += delta;
		//for (uint i = 0; i < 4000;i++)
		batch.DrawTexture(Maths::Vector3f(100, 100, 0), Maths::Vector2f(32, 32), rots, sheet, sheet.GetSectionBounds(1, 1));

		batch.End();
		shader.Enable();
		batch.Render();
		//emitter.Render();
		shader.Disable();

		display.Update();
		frames++;

		if (t.GetElapsedTime() > 1)
		{
			std::cout << "FPS: " << frames << std::endl;
			frames = 0;
			t.Reset();
		}
	}

	content.UnloadAll();

	display.Dispose();
	Core::Deinitialize();

	return 0;
}