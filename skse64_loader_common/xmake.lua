
add_rules("mode.debug", "mode.release")

-- LTO config
if is_mode("release") then
    set_policy("build.optimization.lto", true)
elseif is_mode("debug") then
    set_policy("build.optimization.lto", false)
end

-- external package
add_repositories("monocyte-repo https://github.com/mono-cyte/monocyte-repo.git")
add_requires("common", "skse64_version")


target("skse64_loader_common")
    set_kind("static")
    set_languages("c++11")

    -- dependencies
    add_packages("common","skse64_version")

    add_includedirs("include")
    add_files("src/*.cpp")
    add_headerfiles("include/*.h")

    -- add_syslinks("shlwapi", "version", "comdlg32", "user32", "shell32","advapi32")
