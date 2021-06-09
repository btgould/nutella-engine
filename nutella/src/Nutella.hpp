// defines interface with client applications
#pragma once

// -------------------------------------------------------------------------
// ------------------------------- Core ------------------------------------
// -------------------------------------------------------------------------
#include "Nutella/Core/Application.hpp"
#include "Nutella/Core/Layer.hpp"
#include "Nutella/ImGui/ImGuiLayer.hpp"

#include "Nutella/Core/EntryPoint.hpp"

#include "Nutella/Core/Log.hpp"

// -------------------------------------------------------------------------
// ------------------------------- Input -----------------------------------
// -------------------------------------------------------------------------
#include "Nutella/Input/Input.hpp"
#include "Nutella/Input/KeyCodes.hpp"
#include "Nutella/Input/MouseButtonCodes.hpp"

// -------------------------------------------------------------------------
// ----------------------------- Renderer ----------------------------------
// -------------------------------------------------------------------------
#include "Nutella/Renderer/VertexArray.hpp"
#include "Nutella/Renderer/IndexBuffer.hpp"
#include "Nutella/Renderer/VertexBuffer.hpp"
#include "Nutella/Renderer/Shader.hpp"
#include "Nutella/Renderer/Texture.hpp"
#include "Nutella/Renderer/OrthographicCamera.hpp"
#include "Nutella/Renderer/Renderer.hpp"
#include "Nutella/Renderer/RendererCommand.hpp"

// -------------------------------------------------------------------------
// ------------------------------ Utility ----------------------------------
// -------------------------------------------------------------------------
#include "Nutella/Util/OrthoCamController.hpp"
