#ifndef WEDNESDAY_WTF_MODEL_T_HPP
#define WEDNESDAY_WTF_MODEL_T_HPP

#include "vector.hpp"

namespace sdk
{

	struct model_t {
		void* fn_handle;        // 0x0000
		char name[ 260 ];       // 0x0004
		__int32 load_flags;     // 0x0108
		__int32 server_count;   // 0x010c
		__int32 type;           // 0x0110
		__int32 flags;          // 0x0114
		vector mins;            // 0x0118
		vector maxs;            // 0x0124
		float radius;           // 0x0130
		char pad0x0134[ 0x1c ]; // 0x0134
	};                          // size=0x0150

} // namespace sdk
#endif // WEDNESDAY_WTF_MODEL_T_HPP
