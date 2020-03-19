#pragma once
#include "token.h"
class Token_stream {
public:
	Token_stream();   
	Token get();      
	void putback(Token t);    
private:
	bool full;        
	Token buffer;     
};
