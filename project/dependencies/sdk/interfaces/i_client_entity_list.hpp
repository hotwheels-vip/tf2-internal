#ifndef WEDNESDAY_WTF_I_CLIENT_ENTITY_LIST_HPP
#define WEDNESDAY_WTF_I_CLIENT_ENTITY_LIST_HPP

#include "../structs/c_base_handle.hpp"

namespace sdk
{
	struct i_client_networkable;
	struct i_client_unknown;
	struct i_client_entity;

	struct i_client_entity_list {
	public:
		// get i_client_networkable interface for specified entity
		virtual i_client_networkable* get_client_networkable( int entnum )                      = 0;
		virtual i_client_networkable* get_client_networkable_from_handle( c_base_handle h_ent ) = 0;
		virtual i_client_unknown* get_client_unknown_from_handle( c_base_handle h_ent )         = 0;

		// note: this function is only a convenience wrapper.
		// it returns get_client_networkable( entnum )->get_i_client_entity().
		virtual i_client_entity* get_client_entity( int entnum )                      = 0;
		virtual i_client_entity* get_client_entity_from_handle( c_base_handle h_ent ) = 0;

		// returns number of entities currently in use
		virtual int number_of_entities( bool b_include_non_networkable ) = 0;

		// returns highest index actually used
		virtual int get_highest_entity_index( void ) = 0;

		// sizes entity list to specified size
		virtual void set_max_entities( int maxents ) = 0;
		virtual int get_max_entities( )              = 0;

		// fo' da cultua!
		template< class T >
		T* get( const std::uint32_t& index )
		{
			return ( T* )get_client_entity( index );
		}

		template< class T >
		T* get( c_base_handle handle )
		{
			return ( T* )get_client_entity_from_handle( handle );
		}
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_I_CLIENT_ENTITY_LIST_HPP
