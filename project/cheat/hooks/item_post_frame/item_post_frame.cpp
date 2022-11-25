#include "item_post_frame.hpp"

void __fastcall item_post_frame::detour( void* ecx, void* edx )
{
	if ( g_prediction->running_post_think )
		return;

	g_item_post_frame->_hook.call( ecx, edx );
}
