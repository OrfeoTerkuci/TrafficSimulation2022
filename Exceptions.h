//
//  Exceptions.h
//  SimpleCalculator
//
//  Created by Quinten Soetens on 12/02/14.
//  Copyright (c) 2014 Quinten Soetens. All rights reserved.
//

#ifndef SimpleCalculator_Exceptions_h
#define SimpleCalculator_Exceptions_h

#include <exception>

using namespace std;


/**
 * class IllegalArgumentException is a class that is derived from the Standard std::exception class.
 * it is used as an exception when a method/function is called with an illegal argument.
 */
class IllegalArgumentException: public exception{
    
    const char* message;
public:
    /**
     * Constructor for an IllegalArgumentException
     * @param message: the string identifying the actual exception.
     */
    IllegalArgumentException(const char * message){
        this->message = message;
    }
    
    /**
     * Get the string identifying the exception
     * Returns a null terminated character sequence that may be used to identify the exception.
     */
    virtual const char* what() const throw(){
        return message;
    }
};


#endif
