set(SHARED_SOURCES
  cfg.cpp
  vm.cpp
  code.cpp
  datatypes.cpp
  exceptions.cpp
  util.cpp
)

target_sources(${EXE} PUBLIC ${SHARED_SOURCES})

target_sources(${EXE_TEST} PUBLIC ${SHARED_SOURCES})
