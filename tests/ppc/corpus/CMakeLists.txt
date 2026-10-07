# Hardware-captured PPC test corpus (RG-GDK-054)
# The xenia-project gen_tests corpus as has207/xenia-edge carries it; see
# README.md. Built with REXGLUE_PPC_CORPUS=ON, labelled ppc_corpus.

include(ppc_test_pipeline)

set(CORPUS_OBJ_DIR ${CMAKE_BINARY_DIR}/tests/ppc_corpus/obj)
set(CORPUS_BIN_DIR ${CMAKE_BINARY_DIR}/tests/ppc_corpus/bin)
set(CORPUS_GEN_DIR ${CMAKE_BINARY_DIR}/tests/ppc_corpus/generated)
file(MAKE_DIRECTORY ${CORPUS_OBJ_DIR} ${CORPUS_BIN_DIR} ${CORPUS_GEN_DIR})

# The cases are generated as data (recompile-tests --table) and split so the
# corpus compiles in parallel; a job pool caps how many chunks compile at once.
set(CORPUS_CHUNKS 16)
set_property(GLOBAL APPEND PROPERTY JOB_POOLS ppc_corpus=4)

file(GLOB CORPUS_ASM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.s)
# Files the bundled assembler cannot assemble (assembler_unsupported.txt).
file(STRINGS ${CMAKE_CURRENT_SOURCE_DIR}/assembler_unsupported.txt UNSUPPORTED_LINES
     REGEX "^[^#]")
foreach(LINE ${UNSUPPORTED_LINES})
    string(REGEX MATCH "^[^ 	]+" STEM "${LINE}")
    list(REMOVE_ITEM CORPUS_ASM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/${STEM}.s)
endforeach()
list(LENGTH CORPUS_ASM_FILES CORPUS_FILE_COUNT)
foreach(ASM_FILE ${CORPUS_ASM_FILES})
    ppc_add_test_binary(${ASM_FILE} ${CORPUS_OBJ_DIR} ${CORPUS_BIN_DIR} PPC_CORPUS)
endforeach()
get_property(CORPUS_BINS GLOBAL PROPERTY PPC_CORPUS_BINS)
get_property(CORPUS_MAPS GLOBAL PROPERTY PPC_CORPUS_MAPS)

set(CORPUS_SOURCES "")
math(EXPR LAST_CHUNK "${CORPUS_CHUNKS} - 1")
foreach(i RANGE ${LAST_CHUNK})
    list(APPEND CORPUS_SOURCES
        ${CORPUS_GEN_DIR}/ppc_test_functions_${i}.cpp
        ${CORPUS_GEN_DIR}/ppc_test_cases_${i}.cpp)
endforeach()

add_custom_command(
    OUTPUT ${CORPUS_SOURCES} ${CORPUS_GEN_DIR}/ppc_test_decls.h
           ${CORPUS_GEN_DIR}/ppc_table_runner.h
    COMMAND $<TARGET_FILE:rexglue> recompile-tests
            --output=${CORPUS_GEN_DIR}
            --bin-dir=${CORPUS_BIN_DIR}
            --asm-dir=${CMAKE_CURRENT_SOURCE_DIR}
            --chunks=${CORPUS_CHUNKS}
            --table
            --skip-list=${CMAKE_CURRENT_SOURCE_DIR}/skip.txt
            --known-failures=${CMAKE_CURRENT_SOURCE_DIR}/known_failures.txt
    DEPENDS ${CORPUS_BINS} ${CORPUS_MAPS} ${CORPUS_ASM_FILES}
            ${CMAKE_CURRENT_SOURCE_DIR}/skip.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/known_failures.txt rexglue
    COMMENT "Generating the PPC corpus tests with rexglue"
    VERBATIM
)
set_source_files_properties(${CORPUS_SOURCES} ${CORPUS_GEN_DIR}/ppc_test_decls.h
    ${CORPUS_GEN_DIR}/ppc_table_runner.h
    PROPERTIES GENERATED TRUE)

add_executable(ppc_corpus_tests ${CORPUS_SOURCES})
target_include_directories(ppc_corpus_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${CORPUS_GEN_DIR}
)
target_link_libraries(ppc_corpus_tests PRIVATE
    simde
    rexruntime
    fmt::fmt
    Catch2::Catch2WithMain
)
if(WIN32 AND TARGET amd_fidelityfx_dx12)
    target_link_options(ppc_corpus_tests PRIVATE
        "LINKER:/DELAYLOAD:$<TARGET_FILE_NAME:amd_fidelityfx_dx12>")
    target_link_libraries(ppc_corpus_tests PRIVATE delayimp)
endif()
set_target_properties(ppc_corpus_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:rexruntime>
    JOB_POOL_COMPILE ppc_corpus
)
target_compile_options(ppc_corpus_tests PRIVATE
    -UTRACY_ENABLE -UREXGLUE_ENABLE_PROFILING
    -UREXGLUE_ENABLE_PERF_COUNTERS -UREXGLUE_PROFILE_GUEST_FUNCTIONS
    -msse4.1 -mssse3 -w
)

# One CTest test per file, as the generated sources have one TEST_CASE per file.
foreach(ASM_FILE ${CORPUS_ASM_FILES})
    get_filename_component(STEM ${ASM_FILE} NAME_WE)
    add_test(NAME ppc_corpus.${STEM} COMMAND ppc_corpus_tests "[${STEM}]" --allow-running-no-tests)
    set_tests_properties(ppc_corpus.${STEM} PROPERTIES LABELS "ppc_corpus" TIMEOUT 300)
endforeach()

message(STATUS "Configured the PPC corpus with ${CORPUS_FILE_COUNT} files")
