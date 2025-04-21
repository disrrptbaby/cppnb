# cppnb

🚧 **Work in Progress — Interactive C++ Notebook**  
A native C++ Jupyter-style notebook built with **Dear ImGui**, **TextEditor**, **ImPlot**, and **Markdown** rendering.

## 😍 Why cppnb?

As a student learning AI/ML using C++, I needed a lightweight, interactive notebook — similar to Jupyter — but native to C++. This tool is being developed to streamline that workflow and give me full control over execution, plotting, and layout.

---

## 📦 Features

- **Code Cells**: Write and execute C++ code directly in the notebook.
- **Markdown Cells**: Add rich text notes using Markdown.
- **Output Display**: View execution results and errors in real-time.
- **Plotting**: Visualize data using ImPlot.
- **Customizable UI**: Switch between light/dark modes and customize fonts.

---

## 🛠️ Dependencies

This project uses the following libraries and tools:

- **Dear ImGui**: For the user interface.
- **ImGuiColorTextEdit**: For the code editor.
- **imgui_markdown**: For rendering Markdown.
- **ImPlot**: For data visualization.
- **SDL2**: For window and input handling.
- **GLAD**: For OpenGL function loading.

---

## 🚀 Getting Started

### 1️⃣ Clone the Repository

```bash
git clone https://github.com/your-repo/cppnb.git
cd cppnb
```

### 2️⃣ Install Dependencies

#### Install SDL2

```bash
brew install sdl2
```

#### Set Up Third-Party Libraries

```bash
mkdir third_party
cd third_party

# Clone Dear ImGui
git clone https://github.com/ocornut/imgui.git

# Clone ImGuiColorTextEdit
git clone https://github.com/BalazsJako/ImGuiColorTextEdit.git

# Clone imgui_markdown
git clone https://github.com/juliettef/imgui_markdown.git

# Clone ImPlot
git clone https://github.com/epezent/implot.git
```

#### Set Up GLAD

1. Download GLAD from the [GLAD Generator](https://glad.dav1d.de/)
   - API: OpenGL
   - Profile: Core
   - Language: C/C++
2. Generate and extract the ZIP into `third_party/glad`:

```bash
mkdir glad
unzip glad.zip -d glad
```

### 3️⃣ Build the Project

#### Install CMake (if not already installed)

```bash
brew install cmake
```

#### Build the Project

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### 4️⃣ Run the Application

```bash
./cppnb
```

---

## 📂 Project Structure

```
cppnb/
├── CMakeLists.txt
├── main.cpp
├── README.md
├── src/
│   ├── core/
│   │   ├── cell.hpp
│   │   ├── notebook.hpp
│   │   └── config.hpp
│   ├── runtime/
│   │   ├── compiler.cpp
│   │   ├── executor.cpp
│   │   └── metrics.cpp
│   ├── ui/
│   │   ├── notebook.cpp
│   │   ├── code_cell.cpp
│   │   ├── markdown_cell.cpp
│   │   ├── editor.cpp
│   │   └── theme.cpp
│   └── utils/
│       ├── file_io.cpp
│       ├── markdown_parser.cpp
│       └── logger.cpp
├── third_party/
│   ├── imgui/
│   ├── TextEditor/
│   ├── imgui_markdown/
│   ├── ImPlot/
│   └── glad/
└── notebooks/
    └── getting_started.cppnb
```

---

## 🧪 Example Workflow

1. **Add a Code Cell**:
   - Write C++ code in the code editor.
   - Click the "Run" button to compile and execute the code.

2. **Add a Markdown Cell**:
   - Write notes using Markdown syntax.
   - Render the Markdown in real-time.

3. **View Output**:
   - See the output of your code execution below the code cell.
   - View errors and execution time.

---

## 🛠️ Planned Features

- **Syntax Highlighting**: Improve the code editor with syntax highlighting.
- **Auto-Complete**: Add intelligent code suggestions.
- **Rich Error Feedback**: Highlight errors in the code editor with suggestions.
- **Data Visualization**: Add advanced plotting capabilities using ImPlot.

---

## 🧑‍💻 Contributing

Contributions are welcome! Feel free to open issues or submit pull requests.

