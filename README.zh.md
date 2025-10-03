# 使用 Xmake 重建的 SKSE64 项目

由于对 Visual Studio（VS）的臃肿和 CMake 配置的繁琐非常不爽，我用 Xmake 构建，可读性和可维护性良好

本项目引用了个人仓库中 fork 的 common 库，因为 Xmake 官方仓库中缺少相应内容，且我暂不打算将其提交至官方仓库

项目包含多个子项目：`*_common` 格式的为静态库，`skse64` 是与游戏版本相关的注入 DLL，`skse64_loader` 为可执行程序。

对于用户：

| 项目名称             | 类型       | 描述说明                             | 是否必需           |
| -------------------- | ---------- | ------------------------------------ | ------------------ |
| skse64_version       | phony      | 为其他项目提供版本信息               | :x:                |
| skse64_common        | 静态库     | 通用和辅助函数库                     | :x:                |
| skse64_loader_common | 静态库     | loader 的工具代码                    | :x:                |
| skse64               | 动态库     | 需被注入游戏进程的 SKSE64 动态链接库 | :heavy_check_mark: |
| skse64_loader        | 可执行程序 | 用于加载 SKSE64 的游戏的可执行程序   | :heavy_check_mark: |
