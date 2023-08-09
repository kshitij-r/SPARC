#ifndef SYSHEAD
#define SYSHEAD
#ifndef __clang__
#include <thread>
#include <iostream>
#endif
#include <stdlib.h>
#include <cstdarg>
#include <string>
#include <assert.h>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <queue>
#include <set>
#include <list>
#include <map>
#include "guard.h"
#include "interface.cpp"
#include "baseIP.cpp"
#include "slave_config.cpp"
// #include "master_config.cpp"
#include "resetController.cpp"
#include "timerController.cpp"
#include "crcController.cpp"
#include "softwareController.cpp"
#endif
