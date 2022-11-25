#ifndef WEDNESDAY_WTF_I_GLOBAL_VARS_BASE_HPP
#define WEDNESDAY_WTF_I_GLOBAL_VARS_BASE_HPP

namespace sdk
{
	struct i_global_vars_base {
	public:
		// Absolute time (per frame still - Use Plat_FloatTime() for a high precision real time
		//  perf clock, but not that it doesn't obey host_timescale/host_framerate)
		float real_time;
		// Absolute frame counter
		int frame_count;
		// Non-paused frametime
		float absolute_frametime;

		// Current time
		//
		// On the client, this (along with tickcount) takes a different meaning based on what
		// piece of code you're in:
		//
		//   - While receiving network packets (like in PreDataUpdate/PostDataUpdate and proxies),
		//     this is set to the SERVER TICKCOUNT for that packet. There is no interval between
		//     the server ticks.
		//     [server_current_Tick * tick_interval]
		//
		//   - While rendering, this is the exact client clock
		//     [client_current_tick * tick_interval + interpolation_amount]
		//
		//   - During prediction, this is based on the client's current tick:
		//     [client_current_tick * tick_interval]
		float cur_time;

		// Time spent on last server or client frame (has nothing to do with think intervals)
		float frame_time;
		// current maxplayers setting
		int max_clients;

		// Simulation ticks
		int tick_count;

		// Simulation tick interval
		float interval_per_tick;

		// interpolation amount ( client-only ) based on fraction of next tick which has elapsed
		float interpolation_amount;
		int sim_ticks_this_frame;

		int network_protocol;

		// current saverestore data
		void* save_data;

		// Set to true in client code.
		bool client;

		// 100 (i.e., tickcount is rounded down to this base and then the "delta" from this base is networked
		int timestamp_networking_base;
		// 32 (entindex() % nTimestampRandomizeWindow ) is subtracted from gpGlobals->tickcount to set the networking basis, prevents
		//  all of the entities from forcing a new PackedEntity on the same tick (i.e., prevents them from getting lockstepped on this)
		int teimstamp_randomize_window;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_I_GLOBAL_VARS_BASE_HPP
