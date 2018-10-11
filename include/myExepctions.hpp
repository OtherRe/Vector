#ifndef MY_EXEPCTIONS_HPP
#define MY_EXEPCTIONS_HPP
#include <exception>


class NotImplementedExepction: public std::exception {
    virtual const char* what() const throw(){
        return "Function was not implemented";
    }
};

// struct MyException : public std::exception
// {
// 	const char * what () const throw ()
//     {
//     	return "C++ Exception";
//     }
// };

#endif