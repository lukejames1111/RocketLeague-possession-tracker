#include "pch.h"
#include "rocketLeaguePossessionTracker.h"

/* Plugin Settings Window code here
std::string rocketLeaguePossessionTracker::GetPluginName() {
	return "rocketLeaguePossessionTracker";
}

void rocketLeaguePossessionTracker::SetImGuiContext(uintptr_t ctx) {
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

// Render the plugin settings here
// This will show up in bakkesmod when the plugin is loaded at
//  f2 -> plugins -> rocketLeaguePossessionTracker
void rocketLeaguePossessionTracker::RenderSettings() {
	ImGui::TextUnformatted("rocketLeaguePossessionTracker plugin settings");
}
*/

/*
// Do ImGui rendering here
void rocketLeaguePossessionTracker::Render()
{
	if (!ImGui::Begin(menuTitle_.c_str(), &isWindowOpen_, ImGuiWindowFlags_None))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	ImGui::End();

	if (!isWindowOpen_)
	{
		cvarManager->executeCommand("togglemenu " + GetMenuName());
	}
}

// Name of the menu that is used to toggle the window.
std::string rocketLeaguePossessionTracker::GetMenuName()
{
	return "rocketleaguepossessiontracker";
}

// Title to give the menu
std::string rocketLeaguePossessionTracker::GetMenuTitle()
{
	return menuTitle_;
}

// Don't call this yourself, BM will call this function with a pointer to the current ImGui context
void rocketLeaguePossessionTracker::SetImGuiContext(uintptr_t ctx)
{
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

// Should events such as mouse clicks/key inputs be blocked so they won't reach the game
bool rocketLeaguePossessionTracker::ShouldBlockInput()
{
	return ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard;
}

// Return true if window should be interactive
bool rocketLeaguePossessionTracker::IsActiveOverlay()
{
	return true;
}

// Called when window is opened
void rocketLeaguePossessionTracker::OnOpen()
{
	isWindowOpen_ = true;
}

// Called when window is closed
void rocketLeaguePossessionTracker::OnClose()
{
	isWindowOpen_ = false;
}
*/