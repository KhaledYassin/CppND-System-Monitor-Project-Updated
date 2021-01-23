#include "processor.h"

Processor::Processor(const std::string name) { name_ = name; }

const std::string Processor::EnumStrings[] = {
    "user", "nice",    "system", "idle",  "iowait",
    "irq",  "softirq", "steal",  "guest", "guest_nice"};

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { return cpu_utilization_; }

long Processor::TotalIdle() { return idle_ + iowait_; }
long Processor::TotalNonIdle() { return user_ + nice_ + system_ + irq_ + softirq_ + steal_; }

void Processor::UpdateStatistics() {
    long prev_idle = TotalIdle();
    long prev_non_idle = TotalNonIdle();
    long prev_total = prev_idle + prev_non_idle;

    user_ = metrics_[EnumStrings[kUser_]].GetValue();
    nice_ = metrics_[EnumStrings[kNice_]].GetValue();
    system_ = metrics_[EnumStrings[kSystem_]].GetValue();
    idle_ = metrics_[EnumStrings[kIdle_]].GetValue();
    iowait_ = metrics_[EnumStrings[kIOwait_]].GetValue();
    irq_ = metrics_[EnumStrings[kIRQ_]].GetValue();
    softirq_ = metrics_[EnumStrings[kSoftIRQ_]].GetValue();
    steal_ = metrics_[EnumStrings[kSteal_]].GetValue();
    guest_ = metrics_[EnumStrings[kGuest_]].GetValue();
    guest_nice = metrics_[EnumStrings[kGuestNice_]].GetValue();

    long idle = TotalIdle();
    long non_idle = TotalNonIdle();
    long total = idle + non_idle;

    long totald = total - prev_total;
    long idled = idle - prev_idle;

    cpu_utilization_ = (float)(totald - idled) / (float)totald;
}