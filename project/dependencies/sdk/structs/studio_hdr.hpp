#ifndef WEDNESDAY_WTF_STUDIO_HDR_HPP
#define WEDNESDAY_WTF_STUDIO_HDR_HPP
#include "mstudio.hpp"

namespace sdk
{
	class studio_hdr_t
	{
	public:
		__int32 id;                    // 0x0000
		__int32 version;               // 0x0004
		long checksum;                 // 0x0008
		char name[ 64 ];               // 0x000c
		__int32 length;                // 0x004c
		vector eye_pos;                // 0x0050
		vector illum_pos;              // 0x005c
		vector hull_min;               // 0x0068
		vector hull_max;               // 0x0074
		vector bb_min;                 // 0x0080
		vector bb_max;                 // 0x008c
		__int32 flags;                 // 0x0098
		__int32 num_bones;             // 0x009c
		__int32 bone_index;            // 0x00a0
		__int32 num_bone_controllers;  // 0x00a4
		__int32 bone_controller_index; // 0x00a8
		__int32 num_hitbox_sets;       // 0x00ac
		__int32 hitbox_set_index;      // 0x00b0
		__int32 num_local_anim;        // 0x00b4
		__int32 local_anim_index;      // 0x00b8
		__int32 num_local_sequence;    // 0x00bc
		__int32 local_sequence_index;  // 0x00c0
		__int32 activity_list_version; // 0x00c4
		__int32 events_indexed;        // 0x00c8
		__int32 num_textures;          // 0x00cc
		__int32 texture_index;         // 0x00d0

		m_studio_hitbox_set_t* get_hitbox_set( int i )
		{
			if ( i > num_hitbox_sets )
				return nullptr;
			return ( m_studio_hitbox_set_t* )( ( uint8_t* )this + hitbox_set_index ) + i;
		}

		m_studio_b_box_t* get_hitbox( int i, int set )
		{
			m_studio_hitbox_set_t* s = get_hitbox_set( set );

			if ( !s )
				return nullptr;

			return s->get_hitbox( i );
		}

		m_studio_bone_t* get_bone( int i )
		{
			if ( i > num_bones )
				return nullptr;
			return ( m_studio_bone_t* )( ( uint8_t* )this + bone_index ) + i;
		}

	}; // size=0x00d4
} // namespace sdk
#endif // WEDNESDAY_WTF_STUDIO_HDR_HPP
