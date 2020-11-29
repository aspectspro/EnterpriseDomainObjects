from conans import ConanFile, CMake, tools


class DatabaseConan(ConanFile):
    name = "EnterpriseDomainObjects"
    author = "Greg greg@aspectspro.com"
    description = "Enterprise Domain Objects"

    def requirements(self):
        self.requires("AbstractObjects/2.1.1")

#dynamically sets version number from master tag or testing if other branches
    def set_version(self):
            git = tools.Git(folder=self.recipe_folder)
            tag = "%s" % (git.get_tag())

            if tag == "None":
                tag = "testing"
            else:
                tag = "%s" % (git.get_tag())
            self.version = "%s" % (tag)

    generators = "cmake"
    settings = "os", "arch", "compiler"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"

    exports_sources = "src/*"

    def configure(self):
        if self.settings.compiler == "Visual Studio":
           del self.settings.compiler.runtime

#Creates both debug and release configurations
    def build(self):
#        cmake_release = CMake(self, build_type="Debug")
#        cmake_release.configure(source_folder="src")
#        cmake_release.build()

        cmake_debug = CMake(self, build_type="Release")
        cmake_debug.configure(source_folder="src")
        cmake_debug.build()

    def package(self):
        self.copy("*.h", dst="include", src="src")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = [self.name]
#        self.cpp_info.debug.libs = ["%s_d" % (self.name)]
