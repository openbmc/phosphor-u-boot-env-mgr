/*
// Copyright (c) 2024 Hewlett Packard Enterprise
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/

#pragma once

#include <sdbusplus/async.hpp>
#include <xyz/openbmc_project/MachineContext/aserver.hpp>

#include <map>
#include <vector>

static constexpr const char* node_base_path = "/proc/device-tree/";

enum SupportedNodes
{
    model,
    serial_number,
    local_mac_address,
    mac_address
};

// map nodes to their path relative to node_base_path
static const std::map<SupportedNodes, std::string> node_paths = {
    {SupportedNodes::model, "model"},
    {SupportedNodes::serial_number, "serial-number"},
    {SupportedNodes::local_mac_address, "local-mac-address"},
    {SupportedNodes::mac_address, "mac-address"}};

class MachineContext :
    public sdbusplus::aserver::xyz::openbmc_project::MachineContext<
        MachineContext>
{
  public:
    explicit MachineContext(sdbusplus::async::context& ctx, auto path) :
        sdbusplus::aserver::xyz::openbmc_project::MachineContext<
            MachineContext>(ctx, path)
    {
        populateMachineContext();
    }

    void populateMachineContext();

    std::vector<uint8_t> bytesToDBusVec(char* byte_buffer, int buffer_size);
};
