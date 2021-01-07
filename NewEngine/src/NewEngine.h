#pragma once

//only for NewEngine applications

//-----------------Core System-------------------
#include "NewEngine/Core/Application.h"
#include "NewEngine/Core/Event.h"

#include "NewEngine/Events/ApplicationEvents.h"
#include "NewEngine/Events/MouseEvents.h"
#include "NewEngine/Events/KeyBoardEvents.h"
#include "NewEngine/Layer/Layer.h"

//---------------Logging System------------------
#include "NewEngine/Log/Log.h"

//----------------Render System------------------
#include "NewEngine/Renderer/Renderer.h"
#include "NewEngine/Renderer/RenderCommand.h"

#include "NewEngine/Renderer/VertexBuffer.h"
#include "NewEngine/Renderer/IndexBuffer.h"
#include "NewEngine/Renderer/VertexArray.h"
#include "NewEngine/Renderer/Texture.h"
#include "NewEngine/Renderer/Shader.h"

#include "NewEngine/Camera/PerspectiveCameraController.h"

#include "NewEngine/ImGui/ImGuiDriver.h"

#include "NewEngine/Objects/Object.h"
#include "NewEngine/Objects/Cube.h"
#include "NewEngine/Objects/Plane.h"
#include "NewEngine/Objects/Light.h"
#include "NewEngine/Objects/PointLight.h"

#include "NewEngine/Renderer/Scene.h"
//-----------------File System-------------------