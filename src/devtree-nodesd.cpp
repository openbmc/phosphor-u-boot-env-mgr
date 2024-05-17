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

#include "devtree-nodesd.hpp"

#include <boost/process/child.hpp>
#include <boost/process/io.hpp>
#include <phosphor-logging/elog-errors.hpp>
#include <phosphor-logging/log.hpp>
#include <xyz/openbmc_project/Common/error.hpp>

#include <fstream>
#include <vector>

DevTreeNodesDaemon::DevTreeNodesDaemon(
    boost::asio::io_service& io_, sdbusplus::asio::object_server& srv_,
    std::shared_ptr<sdbusplus::asio::connection>& conn_) :
    io(io_),
    server(srv_), conn(conn_)
{
    // Check if these device-tree nodes are present and populated
    // supportedNodes pair: <node name, dbus property (display) name>
    std::vector<std::pair<std::string, std::string>> supportedNodes = {
        {"model", "model"},
        {"local-mac-address", "mac1"},
        {"mac-address", "mac2"},
        {"serial-number", "serial-number"}};

    iface = server.add_interface(MachineContextPath, MachineContextIface);

    // iterate over supported nodes
    for (std::pair<std::string, std::string> nodeData : supportedNodes)
    {
        std::string nodeRelativePath = nodeData.first;
        std::string nodeFullPath = nodeBasePath + nodeRelativePath;
        std::string nodeValue;

        std::ifstream fruStream;
        fruStream.open(nodeFullPath);
        if (!fruStream || !std::getline(fruStream, nodeValue))
            continue;

        // dtree node was sucessfully read, write the data to dbus under given
        // property name
        std::string dBuspropertyName = nodeData.second;
        iface->register_property(dBuspropertyName, nodeValue);
    }

    iface->initialize(true);
}

int main()
{
    boost::asio::io_service io;
    auto conn = std::make_shared<sdbusplus::asio::connection>(io);
    conn->request_name(MachineContextServiceName);
    sdbusplus::asio::object_server server(conn);

    DevTreeNodesDaemon devTreeNodesDaemon(io, server, conn);

    io.run();

    return 0;
}
