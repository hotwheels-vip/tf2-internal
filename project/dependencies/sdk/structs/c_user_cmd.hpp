#ifndef WEDNESDAY_WTF_C_USER_CMD_HPP
#define WEDNESDAY_WTF_C_USER_CMD_HPP

#include <valve/crc32.hpp>
#include "../structs/qangle.hpp"

namespace sdk
{
	struct c_user_cmd {
	public:
		virtual ~c_user_cmd( ){ };
		int command_number;
		int tick_count;
		sdk::qangle view_angles;
		float forward_move;
		float side_move;
		float up_move;
		int buttons;
		std::uint8_t impulse;
		int weapon_select;
		int weapon_subtype;
		int random_seed;
		short mouse_dx;
		short mouse_dy;
		bool has_been_predicted;

		CRC32_t get_checksum( )
		{
			CRC32_t crc;

			CRC32_Init( &crc );
			CRC32_ProcessBuffer( &crc, &command_number, sizeof( command_number ) );
			CRC32_ProcessBuffer( &crc, &tick_count, sizeof( tick_count ) );
			CRC32_ProcessBuffer( &crc, &view_angles, sizeof( view_angles ) );
			CRC32_ProcessBuffer( &crc, &forward_move, sizeof( forward_move ) );
			CRC32_ProcessBuffer( &crc, &side_move, sizeof( side_move ) );
			CRC32_ProcessBuffer( &crc, &up_move, sizeof( up_move ) );
			CRC32_ProcessBuffer( &crc, &buttons, sizeof( buttons ) );
			CRC32_ProcessBuffer( &crc, &impulse, sizeof( impulse ) );
			CRC32_ProcessBuffer( &crc, &weapon_select, sizeof( weapon_select ) );
			CRC32_ProcessBuffer( &crc, &weapon_subtype, sizeof( weapon_subtype ) );
			CRC32_ProcessBuffer( &crc, &random_seed, sizeof( random_seed ) );
			CRC32_ProcessBuffer( &crc, &mouse_dx, sizeof( mouse_dx ) );
			CRC32_ProcessBuffer( &crc, &mouse_dy, sizeof( mouse_dy ) );
			CRC32_Final( &crc );

			return crc;
		}
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_C_USER_CMD_HPP
