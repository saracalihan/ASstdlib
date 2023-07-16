/*
 * Copyright (c) 2023, Alihan SARAÇ <saracalihan@gmail.com>
 *
 * This file is under the "MIT" license. Please read "LICENSE" file for more detail.
 */

#pragma once
#include <assert.h>
#include <cstdio>
#include <iostream>

#define ASSERT(exp) assert(exp)
#define NOT_IMPLEMENTED cerr<< "[ NOT IMPLEMENTED ] " << __func__ << ":" << __LINE__ << " at " <<__FILE__ <<"\n"; abort()
#define  DO_NOT_RUN_HERE() cerr<< "[ DO NOT RUN HERE ] "<<__func__ <<":"<<__LINE__<< " at "<<__FILE__<<"\n"; abort()
