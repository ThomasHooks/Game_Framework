#include "FlatColorMaterial.h"




FlatColorMaterial::FlatColorMaterial(const glm::vec4& colorIn)
	: IMaterial("FlatColor"), color(colorIn)
{
}



void FlatColorMaterial::submitData(const std::weak_ptr<Shader>& shaderIn)
{
	shaderIn.lock()->setUniform("u_color", ShaderUniform::Type::Float4, color);
}



