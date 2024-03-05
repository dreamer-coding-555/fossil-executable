dir = include_directories('.')
code = files('app.c')

executable('app',
    sources: ['main.c', code],
    include_directories: dir,
    dependencies: deps,
    install: true)
