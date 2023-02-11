#pragma once

#include "../enums/class_ids.hpp"

namespace sdk
{
	enum should_transmit_state_t;
	enum data_update_type_t;

	struct i_client_unknown;
	struct client_class;
	class bf_read;

	struct i_client_networkable {
	public:
		// gets at the containing class...
		virtual i_client_unknown* get_i_client_unknown( ) = 0;

		// called by the engine when the server deletes the entity.
		virtual void release( ) = 0;

		// supplied automatically by the implement_clientclass macros.
		virtual client_class* get_client_class( ) = 0;

		// this tells the entity what the server says for should_transmit on this entity.
		// note: this used to be entity_entered_pvs/entity_remained_in_pvs/entity_left_pvs.
		virtual void notify_should_transmit( should_transmit_state_t state ) = 0;

		//
		// note for entity writers:
		//
		// in 90% of the cases, you should hook on_pre_data_changed/on_data_changed instead of
		// pre_data_update/post_data_update.
		//
		// the data_changed events are only called once per frame whereas pre/post_data_update
		// are called once per packet (and sometimes multiple times per frame).
		//
		// on_data_changed is called during simulation where entity origins are correct and
		// attachments can be used. whereas post_data_update is called while parsing packets
		// so attachments and other entity origins may not be valid yet.
		//

		virtual void on_pre_data_changed( data_update_type_t update_type ) = 0;
		virtual void on_data_changed( data_update_type_t update_type )     = 0;

		// called when data is being updated across the network.
		// only low-level entities should need to know about these.
		virtual void pre_data_update( data_update_type_t update_type )  = 0;
		virtual void post_data_update( data_update_type_t update_type ) = 0;

		// objects become dormant on the client if they leave the pvs on the server.
		virtual bool is_dormant( void ) = 0;

		// ent index is the server handle used to reference this entity.
		// if the index is < 0, that indicates the entity is not known to the server
		virtual int entindex( void ) const = 0;

		// server to client entity message received
		virtual void receive_message( int class_id, bf_read& msg ) = 0;

		// get the base pointer to the networked data that get_client_class->m_p_recv_table starts at.
		// (this is usually just the "this" pointer).
		virtual void* get_data_table_base_ptr( ) = 0;

		// tells the entity that it's about to be destroyed due to the client receiving
		// an uncompressed update that's caused it to destroy all entities & recreate them.
		virtual void set_destroyed_on_recreate_entities( void ) = 0;

		virtual void on_data_unchanged_in_pvs( ) = 0;
	};
} // namespace sdk
