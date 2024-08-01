#ifndef _DCHESS_EXCEPTIONS_HPP_
#define _DCHESS_EXCEPTIONS_HPP_

#include<stdexcept>
#include<string>

namespace dchess {
using string = std::string;
using logic_error = std::logic_error;

class illegal_move : public logic_error {
public:
	using logic_error::what;
	illegal_move(const string& what_arg) :
		logic_error(what_arg) {};
	illegal_move(const char* what_arg) :
		logic_error(what_arg) {};
};

class illegal_turn : public logic_error {
public:
	using logic_error::what;
	illegal_turn(const string& what_arg) :
		logic_error(what_arg) {};
	illegal_turn(const char* what_arg) :
		logic_error(what_arg) {};
};

class illegal_place : public logic_error {
public:
	using logic_error::what;
	illegal_place(const string& what_arg) :
		logic_error(what_arg) {};
	illegal_place(const char* what_arg) :
		logic_error(what_arg) {};
};

}

#endif // !_DCHESS_EXCEPTIONS_HP_
