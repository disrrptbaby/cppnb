#include "notebook.hpp"
#include "imgui.h"
#include "TextEditor.h"
#include "imgui_markdown.h"
#include "../utils/logger.hpp"
#include <SDL.h> // Include SDL2 header for clipboard functions
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <set>

enum CellType { CODE, MARKDOWN };

struct Cell {
    CellType type;
    std::string content;
    TextEditor editor;
    std::string output;
    float executionTime = 0.0f;
};

static std::vector<Cell> cells;
static std::string globalContextCode;
static bool darkMode = true;
static std::string selectedFont = "Default";

// Function to execute code from the cell
void executeCode(Cell& cell) {
    std::ofstream file("temp.cpp");

    // Basic includes
    file << "#include <iostream>\n";
    file << "#include <string>\n";
    file << "#include <vector>\n";
    file << "using namespace std;\n\n";

    // Write previously collected global context (including classes)
    file << globalContextCode << "\n";

    // Get current cell content
    std::string cellCode = cell.editor.GetText();
    std::istringstream codeStream(cellCode);
    std::string line;
    std::string currentCellGlobals;
    std::string mainCode;
    
    // State tracking for class extraction
    bool insideClass = false;
    std::string currentClass;
    int braceLevel = 0;

    while (std::getline(codeStream, line)) {
        std::string trimmed = line;
        trimmed.erase(0, trimmed.find_first_not_of(" \t"));
        trimmed.erase(trimmed.find_last_not_of(" \t") + 1);

        // Class detection
        if (!insideClass && trimmed.find("class ") == 0) {
            insideClass = true;
            braceLevel = 0;
            currentClass = line + "\n";
            continue;
        }

        if (insideClass) {
            currentClass += line + "\n";
            
            // Count braces
            for (char c : line) {
                if (c == '{') braceLevel++;
                else if (c == '}') braceLevel--;
            }

            // Class complete when we return to braceLevel 0 with semicolon
            if (braceLevel == 0 && trimmed.find("};") != std::string::npos) {
                currentCellGlobals += currentClass;
                globalContextCode += currentClass;  // Add to persistent global context
                insideClass = false;
                currentClass.clear();
                continue;
            }
        }

        if (!insideClass) {
            mainCode += line + "\n";
        }
    }

    // Handle any unterminated class
    if (insideClass) {
        if (braceLevel > 0) {
            currentClass += std::string(braceLevel, '}');
        }
        currentClass += ";\n";
        currentCellGlobals += currentClass;
        globalContextCode += currentClass;
    }

    // Write current cell's global declarations
    file << currentCellGlobals;

    // Write main code
    if (mainCode.find("int main(") == std::string::npos &&
        mainCode.find("void main(") == std::string::npos) {
        file << "int main() {\n" << mainCode << "    return 0;\n}\n";
    } else {
        file << mainCode;
    }

    file.close();

    // Compile and execute
    auto start = std::chrono::high_resolution_clock::now();
    int result = std::system("g++ temp.cpp -o temp 2> compile_errors.txt && ./temp > output.txt 2> runtime_errors.txt");
    auto end = std::chrono::high_resolution_clock::now();
    cell.executionTime = std::chrono::duration<float>(end - start).count();

    // Handle output
    if (result == 0) {
        std::ifstream outputFile("output.txt");
        if (outputFile.is_open()) {
            std::stringstream buffer;
            buffer << outputFile.rdbuf();
            cell.output = buffer.str();
            log("Execution successful. Output:\n" + cell.output);
        } else {
            cell.output = "❌ Error: Failed to read output file.";
            log("Error: Failed to read output file.");
        }
    } else {
        std::ifstream compileErrorFile("compile_errors.txt");
        std::ifstream runtimeErrorFile("runtime_errors.txt");
        std::stringstream errorBuffer;

        if (compileErrorFile.is_open()) {
            errorBuffer << "❌ Compilation Errors:\n";
            errorBuffer << compileErrorFile.rdbuf();
        }

        if (runtimeErrorFile.is_open()) {
            errorBuffer << "\n❌ Runtime Errors:\n";
            errorBuffer << runtimeErrorFile.rdbuf();
        }

        cell.output = errorBuffer.str().empty() ? 
            "❌ Unknown error occurred during compilation or execution." : 
            errorBuffer.str();

        log("Compilation/Execution failed. Errors:\n" + cell.output);
    }
}

// Function to handle clipboard functionality for ImGui with SDL2
void handleClipboard() {
    ImGuiIO& io = ImGui::GetIO();
    io.SetClipboardTextFn = [](void* user_data, const char* text) {
        SDL_SetClipboardText(text); // Use SDL2 function to set clipboard text
    };
    io.GetClipboardTextFn = [](void* user_data) -> const char* {
        return SDL_GetClipboardText(); // Use SDL2 function to get clipboard text
    };
    io.ClipboardUserData = nullptr;
}

void drawNotebook() {
    // Enable clipboard support for ImGui using SDL2
    ImGuiIO& io = ImGui::GetIO();
    io.SetClipboardTextFn = [](void* user_data, const char* text) {
        SDL_SetClipboardText(text); // Use SDL2 function to set clipboard text
    };
    io.GetClipboardTextFn = [](void* user_data) -> const char* {
        return SDL_GetClipboardText(); // Use SDL2 function to get clipboard text
    };
    io.ClipboardUserData = nullptr;

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 6.0f;
    style.FrameRounding = 4.0f;
    style.ItemSpacing = ImVec2(12, 10);
    style.FramePadding = ImVec2(8, 6);

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(12, 10));

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Preferences")) {
            if (ImGui::MenuItem("Light Mode", nullptr, !darkMode)) {
                darkMode = false;
                ImGui::StyleColorsLight();
            }
            if (ImGui::MenuItem("Dark Mode", nullptr, darkMode)) {
                darkMode = true;
                ImGui::StyleColorsDark();
            }
            if (ImGui::BeginMenu("Font")) {
                const char* fonts[] = {"Default", "Monospace", "Serif"};
                for (auto& font : fonts)
                    if (ImGui::MenuItem(font, nullptr, selectedFont == font))
                        selectedFont = font;
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize, ImGuiCond_Always);
    ImGui::SetNextWindowPos({0, 20}, ImGuiCond_Always);

    ImGui::Begin("Notebook", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

    ImGui::Separator();
    if (ImGui::Button("➕ Add Code Cell")) cells.push_back({CODE, "", TextEditor(), ""});
    ImGui::SameLine();
    if (ImGui::Button("📝 Add Markdown Cell")) cells.push_back({MARKDOWN, "", TextEditor(), ""});
    ImGui::Separator();

    for (size_t i = 0; i < cells.size(); ++i) {
        ImGui::PushID(static_cast<int>(i));

        if (cells[i].type == CODE) {
            ImGui::Text("🧠 Code Cell %zu", i + 1);
            ImGui::SameLine(ImGui::GetContentRegionAvail().x - 60);
            if (ImGui::Button(("▶ Run##" + std::to_string(i)).c_str(), {50, 0})) {
                executeCode(cells[i]);
            }

            ImGui::Separator();
            ImGui::BeginChild(("Editor" + std::to_string(i)).c_str(), ImVec2(0, 300), true);

            // Enable clipboard support in TextEditor
            cells[i].editor.SetHandleKeyboardInputs(true);
            cells[i].editor.SetHandleMouseInputs(true);
            cells[i].editor.Render(("##editor" + std::to_string(i)).c_str());

            ImGui::EndChild();

            if (!cells[i].output.empty()) {
                ImGui::Spacing();
                ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "📤 Output:");
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
                ImGui::BeginChild(("output" + std::to_string(i)).c_str(), ImVec2(0, 100), true);
                ImGui::TextWrapped("%s", cells[i].output.c_str());
                ImGui::EndChild();
                ImGui::PopStyleColor();
                ImGui::Text("⏱️ Time: %.2f ms", cells[i].executionTime * 1000);
            }
        } else if (cells[i].type == MARKDOWN) {
            ImGui::Text("📝 Markdown Cell %zu", i + 1);
            if (cells[i].content.capacity() == 0) cells[i].content.reserve(1024);
            ImGui::InputTextMultiline(("##md" + std::to_string(i)).c_str(), &cells[i].content[0], cells[i].content.capacity(), ImVec2(-1, 120));
            ImGui::Separator();
            ImGui::Markdown(cells[i].content.c_str(), cells[i].content.length(), {});
        }

        if (ImGui::InvisibleButton(("hoverzone" + std::to_string(i)).c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 10)) && ImGui::IsItemHovered()) {
            ImGui::OpenPopup(("AddCellPopup" + std::to_string(i)).c_str());
        }

        if (ImGui::BeginPopup(("AddCellPopup" + std::to_string(i)).c_str())) {
            if (ImGui::Selectable("➕ Add Code Below"))
                cells.insert(cells.begin() + i + 1, {CODE, "", TextEditor(), ""});
            if (ImGui::Selectable("📝 Add Markdown Below"))
                cells.insert(cells.begin() + i + 1, {MARKDOWN, "", TextEditor(), ""});
            ImGui::EndPopup();
        }

        ImGui::Separator();
        ImGui::PopID();
    }

    ImGui::End();
    ImGui::PopStyleVar(2);
}
