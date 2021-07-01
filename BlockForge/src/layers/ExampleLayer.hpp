#ifndef ExampleLayer_H_
#define ExampleLayer_H_


#include <vector>

#include "layers/IApplicationLayer.hpp"
#include "entities/Entity.hpp"




class ExampleLayer : public IApplicationLayer
{
public:

	ExampleLayer(class Application& app);



	~ExampleLayer();



	void onAttach(class Application& app) override;



	void onTick(const class Camera& cameraIn, float deltaTime) override;



	void onRender(const std::shared_ptr<class Camera>& cameraIn, class Renderer& rendererIn) override;



	class Application& getGame() { return m_game; }



private:

	class Application& m_game;

	std::vector<Entity> m_entities;
}; 


#endif



