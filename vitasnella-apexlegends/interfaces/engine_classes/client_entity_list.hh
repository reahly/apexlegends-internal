#pragma once

struct client_entity_list_t {
	virtual int unk1( ) = 0;
	virtual int unk2( ) = 0;
	virtual int unk3( ) = 0;
	virtual int unk4( ) = 0;
	virtual void* get_client_entity( int idx ) = 0;
	virtual void* get_client_entity_from_handle( uintptr_t handle ) = 0;
	virtual int number_of_entities( bool include_dormant ) = 0;
	virtual int unk5( ) = 0;
	virtual int get_highest_entity_index( ) = 0;
	virtual void set_max_entities( int max ) = 0;
	virtual int get_max_entities( ) = 0;
};
