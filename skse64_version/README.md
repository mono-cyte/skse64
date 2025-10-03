# Some notes about SKSE64 repacked version

This is a reorganized SKSE64 project using xmake.
这是使用 xmake 重新组织的 SKSE64 项目

Following is a list of supported versions:
以下为支持的版本列表:

| Game Version | Runtime      |
| ------------ | ------------ |
| 1.1.47       | bethesda     |
| 1.1.51       | bethesda     |
| 1, 2, 36     | bethesda     |
| 1, 2, 39     | bethesda     |
| 1, 3, 5      | bethesda     |
| 1, 3, 9      | bethesda     |
| 1, 4, 2      | bethesda     |
| 1, 5, 3      | bethesda     |
| 1, 5, 16     | bethesda     |
| 1, 5, 23     | bethesda     |
| 1, 5, 39     | bethesda     |
| 1, 5, 50     | bethesda     |
| 1, 5, 53     | bethesda     |
| 1, 5, 62     | bethesda     |
| 1, 5, 73     | bethesda     |
| 1, 5, 80     | bethesda     |
| 1, 5, 97     | bethesda     |
| 1, 6, 317    | bethesda     |
| 1, 6, 318    | bethesda     |
| 1, 6, 323    | bethesda     |
| 1, 6, 342    | bethesda     |
| 1, 6, 353    | bethesda     |
| 1, 6, 629    | bethesda     |
| 1, 6, 640    | bethesda     |
| 1, 6, 659    | gog          |
| 1, 6, 678    | epic         |
| 1, 6, 1130   | bethesda     |
| 1, 6, 1170   | bethesda,gog |

Some unnecessary defines have been removed, and equivalent functionality has been implemented through xmake. For details, refer to `skse64_versioning.lua` , the following is removed.

移除了部分不必要的 defines, 并通过 xmake 实现等效功能, 具体参考 `skse64_versioning.lua`, 以下为移除的部分

```cpp

#define MAKE_EXE_VERSION_EX(major, minor, build, sub)	((((major) & 0xFF) << 24) | (((minor) & 0xFF) << 16) | (((build) & 0xFFF) << 4) | ((sub) & 0xF))
#define MAKE_EXE_VERSION(major, minor, build)			MAKE_EXE_VERSION_EX(major, minor, build, 0)


#define RUNTIME_VERSION_1_1_47 MAKE_EXE_VERSION(1, 1, 47)							   // 0x010102F0	initial version released on steam, has edit-and-continue enabled
#define RUNTIME_VERSION_1_1_51 MAKE_EXE_VERSION(1, 1, 51)							   // 0x01010330	initial version released on steam, has edit-and-continue enabled
#define RUNTIME_VERSION_1_2_36 MAKE_EXE_VERSION(1, 2, 36)							   // 0x01020240	edit-and-continue disabled
#define RUNTIME_VERSION_1_2_39 MAKE_EXE_VERSION(1, 2, 39)							   // 0x01020270	edit-and-continue disabled
#define RUNTIME_VERSION_1_3_5 MAKE_EXE_VERSION(1, 3, 5)								   // 0x01030050
#define RUNTIME_VERSION_1_3_9 MAKE_EXE_VERSION(1, 3, 9)								   // 0x01030090
#define RUNTIME_VERSION_1_4_2 MAKE_EXE_VERSION(1, 4, 2)								   // 0x01040020
#define RUNTIME_VERSION_1_5_3 MAKE_EXE_VERSION(1, 5, 3)								   // 0x01050030	creation club
#define RUNTIME_VERSION_1_5_16 MAKE_EXE_VERSION(1, 5, 16)							   // 0x01050100	creation club cleanup (thanks)
#define RUNTIME_VERSION_1_5_23 MAKE_EXE_VERSION(1, 5, 23)							   // 0x01050170	creation club
#define RUNTIME_VERSION_1_5_39 MAKE_EXE_VERSION(1, 5, 39)							   // 0x01050270	creation club
#define RUNTIME_VERSION_1_5_50 MAKE_EXE_VERSION(1, 5, 50)							   // 0x01050320	creation club
#define RUNTIME_VERSION_1_5_53 MAKE_EXE_VERSION(1, 5, 53)							   // 0x01050350	creation club
#define RUNTIME_VERSION_1_5_62 MAKE_EXE_VERSION(1, 5, 62)							   // 0x010503E0	creation club
#define RUNTIME_VERSION_1_5_73 MAKE_EXE_VERSION(1, 5, 73)							   // 0x01050490	creation club
#define RUNTIME_VERSION_1_5_80 MAKE_EXE_VERSION(1, 5, 80)							   // 0x01050500	creation club - no code or data differences
#define RUNTIME_VERSION_1_5_97 MAKE_EXE_VERSION(1, 5, 97)							   // 0x01050610	creation club
#define RUNTIME_VERSION_1_6_317 MAKE_EXE_VERSION(1, 6, 317)							   // 0x010613D0	anniversary edition
#define RUNTIME_VERSION_1_6_318 MAKE_EXE_VERSION(1, 6, 318)							   // 0x010613E0
#define RUNTIME_VERSION_1_6_323 MAKE_EXE_VERSION(1, 6, 323)							   // 0x01061430
#define RUNTIME_VERSION_1_6_342 MAKE_EXE_VERSION(1, 6, 342)							   // 0x01061560
#define RUNTIME_VERSION_1_6_353 MAKE_EXE_VERSION(1, 6, 353)							   // 0x01061610
#define RUNTIME_VERSION_1_6_629 MAKE_EXE_VERSION(1, 6, 629)							   // 0x01062750	to be hotfixed
#define RUNTIME_VERSION_1_6_640 MAKE_EXE_VERSION(1, 6, 640)							   // 0x01062800	the hotfix
#define RUNTIME_VERSION_1_6_659_GOG MAKE_EXE_VERSION_EX(1, 6, 659, RUNTIME_TYPE_GOG)   // 0x01062931
#define RUNTIME_VERSION_1_6_678_EPIC MAKE_EXE_VERSION_EX(1, 6, 678, RUNTIME_TYPE_EPIC) // 0x01062A62
#define RUNTIME_VERSION_1_6_1130 MAKE_EXE_VERSION(1, 6, 1130)						   // 0x010646A0	creations patch
#define RUNTIME_VERSION_1_6_1170 MAKE_EXE_VERSION(1, 6, 1170)						   // 0x01064920
#define RUNTIME_VERSION_1_6_1170_GOG MAKE_EXE_VERSION_EX(1, 6, 1170, RUNTIME_TYPE_GOG) // 0x01064921	same version number as steam, possible problem

```
