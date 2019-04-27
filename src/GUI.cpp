#include <BlackBox/GUI.hpp>
#include <BlackBox/CGame.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#include <string>

#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd
#else
#include <unistd.h>
#endif

GUI::GUI()
{

}

GUI::GUI(CGame *game) : m_Game(game)
{
  m_MainMenu = new MainMenuBar;
}

void GUI::Draw()
{
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
        ShowMenuFile();
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Edit"))
    {
        if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
        if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
        ImGui::Separator();
        if (ImGui::MenuItem("Cut", "CTRL+X")) {
          ;
        }
        if (ImGui::MenuItem("Copy", "CTRL+C")) {}
        if (ImGui::MenuItem("Paste", "CTRL+V")) {}
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }

  ImGui::Begin("Control panel");
    ImGui::Checkbox("Show Plyer", &show_player);
    ImGui::Checkbox("Show Camera", &show_camera);
    ImGui::Checkbox("Show Demo", &show_demo);
  ImGui::End();
  if (show_player) {
    //ImGui::SetNextWindowPos(ImVec2(0.0, 0.0));
    ImGui::SetNextWindowSize(ImVec2(200, 400));
    ImGui::Begin("Music Player");
    if (ImGui::Button("Pause"))
    {
      m_Game->m_PlayList.pause();
    }
    if (ImGui::Button("Play"))
    {
      m_Game->m_PlayList.play();
    }
    if (ImGui::Button("Next"))
    {
      m_Game->m_PlayList.next();
    }
    if (ImGui::Button("Previos"))
    {
      m_Game->m_PlayList.play();
    }
    if (ImGui::Button("Stop"))
    {
      m_Game->m_PlayList.stop();
    }
    ImGui::End();
  }
  if (ImGui::TreeNode("Basic"))
  {
    static bool selection[5] = { false, true, false, false, false };
    ImGui::Selectable("1. I am selectable", &selection[0]);
    ImGui::Selectable("2. I am selectable", &selection[1]);
    ImGui::Text("3. I am not selectable");
    ImGui::Selectable("4. I am selectable", &selection[3]);
    if (ImGui::Selectable("5. I am double clickable", selection[4], ImGuiSelectableFlags_AllowDoubleClick))
        if (ImGui::IsMouseDoubleClicked(0))
            selection[4] = !selection[4];
    ImGui::TreePop();
  }
  if (show_camera) {
    ImGui::Begin("Camera");
      if (ImGui::Button("Reset"))
      {
        m_Game->m_active_camera->reset();
      }
    ImGui::End();
  }
  if (show_demo)
  {
    ImGui::ShowDemoWindow();
  }
  if (ImGui::Button("Exit"))
  {
    m_Game->m_running = false;
  }
  ImGui::Begin("Object Inspector");
  for (const auto &obj : m_Game->m_World->getObjects())
  {
    if (ImGui::TreeNode(obj.first.c_str()))
    {
      if (ImGui::TreeNode("Transform"))
      {
        ImGui::Text("x: %f", obj.second->m_transform.position.x);
        ImGui::Text("y: %f", obj.second->m_transform.position.y);
        ImGui::Text("z: %f", obj.second->m_transform.position.z);
        ImGui::TreePop();
      }
      ImGui::TreePop();
    }
  }
  ImGui::End();
}

void GUI::ShowMenuFile()
{
  static bool Import = false;
  ImGui::MenuItem("(dummy menu)", NULL, false, false);
  if (ImGui::MenuItem("New")) {}
  if (ImGui::MenuItem("Open", "Ctrl+O")) {Import = true;}
  if (ImGui::BeginMenu("Open Recent"))
  {
      ImGui::MenuItem("fish_hat.c");
      ImGui::MenuItem("fish_hat.inl");
      ImGui::MenuItem("fish_hat.h");
      if (ImGui::BeginMenu("More.."))
      {
          ImGui::MenuItem("Hello");
          ImGui::MenuItem("Sailor");
          if (ImGui::BeginMenu("Recurse.."))
          {
              ShowMenuFile();
              ImGui::EndMenu();
          }
          ImGui::EndMenu();
      }
      ImGui::EndMenu();
  }
  if (ImGui::MenuItem("Save", "Ctrl+S")) {}
  if (ImGui::MenuItem("Save As..")) {}
  ImGui::Separator();
  if (ImGui::BeginMenu("Options"))
  {
      static bool enabled = true;
      ImGui::MenuItem("Enabled", "", &enabled);
      ImGui::BeginChild("child", ImVec2(0, 60), true);
      for (int i = 0; i < 10; i++)
          ImGui::Text("Scrolling Text %d", i);
      ImGui::EndChild();
      static float f = 0.5f;
      static int n = 0;
      static bool b = true;
      ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
      ImGui::InputFloat("Input", &f, 0.1f);
      ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
      ImGui::Checkbox("Check", &b);
      ImGui::EndMenu();
  }
  if (ImGui::BeginMenu("Colors"))
  {
      float sz = ImGui::GetTextLineHeight();
      for (int i = 0; i < ImGuiCol_COUNT; i++)
      {
          const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
          ImVec2 p = ImGui::GetCursorScreenPos();
          ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x+sz, p.y+sz), ImGui::GetColorU32((ImGuiCol)i));
          ImGui::Dummy(ImVec2(sz, sz));
          ImGui::SameLine();
          ImGui::MenuItem(name);
      }
      ImGui::EndMenu();
  }
  if (ImGui::BeginMenu("Disabled", false)) // Disabled
  {
      IM_ASSERT(0);
  }
  if (ImGui::MenuItem("Checked", NULL, true)) {}
  if (ImGui::MenuItem("Quit", "Alt+F4")) {}
  if (Import)
  {
    ImGui::OpenPopup("Import");
    if (ImGui::BeginPopup("Import"))
    {
      std::vector<char> cwd;
      cwd.resize(260);
      std::string file;
      if (OpenFileDialog(getcwd(&cwd[0], cwd.size()), file))
      {

        ;//m_Game->m_World->add(file, )
      }
      ImGui::EndPopup();
    }
  }
}

bool GUI::OpenFileDialog(char *cwd, std::string &file)
{
  static bool pushedImport = false;
  static std::vector<bool> selection;
  DIR *Dir;
  dirent *entry;
  std::string tmp_file;

  if (nullptr != cwd){
    if (ImGui::Button("Import"))
    {
      pushedImport = true;
    }
    if (pushedImport)
    {
      Dir = opendir(cwd);
      ImGui::BeginChild("child", ImVec2(0, 60), true);
      for (int i = 0; (entry = readdir(Dir)) != nullptr; i++)
      {
        if (ImGui::Selectable(entry->d_name))
        {
          tmp_file = entry->d_name;
        }
      }
      ImGui::EndChild();
      if (ImGui::Button("Open"))
      {
        file = tmp_file;
        return true;
      }
    }
  }
  return false;
}

bool GUI::OnInputEvent(sf::Event &event)
{
  ImGui::SFML::ProcessEvent(event);
}

MainMenuBar::MainMenuBar()
{

}

bool MainMenuBar::Draw()
{
  for (const auto &item : m_Menus)
  {
    if(item->Draw())
      break;
  }
}



FileMenu::FileMenu(std::string name)
{
  m_Name = name;
}

bool FileMenu::Draw()
{

}


EditMenu::EditMenu(std::string name)
{
  m_Name = name;
}

bool EditMenu::Draw()
{

}


