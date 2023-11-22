#pragma once

// This is only for external use

// --- Utils ----------------------
#include "Fracture\Utils\Log.h"
#include "Fracture\Utils\Instrumentation.h"
#include "Fracture\Utils\Timestep.h"

// For use by Fracture applications
#include "Fracture\Core\Application.h"
#include "Fracture\Core\Layer.h"
#include "imgui/imgui.h"

// --- Input ----------------------
#include "Fracture\Input\Input.h"
#include "Fracture\Input\KeyCodes.h"
#include "Fracture\Input\MouseButtonCodes.h"

// --- Events ----------------------	
#include "Fracture\Events\Event.h"
#include "Fracture\Events\ApplicationEvent.h"
#include "Fracture\Events\KeyEvent.h"
#include "Fracture\Events\MouseEvent.h"

// --- Renderer ----------------------]
#include "Fracture\Renderer\Renderer.h"
#include "Fracture\Renderer\RenderCommand.h"
#include "Fracture\Renderer\Shader.h"
#include "Fracture\Renderer\Buffer.h"
#include "Fracture\Renderer\VertexArray.h"
#include "Fracture\Renderer\OrthographicCamera.h"
#include "Fracture\Renderer\OrthographicCameraController.h"
#include "Fracture\Renderer\Texture.h"

// --- Components ----------------------
#include "Fracture\Components\Component.h"

