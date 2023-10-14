code = files('app.c')

deps = [
    dependency('trilo-xcore-c'),
    dependency('trilo-xdata-c')
]

executable('app', ['main.c', code],
    dependencies: deps,
    include_directories: '.',
    install: true)