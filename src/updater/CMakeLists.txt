add_executable(rexglue-updater WIN32
    main.cpp
    ${REXGLUE_ROOT}/src/system/release_update.cpp
)
target_include_directories(rexglue-updater PRIVATE
    ${REXGLUE_ROOT}/include
    ${REXGLUE_ROOT}/thirdparty/inja/third_party/include
)
target_link_libraries(rexglue-updater PRIVATE fmt::fmt bcrypt shell32)
set_target_properties(rexglue-updater PROPERTIES EXPORT_NAME updater)
add_executable(rex::updater ALIAS rexglue-updater)
