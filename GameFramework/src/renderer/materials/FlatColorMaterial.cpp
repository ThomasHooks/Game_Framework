#include "FlatColorMaterial.h"




FlatColorMaterial::FlatColorMaterial(const glm::vec4& colorIn)
	: IMaterial("FlatColor"), color(colorIn)
{
}



void FlatColorMaterial::submitData(const std::weak_ptr<Shader>& shaderIn)
{
	//shaderIn.lock()->setUniformFloat4("u_color", color);
}



