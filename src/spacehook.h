#pragma once
#include <thread>
#include <chrono>
#include <fcntl.h>
#include <sys/stat.h>

#include "hooker.h"
#include "interfaces.h"
#include "Utils/util.h"

namespace SpaceHook
{
	void SelfShutdown();
	extern char buildID[NAME_MAX];
}
