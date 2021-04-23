#ifndef IGameLayer_H_
#define IGameLayer_H_

#include <memory>




class IGameLayer 
{
public:

	virtual ~IGameLayer() = default;



	IGameLayer(const IGameLayer& other) = delete;



	/// <summary>
	/// Used for post-initialization of this GameLayer
	/// <para>
	/// This method will be called just after this GameLayer's constructor is called
	/// </para>
	/// </summary>
	/// <param name="game">Reference to the Game object</param>
	virtual void onAttach(class Game& game) {}



	/// <summary>
	/// Used for pre-destruction of this GameLayer
	/// <para>
	/// This method will be called just be for this GameLayer's destructor is called
	/// </para>
	/// </summary>
	virtual void onDetach() {}



	/// <summary>
	/// This method is called each tick so that this GameLayer can update itself
	/// </summary>
	/// <param name="cameraIn"></param>
	/// <param name="worldIn"></param>
	/// <param name="deltaTime"></param>
	virtual void onTick(const class Camera& cameraIn, class TileMap& worldIn, float deltaTime) {}



	/// <summary>
	/// This method is called each frame so that this GameLayer can render itself
	/// </summary>
	/// <param name="cameraIn"></param>
	/// <param name="rendererIn"></param>
	virtual void onRender(const std::shared_ptr<class Camera>& cameraIn, class Renderer& rendererIn) {}



	/// <summary>
	/// Sets this GameLayer to be active
	/// <para>
	/// When a GameLayer is active it will be updated each tick and rendered every frame
	/// </para>
	/// </summary>
	void markActive() { m_isActive = true; }



	/// <summary>
	/// Sets this GameLayer to be inactive
	/// <para>
	/// When a GameLayer is inactive it will not be updated or rendered
	/// </para>
	/// </summary>
	void markInactive() { m_isActive = false; }



	/// <summary>
	/// Checks if this GameLayer is currently active
	/// </summary>
	/// <returns>True if active</returns>
	bool isActive() const { return m_isActive; }



protected:

	IGameLayer() = default;



	bool m_isActive = true;
}; 


#endif



