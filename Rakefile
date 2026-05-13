# General Documentation:    https://ruby.github.io/rake/
# Domain-Specific Language: https://ruby.github.io/rake/Rake/DSL.html

require 'rake/clean'

# =============
# Command Names
# =============

CC   = ENV['CC']  || 'cc'
BIN  = ENV['BIN'] || 'Game.so'
EXE  = ENV['EXE'] || 'game'
MRBC = "#{EXE}-mrbc"

# =====
# Paths
# =====

SRC_DIRNAME     = 'Src'
INCLUDE_DIRNAME = 'Include'
MRBLIB_DIRNAME  = 'Mrblib'

# =====
# Flags
# =====

OPTIMIZATION_FLAGS = %w(-O2).join ' '
WARNING_FLAGS      = %w(-Wall -Werror -Wextra).join ' '
INCLUDE_FLAGS      = %W(-I #{INCLUDE_DIRNAME}).join ' '
ASSERT_LEVEL       = ENV['ASSERT_LEVEL'] || '2'
DEFINE_FLAGS       = %W(-D SDL_ASSERT_LEVEL=#{ASSERT_LEVEL}).join ' '
RELOCATION_FLAGS   = %w(-fpic).join ' '
PKGS               = %w(game-mruby sdl3 sdl3-ttf).join ' '

# ==============
# Specifications
# ==============

task :default => :all

SOURCES = FileList["#{SRC_DIRNAME}/*.c"]
OBJECTS = SOURCES.ext '.o'
CFLAGS  = %W(#{OPTIMIZATION_FLAGS} #{WARNING_FLAGS} #{INCLUDE_FLAGS} #{DEFINE_FLAGS} #{RELOCATION_FLAGS}).join ' '

def pkg_config(opt)
  `pkg-config --#{opt} #{PKGS}`
end

desc 'Builds all source files'
task :all => OBJECTS do
  # Link object files into the binary executable.
  sh "#{CC} #{OBJECTS} -shared -o #{BIN} #{ pkg_config 'libs' }"
end

rule '.o' => '.c' do |file_task|
  src      = file_task.source
  obj      = "#{File.basename src, '.c'}.o"
  obj_path = "#{SRC_DIRNAME}/#{obj}"

  # Compile individual object files.
  sh "#{CC} #{CFLAGS} -c #{src} -o #{obj_path} #{ pkg_config 'cflags' }"
end

desc 'Compile a Ruby file'
task :mrbc, [:filename] do |task, args|
  filename = args[:filename]
  basename = File.basename(filename, '.rb')
  path     = "#{MRBLIB_DIRNAME}/#{filename}"

  sh "#{MRBC} -B #{basename}_symbol #{path}"

  src  = "#{MRBLIB_DIRNAME}/#{basename}.c"
  dest = "#{INCLUDE_DIRNAME}/#{basename}.c"

  FileUtils.mv src, dest, verbose: true
end

CLEAN.include("#{SRC_DIRNAME}/*.o", BIN)
