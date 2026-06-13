#pragma once
#include <chrono>
#include <cassert>

class CpuTimer {
public:
    void start()
    {
        startTime = std::chrono::steady_clock::now();
        isRunning = true;
    }
    void stop()
    {
        if(isRunning){
            stopTime = std::chrono::steady_clock::now();
            isRunning = false;
        }
    }
    double milliseconds() const{
        assert(startTime != std::chrono::time_point<std::chrono::steady_clock>{} && "CpuTimer: milliseconds() called before start()");
        auto end = isRunning ? std::chrono::steady_clock::now() : stopTime;
        return std::chrono::duration<double, std::milli>(end - startTime).count();
    }

private:
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    std::chrono::time_point<std::chrono::steady_clock> stopTime;
    bool isRunning = false;
};

class GpuTimer{
public:
    GpuTimer();
    ~GpuTimer();
    void start();                   //cudaEventRecord Start
    void stop();                    //cudaEventRecord Stop
    void sync();                    //cudaEventSyncronise
    float milliseconds() const;    //elapsed time

private:
    //cudaEvent_t startEvent;
    //cudaEvent_t stopEvent;
};
