Environment(
    CCFLAGS=['-s', '-O3'],
)
SConscript('client.sconscript.py', duplicate=False)
SConscript('library.sconscript.py', duplicate=False)
