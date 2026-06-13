#include "../../include/timer.h"

GpuTimer::GpuTimer(){
    cudaEventCreate(&startEvent);
    cudaEventCreate(&stopEvent);
};

GpuTimer::~GpuTimer(){
    cudaEventDestroy(startEvent);
    cudaEventDestroy(stopEvent);
};

void GpuTimer::start()
{
    cudaEventRecord(startEvent);
}
void GpuTimer::stop()
{
    cudaEventRecord(stopEvent);
}                    //cudaEventRecord Stop
void GpuTimer::sync()
{
    cudaEventSynchronize(stopEvent);
}                    //cudaEventSyncronise
float GpuTimer::milliseconds() const
{
    float ms;
    cudaEventElapsedTime(&ms, startEvent, stopEvent);
    return ms;
}    //elapsed time

