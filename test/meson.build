if get_option('with_xunit').enabled()
    test_deps = [
        dependency('tscl-xtest-c')
    ]

    test_src = ['xunit_runner.c']
    test_cubes = ['cases']

    foreach cube : test_cubes
        test_src += ['xtest_' + cube + '.c']
    endforeach

    pizza = executable('xcli', test_src, include_directories: dir, dependencies : [test_deps, app_dep])
    test('Execute project Xunit tests', pizza)

endif
