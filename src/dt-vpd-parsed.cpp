#include "machinecontext.hpp"

int main()
{
    constexpr auto path = "/xyz/openbmc_project/Inventory/MachineContext";
    sdbusplus::async::context ctx;

    sdbusplus::server::manager_t manager{ctx, path};

    MachineContext c{ctx, path};
    ctx.spawn([](sdbusplus::async::context& ctx) -> sdbusplus::async::task<> {
        ctx.request_name("xyz.openbmc_project.Inventory.MachineContext");
        co_return;
    }(ctx));

    ctx.run();

    return 0;
};
