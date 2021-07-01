#ifndef LAYERSTACK_HPP_
#define LAYERSTACK_HPP_


#include <memory>
#include <vector>

#include "layers/IApplicationLayer.hpp"




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
	void push(class Application& game, Args&&... args) 
	{
		m_layers.emplace_back(new LayerType((args)...));
		m_layers.back()->onAttach(game);
	}



	std::vector<IApplicationLayer*>::iterator begin() { return m_layers.begin(); }



	std::vector<IApplicationLayer*>::iterator end() { return m_layers.end(); }



private:

	std::vector<IApplicationLayer*> m_layers;
}; 


#endif /* LAYERSTACK_HPP_ */



