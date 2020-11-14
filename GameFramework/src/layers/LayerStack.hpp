#ifndef LayerStack_H_
#define LayerStack_H_


#include <memory>
#include <vector>

#include "layers/IGameLayer.hpp"




class LayerStack 
{
public:

	LayerStack() = default;



	~LayerStack()
	{
		for (auto& itr : m_layers)
		{
			itr->onDetach();
			delete itr;
		}
	}



	LayerStack(const LayerStack& other) = delete;



	LayerStack(const LayerStack&& other) = delete;



	template<class LayerType, typename... Args>
	void push(class Game& game, Args&&... args) 
	{
		m_layers.emplace_back(new LayerType((args)...));
		m_layers.back()->onAttach(game);
	}



	std::vector<IGameLayer*>::iterator begin() { return m_layers.begin(); }



	std::vector<IGameLayer*>::iterator end() { return m_layers.end(); }



private:

	std::vector<IGameLayer*> m_layers;
}; 


#endif



