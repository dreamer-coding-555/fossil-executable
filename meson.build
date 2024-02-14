project('Fossil App', 'c',
    meson_version: '>=1.0.0',
    version: '0.1.0',
    default_options: ['c_std=c18', 'werror=true', 'buildtype=minsize'])

deps = [
    dependency('fscl-xcore-c'),
    dependency('fscl-xutil-c'),
    dependency('fscl-xstring-c')
]

subdir('data')
subdir('code')
subdir('test')
