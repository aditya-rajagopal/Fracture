#pragma once


namespace Fracture {

	class FRACTURE_API GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};

}