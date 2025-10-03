set_version("2.2.6")

add_rules("mode.debug", "mode.release")

includes("rules.lua") -- version rules and others

option("skyrim_version", {showmenu = true,  default = "1.6.1170", type = "string"})
option("runtime", {showmenu = true,  default = "bethesda", type = "string", values = {"bethesda", "gog", "epic"}})

add_repositories("monocyte-repo https://github.com/mono-cyte/monocyte-repo.git")
add_requires("common","xbyak")

set_languages("c++17")


target("skse64_version")
    set_kind("phony")
    add_rules("skse64_versioning")
    add_configfiles("skse64_version/template/*.in", {prefixdir = "version"})


target("skse64_common")
    set_kind("static")
    -- dependencies
    add_packages("common")
    add_deps("skse64_version")
    -- sources
    add_includedirs("skse64_common/include", {public = true})
    add_files("skse64_common/src/*.cpp")
    -- rule
    add_rules("attach_version")


target("skse64_loader_common")
    set_kind("static")
    -- dependencies
    add_packages("common")
    add_deps("skse64_version")
    -- sources
    add_includedirs("skse64_loader_common/include", {public = true})
    add_files("skse64_loader_common/src/*.cpp")
    -- rule
    add_rules("attach_version")


target("skse64")
    set_kind("shared")
    -- dependencies
    add_packages("common", "xbyak")
    add_deps("skse64_common")
    -- sources
    add_includedirs("skse64/include","skse64/res")
    add_files("skse64/src/**.cpp", "skse64/res/*.rc", "skse64/src/*.def")
    add_headerfiles("skse64/include/(**.h)","skse64/include/(**.inl)")
    -- system lib
    add_syslinks("user32", "comdlg32", "shell32")
    -- rule
    add_rules("attach_version", "OptimizeLTO")

target("skse64_loader")
    set_kind("binary")

    -- dependencies
    add_packages("common")
    add_deps("skse64_common","skse64_loader_common")
    -- sources
    add_includedirs("skse64_loader/include")
    add_files("skse64_loader/src/*.cpp")
    -- system lib
    add_syslinks("advapi32","version","user32","comdlg32","shell32")
    -- rule
    add_rules("attach_version", "OptimizeLTO")