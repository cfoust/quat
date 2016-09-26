#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/
cmake_policy(SET CMP0017 NEW)

cmake_minimum_required(VERSION 2.8)

set(APP_NAME QUAT)
project (${APP_NAME})

set(COCOS2D_ROOT ${CMAKE_SOURCE_DIR}/cocos2d)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${COCOS2D_ROOT}/cmake/Modules/")
include(CocosBuildHelpers)

# libcocos2d
set(BUILD_CPP_TESTS OFF CACHE BOOL "turn off build cpp-tests")
set(BUILD_LUA_LIBS OFF CACHE BOOL "turn off build lua related targets")
set(BUILD_JS_LIBS OFF CACHE BOOL "turn off build js related targets")
add_subdirectory(${COCOS2D_ROOT})

# Some macro definitions
if(WINDOWS)
  if(BUILD_SHARED_LIBS)
    ADD_DEFINITIONS (-D_USRDLL -D_EXPORT_DLL_ -D_USEGUIDLL -D_USREXDLL -D_USRSTUDIODLL)
  else()
    ADD_DEFINITIONS (-DCC_STATIC)
  endif()

  ADD_DEFINITIONS (-DCOCOS2DXWIN32_EXPORTS -D_WINDOWS -DWIN32 -D_WIN32)
  set(PLATFORM_FOLDER win32)
elseif(MACOSX OR APPLE)
  ADD_DEFINITIONS (-DCC_TARGET_OS_MAC)
  ADD_DEFINITIONS (-DUSE_FILE32API)
  set(PLATFORM_FOLDER mac)
elseif(LINUX)
  ADD_DEFINITIONS(-DLINUX)
  set(PLATFORM_FOLDER linux)
elseif(ANDROID)
  ADD_DEFINITIONS (-DUSE_FILE32API)
  set(PLATFORM_FOLDER android)
else()
  message( FATAL_ERROR "Unsupported platform, CMake will exit" )
endif()


# Compiler options
if(MSVC)
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS
                  -wd4251 -wd4244 -wd4334 -wd4005 -wd4820 -wd4710
                  -wd4514 -wd4056 -wd4996 -wd4099)
else()
  set(CMAKE_C_FLAGS_DEBUG "-g -Wall -DCOCOS2D_DEBUG=1")
  set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-deprecated-declarations -Wno-reorder")
  if(CLANG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
  endif()
endif(MSVC)



set(PLATFORM_SPECIFIC_SRC)
set(PLATFORM_SPECIFIC_HEADERS)
if(MACOSX OR APPLE)
set(PLATFORM_SPECIFIC_SRC
  proj.ios_mac/ios/main.m
  proj.ios_mac/ios/RootViewController.mm
  proj.ios_mac/ios/AppController.mm
)
set(PLATFORM_SPECIFIC_HEADERS
  proj.ios_mac/ios/RootViewController.h
  proj.ios_mac/ios/AppController.h
)
elseif(LINUX) #assume linux
set(PLATFORM_SPECIFIC_SRC
  proj.linux/main.cpp
)
elseif ( WIN32 )
set(PLATFORM_SPECIFIC_SRC
  proj.win32/main.cpp
)
set(PLATFORM_SPECIFIC_HEADERS
  proj.win32/main.h
  proj.win32/resource.h
)
endif()

include_directories(
  /usr/local/include/GLFW
  /usr/include/GLFW
  ${COCOS2D_ROOT}/cocos
  ${COCOS2D_ROOT}/cocos/platform
  ${COCOS2D_ROOT}/cocos/audio/include/
  Classes
)
if ( WIN32 )
  include_directories(
  ${COCOS2D_ROOT}/external/glfw3/include/win32
  ${COCOS2D_ROOT}/external/win32-specific/gles/include/OGLES
)
endif( WIN32 )

set(GAME_SRC
  Classes/AppDelegate.cpp
  Classes/BackgroundLayer.cpp
  Classes/Clickable.cpp
  Classes/CloseButton.cpp
  Classes/GameScene.cpp
  Classes/GameStateController.cpp
  Classes/MenuButtonLayer.cpp
  Classes/TouchInputManager.cpp
  Classes/ads/AdLayer.cpp
  Classes/defs/Definition.cpp
  Classes/defs/DefinitionLayer.cpp
  Classes/menu/DrawnBanner.cpp
  Classes/menu/MenuButton.cpp
  Classes/menu/MenuLayer.cpp
  Classes/menu/RankCard.cpp
  Classes/models/Dictionary.cpp
  Classes/models/Game.cpp
  Classes/models/Puzzle.cpp
  Classes/models/PuzzleManager.cpp
  Classes/models/themes/RankTheme.cpp
  Classes/models/Theme.cpp
  Classes/models/User.cpp
  Classes/nodes/RectRadius.cpp
  Classes/solver/PuzzleLayer.cpp
  Classes/solver/SolverStateController.cpp
  Classes/solver/input/BorderedWordNode.cpp
  Classes/solver/input/KeyboardLayer.cpp
  Classes/solver/input/SolverKeyboardManager.cpp
  Classes/solver/input/SolverTouchInputManager.cpp
  Classes/solver/input/UndoButtonLayer.cpp
  Classes/solver/input/WordNode.cpp
  Classes/solver/info/DefinitionButtonLayer.cpp
  Classes/solver/info/StepsIndicatorLayer.cpp
  Classes/solver/info/StepsLayer.cpp
  Classes/solver/info/TextIndicatorLayer.cpp
  Classes/solver/info/banner/BannerButtonLayer.cpp
  Classes/solver/info/banner/ExplodingCircle.cpp
  ${PLATFORM_SPECIFIC_SRC}
)

set(GAME_HEADERS
  Classes/AppDelegate.h
  Classes/BackgroundLayer.h
  Classes/Clickable.h
  Classes/CloseButton.h
  Classes/GameScene.h
  Classes/GameStateController.h
  Classes/MenuButtonLayer.h
  Classes/TouchInputManager.h
  Classes/ads/AdLayer.h
  Classes/defs/Definition.h
  Classes/defs/DefinitionLayer.h
  Classes/menu/DrawnBanner.h
  Classes/menu/DrawnBanner.cpp
  Classes/menu/MenuButton.h
  Classes/menu/MenuLayer.h
  Classes/menu/RankCard.h
  Classes/models/Dictionary.h
  Classes/models/Game.h
  Classes/models/Puzzle.h
  Classes/models/PuzzleManager.h
  Classes/models/themes/RankTheme.h
  Classes/models/Theme.h
  Classes/models/User.h
  Classes/nodes/RectRadius.h
  Classes/solver/PuzzleLayer.h
  Classes/solver/SolverStateController.h
  Classes/solver/input/BorderedWordNode.h
  Classes/solver/input/KeyboardLayer.h
  Classes/solver/input/SolverKeyboardManager.h
  Classes/solver/input/SolverTouchInputManager.h
  Classes/solver/input/UndoButtonLayer.h
  Classes/solver/input/WordNode.h
  Classes/solver/info/DefinitionButtonLayer.h
  Classes/solver/info/StepsIndicatorLayer.h
  Classes/solver/info/StepsLayer.h
  Classes/solver/info/TextIndicatorLayer.h
  Classes/solver/info/banner/BannerButtonLayer.h
  Classes/solver/info/banner/ExplodingCircle.h
  ${PLATFORM_SPECIFIC_HEADERS}
)

if(GAME_HEADERS)
  if ( WIN32 )
    add_executable(${APP_NAME} WIN32 ${GAME_SRC} ${GAME_HEADERS})
  else()
    add_executable(${APP_NAME} ${GAME_SRC} ${GAME_HEADERS})
  endif ( WIN32 )
else()
  if ( WIN32 )
    add_executable(${APP_NAME} WIN32 ${GAME_SRC})
  else()
    add_executable(${APP_NAME} ${GAME_SRC})
  endif ( WIN32 )
endif()

target_link_libraries(${APP_NAME} cocos2d)

set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin")

set_target_properties(${APP_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

if ( WIN32 )
  #also copying dlls to binary directory for the executable to run
  pre_build(${APP_NAME}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy ${COCOS2D_ROOT}/external/win32-specific/gles/prebuilt/glew32.dll ${APP_BIN_DIR}/${CMAKE_BUILD_TYPE}
	COMMAND ${CMAKE_COMMAND} -E copy ${COCOS2D_ROOT}/external/win32-specific/zlib/prebuilt/zlib1.dll ${APP_BIN_DIR}/${CMAKE_BUILD_TYPE}
	)
else()
  pre_build(${APP_NAME}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}/Resources
    )

endif()
