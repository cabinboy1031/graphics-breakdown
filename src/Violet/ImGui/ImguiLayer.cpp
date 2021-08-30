#include "Violet/ImGui/ImguiLayer.hpp"

#include "Violet/Application.hpp"

#include "imgui.h"
#include "Violet/Platform/OpenGL/ImguiOpenGLRenderer.hpp"

//TEMPORARY
#include "glad/glad.h"
#include "GLFW/glfw3.h"

using namespace Violet;

ImguiLayer::~ImguiLayer(){

}

void ImguiLayer::onAttach() {
    ImGui::SetCurrentContext(ImGui::CreateContext());
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
    io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
    io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
    io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
    io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
    io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
    io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
    io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
    io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
    io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
    io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

    Application& app = Application::get();
    ImGui_ImplOpenGL3_Init("#version 410");
    VGE_CORE_TRACE("ImGui initialized correctly!")
}

void ImguiLayer::onDetach() {
}

void ImguiLayer::onUpdate() {
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::get();
    io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());

    float time = (float) glfwGetTime();
    io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void ImguiLayer::onEvent(Event& event) {
    EventDispatcher dispatcher(event);
    dispatcher.dispatch<MouseButtonPressedEvent> (VGE_BIND_EVENT_FN(ImguiLayer::onMouseButtonPressedEvent ));
    dispatcher.dispatch<MouseButtonReleasedEvent>(VGE_BIND_EVENT_FN(ImguiLayer::onMouseButtonReleasedEvent));
    dispatcher.dispatch<MouseMovedEvent>         (VGE_BIND_EVENT_FN(ImguiLayer::onMouseMovedEvent         ));
    dispatcher.dispatch<MouseScrolledEvent>      (VGE_BIND_EVENT_FN(ImguiLayer::onMouseScrolledEvent      ));
    dispatcher.dispatch<KeyPressedEvent>         (VGE_BIND_EVENT_FN(ImguiLayer::onKeyPressedEvent         ));
    dispatcher.dispatch<KeyReleasedEvent>        (VGE_BIND_EVENT_FN(ImguiLayer::onKeyReleasedEvent        ));
    dispatcher.dispatch<WindowResizeEvent>       (VGE_BIND_EVENT_FN(ImguiLayer::onWindowResizedEvent      ));
    dispatcher.dispatch<KeyTypedEvent>           (VGE_BIND_EVENT_FN(ImguiLayer::onKeyTypedEvent           ));
}


bool ImguiLayer::onMouseButtonPressedEvent     (MouseButtonPressedEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[e.getMouseButton()] = true;

    return false;
}
bool ImguiLayer::onMouseButtonReleasedEvent    (MouseButtonReleasedEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[e.getMouseButton()] = false;

    return false;
}
bool ImguiLayer::onMouseMovedEvent             (MouseMovedEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(e.getX(), e.getY());

    return false;
}
bool ImguiLayer::onMouseScrolledEvent          (MouseScrolledEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheelH += e.getXOffset();
    io.MouseWheel += e.getYOffset();

    return false;
}
bool ImguiLayer::onKeyPressedEvent             (KeyPressedEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[e.getKeyCode()] = true;
    io.KeyCtrl =  io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
    io.KeyAlt =   io.KeysDown[GLFW_KEY_LEFT_ALT]     || io.KeysDown[GLFW_KEY_RIGHT_ALT];
    io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT]   || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
    io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER]   || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

    return false;
}
bool ImguiLayer::onKeyReleasedEvent            (KeyReleasedEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[e.getKeyCode()] = false;

    return false;
}
bool ImguiLayer::onWindowResizedEvent          (WindowResizeEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(e.getWidth(), e.getHeight());
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    glViewport(0, 0, e.getWidth(), e.getHeight());

    return false;
}

bool ImguiLayer::onKeyTypedEvent(KeyTypedEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    int keycode = e.getKeyCode();

    if(keycode > 0 && keycode < 0x10000){
        io.AddInputCharacter((unsigned short) keycode);
    }
    return false;
}
