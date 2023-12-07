if get_option('with_xunit').enabled()
    test_deps = [
        dependency('trilo-xtest-c')
    ]

    test_src = ['xunit_runner.c']
    test_cubes = ['cases']

    foreach cube : test_cubes
        test_src += ['xtest_' + cube + '.c']
    endforeach

    pizza = executable('xcli', test_src, include_directories: dir, dependencies : [test_deps, deps])
    test('Execute project Xunit tests', pizza)

endif
