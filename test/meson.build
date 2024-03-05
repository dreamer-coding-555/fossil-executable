if get_option('with_test').enabled()
    test_deps = [
        dependency('fscl-xtest-c')
    ]

    test_src = ['xunit_runner.c']
    test_cubes = ['cases']

    foreach cube : test_cubes
        test_src += ['xtest_' + cube + '.c']
    endforeach

    pizza = executable('xcli', [test_src, ss.sources()], include_directories: dir, dependencies : [test_deps, app_dep])
    test('Execute project Xunit tests', pizza)

endif
