# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "D:/study/c-code/testproject2/tmp/test2+Target_1")
  file(MAKE_DIRECTORY "D:/study/c-code/testproject2/tmp/test2+Target_1")
endif()
file(MAKE_DIRECTORY
  "D:/study/c-code/testproject2/tmp/1"
  "D:/study/c-code/testproject2/tmp/test2+Target_1"
  "D:/study/c-code/testproject2/tmp/test2+Target_1/tmp"
  "D:/study/c-code/testproject2/tmp/test2+Target_1/src/test2+Target_1-stamp"
  "D:/study/c-code/testproject2/tmp/test2+Target_1/src"
  "D:/study/c-code/testproject2/tmp/test2+Target_1/src/test2+Target_1-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/study/c-code/testproject2/tmp/test2+Target_1/src/test2+Target_1-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/study/c-code/testproject2/tmp/test2+Target_1/src/test2+Target_1-stamp${cfgdir}") # cfgdir has leading slash
endif()
