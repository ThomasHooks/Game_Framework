#include <glm/gtc/matrix_transform.hpp>

#include "renderer/screen/Camera.h"




Camera::Camera(float width, float height)
	: m_projection(glm::ortho<float>(0.0f, width, height, 0.0f, -1.0f, 1.0f)), m_view(1.0f), m_viewProjection(1.0f), m_position(0.0f, 0.0f, 0.0f), m_width(width), m_height(height)
{
	m_logger = Loggers::getLog();
	update();
	m_logger->info("Camera has been built");
}



Camera::~Camera() 
{
	m_logger->info("Camera has been removed");
}



const glm::vec3& Camera::pos() const
{
	return m_position;
}



glm::vec3& Camera::pos()
{
	return m_position;
}



float Camera::width() const
{
	return m_width;
}



float Camera::height() const
{
	return m_height;
}



const glm::mat4& Camera::getView() const
{
	return m_view;
}



const glm::mat4& Camera::getProjection() const
{
	return m_projection;
}



const glm::mat4& Camera::getViewProjection() const
{
	return m_viewProjection;
}



void Camera::SetViewportSize(float width, float height)
{
	m_projection = glm::ortho<float>(0.0f, width, height, 0.0f, -1.0f, 1.0f);
	update();
	m_width = width;
	m_height = height;
}



void Camera::update()
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0, 0, 1));
	m_view = glm::inverse(transform);
	m_viewProjection = m_projection * m_view;
}



