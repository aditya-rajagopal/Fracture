#pragma once


#include "Fracture\Core\Core.h"

#include <string>
#include <glm\glm.hpp>

namespace Fracture {

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual uint32_t GetRendererID() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(uint32_t width, uint32_t height, glm::vec3 color);
		static Ref<Texture2D> Create(const std::string& path);
	};

}

