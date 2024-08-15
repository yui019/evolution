project('libimplot', 'cpp')

compiler = meson.get_compiler('cpp')

inc = [
  include_directories('repo'),
  include_directories('../imgui/repo'),
]

src = [
    'repo/implot.cpp',
    'repo/implot_items.cpp',
    'repo/implot_demo.cpp',
]

libimplot = static_library('implot',
  src,
  include_directories : inc,
  dependencies: compiler.find_library('dl'))

libimplot_dep = declare_dependency(
  include_directories : inc,
  link_with : libimplot
)