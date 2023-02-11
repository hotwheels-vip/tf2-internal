#pragma once

#include <iostream>
#include <sdk/crc32.hpp>

namespace sdk
{
	struct player_info {
	public:
		char name[ 32 ];
		int user_id;
		char guid[ 32 + 1 ];
		std::uint32_t friends_id;
		char friends_name[ 32 ];
		bool fake_player;
		bool is_hltv;
		bool is_replay;
		CRC32_t custom_files[ 4 ];
		unsigned char filesDownloaded;
	};
} // namespace sdk
