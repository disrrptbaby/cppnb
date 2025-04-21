#include "imgui.h"
#include "imgui_markdown.h"

void drawMarkdownCell(const char* markdownText) {
    ImGui::Begin("Markdown Cell");
    ImGui::MarkdownConfig mdConfig;
    mdConfig.linkCallback = nullptr;
    mdConfig.tooltipCallback = nullptr;
    mdConfig.imageCallback = nullptr;
    mdConfig.linkIcon = "";
    mdConfig.headingFormats[0] = ImGui::MarkdownHeadingFormat{ ImGui::GetFont(), true };
    mdConfig.headingFormats[1] = ImGui::MarkdownHeadingFormat{ ImGui::GetFont(), true };
    mdConfig.headingFormats[2] = ImGui::MarkdownHeadingFormat{ ImGui::GetFont(), false };
    mdConfig.userData = nullptr;
    ImGui::Markdown(markdownText, strlen(markdownText), mdConfig);
    ImGui::End();
}