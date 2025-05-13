// Copyright 2013 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include <fstream>
#include <sstream>
#include <string>

#include "Common/CommonTypes.h"
#include "Common/FileUtil.h"

static int CPUDetectFastestCore(int num_cores)
{
  int fastest_core = 0;
  u32 fastest_freq = 0;
#ifdef __linux__
  std::ostringstream ss;
  for (int i = 0; i < num_cores; i++)
  {
    ss.str("/sys/devices/system/cpu/cpu");
    ss << i << "/cpufreq/cpuinfo_max_freq";

    std::ifstream file;
    File::OpenFStream(file, ss.str(), std::ios_base::in);
    if (!file)
      continue;

    u32 freq;
    file >> freq;
    if (freq > fastest_freq)
    {
      fastest_freq = freq;
      fastest_core = i;
    }
  }
#else
  // TODO
#endif
  return fastest_core;
}
