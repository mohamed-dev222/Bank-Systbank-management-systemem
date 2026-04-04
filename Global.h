#pragma once
/*
 * This file contains global variables and definitions for the application.
 */
#include <iostream>
#include "Models/clsUser.h"
clsUser CurrentUser = clsUser::Find("", "");
