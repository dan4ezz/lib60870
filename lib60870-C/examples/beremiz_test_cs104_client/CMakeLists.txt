include_directories(
   .
)

set(example_SRCS
   beremiz_test_cs104_client.c
)

IF(WIN32)
set_source_files_properties(${example_SRCS}
                                       PROPERTIES LANGUAGE CXX)
ENDIF(WIN32)

add_executable(beremiz_test_cs104_client
  ${example_SRCS}
)

target_link_libraries(beremiz_test_cs104_client
    lib60870
)
