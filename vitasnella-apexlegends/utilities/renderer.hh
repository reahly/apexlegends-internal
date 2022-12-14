#pragma once
#include "../imgui/imgui.h"

namespace render {
	void text( const char*, ImVec2, float, const ImU32&, bool outline = false, bool center = true );
	void circle( float, float, float, float, const ImU32& );
	void rect( ImVec2, ImVec2, const ImU32& );
	void filled_rect( ImVec2, ImVec2, const ImU32& );
}