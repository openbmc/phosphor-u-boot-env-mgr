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

#include "machinecontext.hpp"

#include <fstream>
#include <map>

namespace DTParse
{

static constexpr const char* node_base_path = "/proc/device-tree/";

enum SupportedNode
{
    model,
    serial_number
};

// associate nodes with a path relative to node_base_path
static const std::map<SupportedNode, std::string> node_rel_paths = {
    {SupportedNode::model, "model"},
    {SupportedNode::serial_number, "serial-number"}};
}; // namespace DTParse

void MachineContext::populateMachineContext()
{
    using DTNode = DTParse::SupportedNode;

    // walk supported node paths
    for (std::pair<DTNode, std::string> node_data : DTParse::node_rel_paths)
    {
        std::string node_value;

        std::string node_rel_path = node_data.second;
        std::string node_full_path = DTParse::node_base_path + node_rel_path;

        std::ifstream vpd_stream;

        vpd_stream.open(node_full_path);

        if (!vpd_stream || !std::getline(vpd_stream, node_value))
            continue;

        switch (node_data.first)
        {
            case DTNode::model:

                MachineContext::Asset::model(node_value);

                break;

            case DTNode::serial_number:

                MachineContext::Asset::serial_number(node_value);

                break;

            default:
                break;
        }
    }
};
