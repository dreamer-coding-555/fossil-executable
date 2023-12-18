deps = [
    dependency('tscl-xcore-c'),
    dependency('tscl-xutil-c')
]
code = import('sourceset').source_set()
code.add(files('main.c', 'app.c'))

dir = include_directories('.')

executable('app', code.sources(),
    dependencies: deps,
    include_directories: dir,
    install: true)
