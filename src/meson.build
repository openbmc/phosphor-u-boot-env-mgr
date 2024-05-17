if get_option('phosphor-u-boot-env-mgrd').allowed()
    executable(
        'phosphor-u-boot-env-mgr',
        'u-boot-env-mgr.cpp',
        'mainapp.cpp',
        include_directories : incdir,
        dependencies: default_deps,
        install: true,
    )
endif