//
//  node_delete.h
//  junk
//
//  Created by Lee Barney on 10/20/18.
//  Copyright © 2018 Lee Barney. All rights reserved.
//

#ifndef unit_testing_delete_h
#define unit_testing_delete_h

#include <cstdlib>//linux g++ compiler support


#ifdef UNIT_TESTING
//This global int variable is used to track calls to delete for unit testing purposes only.
int unit_testing_delete_call_counter = 0;
//overloading the delete operator globally.
//DON'T EDIT THIS CODE!! IF YOU DO, YOU WILL HATE LIFE.
#ifdef __APPLE__
void operator delete(void * p) _NOEXCEPT
#else
void operator delete(void * p)
#endif
{
    free(p);
    unit_testing_delete_call_counter++;
}
#endif

#endif /* unit_testing_delete_h */
