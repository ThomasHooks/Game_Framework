#ifndef IMaterial_H_
#define IMaterial_H_

#include <string>
#include <memory>

#include "renderer/shaders/Shader.h"




class IMaterial 
{
public:

	virtual ~IMaterial() = default;



	const std::string& getShaderName() const { return m_shaderName; }



	virtual void submitData(const std::weak_ptr<Shader>& shaderIn) = 0;



protected:

	IMaterial(const std::string& shaderNameIn) 
		: m_shaderName(shaderNameIn) 
	{
	}



	std::string m_shaderName;
}; 


#endif /* IMaterial_H_ */



