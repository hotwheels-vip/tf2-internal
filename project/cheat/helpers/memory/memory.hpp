#pragma once

#include "../console/console.hpp"

#include <Windows.h>
#include <hash/hash.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>

class memory
{
public:
	struct address {
		std::uintptr_t address_{ };

		address( ) = default;
		address( std::uintptr_t address_ ) : address_( address_ ) { }
		address( void* address_ ) : address_( reinterpret_cast< std::uintptr_t >( address_ ) ) { }

		operator std::uintptr_t( )
		{
			return address_;
		}

		operator void*( )
		{
			return reinterpret_cast< void* >( address_ );
		}

		template< typename T = address >
		T to( )
		{
			return *reinterpret_cast< T* >( address_ );
		}

		template< typename T = address >
		T as( )
		{
			return ( T )( address_ );
		}

		template< typename T = address >
		T at( std::ptrdiff_t offset )
		{
			return *reinterpret_cast< T* >( address_ + offset );
		}

		template< typename T = address >
		T add( std::ptrdiff_t offset )
		{
			return ( T )( address_ + offset );
		}

		template< typename T = address >
		T sub( std::ptrdiff_t offset )
		{
			return ( T )( address_ - offset );
		}

		template< typename T = address >
		T get( std::size_t dereference = 1 )
		{
			for ( std::size_t i = 0; i < dereference; i++ )
				address_ = *reinterpret_cast< std::uintptr_t* >( address_ );

			return ( T )( address_ );
		}

		template< typename T = address >
		void set( T& value )
		{
			*reinterpret_cast< T* >( address_ ) = value;
		}

		template< typename T = address >
		T relative( std::ptrdiff_t offset )
		{
			std::uintptr_t address       = address_ + offset;
			std::int32_t relative_offset = *reinterpret_cast< std::int32_t* >( address );

			return reinterpret_cast< T >( address + relative_offset + sizeof( std::int32_t ) );
		}
	};

	std::uintptr_t find_pattern( std::uint8_t* region_start, std::uintptr_t region_size, const char* pattern );

	std::vector< int > pattern_to_bytes( const char* pattern );
};

inline memory* g_memory = new memory( );

class modules
{
public:
	struct module {
		std::string module_name{ };
		HMODULE module_{ };

		module( std::string module_name ) :module_name( module_name )
		{
			while ( !module_ ) {
				module_ = GetModuleHandleA( module_name.data( ) );
			}
		}

		memory::address scan( std::string_view pattern )
		{
			std::uint8_t* module_address = reinterpret_cast< std::uint8_t* >( module_ );
			PIMAGE_DOS_HEADER dos_header = reinterpret_cast< PIMAGE_DOS_HEADER >( module_address );
			PIMAGE_NT_HEADERS nt_headers = reinterpret_cast< PIMAGE_NT_HEADERS >( module_address + dos_header->e_lfanew );

			return g_memory->find_pattern( module_address, nt_headers->OptionalHeader.SizeOfImage, pattern.data( ) );
		}
	};

	bool run( );
	bool end( );
};

inline modules* g_modules = new modules( );
inline modules::module* g_client{ };
inline modules::module* g_engine{ };
inline modules::module* g_shaderapidx9{ };
inline modules::module* g_server{ };

class virtuals
{
public:
	std::uintptr_t* get_virtual_table( void* address_ );
	std::uintptr_t* get_virtual_function( void* address_, std::size_t index );
};

inline virtuals* g_virtuals = new virtuals( );

class signatures
{
public:
	bool run( );
	bool end( );
};

class database
{
public:
	struct signature {
		const char* pattern{ };
		modules::module* module{ };
	};

	std::unordered_map< std::uint32_t, memory::address > database_{ };

	memory::address operator[]( std::uint32_t pattern )
	{
		return database_[ pattern ];
	}
};

inline database g_database{ };
inline signatures* g_signatures = new signatures{ };
