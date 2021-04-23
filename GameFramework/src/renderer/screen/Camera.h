#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>

#include "utilities/physics/TilePos.h"
#include "utilities/math/Pos2.hpp"
#include "utilities/Loggers.hpp"




class Camera 
{
public:

	Camera(float width, float height);



	virtual ~Camera();



	/// <summary>
	/// Gets the current position of this camera
	/// </summary>
	/// <returns></returns>
	const glm::vec3& pos() const;



	/// <summary>
	/// Gets the current position of this camera
	/// </summary>
	/// <returns></returns>
	glm::vec3& pos();



	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	float width() const;



	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	float height() const;



	/// <summary>
	/// Gets the current view matrix of this camera
	/// </summary>
	/// <returns></returns>
	const glm::mat4& getView() const;



	/// <summary>
	/// Gets the current projection matrix of this camera
	/// </summary>
	/// <returns></returns>
	const glm::mat4& getProjection() const;



	/// <summary>
	/// Gets the current view-projection matrix of this camera
	/// </summary>
	/// <returns></returns>
	const glm::mat4& getViewProjection() const;



	/// <summary>
	/// 
	/// </summary>
	/// <param name="width"></param>
	/// <param name="height"></param>
	void SetViewportSize(float width, float height);



	/// <summary>
	/// Updates this camera's view matrix
	/// </summary>
	void update();



private:

	std::shared_ptr<spdlog::logger> m_logger;

	glm::mat4 m_projection;

	glm::mat4 m_view;

	glm::mat4 m_viewProjection;

	glm::vec3 m_position;

	float m_rotation = 0.0f;

	float m_width, m_height;
};


#endif /* CAMERA_H_ */



