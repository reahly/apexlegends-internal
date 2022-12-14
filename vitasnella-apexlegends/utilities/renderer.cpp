#include <cmath>
#include "renderer.hh"
#include "../imgui/imgui_internal.h"

void render::text( const char* text, ImVec2 pos, const float size, const ImU32& color, const bool outline, const bool center ) {
	const auto text_size = ImGui::GetDefaultFont( )->CalcTextSizeA( size, FLT_MAX, 0.0f, text );

	if ( center )
		pos.x -= text_size.x / 2.0f;

	if ( outline ) {
		ImGui::GetCurrentWindow( )->DrawList->AddText( ImGui::GetDefaultFont( ), size, ImVec2( pos.x + 1, pos.y + 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, 1 ) ), text );
		ImGui::GetCurrentWindow( )->DrawList->AddText( ImGui::GetDefaultFont( ), size, ImVec2( pos.x - 1, pos.y - 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, 1 ) ), text );
		ImGui::GetCurrentWindow( )->DrawList->AddText( ImGui::GetDefaultFont( ), size, ImVec2( pos.x + 1, pos.y - 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, 1 ) ), text );
		ImGui::GetCurrentWindow( )->DrawList->AddText( ImGui::GetDefaultFont( ), size, ImVec2( pos.x - 1, pos.y + 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, 1 ) ), text );		
	}

	ImGui::GetOverlayDrawList( )->AddText( ImGui::GetDefaultFont( ), size, pos, color, text );
}

void render::circle( const float x, const float y, const float r, const float s, const ImU32& color ) {
	const float step = 3.14159265359 * 2.0 / s;
	for ( float a = 0; a < 3.14159265359 * 2.0; a += step ) {
		const auto x1 = r * std::cos( a ) + x;
		const auto y1 = r * std::sin( a ) + y;
		const auto x2 = r * std::cos( a + step ) + x;
		const auto y2 = r * std::sin( a + step ) + y;

		ImGui::GetCurrentWindow( )->DrawList->AddLine( ImVec2( x1, y1 ), ImVec2( x2, y2 ), color );
	}
}

void render::rect( const ImVec2 start, const ImVec2 end, const ImU32& color ) {
	ImGui::GetOverlayDrawList( )->AddRect( ImVec2( start.x, start.y ), ImVec2( start.x + end.x, start.y + end.y ), color );
}

void render::filled_rect( const ImVec2 start, const ImVec2 end, const ImU32& color ) {
	ImGui::GetOverlayDrawList( )->AddRectFilled( ImVec2( start.x, start.y ), ImVec2( start.x + end.x, start.y + end.y ), color );
}