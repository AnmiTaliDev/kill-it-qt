project('kill-it-qt', 'cpp',
  version : '1.4',
  default_options : [
    'warning_level=3',
    'cpp_std=c++17',
    'buildtype=release'
  ],
  license : 'GPL-3.0-or-later',
  meson_version : '>=0.56.0'
)

# Project information
project_description = 'Simple Qt6 power management application for Linux'
project_url = 'https://github.com/AnmiTaliDev/kill-it-qt'

# Qt6 dependency and modules
qt6 = import('qt6')
qt6_dep = dependency('qt6', modules: ['Core', 'Widgets'])

# Source files
sources = files(
  'src/main.cpp',
  'src/parse_config.cpp'
)

# Header files
headers = files(
  'src/parse_config.h'
)

# Process Qt MOC files (for Q_OBJECT)
moc_files = qt6.compile_moc(
  sources : 'src/main.cpp',
  extra_args : ['-DMOC_OUTPUT']
)

# Create executable
executable('kill-it-qt',
  sources,
  moc_files,
  dependencies : qt6_dep,
  include_directories : include_directories('src'),
  install : true,
  install_dir : get_option('bindir')
)

# Summary
summary({
  'Project': meson.project_name(),
  'Version': meson.project_version(),
  'License': meson.project_license()[0],
  'Build type': get_option('buildtype'),
  'C++ standard': get_option('cpp_std'),
  'Install prefix': get_option('prefix'),
  'Install bindir': get_option('prefix') / get_option('bindir'),
}, section: 'Configuration')

summary({
  'Qt6': qt6_dep.found() ? qt6_dep.version() : 'not found',
  'Compiler': meson.get_compiler('cpp').get_id(),
  'Compiler version': meson.get_compiler('cpp').version(),
}, section: 'Dependencies')

# Print configuration
message('Configuring @0@ @1@'.format(meson.project_name(), meson.project_version()))
message('Build type: @0@'.format(get_option('buildtype')))
message('C++ standard: @0@'.format(get_option('cpp_std')))
message('Warning level: @0@'.format(get_option('warning_level')))