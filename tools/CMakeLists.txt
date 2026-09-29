# Optional local diagnostic tools. Not installed or included in title builds.
add_executable(xma_probe EXCLUDE_FROM_ALL xma_probe.cpp)
target_link_libraries(xma_probe PRIVATE libavcodec libavutil)
