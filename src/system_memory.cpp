#include "system_memory.h"

void SystemMemory::UpdateStatistics() {
    memTotal_ = metrics_["MemTotal"].GetValue();
    memFree_ = metrics_["MemFree"].GetValue();
    buffers_ = metrics_["Buffers"].GetValue();
    cached_ = metrics_["Cached"].GetValue() + metrics_["SReclaimable"].GetValue() - metrics_["Shmem"].GetValue();
    swapTotal_ = metrics_["swapTotal"].GetValue();
    swapFree_ = metrics_["swapFree"].GetValue();
}

float SystemMemory::MemoryUtilization() { 
    return (float)(memTotal_ - (cached_ + buffers_)) / (float)memTotal_; 
}