# libFuzzer targets for the file parsers (#234), built with AddressSanitizer.

set(REXGLUE_FUZZ_SECONDS 60 CACHE STRING "Seconds each fuzz.<parser> CTest test runs")

add_executable(fuzz_seeds fuzz_seeds.cpp)
target_link_libraries(fuzz_seeds PRIVATE rexruntime)
set_target_properties(fuzz_seeds PROPERTIES RUNTIME_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:rexruntime>)

set(_fuzz_seeds_dir ${CMAKE_CURRENT_BINARY_DIR}/seeds)
add_test(NAME fuzz.seeds COMMAND fuzz_seeds ${_fuzz_seeds_dir})
set_tests_properties(fuzz.seeds PROPERTIES FIXTURES_SETUP fuzz_seeds LABELS "fuzz")

foreach(_parser xex xdbf xdvdfs stfs)
    add_executable(${_parser}_fuzzer ${_parser}_fuzzer.cpp)
    target_include_directories(${_parser}_fuzzer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(${_parser}_fuzzer PRIVATE rexruntime)
    target_link_options(${_parser}_fuzzer PRIVATE -fsanitize=fuzzer)
    set_target_properties(${_parser}_fuzzer PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:rexruntime>)

    set(_corpus ${CMAKE_CURRENT_BINARY_DIR}/corpus/${_parser})
    set(_artifacts ${CMAKE_CURRENT_BINARY_DIR}/artifacts/${_parser})
    file(MAKE_DIRECTORY ${_corpus} ${_artifacts})
    add_test(NAME fuzz.${_parser}
        COMMAND ${_parser}_fuzzer
            -max_total_time=${REXGLUE_FUZZ_SECONDS}
            -rss_limit_mb=4096
            -print_final_stats=1
            -artifact_prefix=${_artifacts}/
            ${_corpus} ${_fuzz_seeds_dir}/${_parser})
    set_tests_properties(fuzz.${_parser} PROPERTIES
        FIXTURES_REQUIRED fuzz_seeds
        LABELS "fuzz"
        TIMEOUT 0)
endforeach()
