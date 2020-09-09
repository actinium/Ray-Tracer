#include "Material.hpp"

#include "Scene/Objects/Materials/SimpleMaterial.hpp"

namespace {
SimpleMaterial sm;
}

const Material& Material::Default = sm;
