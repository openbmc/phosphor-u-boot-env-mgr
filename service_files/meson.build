systemd = dependency('systemd')
systemd_system_unit_dir = systemd.get_variable(
    'systemdsystemunitdir',
    pkgconfig_define: ['prefix', get_option('prefix')],
)

unit_files = [
    ['phosphor-u-boot-env-mgrd', 'xyz.openbmc_project.U_Boot.Environment.Manager.service'],
    ['dt-vpd-parsed', 'xyz.openbmc_project.DeviceTree.VPD.Parser.service'],
]

fs = import('fs')
foreach tuple : unit_files
        fs.copyfile(
            tuple[1],
            install: true,
            install_dir: systemd_system_unit_dir,
        )
endforeach
