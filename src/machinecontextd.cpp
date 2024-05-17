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

#include "machinecontextd.hpp"

#include <fstream>

void MachineContext::populateMachineContext()
{
    int mac_buffer_size = 6;

    // walk supported node paths
    for (std::pair<SupportedNodes, std::string> node_data : node_paths)
    {
        std::string node_value_str;

        char* mac_buffer_bytes;
        std::vector<uint8_t> node_value_bytes;

        std::string node_rel_path = node_data.second;
        std::string node_full_path = node_base_path + node_rel_path;

        std::ifstream vpd_stream;

        switch ((SupportedNodes)node_data.first)
        {
            case SupportedNodes::model:

                vpd_stream.open(node_full_path);

                if (!vpd_stream || !std::getline(vpd_stream, node_value_str))
                    continue;

                MachineContext::model(node_value_str);

                break;

            case SupportedNodes::serial_number:

                vpd_stream.open(node_full_path);

                if (!vpd_stream || !std::getline(vpd_stream, node_value_str))
                    continue;

                MachineContext::serial_number(node_value_str);

                break;

            case SupportedNodes::mac_address:

                vpd_stream.open(node_full_path, std::fstream::binary);

                if (!vpd_stream)
                    continue;

                mac_buffer_bytes = new char[mac_buffer_size];

                if (!vpd_stream.read(mac_buffer_bytes, mac_buffer_size))
                    continue;

                node_value_bytes = bytesToDBusVec(mac_buffer_bytes,
                                                  mac_buffer_size);
                MachineContext::mac_address(std::move(node_value_bytes));

                break;

            case SupportedNodes::local_mac_address:

                vpd_stream.open(node_full_path, std::fstream::binary);

                if (!vpd_stream)
                    continue;

                mac_buffer_bytes = new char[mac_buffer_size];

                if (!vpd_stream.read(mac_buffer_bytes, mac_buffer_size))
                    continue;

                node_value_bytes = bytesToDBusVec(mac_buffer_bytes,
                                                  mac_buffer_size);
                MachineContext::local_mac_address(std::move(node_value_bytes));

                break;

            default:
                break;
        }
    }
};

std::vector<uint8_t> MachineContext::bytesToDBusVec(char* byte_buffer,
                                                    int buffer_size)
{
    std::vector<uint8_t> byte_vec;

    for (int i = 0; i < buffer_size; i++)
    {
        byte_vec.push_back(byte_buffer[i]);
    }

    return byte_vec;
}

int main()
{
    constexpr auto path = MachineContext::instance_path;
    sdbusplus::async::context ctx;

    sdbusplus::server::manager_t manager{ctx, path};
    MachineContext c{ctx, path};

    ctx.spawn([](sdbusplus::async::context& ctx) -> sdbusplus::async::task<> {
        ctx.request_name(MachineContext::default_service);
        co_return;
    }(ctx));

    ctx.run();

    return 0;
}
