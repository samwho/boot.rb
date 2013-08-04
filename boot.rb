# Cross Compiling configuration for boot.rb
#
MRuby::CrossBuild.new("host") do |conf|
  toolchain :gcc

  BOOTRB_PATH = File.dirname(__FILE__)

  CXXFLAGS = %W[-std=c99 -Wall -nostdinc -ffreestanding  -fno-stack-protector -fno-builtin -g -Iinclude -m32 -O0 -mno-sse]
  #ASFLAGS  = %w[-felf32 -g]
  #LDFLAGS  = %w[-nostdlib -melf_i386 -g]

  #STAGE2   = "/boot/grub/stage2_eltorito"

  #CXXFILES := $(shell find "src" -name "*.cpp")
  #HDRFILES := $(shell find "src" -name "*.h")
  #ASMFILES := $(shell find "src" -name "*.asm")
  #OBJFILES := $(patsubst %.asm,%.o,$(ASMFILES)) $(patsubst %.cpp,%.o,$(CXXFILES))



  #BIN_PATH = "#{ARDUINO_PATH}/hardware/tools/g++_arm_none_eabi/bin"
  #SAM_PATH = "#{ARDUINO_PATH}/hardware/arduino/sam"
  #TARGET_PATH = "#{SAM_PATH}/variants/arduino_due_x"

  conf.cc do |cc|
    #cc.command = "#{BIN_PATH}/arm-none-eabi-gcc"
    cc.include_paths << ["#{BOOTRB_PATH}/include"]
    cc.flags = CXXFLAGS
    cc.compile_options = "%{flags} -o %{outfile} -c %{infile}"

    #configuration for low memory environment
    #cc.defines << %w(MRB_HEAP_PAGE_SIZE=64)
    #cc.defines << %w(MRB_USE_IV_SEGLIST)
    #cc.defines << %w(KHASH_DEFAULT_SIZE=8)
    #cc.defines << %w(MRB_STR_BUF_MIN_SIZE=20)
    #cc.defines << %w(MRB_GC_STRESS)
    #cc.defines << %w(DISABLE_STDIO) #if you dont need stdio.
    #cc.defines << %w(POOL_PAGE_SIZE=1000) #effective only for use with mruby-eval
  end

  conf.cxx do |cxx|
    cxx.command = conf.cc.command.dup
    cxx.include_paths = conf.cc.include_paths.dup
    cxx.flags = conf.cc.flags.dup
    cxx.defines = conf.cc.defines.dup
    cxx.compile_options = conf.cc.compile_options.dup
  end

  conf.archiver do |archiver|
    #archiver.command = "#{BIN_PATH}/arm-none-eabi-ar"
    archiver.archive_options = 'rcs %{outfile} %{objs}'
  end

  #no executables
  conf.bins = []

  #do not build executable test
  conf.build_mrbtest_lib_only

  #gems from core
  conf.gem :core => "mruby-print" 
  conf.gem :core => "mruby-math"
  conf.gem :core => "mruby-enum-ext"

  #light-weight regular expression
  conf.gem :github => "masamitsu-murase/mruby-hs-regexp", :branch => "master" 

  #Arduino API
  #conf.gem :github =>"kyab/mruby-arduino", :branch => "master"

end
