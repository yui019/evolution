project('libimgui', 'cpp')

compiler = meson.get_compiler('cpp')

inc = include_directories('repo')

src = [
    'repo/imgui.cpp',
    'repo/imgui_demo.cpp',
    'repo/imgui_draw.cpp',
    'repo/imgui_tables.cpp',
    'repo/imgui_widgets.cpp',
    'repo/backends/imgui_impl_glfw.cpp',
    'repo/backends/imgui_impl_opengl3.cpp',
]

libimgui = static_library('imgui',
  src,
  include_directories : inc,
  dependencies: compiler.find_library('dl'))

libimgui_dep = declare_dependency(
  include_directories : inc,
  link_with : libimgui
)