#include "memory.hpp"

#include <spdlog/spdlog.h>

std::uintptr_t memory::find_pattern( std::uint8_t* region_start, std::uintptr_t region_size, const char* pattern )
{
	std::vector< int > bytes = pattern_to_bytes( pattern );

	for ( unsigned long i = 0; i < region_size - bytes.size( ); ++i ) {
		bool found = true;

		for ( unsigned long j = 0; j < bytes.size( ); ++j ) {
			if ( region_start[ i + j ] != bytes[ j ] && bytes[ j ] != -1 ) {
				found = false;
				break;
			}
		}

		if ( found )
			return ( std::uintptr_t )( &region_start[ i ] );
	}

	return 0;
}

std::vector< int > memory::pattern_to_bytes( const char* pattern )
{
	std::vector< int > bytes;

	char* start = ( char* )pattern;
	char* end   = ( char* )( start + strlen( pattern ) );

	for ( char* szCurrent = start; szCurrent < end; ++szCurrent ) {
		if ( *szCurrent == '?' ) {
			++szCurrent;

			if ( *szCurrent == '?' )
				++szCurrent;

			bytes.push_back( -1 );
		} else {
			bytes.push_back( strtoul( szCurrent, &szCurrent, 16 ) );
		}
	}

	return bytes;
}

void modules::run( )
{
	g_client       = new modules::module( "client.dll" );
	g_engine       = new modules::module( "engine.dll" );
	g_shaderapidx9 = new modules::module( "shaderapidx9.dll" );
	g_server       = new modules::module( "server.dll" );
}

void modules::end( ) { }

std::uintptr_t* virtuals::get_virtual_table( void* pAddress )
{
	return *( std::uintptr_t** )pAddress;
}

std::uintptr_t* virtuals::get_virtual_function( void* pAddress, std::size_t iIndex )
{
	return ( std::uintptr_t* )get_virtual_table( pAddress )[ iIndex ];
}

void signatures::run( )
{
	using namespace spdlog;

	std::vector< signature > signatures{
		{ "8B 0D ? ? ? ? FF 75 ? D9 45 ? 51 8B 01 D9 1C ? FF 75", g_client },
		{ "55 8B EC 56 8B 75 ? 85 F6 74 ? 8B 16 8B CE", g_client },
		{ "8B 0D ? ? ? ? 8B 02 D9 05", g_client },
		{ "A1 ? ? ? ? 50 8B 08 FF 51 0C", g_shaderapidx9 },
		{ "68 ? ? ? ? 50 50 FF 12", g_engine },
		{ "55 8B EC 56 57 8B F1 E8 ? ? ? ? 8B 7D 08 F3", g_client },
		{ "A1 ? ? ? ? 48 C7 81", g_client },
		{ "FF 35 ? ? ? ? 50 8B 11", g_client },
		{ "55 8B EC 8B 45 ? 85 C0 75 ? C7 05", g_client },
		{ "83 3D ? ? ? ? ? 74 ? 6A ? 50", g_client },
		{ "68 ? ? ? ? 6A ? 68 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? E8 ? ? ? ? 83 C4 ? C3", g_client },
		{ "53 56 8B 35 ? ? ? ? 8B D9 8B CE 8B 06", g_client },
		{ "56 8B F1 8B 06 FF 90 ? ? ? ? 8B 06 8B CE FF 90 ? ? ? ? 8B CE", g_client },
		{ "8B 0D ? ? ? ? 8B 46 08 68 ? ? ? ? 05 ? ? ? ? 8B 11 50", g_client },
		{ "55 8B EC 83 EC ? 53 56 8B 35 ? ? ? ? 33 DB 57 33 FF 89 5D ? 89 7D ? 8B 46", g_engine },
		{ "55 8B EC 83 EC ? 56 8B F1 E8 ? ? ? ? 3B F0", g_client },
		{ "55 8B EC 81 EC ? ? ? ? 53 57 8B F9 8B 9F", g_client },
		{ "55 8B EC 8B 55 ? 85 D2 7E ? A1", g_server },
		{ "55 8B EC 81 EC ? ? ? ? 53 56 8B 35 ? ? ? ? 8B D9 33 C9 33 D2 89 4D EC 89 55 F0 8B 46 08", g_client },
		{ "55 8B EC 81 EC ? ? ? ? 53 56 57 6A 01 68 ? ? ? ? 8B F9 68 ? ? ? ? 68 ? ? ? ? 8D 87 ? ? ? ? 50 8D 45 A0 "
		  "50 E8 ? ? ? ? 8B 0D ? ? ? ? 33 D2 33 F6 89 55 DC 89 75 E0 83 C4 18 89 55 E4",
		  g_server },
		{ "8A 81 ? ? ? ? C3 CC CC CC CC CC CC CC CC CC 80 B9", g_engine },
		{ "84 C0 75 ? 38 05 ? ? ? ? 75 ? A1", g_engine },
		{ "53 8B DC 83 EC ? 83 E4 ? 83 C4 ? 55 8B 6B ? 89 6C 24 ? 8B EC 83 EC ? 83 3D", g_engine },
		{ "55 8B EC 83 EC 38 83 3D ? ? ? ? ?", g_engine },
		{ "55 8B EC 57 8B F9 8D 8F ? ? ? ? E8 ? ? ? ? 85 C0 75 ? B0 ? 5F 5D C2 ? ? 53", g_engine },
		{ "8B 45 ? C7 45 ? ? ? ? ? 5F 5E 85 C0 74 ? 6A ? 50 E8 ? ? ? ? 83 C4 ? 8B E5 5D C3", g_engine },
		{ "C7 05 ? ? ? ? ? ? ? ? C7 05 ? ? ? ? ? ? ? ? DD 1D", g_engine },
		{ "55 8B EC 51 53 56 8B F1 57 89 75 ? E8 ? ? ? ? 8B 7D", g_client },
		{ "55 8B EC 83 EC ? 56 57 8B F9 8B 37", g_client },
		{ "55 8B EC 51 80 B9 14 4B 00 00", g_engine },
		{ "D9 43 ? DF F1", g_engine },
		{ "55 8B EC 81 EC ? ? ? ? 8B 0D ? ? ? ? 33 D2 89 55 ? 89 55 ? 89 55 ? 8B 41", g_engine },
		{ "55 8B EC 83 EC 34 53 8B 5D 08 57 8B F9 89 7D FC 85 DB", g_engine },
		{ "0F B7 81 ? ? ? ? 50 E8 ? ? ? ? 83 C4 ? C3", g_client },
		{ "A1 ? ? ? ? 03 05", g_engine },
		{ "03 05 ? ? ? ? 8B 15", g_engine },
		{ "8B 15 ? ? ? ? 85 D2 8B 35", g_engine },
		{ "FF 35 ? ? ? ? 8B 3E", g_engine },
		{ "55 8B EC 53 56 8B 75 ? 8B CE 57 FF 75 ? E8", g_client },
		{ "55 8B EC B8 88 20 00 00", g_engine },
		{ "55 8B EC 8B 45 ? 56 57 8B F9 83 EC", g_engine },
		{ "55 8B EC 53 56 8B 75 ? 57 8B F9 89 77", g_engine },
		//{ "83 B9 ? ? ? ? ? 7E ? 69 91 ? ? ? ? ? ? ? ? 8B 81 ? ? ? ? 83 C0", g_engine },
	};

	for ( auto& i : signatures ) {
		auto pattern = i.module->Scan( i.pattern );

		if ( !pattern.address_ ) {
			error( "failed to find signature for pattern {}", i.pattern );
		}

		info( "found signature for pattern hash {} at {}", RT_HASH( i.pattern ), ( void* )pattern.address_ );

		database.insert( std::make_pair( RT_HASH( i.pattern ), pattern ) );
	}
}

void signatures::end( ) { }
