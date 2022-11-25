#include "../structs/c_base_player.hpp"
#include "../../../cheat/helpers/interfaces/interfaces.hpp"
#include "../../../cheat/helpers/memory/memory.hpp"
#include "../structs/matrix.hpp"
#include "../structs/player_info.hpp"

std::string sdk::c_base_player::name( )
{
	if ( sdk::player_info info{ }; g_interfaces->engine_client->get_player_info( this->entindex( ), &info ) )
		return { info.name };

	return { };
}

sdk::vector sdk::c_base_player::get_hitbox_position( const std::uint32_t hitbox_index )
{
	matrix_3x4 matrix[ 128 ];

	auto hdr = g_interfaces->model_info->get_studio_model( get_model( ) );

	if ( !hdr )
		return { };

	if ( !setup_bones( matrix, 128, 0x100, 0.f ) )
		return { };

	auto set = hdr->get_hitbox_set( hitbox_set( ) );

	[[unlikely]] if ( !set )
		return { };

	auto hitbox = set->get_hitbox( hitbox_index );

	if ( !hitbox )
		return { };

	if ( hitbox->bone >= 128 || hitbox->bone < 0 )
		return { };

	return math::vector_transform( ( hitbox->bb_min + hitbox->bb_max ) * 0.5f, matrix[ hitbox->bone ] );
}

sdk::vector sdk::c_base_player::get_hitbox_position( const std::uint32_t hitbox_index, sdk::matrix_3x4* matrix )
{
	auto hdr = g_interfaces->model_info->get_studio_model( get_model( ) );

	if ( !hdr )
		return { };

	auto set = hdr->get_hitbox_set( hitbox_set( ) );

	[[unlikely]] if ( !set )
		return { };

	auto hitbox = set->get_hitbox( hitbox_index );

	if ( !hitbox )
		return { };

	return math::vector_transform( ( hitbox->bb_min + hitbox->bb_max ) * 0.5f, matrix[ hitbox->bone ] );
}
