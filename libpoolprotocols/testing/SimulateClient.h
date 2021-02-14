#pragma once

#include <iostream>

#include <libdevcore/Worker.h>
#include <libvapcore/VapashAux.h>
#include <libvapcore/Farm.h>
#include <libvapcore/Miner.h>

#include "../PoolClient.h"

using namespace std;
using namespace dev;
using namespace vap;

class SimulateClient : public PoolClient, Worker
{
public:
    SimulateClient(unsigned const& block);
    ~SimulateClient() override;

    void connect() override;
    void disconnect() override;

    bool isPendingState() override { return false; }
    string ActiveEndPoint() override { return ""; };

    void submitHashrate(uint64_t const& rate, string const& id) override;
    void submitSolution(const Solution& solution) override;

private:

    void workLoop() override;
    unsigned m_block;
    std::chrono::steady_clock::time_point m_start_time;

    float hr_alpha = 0.45f;
    float hr_max = 0.0f;
    float hr_mean = 0.0f;
};
