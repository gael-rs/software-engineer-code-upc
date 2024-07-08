#pragma once

template<typename Key, typename Value>
class Entidad {
private:	
	Key key;
	Value value;
public:
	Entidad(Key key, Value value) {
		this->key = key;
		this->value = value;
	}
	Key getKey() { return key; }
	Value getValue() { return value; }
};
