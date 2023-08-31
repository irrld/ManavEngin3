
//
//    Copyright 2023 Metehan Gezer
//
//     Licensed under the Apache License, Version 2.0 (the "License");
//     you may not use this file except in compliance with the License.
//     You may obtain a copy of the License at
//
//         http://www.apache.org/licenses/LICENSE-2.0
//

#include "w_demo.hpp"
#include "input/w_input.hpp"
#include "layer/w_layerimgui.hpp"
#include "scene/w_componentutil.hpp"
#include "script/mono/w_monobehavior.hpp"
#include "systems/w_canvas_system.hpp"
#include "util/w_keycodes.hpp"
#include "util/w_math.hpp"
#include "w_engine.hpp"
#include "w_entrypoint.hpp"

#include <random>

using namespace Wiesel;

namespace WieselDemo {

DemoLayer::DemoLayer(DemoApplication& app) : m_App(app), Layer("Demo Layer") {
  m_Scene = app.GetScene();
  m_Renderer = Engine::GetRenderer();

  m_CameraMoveSpeed = 8.0f;
}

DemoLayer::~DemoLayer() = default;

uint32_t nLehmer = 0;

uint32_t Lehmer32() {
  nLehmer += 0xe120fc15;
  uint64_t tmp;
  tmp = (uint64_t)nLehmer * 0x4a39b70d;
  uint32_t m1 = (tmp >> 32) ^ tmp;
  tmp = (uint64_t)m1 * 0x12fad5c9;
  uint32_t m2 = (tmp >> 32) ^ tmp;
  return m2;
}

void DemoLayer::OnAttach() {
  LOG_DEBUG("OnAttach");

  /*int dd = 1;
		glm::ivec3 dims{128,128,128};
		std::vector<std::vector<std::vector<int>>> voxels;
		voxels.resize(dims.x);
		for (int x = 0; x < dims.x; x++) {
			voxels[x].resize(dims.z);
			for (int z = 0; z < dims.z; z++) {
				voxels[x][z].resize(dims.y);
			}
		}

		for (int x = 0; x < dims.x; x++) {
			for (int z = 0; z < dims.z; z++) {
				nLehmer = x << 16 | z;
				int maxY = 1 + Lehmer32() % dims.y / 8;
				for (int y = 0; y < dims.y; y++) {
					if (y < maxY) {
						voxels[x][z][y] = 1;
					} else {
						voxels[x][z][y] = 0;
					}
				}
				dd++;
			}
		}

		auto mesh = CreateReference<Mesh>();
		for (int x = 0; x < dims.x; x++) {
			for (int z = 0; z < dims.z; z++) {
				for (int y = 0; y < dims.y; y++) {
					int block = voxels[x][z][y];
					if (block != 1) {
						continue;
					}

					glm::vec3 vertexPos[8]{
							{-1, 1,  -1},
							{-1, 1,  1},
							{1,  1,  1},
							{1,  1,  -1},
							{-1, -1, -1},
							{-1, -1, 1},
							{1,  -1, 1},
							{1,  -1, -1},
					};

					int faces[6][9]{
							{0, 1, 2, 3, 0,  1,  0,  0, 0},     //top
							{7, 6, 5, 4, 0,  -1, 0,  1, 0},   //bottom
							{2, 1, 5, 6, 0,  0,  1,  1, 1},     //right
							{0, 3, 7, 4, 0,  0,  -1, 1, 1},   //left
							{3, 2, 6, 7, 1,  0,  0,  1, 1},    //front
							{1, 0, 4, 5, -1, 0,  0,  1, 1}    //back
					};

					for (int facenum = 0; facenum < 6; facenum++) {
						int nextX = x + faces[facenum][4];
						int nextY = y + faces[facenum][5];
						int nextZ = z + faces[facenum][6];
						if (nextX < dims.x && nextX >= 0
								&& nextY < dims.y && nextY >= 0
								&& nextZ < dims.z && nextZ >= 0) {
							if (voxels[nextX][nextZ][nextY] != 0) {
								continue;
							}
						}

						int v = mesh->Vertices.size();
						for (int i = 0; i < 4; i++) {
							Vertex vertex;
							vertex.Pos = {x, y, z};
							vertex.Pos /= 32.0f;
							vertex.Pos += vertexPos[faces[facenum][i]] / 64.0f;
							vertex.Color = {1.0f, 1.0f, 1.0f};
							mesh->Vertices.push_back(vertex);
						}

						glm::vec3 v1 = mesh->Vertices[v].Pos - mesh->Vertices[v + 3].Pos;
						glm::vec3 v2 = mesh->Vertices[v + 2].Pos - mesh->Vertices[v + 3].Pos;
						glm::vec3 v3 = glm::cross(v1, v2);
						glm::vec3 normal = glm::normalize(v3);
						for (int i = 0; i < 4; i++) {
							mesh->Vertices[v + i].Normal = normal;
						}

						mesh->Indices.push_back(v);
						mesh->Indices.push_back(v + 3);
						mesh->Indices.push_back(v + 2);
						mesh->Indices.push_back(v + 1);
						mesh->Indices.push_back(v);
						mesh->Indices.push_back(v + 2);

						// Add uvs
						//	glm::vec3 bottomLeft{faces[facenum, 7], faces[facenum, 8]};
						//	bottomLeft /= 2.0f;
						//	uv.AddRange(new List<Vector2>() { bottomleft + new Vector2(0, 0.5f), bottomleft + new Vector2(0.5f, 0.5f), bottomleft + new Vector2(0.5f, 0), bottomleft });
					}
				}
			}
		}
		mesh->Allocate();

		Entity entity = m_Scene->CreateEntity("Voxel Mesh");
		auto& model = entity.AddComponent<ModelComponent>();
		auto& transform = entity.GetComponent<TransformComponent>();
//		transform.Scale = {0.01f, 0.01f, 0.01f};
		model.Data.Meshes.push_back(mesh);*/
  // Loading a model to the scene
  {
    Entity entity = m_Scene->CreateEntity("Sponza");
    auto& transform = entity.GetComponent<TransformComponent>();
    transform.Scale = {0.01f, 0.01f, 0.01f};
    auto& model = entity.AddComponent<ModelComponent>();
    Engine::LoadModel(transform, model, "assets/models/sponza/sponza.gltf");
    auto& behaviors = entity.AddComponent<BehaviorsComponent>();
    behaviors.AddBehavior<MonoBehavior>(entity, "assets/scripts/TestBehavior.cs");
  }
  {
    Entity entity = m_Scene->CreateEntity("Canvas");
    auto& ui = entity.AddComponent<CanvasComponent>();
  }

  // Custom camera
  m_Renderer->SetClearColor(0.1f, 0.1f, 0.2f);
  m_Renderer->SetVsync(false);
}

void DemoLayer::OnDetach() {
  LOG_DEBUG("OnDetach");
}

void DemoLayer::OnUpdate(float_t deltaTime) {
  //LOG_INFO("OnUpdate {}", deltaTime);
  if (!m_Scene->GetPrimaryCamera()) {
    return;
  }
  Entity cameraEntity = m_Scene->GetPrimaryCameraEntity();
  CameraComponent& cameraComponent =
      cameraEntity.GetComponent<CameraComponent>();
  Camera& camera = cameraComponent.m_Camera;
  TransformComponent& transform =
      cameraEntity.GetComponent<TransformComponent>();
  float axisX = InputManager::GetAxis("Horizontal");
  float axisY = InputManager::GetAxis("Vertical");
  transform.Move(transform.GetForward() * deltaTime * m_CameraMoveSpeed *
                 axisY);
  transform.Move(transform.GetRight() * deltaTime * m_CameraMoveSpeed * axisX);

  float inputX = InputManager::GetAxis("Mouse X");
  float inputY = InputManager::GetAxis("Mouse Y");
  transform.SetRotation(inputY, inputX, 0.0f);
  camera.m_IsChanged = true;
}

void DemoLayer::OnEvent(Event& event) {
  EventDispatcher dispatcher(event);

  dispatcher.Dispatch<KeyPressedEvent>(WIESEL_BIND_FN(OnKeyPress));
  dispatcher.Dispatch<KeyReleasedEvent>(WIESEL_BIND_FN(OnKeyReleased));
  dispatcher.Dispatch<MouseMovedEvent>(WIESEL_BIND_FN(OnMouseMoved));
}

bool DemoLayer::OnKeyPress(KeyPressedEvent& event) {
  if (event.GetKeyCode() == KeyF1) {
    m_App.Close();
    return true;
  } else if (event.GetKeyCode() == KeyEscape) {
    if (m_App.GetWindow()->GetCursorMode() == CursorModeRelative) {
      m_App.GetWindow()->SetCursorMode(CursorModeNormal);
    } else {
      m_App.GetWindow()->SetCursorMode(CursorModeRelative);
    }
    return false;
  }
  return false;
}

bool DemoLayer::OnKeyReleased(KeyReleasedEvent& event) {
  return false;
}

bool DemoLayer::OnMouseMoved(MouseMovedEvent& event) {
  return false;
}

DemoOverlay::DemoOverlay(DemoApplication& app, Ref<DemoLayer> demoLayer)
    : m_App(app), m_DemoLayer(demoLayer), Layer("Demo Overlay") {}

DemoOverlay::~DemoOverlay() = default;

void DemoOverlay::OnAttach() {
  LOG_DEBUG("OnAttach");
}

void DemoOverlay::OnDetach() {
  LOG_DEBUG("OnDetach");
}

void DemoOverlay::OnUpdate(float_t deltaTime) {}

void DemoOverlay::OnEvent(Wiesel::Event& event) {}

static entt::entity selectedEntity;
static bool hasSelectedEntity = false;

void DemoOverlay::OnImGuiRender() {
  static bool scenePropertiesOpen = true;
  //ImGui::ShowDemoWindow(&scenePropertiesOpen);
  if (ImGui::Begin("Scene Properties", &scenePropertiesOpen)) {
    ImGui::SeparatorText("Controls");
    ImGui::InputFloat(PrefixLabel("Camera Speed").c_str(),
                      &m_DemoLayer->m_CameraMoveSpeed);
    if (ImGui::Checkbox(PrefixLabel("Wireframe Mode").c_str(),
                        Engine::GetRenderer()->IsWireframeEnabledPtr())) {
      Engine::GetRenderer()->SetRecreateGraphicsPipeline(true);
    }
    if (ImGui::Button("Recreate Pipeline")) {
      Engine::GetRenderer()->SetRecreateGraphicsPipeline(true);
    }
    if (ImGui::Button("Recreate Shaders")) {
      Engine::GetRenderer()->SetRecreateShaders(true);
    }
  }
  ImGui::End();

  static bool sceneOpen = true;
  if (ImGui::Begin("Scene Hierarchy", &sceneOpen)) {
    bool ignoreMenu = false;

    for (const auto& item :
         m_App.GetScene()->GetAllEntitiesWith<TagComponent>()) {
      Entity entity = {item, &*m_App.GetScene()};
      auto& tagComponent = entity.GetComponent<TagComponent>();
      if (ImGui::Selectable(tagComponent.Tag.c_str(),
                            hasSelectedEntity && selectedEntity == item,
                            ImGuiSelectableFlags_None, ImVec2(0, 0))) {
        selectedEntity = item;
        hasSelectedEntity = true;
      }
      if (ImGui::BeginPopupContextItem()) {
        selectedEntity = item;
        if (ImGui::Button("Remove Entity")) {
          m_App.GetScene()->DestroyEntity(entity);
          hasSelectedEntity = false;
        }
        ImGui::EndPopup();
        ignoreMenu = true;
      }
    }

    if (!ignoreMenu && ImGui::IsMouseClicked(1, false))
      ImGui::OpenPopup("right_click_hierarcy");
    if (ImGui::BeginPopup("right_click_hierarcy")) {
      if (ImGui::BeginMenu("Add")) {
        if (ImGui::MenuItem("Empty Object")) {
          m_App.GetScene()->CreateEntity();
          ImGui::CloseCurrentPopup();
        }
        ImGui::EndMenu();
      }
      ImGui::EndPopup();
    }
  }
  ImGui::End();

  static bool componentsOpen = true;
  if (ImGui::Begin("Components", &componentsOpen) && hasSelectedEntity) {
    Entity entity = {selectedEntity, &*m_App.GetScene()};
    TagComponent& tag = entity.GetComponent<TagComponent>();
    if (ImGui::InputText("##", &tag.Tag, ImGuiInputTextFlags_AutoSelectAll)) {
      bool hasSpace = false;
      for (int i = 0; i < tag.Tag.size(); i++) {
        const char& c = tag.Tag[i];
        if (c == ' ') {
          hasSpace = true;
        }
        break;
      }
      if (hasSpace) {
        TrimLeft(tag.Tag);
      }

      if (tag.Tag.empty()) {
        tag.Tag = "Entity";
      }
    }
    ImGui::SameLine();
    if (ImGui::Button("Add Component"))
      ImGui::OpenPopup("add_component_popup");
    if (ImGui::BeginPopup("add_component_popup")) {
      GENERATE_COMPONENT_ADDERS(entity);
      /*if (ImGui::BeginMenu("Sub-menu")) {
					ImGui::MenuItem("Click me");
					ImGui::EndMenu();
				}*/
      //	ImGui::Separator();

      ImGui::EndPopup();
    }

    GENERATE_COMPONENT_EDITORS(entity);
  }
  ImGui::End();
}

void DemoApplication::Init() {
  LOG_DEBUG("Init");
  Ref<DemoLayer> demoLayer = CreateReference<DemoLayer>(*this);
  PushLayer(demoLayer);
  PushOverlay(CreateReference<DemoOverlay>(*this, demoLayer));
}

DemoApplication::DemoApplication() : Application({"Wiesel Demo"}) {
  LOG_DEBUG("DemoApp constructor");
}

DemoApplication::~DemoApplication() {
  LOG_DEBUG("DemoApp destructor");
}
}  // namespace WieselDemo

// Called from entrypoint
Application* Wiesel::CreateApp() {
  return new WieselDemo::DemoApplication();
}
