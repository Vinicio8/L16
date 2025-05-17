#pragma once
#include <iostream>
#include <chrono>
#include <thread>

class ProgressBar {
public:
    ProgressBar(const std::string& name) : name_(name) {}
    void setMax(size_t max) { max_ = max; }
    void start() { std::cout << name_ << " [0%]\r"; }
    void tick() {
        progress_++;
        int percent = static_cast<int>(100 * progress_ / max_);
        std::cout << name_ << " [" << percent << "%]\r";
    }
    void finish() { std::cout << std::endl; }
private:
    std::string name_;
    size_t max_ = 100;
    size_t progress_ = 0;
};
