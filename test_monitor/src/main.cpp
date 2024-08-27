#include <memory>
#include <thread>
#include <vector>

#include "client/rpc_client.h"
#include "monitor/cpu_load_monitor.h"
#include "monitor/cpu_softirq_monitor.h"
#include "monitor/cpu_stat_monitor.h"
#include "monitor/mem_monitor.h"
#include "monitor/monitor_inter.h"
#include "monitor/net_monitor.h"

#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

int main(){
    std::vector<std::shared_ptr<monitor::MonitorInter>> runners;
    runners.emplace_back(new monitor::CpuSoftIrqMonitor());
    runners.emplace_back(new monitor::CpuLoadMonitor());
    runners.emplace_back(new monitor::CpuStatMonitor());
    runners.emplace_back(new monitor::MemMonitor());
    runners.emplace_back(new monitor::NetMonitor());

    monitor::RpcClient rpc_client;

    char *name = getenv("USER");

    std::unique_ptr<std::thread> thread = nullptr;
    thread = std::make_unique<std::thread>([&](){
        while(true){
            monitor::proto::MonitorInfo monitor_info;
            monitor_info.set_name(std::string(name));
            for (auto& runner : runners) {
                runner->UpdateOnce(&monitor_info);
            }

            rpc_client.SetMonitorInfo(monitor_info);
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
    );

    thread->join();
    return 0;
}