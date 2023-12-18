deps = [
    dependency('tscl-xcore-c'),
    dependency('tscl-xutil-c')
]
code = files('main.c', 'app.c')

dir = include_directories('.')

executable('app', code,
    dependencies: deps,
    include_directories: dir,
    install: true)
