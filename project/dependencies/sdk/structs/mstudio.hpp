#ifndef WEDNESDAY_WTF_MSTUDIO_HPP
#define WEDNESDAY_WTF_MSTUDIO_HPP

#include "matrix.hpp"
#include "qangle.hpp"
#include "vector.hpp"

namespace sdk
{

	typedef float quaternion[ 4 ];
	typedef float radian_euler[ 3 ];

	typedef unsigned short mdl_handle_t;

	struct m_studio_bone_t {
		int name_index;
		inline char* const get_name( void ) const
		{
			return ( ( char* )this ) + name_index;
		}
		int parent;
		int bone_controller[ 6 ]; // bone controller index, -1 == none
		vector pos;
		quaternion unknown_quaternion;
		radian_euler rot;
		// compression scale
		vector pos_scale;
		vector rot_scale;

		matrix_3x4 pose_to_bone;
		quaternion alignment;
		int flags;
		int proctype;
		int procindex;
		mutable int physicsbone;

		inline void* p_procedure( ) const
		{
			if ( procindex == 0 )
				return 0;

			else
				return ( void* )( ( ( std::byte* )this ) + proctype );
		};

		int surface_prop_idx;
		inline char* const get_unknown_surface_prop_string( void ) const
		{
			return ( ( char* )this ) + surface_prop_idx;
		}
		inline int get_surface_prop( void ) const
		{
			return surface_prop_lookup;
		}

		int contents;
		int surface_prop_lookup;
		int pad01[ 7 ];

		m_studio_bone_t( ) { }

	private:
		// no copy constructors allowed
		m_studio_bone_t( const m_studio_bone_t& v_other );
	};

	struct m_studio_b_box_t {
		int bone;
		int group;
		vector bb_min;
		vector bb_max;
		int hitbox_name_index;
		qangle rotation;
		float radius;
		int32_t pad02[ 4 ];

		const char* get_name( )
		{
			if ( !hitbox_name_index )
				return nullptr;
			return ( const char* )( ( uint8_t* )this + hitbox_name_index );
		}
	};

	struct m_studio_hitbox_set_t {
		int name_index;
		int num_hitboxes;
		int hitbox_index;

		const char* get_name( )
		{
			if ( !name_index )
				return nullptr;
			return ( const char* )( ( uint8_t* )this + name_index );
		}

		m_studio_b_box_t* get_hitbox( int i )
		{
			if ( i > num_hitboxes )
				return nullptr;
			return ( m_studio_b_box_t* )( ( uint8_t* )this + hitbox_index ) + i;
		}
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_MSTUDIO_HPP
