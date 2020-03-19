#include "std_lib_facilities.h"
#include "grammar.h"
#include "token.h"
#include "token_stream.h"

double primary(Token_stream& ts)
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':    // handle '(' expression ')'
	{
		double d = expression(ts);
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case '8':
		//if (t.kind == '!') {
		//	if (t.value == 0)return 1;
		//}
		//else
		//{
		//
		//}
		return t.value; 
	case 'q': {ts.putback(t); return 0; }

	default:
		error("primary expected");
	}
}

//------------------------------------------------------------------------------

// deal with *, /, and %
double term(Token_stream& ts)
{
	double left = primary(ts);
	Token t = ts.get();        

	while (true) {
		switch (t.kind) {
		case '*': {
			left *= primary(ts);
			t = ts.get(); break; }
		case '/':
		{
			double d = primary(ts);
			if (d == 0) error("divide by zero");
			left /= d;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);     
			return left;
		}
	}
}

//------------------------------------------------------------------------------

// deal with + and -
double expression(Token_stream& ts)
{
	double left = term(ts);      
	Token t = ts.get();        

	while (true) {
		switch (t.kind) {
		case '+':
			left += term(ts);    
			t = ts.get();
			break;
		case '-':
			left -= term(ts);    
			t = ts.get();
			break;
		default:
			ts.putback(t);     
			return left;       
		}
	}
}