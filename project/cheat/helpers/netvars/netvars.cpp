#include "netvars.hpp"

#include "../interfaces/interfaces.hpp"

#include <sdk/include.hpp>

std::uint32_t netvars::get_offset( sdk::recv_table* table, const char* netvar_name )
{
	for ( auto i = 0; i < table->nprops; i++ ) {
		auto prop = &table->props[ i ];

		if ( RT_HASH( prop->var_name ) == RT_HASH( netvar_name ) )
			return prop->offset;

		auto child = prop->data_table;

		if ( child ) {
			auto offset = get_offset( child, netvar_name );

			if ( offset )
				return offset + prop->offset;
		}
	}

	return 0x0;
}

std::uint32_t netvars::get_table( const char* table_name, const char* netvar_name )
{
	auto client = g_interfaces->client;

	if ( !client )
		return 0x0;

	auto client_class = client->get_all_classes( );

	if ( !client_class )
		return 0x0;

	for ( auto class_ = client_class; class_; class_ = class_->next ) {
		if ( RT_HASH( class_->network_name ) == RT_HASH( table_name ) )
			return get_offset( class_->recv_table, netvar_name );
	}

	return 0x0;
}
