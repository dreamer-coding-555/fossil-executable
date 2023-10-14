if get_option('with_xunit').enabled()
    test_deps = [
        dependency('trilo-xtest-c'),
        dependency('trilo-xmock-c')
    ]
    test_src = files(
        'xtest_cases.c',
        'xunit_runner.c'
    )

    test('Execute project Xunit tests',
        executable('xrunner',
        test_src,
        include_directories: include_directories(meson.project_source_root() / 'code'),
        dependencies : [test_deps, deps]))
endif