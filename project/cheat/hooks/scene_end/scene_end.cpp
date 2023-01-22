#include "scene_end.hpp"

void scene_end::detour( void* ecx, void* edx )
{
	return g_scene_end->_hook.call( ecx, edx );
}
