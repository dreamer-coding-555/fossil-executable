dir = include_directories('.')
ss = import('sourceset').source_set()

ss.add(files('app.c'))

executable('app',
    sources: ['main.c', ss.sources()],
    include_directories: dir,
    dependencies: deps,
    install: true)
