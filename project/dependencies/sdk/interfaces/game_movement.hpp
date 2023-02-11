#pragma once

#include "../../helpers/memory/memory.hpp"
#include "../structs/i_client_entity.hpp"

namespace sdk
{
	struct i_move_helper {
	public:
		virtual char const* get_name( int handle ) const                                                                                        = 0;
		virtual void reset_touch_list( void )                                                                                                   = 0;
		virtual bool add_to_touched( const void* tr, const vector& impactvelocity )                                                             = 0;
		virtual void process_impacts( void )                                                                                                    = 0;
		virtual void con_n_printf( int idx, char const* fmt, ... )                                                                              = 0;
		virtual void start_sound( const vector& origin, int channel, char const* sample, float volume, int soundlevel, int f_flags, int pitch ) = 0;
		virtual void start_sound( const vector& origin, const char* soundname )                                                                 = 0;
		virtual void playback_event_full( int flags, int clientindex, unsigned short eventindex, float delay, vector& origin, vector& angles,
		                                  float fparam1, float fparam2, int iparam1, int iparam2, int bparam1, int bparam2 )                    = 0;
		virtual bool player_falling_damage( void )                                                                                              = 0;
		virtual void player_set_animation( int player_anim )                                                                                    = 0;
		virtual void* get_surface_props( void )                                                                                                 = 0;
		virtual bool is_world_entity( const c_base_handle& handle )                                                                             = 0;
		virtual ~i_move_helper( ) { }

		void set_host( i_client_entity* host )
		{
			using func = void( __thiscall* )( void*, i_client_entity* );
			reinterpret_cast< func >( g_virtuals->get_virtual_function( this, 0 ) )( this, host );
		}
	};

	struct i_game_movement {
	public:
		virtual ~i_game_movement( void ) { }

		// process the current movement command
		virtual void process_movement( c_base_entity* p_player, void* p_move ) = 0;
		virtual void start_track_prediction_errors( c_base_entity* p_player )  = 0;
		virtual void finish_track_prediction_errors( c_base_entity* p_player ) = 0;
		virtual void diff_print( const char* fmt, ... )                        = 0;

		// allows other parts of the engine to find out the normal and ducked player bbox sizes
		virtual vector get_player_mins( bool ducked ) const        = 0;
		virtual vector get_player_maxs( bool ducked ) const        = 0;
		virtual vector get_player_view_offset( bool ducked ) const = 0;
	};

} // namespace sdk
