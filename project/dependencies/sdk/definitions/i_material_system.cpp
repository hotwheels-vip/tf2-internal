#include "../interfaces/i_material_system.hpp"
#include "../../../cheat/helpers/memory/memory.hpp"

sdk::i_material* sdk::i_material_system::find_material( const char* name, const char* group_name, bool complain, const char* complain_prefix )
{
	using find_material_type = sdk::i_material*( __thiscall* )( void*, const char*, const char*, bool, const char* );

	return reinterpret_cast< find_material_type >( g_virtuals->get_virtual_function( this, 84 ) )( this, name, group_name, complain,
	                                                                                               complain_prefix );
}