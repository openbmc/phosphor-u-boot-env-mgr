systemd = dependency('systemd')
systemd_system_unit_dir = systemd.get_variable(
    'systemdsystemunitdir',
    pkgconfig_define: ['prefix', get_option('prefix')],
)

unit_files = [
    ['phosphor-u-boot-env-mgrd', 'xyz.openbmc_project.U_Boot.Environment.Manager.service'],
    ['devtree-nodesd', 'xyz.openbmc_project.U_Boot.Environment.DevTreeNodesd.service'],
]

fs = import('fs')
foreach tuple : unit_files
    if get_option(tuple[0]).allowed()
        fs.copyfile(
            tuple[1],
            install: true,
            install_dir: systemd_system_unit_dir,
        )
    endif
endforeach