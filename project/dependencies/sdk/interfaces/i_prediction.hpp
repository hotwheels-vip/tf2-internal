#ifndef WEDNESDAY_WTF_I_PREDICTION_HPP
#define WEDNESDAY_WTF_I_PREDICTION_HPP
#include "../structs/c_user_cmd.hpp"
#include "../structs/vector.hpp"

#include <cstdint>
namespace sdk
{
	struct c_base_player;

	struct move_data_t {
	public:
		bool first_run_of_functions : 1;
		bool game_code_moved_player : 1;
		c_base_handle player_handle;
		int impulse_command;
		qangle view_angles;
		qangle abs_view_angles;
		int buttons;
		int old_buttons;
		float forward_move;
		float old_forward_move;
		float side_move;
		float up_move;
		float max_speed;
		float client_max_speed;
		vector velocity;
		qangle angles;
		qangle old_angles;
		float step_height;
		vector wish_vel;
		vector jump_vel;
		vector constraint_center;
		float constraint_radius;
		float constraint_width;
		float constraint_speed_factor;
		vector abs_origin;
	};
	class i_prediction
	{
	public:
		virtual ~i_prediction( void ){ };
		virtual void init( void )                                                                               = 0;
		virtual void shutdown( void )                                                                           = 0;
		virtual void update( int startframe, bool validframe, int incoming_acknowledged, int outgoing_command ) = 0;
		virtual void pre_entity_packet_received( int commands_acknowledged, int current_world_update_packet )   = 0;
		virtual void post_entity_packet_received( void )                                                        = 0;
		virtual void post_network_data_received( int commands_acknowledged )                                    = 0;
		virtual void on_received_uncompressed_packet( void )                                                    = 0;
		virtual void get_view_origin( vector& org )                                                             = 0;
		virtual void set_view_origin( vector& org )                                                             = 0;
		virtual void get_view_angles( qangle& ang )                                                             = 0;
		virtual void set_view_angles( qangle& ang )                                                             = 0;
		virtual void get_local_view_angles( qangle& ang )                                                       = 0;
		virtual void set_local_view_angles( qangle& ang )                                                       = 0;
	};

	class c_prediction : public i_prediction
	{
	public:
		~c_prediction( ) override;
		void init( ) override;
		void shutdown( ) override;
		void update( int startframe, bool validframe, int incoming_acknowledged, int outgoing_command ) override;
		void on_received_uncompressed_packet( ) override;
		void pre_entity_packet_received( int commands_acknowledged, int current_world_update_packet ) override;
		void post_entity_packet_received( ) override;
		void post_network_data_received( int commands_acknowledged ) override;
		virtual bool in_prediction( );
		virtual bool is_first_time_predicted( );
		virtual int get_incoming_packet_number( );
		void get_view_origin( vector& org ) override;
		void set_view_origin( vector& org ) override;
		void get_view_angles( qangle& ang ) override;
		void set_view_angles( qangle& ang ) override;
		void get_local_view_angles( qangle& ang ) override;
		void set_local_view_angles( qangle& ang ) override;
		virtual void run_command( c_base_entity* player, c_user_cmd* ucmd, i_move_helper* move_helper );
		virtual void setup_move( c_base_entity* player, c_user_cmd* ucmd, i_move_helper* p_helper, move_data_t* move );
		virtual void finish_move( c_base_entity* player, c_user_cmd* ucmd, move_data_t* move );
		virtual void set_ideal_pitch( c_base_entity* player, const vector& origin, const vector& angles, const vector& viewheight );
		virtual void _update( bool received_new_world_update, bool validframe, int incoming_acknowledged, int outgoing_command );

		// c_handle< c_base_entity > last_ground;
		uint32_t last_ground;
		bool is_in_prediction;
		bool first_time_predicted;
		bool old_cl_predict_value;
		bool engine_paused;
		int previous_start_frame;
		int commands_predicted;
		int server_commands_acknowledged;
		int previous_ack_had_errors;
		int incoming_packet_number;
		float ideal_pitch;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_I_PREDICTION_HPP
