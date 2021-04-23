#ifndef FlatColorMaterial_H_
#define FlatColorMaterial_H_

#include "renderer/materials/IMaterial.h"




class FlatColorMaterial : public IMaterial
{
public:

	FlatColorMaterial(const glm::vec4& colorIn);



	virtual void submitData(const std::weak_ptr<Shader>& shaderIn) override;



	glm::vec4 color;
}; 


#endif /* FlatColorMaterial_H_ */



