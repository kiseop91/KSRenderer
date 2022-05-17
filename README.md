![macos build](https://github.com/kiseop91/KSRenderer/actions/workflows/cmake.yml/badge.svg)
# 🎥 KSRenderer

# 📁 디렉토리 
 - library : 프로젝트에서 사용하는 외부 라이브러리
 - source  : 프로젝트 소스코드 

 # 👨‍💻 빌드
```cmake
cmake_minimum_required(VERSION 3.16.2 FATAL_ERROR)
```
```console
mkdir build
cd build
cmake .. -G Xcode
xcodebuild -project KSRenderer.xcodeproj && ./Debug/KSRenderer
```
