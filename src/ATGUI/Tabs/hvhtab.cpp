#include "hvhtab.h"

void HvH::RenderTab()
{
	const char* yTypes[] = {
			"SLOW SPIN", "FAST SPIN", "JITTER", "BACKJITTER", "SIDE", "BACKWARDS", "FORWARDS", "LEFT", "RIGHT", "STATIC", "STATIC JITTER", "STATIC SMALL JITTER", "CASUALAA",// safe
			"LISP", "LISP SIDE", "LISP JITTER", "ANGEL BACKWARDS", "ANGEL INVERSE", "ANGEL SPIN", "LOWERBODY", "LBYONGROUND", // untrusted
	};

	const char* xTypes[] = {
			"UP", "DOWN", "DANCE", "FRONT", // safe
			"LISP DOWN", "ANGEL DOWN", "ANGEL UP", // untrusted
	};

	ImGui::Columns(2, NULL, true);
	{
		ImGui::BeginChild(XORSTR("HVH1"), ImVec2(0, 0), true);
		{
			ImGui::Text(XORSTR("AntiAim"));
			ImGui::BeginChild(XORSTR("##ANTIAIM"), ImVec2(0, 0), true);
			{
				ImGui::Checkbox(XORSTR("Yaw"), &Settings::AntiAim::Yaw::enabled);
				ImGui::Separator();
				ImGui::Columns(2, NULL, true);
				{
					ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
					ImGui::Text(XORSTR("Yaw Actual"));
					ImGui::Checkbox(XORSTR("Anti Resolver"), &Settings::AntiAim::Yaw::antiResolver);
				}
				ImGui::NextColumn();
				{
					ImGui::PushItemWidth(-1);

					if (ImGui::Combo(XORSTR("##YACTUALTYPE"), (int*)& Settings::AntiAim::Yaw::type, yTypes, IM_ARRAYSIZE(yTypes)))
					{
						if (!ValveDSCheck::forceUT && ((*csGameRules) && (*csGameRules)->IsValveDS()) && Settings::AntiAim::Yaw::type >= AntiAimType_Y::LISP)
						{
							Settings::AntiAim::Yaw::type = AntiAimType_Y::SPIN_SLOW;
							ImGui::OpenPopup(XORSTR("Error###UNTRUSTED_AA"));
						}
					}
					ImGui::PopItemWidth();
				}
				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::Checkbox(XORSTR("Pitch"), &Settings::AntiAim::Pitch::enabled);
				ImGui::Separator();
				ImGui::Columns(2, NULL, true);
				{
					ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
					ImGui::Text(XORSTR("Pitch Actual"));
				}
				ImGui::NextColumn();
				{
					ImGui::PushItemWidth(-1);
					if (ImGui::Combo(XORSTR("##XTYPE"), (int*)& Settings::AntiAim::Pitch::type, xTypes, IM_ARRAYSIZE(xTypes)))
					{
						if (!ValveDSCheck::forceUT && ((*csGameRules) && (*csGameRules)->IsValveDS()) && Settings::AntiAim::Pitch::type >= AntiAimType_X::LISP_DOWN)
						{
							Settings::AntiAim::Pitch::type = AntiAimType_X::STATIC_UP;
							ImGui::OpenPopup(XORSTR("Error###UNTRUSTED_AA"));
						}
					}
					ImGui::PopItemWidth();
				}
				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::Text(XORSTR("Disable"));
				ImGui::Separator();
				ImGui::Checkbox(XORSTR("Knife"), &Settings::AntiAim::AutoDisable::knifeHeld);
				ImGui::Checkbox(XORSTR("No Enemy"), &Settings::AntiAim::AutoDisable::noEnemy);

				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::Text(XORSTR("FreeStanding"));
				ImGui::Separator();
				ImGui::Checkbox(XORSTR("Enabled"), &Settings::AntiAim::FreeStanding::enabled);
				ImGui::Columns(1);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(210, 85));
				if (ImGui::BeginPopupModal(XORSTR("Error###UNTRUSTED_AA")))
				{
					ImGui::Text(XORSTR("You cannot use this antiaim type on a VALVE server."));

					ImGui::Checkbox(XORSTR("This is not a VALVE server"), &ValveDSCheck::forceUT);

					if (ImGui::Button(XORSTR("OK")))
						ImGui::CloseCurrentPopup();

					ImGui::EndPopup();
				}
				ImGui::PopStyleVar();

				ImGui::EndChild();
			}
			ImGui::EndChild();
		}
	}
	ImGui::NextColumn();
	{
		ImGui::BeginChild(XORSTR("HVH2"), ImVec2(0, 0), true);
		{
			ImGui::Text(XORSTR("Resolver"));
			ImGui::Separator();
			ImGui::Checkbox(XORSTR("Resolve All"), &Settings::Resolver::resolveAll);
			ImGui::Separator();
			ImGui::Text(XORSTR("Movement"));
			ImGui::Checkbox(XORSTR("Auto Crouch"), &Settings::Aimbot::AutoCrouch::enabled);
			ImGui::EndChild();
		}
	}
}