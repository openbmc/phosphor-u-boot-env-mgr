if get_option('phosphor-u-boot-env-mgrd').allowed()
    executable(
        'phosphor-u-boot-env-mgr',
	'u-boot-env-mgr.hpp',
        'u-boot-env-mgr.cpp',
        'mainapp.cpp',
        dependencies: default_deps,
        install: true,
    )
endif

if get_option('phosphor-u-boot-env-machinecontextd').allowed()
    executable(
        'phosphor-u-boot-env-machinecontextd',
        'machinecontextd.hpp',
	'machinecontextd.cpp',
        dependencies: default_deps,
        install: true,
    )
endif
