﻿
#include "std_lib_facilities.h"
#include "token.h"
#include "token_stream.h"
#include "grammar.h"
Token_stream ts;       
  
int main()
try
{
	double val;
    while (cin) {
        Token t = ts.get();
        if (t.kind == 'q') break; // 'q' for quit
        if (t.kind == ';')        // ';' for "print now"
            cout << "=" << val << '\n';
        else
            ts.putback(t);
		val = expression(ts);
    }
    keep_window_open();
}
catch (exception & e) {
    cerr << "error: " << e.what() << '\n';
    keep_window_open();
    return 1;
}
catch (...) {
    cerr << "Oops: unknown exception!\n";
    keep_window_open();
    return 2;
}

//------------------------------------------------------------------------------
