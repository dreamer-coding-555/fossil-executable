code = files('app.c')

deps = [
    dependency('trilo-xcore-c'),
    dependency('trilo-xtype-c'),
    dependency('trilo-xdata-c'),
    dependency('trilo-xmath-c')
]

dir = include_directories('.')

executable('app', ['main.c', code],
    dependencies: deps,
    include_directories: dir,
    install: true)
