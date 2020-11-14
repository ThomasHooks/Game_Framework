#ifndef ExampleLayer_H_
#define ExampleLayer_H_


#include "layers/IGameLayer.hpp"




class ExampleLayer : public IGameLayer
{
public:

	ExampleLayer(class Game& game);



	~ExampleLayer();



	void onAttach(class Game& game) override;



	void onTick(const class GameCamera& cameraIn, class TileMap& worldIn, float deltaTime) override;



	void onRender(const class GameCamera& cameraIn, class Renderer& rendererIn) override;



	class Game& getGame() { return m_game; }



private:

	class Game& m_game;



	class IEntity* m_player = nullptr;
}; 


#endif



