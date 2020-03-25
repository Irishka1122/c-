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
		return t.value; 
	case 'q': {ts.putback(t); return 0; }

	default:
		error("primary expected");
	}
}

double fuckt(Token_stream& ts) {
	double left = primary(ts);
	Token t = ts.get();
	int k = 1;
	while (true) {
		switch (t.kind)
		{
		case '!': {
			if (left == 0)return 0;
			else {
				k = 1;
				for (int i = 1;i <= left;i++) { k *= i; }
				left = k;
				t = ts.get();break;
			}
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}//------------------------------------------------------------------------------

// deal with *, /, and %
double term(Token_stream& ts)
{
	double left = fuckt(ts);
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