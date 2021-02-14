/*
This file is part of vapminer.

vapminer is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

vapminer is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with vapminer.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <libdevcore/Worker.h>
#include <libvapcore/VapashAux.h>
#include <libvapcore/Miner.h>

#include <functional>

namespace dev
{
namespace vap
{
class CPUMiner : public Miner
{
public:
    CPUMiner(unsigned _index, CPSettings _settings, DeviceDescriptor& _device);
    ~CPUMiner() override;

    static unsigned getNumDevices();
    static void enumDevices(std::map<string, DeviceDescriptor>& _DevicesCollection);

    void search(const dev::vap::WorkPackage& w);

protected:
    bool initDevice() override;
    bool initEpoch_internal() override;
    void kick_miner() override;

private:
    atomic<bool> m_new_work = {false};
    void workLoop() override;
    CPSettings m_settings;
};


}  // namespace vap
}  // namespace dev
