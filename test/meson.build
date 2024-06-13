if get_option('with_test').enabled()
    run_command(['python3', 'generate-runner.py'], check: true)

    test_src = ['xunit_runner.c']
    test_cubes = ['cases']

    foreach cube : test_cubes
        test_src += ['xtest_' + cube + '.c']
    endforeach

    pizza = executable('runner',
        [test_src, code],
        include_directories: dir,
        dependencies : [dependency('fossil-test'), deps])
    test('Execute project Fossil tests', pizza)
endif
