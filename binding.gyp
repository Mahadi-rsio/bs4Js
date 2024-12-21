{
  "variables": {
    "android_ndk_path": "/data/data/com.termux/files/usr/lib/android-ndk",
    "node_include_path": "/data/data/com.termux/files/usr/include/node",
    "python_lib_path": "/data/data/com.termux/files/usr/lib/python3.12",
    "shared_library_path": "./lib"
  },
  "targets": [
    {
      "target_name": "api",
      "sources": [
        "./api/main.c"
      ],
      "include_dirs": [
        "${android_ndk_path}/sysroot/usr/include",
        "${android_ndk_path}/sysroot/usr/include/arm-linux-androideabi", 
        "${android_ndk_path}/sysroot/usr/include/x86_64-linux-android", 
        "${node_include_path}"
      ],
      "libraries": [
        "-L${shared_library_path}",
        "-L${python_lib_path}",
        "-lpython3.12",     
        "-ldl"
      ],
      "cflags": [
        "-fPIC",
      ]
    }
  ]
}
