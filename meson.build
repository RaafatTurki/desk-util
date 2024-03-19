project('desk-util', 'cpp',
  default_options: 'default_library=static'
)

alsa_dep = dependency('alsa')
argp_dep = dependency('argparse')

executable('bin', [
  './src/main.cpp',

  './src/utils/alsa.cpp',
  './src/utils/utils.cpp',
  ],
  dependencies: [
    argp_dep,
    alsa_dep,
  ],
)
