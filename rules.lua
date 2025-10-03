local RUNTIME_INFO = {
    bethesda = { type = 0, name = "Skyrim Special Edition" },
    gog = { type = 1, name = "Skyrim Special Edition GOG" },
    epic = { type = 2, name = "Skyrim Special Edition EPIC" }
}

local function pack_version(major, minor, patch, type)
    type = type or 0
    return (major & 0xFF) << 24 |
        (minor & 0xFF) << 16 |
        (patch & 0xFFF) << 4 |
        (type & 0xF)
end

rule("skse64_versioning")
do
    on_config(function(target)
        local name = RUNTIME_INFO[get_config("runtime")].name
        local type = RUNTIME_INFO[get_config("runtime")].type

        cprint('${onblue}current runtime: ${underline}' .. get_config("runtime"))

        -- SKSE_VERSION (define in xmake.lua)
        local sv = {}

        local skse_version = target:get("version")
        sv.major, sv.minor, sv.patch = string.match(skse_version, "(%d+)%.(%d+)%.(%d+)")
        sv.major = tonumber(sv.major)
        sv.minor = tonumber(sv.minor)
        sv.patch = tonumber(sv.patch)
        sv.packed = pack_version(sv.major, sv.minor, sv.patch)

        local sv_str = "0" .. "," .. sv.major .. "," .. sv.minor .. "," .. sv.patch
        local sv_padded_str = "0001"
        local sv_release_idx = 72

        cprint('${onblue}current skse version: ${underline}' .. skse_version)

        -- RUNTIME_VERSION
        local runtime_version = get_config("skyrim_version")
        local rv = {}
        rv.major, rv.minor, rv.patch = string.match(runtime_version, "(%d+)%.(%d+)%.(%d+)")
        rv.major = tonumber(rv.major)
        rv.minor = tonumber(rv.minor)
        rv.patch = tonumber(rv.patch)
        rv.packed = pack_version(rv.major, rv.minor, rv.patch, type)

        cprint('${onblue}current runtime version: ${underline}' .. runtime_version)

        -- other
        local SKSE_TARGETING_BETA_VERSION = 0
        local CURRENT_RELEASE_SKSE_STR = sv.major .. "," .. sv.minor .. "," .. sv.patch


        target:set("configvar", "RUNTIME_TYPE_BETHESDA", RUNTIME_INFO["bethesda"].type)
        target:set("configvar", "RUNTIME_TYPE_GOG", RUNTIME_INFO["gog"].type)
        target:set("configvar", "RUNTIME_TYPE_EPIC", RUNTIME_INFO["epic"].type)

        target:set("configvar", "PACKED_SKSE_VERSION", sv.packed)
        target:set("configvar", "SKSE_VERSION_VERSTRING", sv_str)
        target:set("configvar", "SKSE_VERSION_PADDEDSTRING", sv_padded_str)
        target:set("configvar", "SKSE_VERSION_RELEASEIDX", sv_release_idx)

        target:set("configvar", "SKSE_TARGETING_BETA_VERSION", SKSE_TARGETING_BETA_VERSION)
        target:set("configvar", "CURRENT_RELEASE_RUNTIME", rv.packed)
        target:set("configvar", "SKSE_VERSION_PACKED", sv_str)
        target:set("configvar", "SAVE_FOLDER_NAME", name)
    end)
end

rule("attach_version")
on_config(function(target)
    local runtime_version = get_config("skyrim_version")

    local rv = {}
    rv.major, rv.minor, rv.patch = string.match(runtime_version, "(%d+)%.(%d+)%.(%d+)")
    rv.major = tonumber(rv.major)
    rv.minor = tonumber(rv.minor)
    rv.patch = tonumber(rv.patch)

    local type = RUNTIME_INFO[get_config("runtime")].type

    rv.packed = pack_version(rv.major, rv.minor, rv.patch, type)

    local name = target:name() .. "_" .. rv.major .. "_" .. rv.minor .. "_" .. rv.patch
    -- 将版本号
    target:set("basename", name)
    target:add("defines", "RUNTIME")
    target:add("defines", string.format("RUNTIME_VERSION=%d", rv.packed))
    target:add("includedirs", "$(builddir)/version", { public = true })
    target:add("files", "$(builddir)/version/*.rc")
end)

rule("OptimizeLTO")
on_config(function(target)
    if is_mode("release") then
        target:set("policy", "build.optimization.lto", true)
    elseif is_mode("debug") then
        target:set("policy", "build.optimization.lto", false)
    end
end)
