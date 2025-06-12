# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/SoftwareProjects/GameEngine/OverlayCrafter/cmake-build-debug/_deps/ogg-src"
  "D:/SoftwareProjects/GameEngine/OverlayCrafter/cmake-build-debug/_deps/ogg-build"
  "D:/SoftwareProjects/GameEngine/OverlayCrafter/cmake-build-debug/_deps/ogg-subbuild/ogg-populate-prefix"
  "D:/SoftwareProjects/GameEngine/OverlayCrafter/cmake-build-debug/_deps/ogg-subbuild/ogg-populate-prefix/tmp"
  "D:/SoftwareProjects/GameEngine/OverlayCrafter/cmake-build-debug/_deps/ogg-subbuild/ogg-populate-prefix/src/ogg-populate-stamp"
  "D:/SoftwareProjects/GameEngine/OverlayCrafter/cmake-build-debug/_deps/ogg-subbuild/ogg-populate-prefix/src"
  "D:/SoftwareProjects/GameEngine/OverlayCrafter/cmake-build-debug/_deps/ogg-subbuild/ogg-populate-prefix/src/ogg-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/SoftwareProjects/GameEngine/OverlayCrafter/cmake-build-debug/_deps/ogg-subbuild/ogg-populate-prefix/src/ogg-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/SoftwareProjects/GameEngine/OverlayCrafter/cmake-build-debug/_deps/ogg-subbuild/ogg-populate-prefix/src/ogg-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
