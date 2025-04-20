# cppnb

🚧 **Work in Progress — Initial Scaffolding Stage**  
A native C++ Jupyter-style notebook built with **Dear ImGui**, **TextEditor**, **ImPlot**, and **Markdown** rendering.

Designed for:
- ✍️ Note-taking in Markdown
- ⚙️ Executable C++ code cells
- 📊 Visualizing data via ImPlot
- 🤖 Learning & building AI/ML projects with libraries like `Eigen`, `xtensor`, `Shogun`, etc.

---

## 🧠 Why cppnb?

As a student learning AI/ML using C++, I needed a lightweight, interactive notebook — similar to Jupyter — but native to C++. This tool is being developed to streamline that workflow and give me full control over execution, plotting, and layout.

---

## 📦 Planned Stack

- **UI**: Dear ImGui
- **Text Editing**: ImGuiColorTextEdit
- **Markdown**: imgui-markdown
- **Plotting**: ImPlot
- **Backend**: SDL2 or GLFW (configurable)
- **Build System**: CMake

---

## ⏳ Current Status

This repo is currently being scaffolded.  
Expect code pushes, architecture setup, and examples over the coming weeks.

Stay tuned!

---



### ✅ **Initial Setup**
- [x] Set up the basic project structure and CMake configuration
- [x] Configure dependencies (GLFW, ImGui, SDL2, etc.)
- [x] Implement basic UI elements (Font loading, window initialization)

### ✅ **Code Editor**
- [x] Implement code editor for writing and modifying C++ code
- [x] Enable basic code compilation and execution
- [x] Display output of the code execution (successful or errors)
- [x] Handle syntax errors (like missing semicolons) and show relevant messages

### ✅ **Dynamic Code Generation**
- [x] Generate dynamic C++ code from user input
- [x] Implement logic to modify and generate new code snippets during execution

### ✅ **Error Handling**
- [x] Display error messages (e.g., missing semicolons) in the console

### ✅ **Output Handling**
- [x] Display output from the C++ program (like `cout` statements)
- [x] Handle and display runtime errors in a user-friendly manner

### 🚧 **UI Enhancements**
- [ ] Improve the user interface with additional features (syntax highlighting, auto-complete)
- [ ] Add interactive elements for better user experience
- [ ] Provide a rich feedback system for errors (highlighting, suggestions)

