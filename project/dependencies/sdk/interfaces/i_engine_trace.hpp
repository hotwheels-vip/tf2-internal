#ifndef WEDNESDAY_WTF_I_ENGINE_TRACE_HPP
#define WEDNESDAY_WTF_I_ENGINE_TRACE_HPP
#include "../enums/dispsurf_flag.hpp"
#include "../enums/trace_type.hpp"
#include "../structs/c_base_player.hpp"
#include "../structs/qangle.hpp"
#include "../structs/vector_aligned.hpp"
#include "../structs/client_class.hpp"

// @blanket: my cmake is so fucked, im not making new files for each of these!! it'd take years.
namespace sdk
{
	struct cplane {
		qangle normal;
		float dist;
		unsigned char type;
		unsigned char signbits;
		unsigned char pad[ 2 ];
	};
	struct csurface {
		const char* name;
		short surface_props;
		unsigned short flags;
	};

	struct ray_t {
		vector_aligned start;        // starting point, centered within the extents
		vector_aligned delta;        // direction + length of the ray
		vector_aligned start_offset; // add this to start to get the actual ray start
		vector_aligned extents;      // describes an axis aligned box extruded along a ray
		bool is_ray;                 // are the extents zero?
		bool is_swept;               // is delta != 0?

		void init( const vector& start, const vector& end )
		{
			delta    = end - start;
			is_swept = ( delta.length_sqr( ) != 0 );
			// extents.set();
			is_ray = true;
			// start_offset.set();
			this->start = start;
		}

		void init( const vector& start, const vector& end, const vector& mins, const vector& maxs )
		{
			delta    = end - start;
			is_swept = ( delta.length_sqr( ) != 0 );
			extents  = maxs - mins;
			extents *= 0.5f;
			is_ray       = ( extents.length_sqr( ) < 1e-6 );
			start_offset = mins + maxs;
			start_offset *= 0.5f;
			this->start = start + start_offset;
			start_offset *= -1.0f;
		}

		vector inv_delta( ) const
		{
			vector inv_delta;
			for ( int i_axis = 0; i_axis < 3; ++i_axis ) {
				if ( delta[ i_axis ] != 0.0f ) {
					inv_delta[ i_axis ] = 1.0f / delta[ i_axis ];
				} else {
					inv_delta[ i_axis ] = FLT_MAX;
				}
			}
			return inv_delta;
		}

	private:
	};

	struct c_base_trace {
	public:
		bool is_disp_surface( void )
		{
			return ( ( disp_flags & dispsurf_flag_surface ) != 0 );
		}
		bool is_disp_surface_walkable( void )
		{
			return ( ( disp_flags & dispsurf_flag_walkable ) != 0 );
		}
		bool is_disp_surface_buildable( void )
		{
			return ( ( disp_flags & dispsurf_flag_buildable ) != 0 );
		}
		bool is_disp_surface_prop1( void )
		{
			return ( ( disp_flags & dispsurf_flag_surfprop1 ) != 0 );
		}
		bool is_disp_surface_prop2( void )
		{
			return ( ( disp_flags & dispsurf_flag_surfprop2 ) != 0 );
		}

	public:
		vector startpos;           // start position
		vector endpos;             // final position
		cplane plane;              // surface normal at impact
		float fraction;            // time completed, 1.0 = didn't hit anything
		int contents;              // contents on other side of surface hit
		unsigned short disp_flags; // displacement flags for marking surfaces with data
		bool all_solid;            // if true, plane is not valid
		bool start_solid;          // if true, the initial point was in a solid area
	};

	struct c_game_trace : public c_base_trace {
	public:
		float fraction_left_solid; // time we left a solid, only valid if we started in solid
		csurface surface;          // surface hit (impact surface)
		int hitgroup;              // 0 == generic, non-zero is specific body part
		short physics_bone;        // physics bone hit by trace in studio
		c_base_entity* entity;
		// note: this member is overloaded.
		// if h_ent points at the world entity, then this is the static prop index.
		// otherwise, this is the hitbox index.
		int hitbox; // box hit by trace in studio

		inline bool did_hit( ) const
		{
			return fraction < 1 || all_solid || start_solid;
		}
	};

	struct c_trace_filter {
	public:
		virtual bool should_hit_entity( i_handle_entity* server_entity, int contents_mask ) = 0;
		virtual trace_type get_trace_type( ) const                                          = 0;
	};

	struct c_trace_filter_hitscan : public c_trace_filter {
	public:
		void* skip{ };

		bool should_hit_entity( i_handle_entity* server_entity, int contents_mask ) override
		{
			auto entity = reinterpret_cast< c_base_entity* >( server_entity );

			switch ( entity->get_client_class( )->class_id ) {
			case e_class_ids::cfuncareaportalwindow:
			case e_class_ids::cfuncrespawnroomvisualizer:
			case e_class_ids::csniperdot:
			case e_class_ids::ctfknife:
				return false;
			}

			return ( server_entity != skip );
		}

		trace_type get_trace_type( ) const override
		{
			return TRACE_EVERYTHING;
		}
	};

	struct c_trace_filter_entities_only : public c_trace_filter {
	public:
		bool should_hit_entity( i_handle_entity* server_entity, int contents_mask ) override
		{
			return true;
		}

		trace_type get_trace_type( ) const override
		{
			return TRACE_ENTITIES_ONLY;
		}
	};

	struct c_trace_filter_world_only : public c_trace_filter {
	public:
		bool should_hit_entity( i_handle_entity* server_entity, int contents_mask ) override
		{
			return false;
		}

		trace_type get_trace_type( ) const override
		{
			return TRACE_WORLD_ONLY;
		}
	};

	struct c_trace_filter_world_and_props_only : public c_trace_filter {
	public:
		bool should_hit_entity( i_handle_entity* server_entity, int contents_mask ) override
		{
			return false;
		}

		trace_type get_trace_type( ) const override
		{
			return TRACE_EVERYTHING;
		}
	};

	struct c_trace_filter_hit_all : public c_trace_filter {
	public:
		bool should_hit_entity( i_handle_entity* p_server_entity, int contents_mask ) override
		{
			return p_server_entity != skip;
		}

		trace_type get_trace_type( ) const override
		{
			return TRACE_EVERYTHING;
		}

		void* skip;
	};

	struct i_entity_enumerator {
	public:
		virtual bool enum_entity( void* entity_handle ) = 0;
	};

	struct c_trace_list_data;

	struct i_engine_trace {
	public:
		virtual int get_point_contents( const vector& vec_abs_position, i_handle_entity** pp_entity = nullptr )                            = 0;
		virtual int get_point_contents_collideable( i_collideable* p_collide, const vector& vec_abs_position )                             = 0;
		virtual void clip_ray_to_entity( const ray_t& ray, unsigned int f_mask, i_handle_entity* p_ent, c_game_trace* p_trace )            = 0;
		virtual void clip_ray_to_collideable( const ray_t& ray, unsigned int f_mask, i_collideable* p_collide, c_game_trace* p_trace )     = 0;
		virtual void trace_ray( const ray_t& ray, unsigned int f_mask, c_trace_filter* p_trace_filter, c_game_trace* p_trace )             = 0;
		virtual void setup_leaf_and_entity_list_ray( const ray_t& ray, c_trace_list_data& trace_data )                                     = 0;
		virtual void setup_leaf_and_entity_list_box( const vector& vec_box_min, const vector& vec_box_max, c_trace_list_data& trace_data ) = 0;
		virtual void trace_ray_against_leaf_and_entity_list( const ray_t& ray, c_trace_list_data& trace_data, unsigned int f_mask,
		                                                     c_trace_filter* p_trace_filter, c_game_trace* p_trace )                       = 0;
		virtual void sweep_collideable( i_collideable* p_collide, const vector& vec_abs_start, const vector& vec_abs_end, const qangle& vec_angles,
		                                unsigned int f_mask, c_trace_filter* p_trace_filter, c_game_trace* p_trace )                       = 0;
		virtual void enumerate_entities( const ray_t& ray, bool triggers, i_entity_enumerator* p_enumerator )                              = 0;
		virtual void enumerate_entities( const vector& vec_abs_mins, const vector& vec_abs_maxs, i_entity_enumerator* p_enumerator )       = 0;
		virtual i_collideable* get_collideable( i_handle_entity* p_entity )                                                                = 0;
		virtual int get_stat_by_index( int index, bool b_clear )                                                                           = 0;
		virtual void get_brushes_in_aabb( const vector& v_mins, const vector& v_maxs, void* /*c_utl_vector<int>**/ p_output,
		                                  int i_contents_mask = 0xffffffff )                                                               = 0;
		virtual /*c_phys_collide*/ void* get_collidable_from_displacements_in_aabb( const vector& mins, const vector& maxs )               = 0;
		virtual bool get_brush_info( int i_brush, void* /*c_utl_vector<vector4d>**/ p_planes_out, int* p_contents_out )                    = 0;
		virtual bool point_outside_world( const vector& pt_test )                                                                          = 0;
		virtual int get_leaf_containing_point( const vector& pt_test )                                                                     = 0;
	};

} // namespace sdk
#endif // WEDNESDAY_WTF_I_ENGINE_TRACE_HPP
