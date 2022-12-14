#pragma once
#include <nlohmann/json.hh>

struct item {
	template <typename T>
	item( T &value, const std::string& sz, std::vector<item>& items ) {
		this->name = sz;
		this->value = reinterpret_cast<void*>( &value );
		this->type = typeid( T ).name( );

		items.push_back( *this );
	}
	void* value;
	std::string	name;
	std::string type;
};

class c_config {
public:
	bool init( );
	bool load( const std::string& content );
	bool save( );
private:
	std::vector< item > m_items;
};

extern c_config config;