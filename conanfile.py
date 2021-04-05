from conans import ConanFile, CMake


class CanAscParserConan(ConanFile):
    name = "canasc_parser"
    version = "0.0.1"
    license = "MIT License"
    author = "Vinit James vinit.james24@gmail.com"
    url = "https://github.com/vinitjames/CAN-ASCParser"
    description = "A C++ library for parsing CAN/CANFD .asc log files"
    topics = ("CanAsc Parser", "Asc Log Parser", "CAN")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": False}
    generators = "cmake"
    exports_sources = "*"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.test()

        # Explicit way:
        # self.run('cmake %s/hello %s'
        #          % (self.source_folder, cmake.command_line))
        # self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        libname = 'lib' + self.name
        self.copy("*.h", dst="include", src="./include")
        self.copy("{}.lib".format(libname), dst="lib", keep_path=False)
        self.copy("{}.dll".format(libname), dst="bin", keep_path=False)
        self.copy("{}.dylib*".format(libname), dst="lib", keep_path=False)
        self.copy("{}.so".format(libname), dst="lib", keep_path=False)
        self.copy("{}.a".format(libname), dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["canasc_parser"]
