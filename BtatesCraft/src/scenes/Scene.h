#pragma once



namespace Scene
{

	class Scene
	{
	public:
			Scene(){}
	virtual	~Scene() {}

	virtual void Update(double deltaTime) {}
	virtual void Render() {}
	virtual void GuiRender() {}

	};




};
