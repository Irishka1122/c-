#pragma once
#include "token_stream.h"
double expression(Token_stream &ts);
double primary(Token_stream& ts);
double term(Token_stream& ts);