#ifndef ExampleLayer_H_
#define ExampleLayer_H_


#include <vector>

#include "layers/IGameLayer.hpp"
#include "entities/Entity.hpp"




class ExampleLayer : public IGameLayer
{
public:

	ExampleLayer(class Game& game);



	~ExampleLayer();



	void onAttach(class Game& game) override;



	void onTick(const class Camera& cameraIn, class TileMap& worldIn, float deltaTime) override;



	void onRender(const std::shared_ptr<class Camera>& cameraIn, class Renderer& rendererIn) override;



	class Game& getGame() { return m_game; }



private:

	class Game& m_game;

	std::vector<Entity> m_entities;
}; 


#endif



