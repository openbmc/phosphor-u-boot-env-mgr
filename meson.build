project(
    'phosphor-u-boot-env-mgr',
    'cpp',
    default_options: [
        'warning_level=3',
        'werror=true',
        'cpp_std=c++20' 	#highly suspect there should be more entries tied to line 4-6 of CMakeLists.txt.old                 
    ],
    license: 'Apache-2.0',
    version: '0.1',
    meson_version: '>=0.64.0',
)
add_project_arguments('-Wno-psabi',          	#no idea what this line is about or where it came from                     
    '-DBOOST_ERROR_CODE_HEADER_ONLY',
    '-DBOOST_SYSTEM_NO_DEPRECATED',
    '-DBOOST_ALL_NO_LIB',
    '-DBOOST_NO_RTTI',
    '-DBOOST_NO_TYPEID',
    '-DBOOST_ASIO_DISABLE_THREADS',
 language: 'cpp')

boost = dependency('boost', version: '>=1.75.0', include_type: 'system', required : true)
sdbusplus = dependency('sdbusplus', include_type: 'system', required : true)
dbusinterface = dependency('phosphor-dbus-interfaces', include_type: 'system', required : true)
phosphor_logging_dep = dependency('phosphor-logging', required : true)

default_deps =[
	boost,
	phosphor_logging_dep,
	sdbusplus,
	dbusinterface,
	]

subdir('src')
subdir('service_files')
