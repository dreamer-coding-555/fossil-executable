code = files('app.c')

deps = [
    dependency('trilo-xcore-c'),
    dependency('trilo-xdata-c'),
    dependency('sdl2')
]

dir = include_directories('.')

executable('app', ['main.c', code],
    dependencies: deps,
    include_directories: dir,
    install: true)
