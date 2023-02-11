#pragma once

#include "../macros.hpp"
#include "../structs/bf_rw.hpp"

namespace sdk
{
	struct i_net_channel;
	struct netadr_t;

	struct i_net_message {
	public:
		virtual ~i_net_message( ){ };

		// use these to setup who can hear whose voice.
		// pass in client indices (which are their ent indices - 1).
		virtual void set_net_channel( i_net_channel* netchan ){ }; // netchannel this message is from/for
		virtual void set_reliable( bool state ){ };                // set to true if it's a reliable message

		virtual bool process( void )
		{
			return true;
		} // calles the recently set handler to process this message

		virtual bool read_from_buffer( void* buffer )
		{
			return true;
		}; // returns true if parsing was ok
		virtual bool write_to_buffer( void* buffer )
		{
			return true;
		}; // returns true if writing was ok

		virtual bool is_reliable( void ) const
		{
			return true;
		}; // true, if message needs reliable handling

		virtual int get_type( void ) const
		{
			return 1;
		}; // returns module specific header tag eg svc_serverinfo
		virtual int get_group( void ) const
		{
			return 1;
		}; // returns net message group of this message
		virtual const char* get_name( void ) const
		{
			return "";
		}; // returns network message name, eg "svc_serverinfo"
		virtual i_net_channel* get_net_channel( void ) const
		{
			return { };
		};
		virtual const char* to_string( void ) const
		{
			return { };
		}; // returns a human readable string about message content
	};

	struct c_net_message : public i_net_message {
	public:
		c_net_message( )
		{
			reliable = 0;
			own_data = false;
		};
		virtual ~c_net_message( ){ };

		void set_reliable( bool state = true )
		{
			reliable = state;
		};
		bool is_reliable( )
		{
			return reliable;
		};
		bool is_connection_less( )
		{
			return false;
		};

		virtual const char* to_string( )
		{
			return "unknown c_net_message";
		};

		bool reliable;
		bool own_data;
	};

	struct i_net_channel_info {
	public:
		enum {
			generic = 0,  // must be first and is default group
			localplayer,  // bytes for local player entity update
			otherplayers, // bytes for other players update
			entities,     // all other entity bytes
			sounds,       // game sounds
			events,       // event messages
			usermessages, // user messages
			entmessages,  // entity messages
			voice,        // voice data
			stringtable,  // a stringtable update
			move,         // client move cmds
			stringcmd,    // string command
			signon,       // various signondata
			total,        // must be last and is not a real group
		};

		virtual const char* get_name( void ) const     = 0; // get channel name
		virtual const char* get_address( void ) const  = 0; // get channel ip address as string
		virtual float get_time( void ) const           = 0; // current net time
		virtual float get_time_connected( void ) const = 0; // get connection time in seconds
		virtual int get_buffer_size( void ) const      = 0; // netchannel packet history size
		virtual int get_data_rate( void ) const        = 0; // send data rate in byte/sec

		virtual bool is_loopback( void ) const   = 0; // true if loopback channel
		virtual bool is_timing_out( void ) const = 0; // true if timing out
		virtual bool is_playback( void ) const   = 0; // true if demo playback

		virtual float get_latency( int flow ) const                                        = 0; // current latency (rtt), more accurate but jittering
		virtual float get_avg_latency( int flow ) const                                    = 0; // average packet latency in seconds
		virtual float get_avg_loss( int flow ) const                                       = 0; // avg packet loss[0..1]
		virtual float get_avg_choke( int flow ) const                                      = 0; // avg packet choke[0..1]
		virtual float get_avg_data( int flow ) const                                       = 0; // data flow in bytes/sec
		virtual float get_avg_packets( int flow ) const                                    = 0; // avg packets/sec
		virtual int get_total_data( int flow ) const                                       = 0; // total flow in/out in bytes
		virtual int get_sequence_nr( int flow ) const                                      = 0; // last send seq number
		virtual bool is_valid_packet( int flow, int frame_number ) const                   = 0; // true if packet was not lost/dropped/chocked/flushed
		virtual float get_packet_time( int flow, int frame_number ) const                  = 0; // time when packet was send
		virtual int get_packet_bytes( int flow, int frame_number, int group ) const        = 0; // group size of this packet
		virtual bool get_stream_progress( int flow, int* received, int* total ) const      = 0; // tcp progress if transmitting
		virtual float get_time_since_last_received( void ) const                           = 0; // get time since last recieved packet in seconds
		virtual float get_command_interpolation_amount( int flow, int frame_number ) const = 0;
		virtual void get_packet_response_latency( int flow, int frame_number, int* pn_latency_msecs, int* pn_choke ) const = 0;
		virtual void get_remote_framerate( float* pfl_frame_time, float* pfl_frame_time_std_deviation ) const              = 0;

		virtual float get_timeout_seconds( ) const = 0;
	};

	struct i_net_channel : public i_net_channel_info {
	public:
		virtual ~i_net_channel( void ){ };

		virtual void set_data_rate( float rate )                  = 0;
		virtual bool register_message( i_net_message* msg )       = 0;
		virtual bool start_streaming( unsigned int challenge_nr ) = 0;
		virtual void reset_streaming( void )                      = 0;
		virtual void set_timeout( float seconds )                 = 0;
		virtual void set_demo_recorder( void* recorder )          = 0;
		virtual void set_challenge_nr( unsigned int chnr )        = 0;

		virtual void reset( void )                  = 0;
		virtual void clear( void )                  = 0;
		virtual void shutdown( const char* reason ) = 0;

		virtual void process_playback( void )                                        = 0;
		virtual bool process_stream( void )                                          = 0;
		virtual void process_packet( struct netpacket_s* packet, bool b_has_header ) = 0;

		// virtual bool send_net_msg( i_net_message& msg, bool b_force_reliable = false, bool b_voice = false ) = 0;

		virtual bool send_data( void* msg, bool b_reliable = true )                     = 0;
		virtual bool send_file( const char* filename, unsigned int transfer_id )        = 0;
		virtual void deny_file( const char* filename, unsigned int transfer_id )        = 0;
		virtual void request_file_old( const char* filename, unsigned int transfer_id ) = 0; // get rid of this function when we version the
		virtual void set_choked( void )                                                 = 0;
		// virtual int send_datagram( void* data )                                         = 0;
		virtual bool transmit( bool only_reliable = false ) = 0;

		virtual const netadr_t& get_remote_address( void ) const = 0;
		virtual void* get_msg_handler( void ) const              = 0;
		//		virtual int get_drop_number( void ) const                                                                   = 0;
		virtual int get_socket( void ) const                                                                        = 0;
		virtual unsigned int get_challenge_nr( void ) const                                                         = 0;
		virtual void get_sequence_data( int& n_out_sequence_nr, int& n_in_sequence_nr, int& n_out_sequence_nr_ack ) = 0;
		virtual void set_sequence_data( int n_out_sequence_nr, int n_in_sequence_nr, int n_out_sequence_nr_ack )    = 0;

		virtual void update_message_stats( int msggroup, int bits ) = 0;
		virtual bool can_packet( void ) const                       = 0;
		virtual bool is_overflowed( void ) const                    = 0;
		virtual bool is_timed_out( void ) const                     = 0;
		virtual bool has_pending_reliable_data( void )              = 0;

		virtual void set_file_transmission_mode( bool b_background_mode ) = 0;
		virtual void set_compression_mode( bool b_use_compression )       = 0;
		virtual unsigned int request_file( const char* filename )         = 0;
		virtual float get_time_since_last_received( void ) const          = 0; // get time since last received packet in seconds

		virtual void set_max_buffer_size( bool b_reliable, int n_bytes, bool b_voice = false ) = 0;

		virtual bool is_null( ) const                                                               = 0;
		virtual int get_num_bits_written( bool b_reliable )                                         = 0;
		virtual void set_interpolation_amount( float fl_interpolation_amount )                      = 0;
		virtual void set_remote_framerate( float fl_frame_time, float fl_frame_time_std_deviation ) = 0;

		// max # of payload bytes before we must split/fragment the packet
		virtual void set_max_routable_payload_size( int n_split_size ) = 0;
		virtual int get_max_routable_payload_size( )                   = 0;

		virtual int get_protocol_version( ) = 0;

		bool send_net_msg( i_net_message& msg, bool b_force_reliable = false, bool b_voice = false )
		{
			using send_net_msg_fn = bool( __thiscall* )( void*, i_net_message&, bool, bool );

			return g_database[ HASH( "55 8B EC 57 8B F9 8D 8F ? ? ? ? E8 ? ? ? ? 85 C0 75 ? B0 ? 5F 5D C2 ? ? 53" ) ].as< send_net_msg_fn >( )(
				this, msg, b_force_reliable, b_voice );
		}

		int send_datagram( bf_write* data )
		{
			using send_datagram_fn = int( __thiscall* )( void*, bf_write* );

			return g_database[ HASH( "55 8B EC B8 ? ? ? ? E8 ? ? ? ? A1 ? ? ? ? 53 56 8B D9" ) ].as< send_datagram_fn >( )( this, data );
		}

		int& get_drop_number( )
		{
			return *reinterpret_cast< int* >( reinterpret_cast< std::uint32_t >( this ) + 0x22B8 );
		}

		int& get_choked_packets( )
		{
			return *reinterpret_cast< int* >( reinterpret_cast< std::uint32_t >( this ) + 0x1C );
		}
	};

	struct clc_move : public c_net_message {
	public:
		int read_from_buffer( bf_read* buffer )
		{
			return 0;
		};
		int write_to_buffer( bf_write* buffer )
		{
			return 0;
		};
		void clear( ){ };
		const char* to_string( )
		{
			return "clc_move";
		};
		static int get_type( )
		{
			return 9;
		}
		static const char* get_name( )
		{
			return "clc_move";
		}

		int backup_commands;
		int new_commands;
		int length;
		bf_write data;
	};

} // namespace sdk
