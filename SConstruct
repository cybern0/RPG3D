#!/usr/bin/env python

import os
from SCons.Script import Variables, Environment, Exit, Glob, SetOption, Help

# Options
opts = Variables([], ARGUMENTS)
opts.Add(EnumVariable('target', 'Compilation target', 'debug', ['d', 'debug', 'r', 'release']))
opts.Add(EnumVariable('platform', 'Compilation platform', 'windows', ['windows']))
opts.Add(PathVariable('target_path', 'Output directory for libraries', 'demo/bin/'))
opts.Add(BoolVariable('use_lto', 'Enable Link Time Optimization', False))
opts.Add(EnumVariable('optimization', 'Optimization level', '3', ['1', '2', '3', 'size']))  # Par défaut sur 3
opts.Add(BoolVariable('use_clang_cl', 'Use Clang-CL instead of MSVC', False))

# Environnement
env = Environment()
opts.Update(env)

# Vérification plateforme
if env['platform'] != 'windows':
    print("Ce SConstruct est configuré uniquement pour Windows.")
    Exit(1)

# Choix du compilateur
if env['use_clang_cl']:
    env = Environment(tools=['clangxx', 'clang', 'link', 'mslib'])
    env.Append(CXXFLAGS=['-std=c++17'])
else:
    env = Environment(tools=['msvc', 'mslink', 'mslib'])
    env.Append(CXXFLAGS=['/std:c++17'])

opts.Update(env)
Help(opts.GenerateHelpText(env))

# Chemins
target_path = env['target_path'] + 'win64/'
godot_headers_path = 'godot-cpp/godot-headers/'
cpp_bindings_path = 'godot-cpp/'
cpp_library = f'libgodot-cpp.windows.{"debug" if env["target"] in ("debug", "d") else "release"}.64'

# Configuration de base
env.Append(CPPDEFINES=['WIN64', '_WIN64', '_WINDOWS', '_CRT_SECURE_NO_WARNINGS', '__STDC_WANT_SECURE_LIB__=1'])
env.Append(CCFLAGS=['/W3', '/GR', '/EHsc'])
env.Append(CPPPATH=['.', godot_headers_path, cpp_bindings_path + 'include/', cpp_bindings_path + 'include/core/', cpp_bindings_path + 'include/gen/'])
env.Append(LIBPATH=[cpp_bindings_path + 'bin/'])
env.Append(LIBS=[cpp_library])

# Configuration par target
if env['target'] in ('debug', 'd'):
    env.Append(CCFLAGS=['/Zi', '/Od', '/MDd', '/Fd${TARGET}.pdb'])
    env.Append(LINKFLAGS=['/DEBUG:FULL', '/INCREMENTAL:NO'])
else:  # Release
    if env['optimization'] == '1':
        env.Append(CCFLAGS=['/O1'])
    elif env['optimization'] == '2':
        env.Append(CCFLAGS=['/O2'])
    elif env['optimization'] == '3':
        env.Append(CCFLAGS=['/Ox', '/favor:INTEL64'])  # Optimisation pour CPU 64-bit modernes
    elif env['optimization'] == 'size':
        env.Append(CCFLAGS=['/Os'])

    if env['use_lto']:
        env.Append(CCFLAGS=['/GL'])
        env.Append(LINKFLAGS=['/LTCG'])

    env.Append(CCFLAGS=['/MD', '/Gy', '/Gw'])  # /Gw : optimisation des données globales
    env.Append(CPPDEFINES=['NDEBUG'])
    env.Append(LINKFLAGS=['/OPT:REF', '/OPT:ICF'])

    env.Append(CCFLAGS=['/arch:AVX2'])

# Modules
modules = {
    'libCamera': Glob('Camera/*.cpp'),
    'libCoinGold': Glob('CoinGold/*.cpp'),
    'libMusic': Glob('Music/*.cpp'),
    'libPlayer': Glob('Player/*.cpp'),
    'libEnemy': Glob('Enemy/*.cpp'),
    'libUI': Glob('UI/*.cpp')
}

# Création du dossier cible
if not os.path.exists(target_path):
    os.makedirs(target_path)

# Compilation
libraries = []
for lib_name, sources in modules.items():
    if not sources:
        print(f"Erreur : Aucun fichier source trouvé pour {lib_name}")
        Exit(1)
    shared_lib = env.SharedLibrary(
        target=target_path + lib_name,
        source=sources,
        SHLIBSUFFIX='.dll'
    )
    libraries.append(shared_lib)

# Alias et défaut
env.Alias('all', libraries)
env.Default('all')

# Compilation parallèle
SetOption('num_jobs', os.cpu_count())
print(f"Compilation avec {GetOption('num_jobs')} tâches parallèles")