#include "../structs/c_tf_player.hpp"
#include "../../../cheat/features/aimbot/aimbot.hpp"
#include "../../../cheat/helpers/entity_list/entity_list.hpp"
#include "../../../cheat/helpers/interfaces/interfaces.hpp"
#include "../enums/trace_defs.hpp"

void sdk::c_tf_player::pre_think( )
{
	static auto pre_think =
		g_database[ HASH( "56 8B F1 8B 06 FF 90 ? ? ? ? 8B 06 8B CE FF 90 ? ? ? ? 8B CE" ) ].as< void( __thiscall* )( void* ) >( );
	pre_think( this );
}

void sdk::c_tf_player::post_think( )
{
	static auto post_think = g_database[ HASH( "53 56 8B 35 ? ? ? ? 8B D9 8B CE 8B 06" ) ].as< void( __thiscall* )( void* ) >( );
	post_think( this );
}

bool sdk::c_tf_player::can_hit( const vector pos, sdk::c_base_entity* ent )
{
	sdk::c_game_trace trace;
	sdk::c_trace_filter_hitscan filter;
	sdk::ray_t ray;

	if ( g_weapon && g_aimbot->get_weapon_info( ).speed != 0 )
		ray.init( this->eye_position( ), pos, { -2, -2, -2 }, { 2, 2, 2 } );
	else
		ray.init( this->eye_position( ), pos );

	filter.skip = this;

	g_interfaces->engine_trace->trace_ray( ray, ( MASK_SHOT | CONTENTS_GRATE ), &filter, &trace );

	return ( ent && trace.entity == ent ) || trace.fraction > 0.99f;
}

bool sdk::c_tf_player::could_hit( vector pos )
{
	sdk::c_game_trace trace;
	sdk::c_trace_filter_hitscan filter;
	sdk::ray_t ray;

	if ( g_weapon && g_aimbot->get_weapon_info( ).speed != 0 )
		ray.init( this->eye_position( ), pos, { -2, -2, -2 }, { 2, 2, 2 } );
	else
		ray.init( this->eye_position( ), pos );

	filter.skip = this;

	g_interfaces->engine_trace->trace_ray( ray, ( MASK_SHOT | CONTENTS_GRATE ), &filter, &trace );

	return trace.fraction > 0.99f;
}

void sdk::c_tf_player::draw_client_hitbox( const float& duration )
{
	auto hdr = g_interfaces->model_info->get_studio_model( get_model( ) );

	if ( !hdr )
		return;

	auto set = hdr->get_hitbox_set( hitbox_set( ) );

	if ( !set )
		return;

	matrix_3x4 bone_matrix[ 128 ];
	if ( !setup_bones( bone_matrix, 128, 0x0007FF00, 0 ) ) // bone used by anything
		return;

	vector position;
	qangle angle;

	for ( int i = 0; i < set->num_hitboxes; i++ ) {
		auto box = set->get_hitbox( i );

		angle    = bone_matrix[ box->bone ].to_angle( );
		position = bone_matrix[ box->bone ].to_vector( 3 );

		g_interfaces->debug_overlay->add_box_overlay( position, box->bb_min, box->bb_max, angle, 255, 50, 0, 0, duration );
	}
}

sdk::c_base_animating* sdk::c_tf_player::get_server_base_animating( )
{
	static auto server_base_animating = g_database[ HASH( "55 8B EC 8B 55 ? 85 D2 7E ? A1" ) ].as< sdk::c_base_animating*( __cdecl* )( int ) >( );

	return server_base_animating( entindex( ) );
}
