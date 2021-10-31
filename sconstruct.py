if __name__ == '__main__':
    import os
    print("This is *supposed* to be a scons script.")
    os.chdir(os.path.dirname(__file__))
    os.execvp('scons', ['scons'])


def start_env(mode, target):
    e = Environment(
        CFLAGS='-std=c11'
    )
    new_src = f'build/{mode}/{target}/'
    e.VariantDir(new_src, 'src', duplicate=False)
    return e, new_src


MODES = {
    'release': lambda env: env.Environment(
        CCFLAGS=['-g', '-O0'],
    ),
    'debug': lambda env: env.Environment(
        CCFLAGS=['-O3', '-s'],
    )
}

TARGETS = {
    'library': lambda env, src: env.Environment(
            CPPPATH=[f'{src}/include']
        ).SharedLibrary(
            target=f'{src}/../chattor',
            source=Glob(f'{src}/library/*.c'),
        ),
    'client': lambda env, src: env.Environment(
            CPPPATH=[f'{src}/include']
        ).Program(
            target=f'{src}/../chattor',
            source=Glob(f'{src}/client/*.c') + Glob(f'{src}/library/*.c'),
        ),
    'test': lambda env, src: env.Environment(
            CPPPATH=[f'{src}/include']
        ).Program(
            target=f'{src}/../chattor-lib-test',
            source=Glob(f'{src}/test/*.c') + Glob(f'{src}/library/*.c'),
        ),
}

AddOption('--mode',
          type="choice", choices=list(MODES), default='debug')
AddOption('--target',
          type="choice", choices=list(TARGETS), default='client')

mode = GetOption('mode')
target = GetOption('target')

env, src = start_env(mode, target)
moded = MODES[mode](env)
targeted = TARGETS[target](moded, src)
Default(targeted)
