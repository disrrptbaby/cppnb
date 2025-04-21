# 🚀 cppnb – The C++ Notebook Experience

> Think Jupyter, but native. For C++.

`cppnb` is a blazing-fast, interactive, Jupyter-style notebook for **C++**, powered by **Dear ImGui** and a suite of lightweight tools. Designed for developers, learners, and researchers who want a clean, hackable, and offline-first way to prototype, visualize, and explore C++ code in notebook-style cells — *just like Python notebooks, but natively compiled*.

---

## ✨ Features

- 🧠 **Persistent Memory Between Cells** — define variables, structs, classes, and use them across cells.
- 💡 **Markdown Cells** — mix prose and code seamlessly.
- 🎨 **Syntax-Highlighted Editor** — clean, minimalist, and beautiful.
- 📈 **Integrated Plots** with **ImPlot** — visualize your data.
- 🧵 **Lightweight & Fast** — built using C++ with zero runtime bloat.
- 🖼️ **Single Executable GUI App** — no web server, no browser, just run and play.

> Developed as a passion project while exploring AI/ML workflows in C++.<br>
> cppnb makes C++ as expressive as a notebook without compromising performance.

---

## 📸 Preview

> Coming soon: GIFs, screenshots, and demo notebooks!

---

## 📦 Dependencies

- [Dear ImGui](https://github.com/ocornut/imgui) – GUI framework
- [ImGuiColorTextEdit](https://github.com/BalazsJako/ImGuiColorTextEdit) – Code editor with syntax highlighting
- [imgui_markdown](https://github.com/juliettef/imgui_markdown) – Markdown renderer
- [ImPlot](https://github.com/epezent/implot) – Data visualization
- [SDL2](https://www.libsdl.org/) – Input & rendering backend
- [GLAD](https://glad.dav1d.de/) – OpenGL loader

---

## ⚙️ Getting Started

### 🔧 Clone the repo

```bash
git clone https://github.com/Jeevan-04/cppnb.git
cd cppnb
```

### 📥 Install dependencies

```bash
brew install sdl2 cmake
```

Then setup third-party libraries:

```bash
mkdir third_party && cd third_party

# Core GUI and editor
git clone https://github.com/ocornut/imgui.git
git clone https://github.com/BalazsJako/ImGuiColorTextEdit.git
git clone https://github.com/juliettef/imgui_markdown.git
git clone https://github.com/epezent/implot.git

# GLAD setup (after downloading ZIP from glad.dav1d.de)
mkdir glad
unzip glad.zip -d glad
```

### 🛠️ Build the project

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

### 🚀 Run it

```bash
./cppnb
```

---

## 📂 Project Structure

```
cppnb/
├── src/
│   ├── core/         # Notebook logic, cell linking
│   ├── runtime/      # Compiler interface & metrics
│   ├── ui/           # Notebook UI, cells, themes
│   └── utils/        # Logging, markdown parser
├── notebooks/        # Save your notebook files (.cppnb)
├── third_party/      # External libraries
├── build/            # Build artifacts
├── main.cpp
└── README.md
```

---

## 🧪 Sample Workflow

Here’s what working with cppnb looks like:

- 💻 **Cell 1**: Define a class, function, or variable.
- ➕ **Cell 2**: Use that class, call the function — it works across cells!
- 📋 **Cell 3**: Add Markdown commentary or LaTeX-style math.
- 📉 **Cell 4**: Use ImPlot to graph vectors, arrays, or simulations.
- 🧹 **All Clean**: Logs, errors, and execution time per cell are neatly shown.

---

## 🚣️ Roadmap

| Feature                          | Status        |
|----------------------------------|---------------|
| Persistent Global Execution      | ✅ Done     |
| Markdown Cell with Live Render   | ✅ Done     |
| Code Execution with g++          | ✅ Done     |
| Basic Plotting via ImPlot        | ✅ Done     |
| Variable sharing across cells    | ✅ Done     |
| Auto cell add/delete/clear       | ♻️ WIP |
| Improved Error Handling          | ♻️ In Progress |
| Cell Execution Shortcut (⌘+Enter) | ♻️ Planned   |
| Notebook Save/Load               | ♻️ Planned   |
| Export as .cpp or .md            | 🧠 Idea     |
| GitHub Publishing Support        | 🧠 Idea     |

---

## 🤯 Why This Matters

Most C++ dev tools are either:

- ✅ powerful but too static and heavyweight (IDEs)
- ✅ fast but too barebones and old-school (terminals)

**cppnb** hits the sweet spot — fast, modern, and designed for tinkering. Think of it as:

> C++ meets visual prototyping + documentation in one tool.

---
