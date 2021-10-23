CONFIG_BUILD = {
    'release': lambda env: env.Environment(
        CCFLAGS=['-g', '-O0'],
    ),
    'debug': lambda env: env.Environment(
        CCFLAGS=['-O3', '-s'],
    )
}

TARGET_BUILD = {
    'library': lambda env: env.Environment(
            CPPPATH=['src/include']
        ).SharedLibrary(
            target='chattor',
            source=Glob('src/library/*.c'),
        ),
    'client': lambda env: env.Environment(
            CPPPATH=['src/include']
        ).Program(
            target='chattor',
            source=Glob('src/client/*.c') + Glob('src/library/*.c'),
        ),
    'test': lambda env: env.Environment(
            CPPPATH=['src/include']
        ).Program(
            target='chattor',
            source=Glob('src/test/*.c') + Glob('src/library/*.c'),
        ),
}

DEFAULT = ('release', 'client')

env = Environment()
builds = {}
for cfg_name, cfg_build in CONFIG_BUILD.items():
    config = {}
    config_env = cfg_build(env)
    for tgt_name, tgt_build in TARGET_BUILD.items():
        config[tgt_name] = tgt_build(config_env)
    builds[cfg_name] = config
