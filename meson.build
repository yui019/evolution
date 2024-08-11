project('evolution', 'cpp',
  default_options : ['warning_level=3', 'cpp_std=c++20'])

subdir('src')

cxx = meson.get_compiler('cpp')

cmake = import('cmake')

inc = include_directories('include')

raylib_opts = cmake.subproject_options()
raylib_opts.set_install(false)
raylib_opts.add_cmake_defines({
  'BUILD_EXAMPLES': 'OFF',
  'BUILD_SHARED_LIBS': 'ON'
})
raylib_proj = cmake.subproject('raylib', options: raylib_opts)
raylib_dep = raylib_proj.dependency('raylib')

rlimgui_proj = subproject('rlImGui')
rlimgui_dep = rlimgui_proj.get_variable('rlimgui_dep')

imgui_proj = subproject('imgui')
imgui_dep = imgui_proj.get_variable('libimgui_dep')

deps = [
  cxx.find_library('dl'),
  cxx.find_library('m'),
  raylib_dep,
  imgui_dep,
  rlimgui_dep,
]

executable('evolution',
  sources: src,
  dependencies: deps,
  include_directories: inc,
)
