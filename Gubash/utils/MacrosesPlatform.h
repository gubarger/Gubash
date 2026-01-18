// Copyright (c) 2026 Gubarger. All rights reserved.
//
// This file is part of the Gubash project.
// Distributed under the MIT License. See the LICENSE file for details.

#pragma once


// Export.
#if defined(_WIN32)
	#if defined(M_GUBASH_BUILD_SHARED__)
		#define M_GUBASH_EXPORT__ __declspec(dllexport)
	#elif defined(M_GUBASH_USE_SHARED__)
		#define M_GUBASH_EXPORT__ __declspec(dllimport)
	#else
		#define M_GUBASH_EXPORT__
	#endif
#elif defined(__GNUC__) && (defined(__linux__) || defined(__APPLE__))
	#if defined(M_GUBASH_BUILD_SHARED__)
		#define M_GUBASH_EXPORT__ __attribute__((visibility("default")))
	#else
		#define M_GUBASH_EXPORT__
	#endif
#else
	#define M_GUBASH_EXPORT__
#endif

// Architecture (flags).
#if defined(__x86_64__) || defined(_M_X64)
	#define M_GUBASH_ARCH_X86_64__ 1
	#define M_GUBASH_ARCH_64BIT__ 1
#elif defined(__i386__) || defined(_M_IX86)
	#define M_GUBASH_ARCH_X86__ 1
	#define M_GUBASH_ARCH_32BIT__ 1
#elif defined(__aarch64__) || defined(_M_ARM64)
	#define M_GUBASH_ARCH_ARM64__ 1
	#define M_GUBASH_ARCH_64BIT__ 1
#elif defined(__arm__) || defined(_M_ARM)
	#define M_GUBASH_ARCH_ARM__ 1
	#define M_GUBASH_ARCH_32BIT__ 1
#elif defined(__riscv)
	#if __riscv_xlen == 64
		#define M_GUBASH_ARCH_RISCV64__ 1
		#define M_GUBASH_ARCH_64BIT__ 1
	#else
		#define M_GUBASH_ARCH_RISCV32__ 1
		#define M_GUBASH_ARCH_32BIT__ 1
	#endif
#elif defined(__powerpc64__)
	#define M_GUBASH_ARCH_PPC64__ 1
	#define M_GUBASH_ARCH_64BIT__ 1
#elif defined(__mips__)
	#if defined(__mips64)
		#define M_GUBASH_ARCH_MIPS64__ 1
		#define M_GUBASH_ARCH_64BIT__ 1
	#else
		#define M_GUBASH_ARCH_MIPS__ 1
		#define M_GUBASH_ARCH_32BIT__ 1
	#endif
#endif

#ifndef M_GUBASH_ARCH_64BIT__
	#if defined(__SIZEOF_POINTER__) && __SIZEOF_POINTER__ == 8
		#define M_GUBASH_ARCH_64BIT__ 1
	#elif INTPTR_MAX == INT64_MAX
		#define M_GUBASH_ARCH_64BIT__ 1
	#else
		#define M_GUBASH_ARCH_32BIT__ 1
	#endif
#endif

// OS.
#ifdef _WIN32
	#define M_GUBASH_OS_WINDOWS__ 1
	#ifdef _WIN64
		#define M_GUBASH_OS_WIN64__ 1
	#else
		#define M_GUBASH_OS_WIN32__ 1
	#endif
#elif defined(__linux__)
	#define M_GUBASH_OS_LINUX__ 1
#elif defined(__APPLE__) && defined(__MACH__)
	#define M_GUBASH_OS_MACOS__ 1
#elif defined(__FreeBSD__)
	#define M_GUBASH_OS_FREEBSD__ 1
#endif

#if defined(M_GUBASH_OS_LINUX__) || defined(M_GUBASH_OS_MACOS__) || \
    defined(M_GUBASH_OS_FREEBSD__)
	#define M_GUBASH_OS_POSIX__ 1
#endif

// Limited visibility.
// 
// platform-specific API's.
#define M_GUBASH_API__(...)

// OS check.
#define M_GUBASH_WINDOWS_ONLY__(...) \
    M_GUBASH_EXPORT__

#define M_GUBASH_LINUX_ONLY__(...) \
    M_GUBASH_EXPORT__

#define M_GUBASH_MACOS_ONLY__(...) \
    M_GUBASH_EXPORT__

#define M_GUBASH_POSIX_ONLY__(...) \
    M_GUBASH_EXPORT__

// Architecture check.
#define M_GUBASH_64BIT_ONLY__(...) \
    M_GUBASH_EXPORT__

#define M_GUBASH_32BIT_ONLY__(...) \
    M_GUBASH_EXPORT__

#define M_GUBASH_X86_64_ONLY__(...) \
    M_GUBASH_EXPORT__

#define M_GUBASH_ARM64_ONLY__(...) \
    M_GUBASH_EXPORT__

// OC + Architecture.
#define M_GUBASH_WINDOWS_X64_ONLY__(...) \
    M_GUBASH_EXPORT__

#define M_GUBASH_MACOS_ARM64_ONLY__(...) \
    M_GUBASH_EXPORT__

// Conditional class declaration.
#ifdef M_GUBASH_OS_WINDOWS__
	#define M_GUBASH_CLASS_WINDOWS__(name, ...) class __VA_ARGS__ name
	#define M_GUBASH_FUNC_WINDOWS__(ret, name, ...) ret name(__VA_ARGS__)
#else
	#define M_GUBASH_CLASS_WINDOWS__(name, ...) class name##__windows_only_dummy {}
	#define M_GUBASH_FUNC_WINDOWS__(ret, name, ...) inline ret name##__dummy(__VA_ARGS__) { return {}; }
#endif

#ifdef M_GUBASH_OS_LINUX__
	#define M_GUBASH_CLASS_LINUX__(name, ...) class __VA_ARGS__ name
	#define M_GUBASH_FUNC_LINUX__(ret, name, ...) ret name(__VA_ARGS__)
#else
	#define M_GUBASH_CLASS_LINUX__(name, ...) class name##__linux_only_dummy {}
	#define M_GUBASH_FUNC_LINUX__(ret, name, ...) inline ret name##__dummy(__VA_ARGS__) { return {}; }
#endif

#ifdef M_GUBASH_OS_MACOS__
	#define M_GUBASH_CLASS_MACOS__(name, ...) class __VA_ARGS__ name
	#define M_GUBASH_FUNC_MACOS__(ret, name, ...) ret name(__VA_ARGS__)
#else
	#define M_GUBASH_CLASS_MACOS__(name, ...) class name##__macos_only_dummy {}
	#define M_GUBASH_FUNC_MACOS__(ret, name, ...) inline ret name##__dummy(__VA_ARGS__) { return {}; }
#endif

#ifdef M_GUBASH_ARCH_64BIT__
	#define M_GUBASH_CLASS_64BIT__(name, ...) class __VA_ARGS__ name
	#define M_GUBASH_FUNC_64BIT__(ret, name, ...) ret name(__VA_ARGS__)
#else
	#define M_GUBASH_CLASS_64BIT__(name, ...) class name##__64bit_only_dummy {}
	#define M_GUBASH_FUNC_64BIT__(ret, name, ...) inline ret name##__dummy(__VA_ARGS__) { return {}; }
#endif

// Takes a list of platforms and declares a class/function only for them.
#define M_GUBASH_FOR_PLATFORMS__(platforms, type, name, ...) \
    template<bool enabled = false> \
    struct name##_platform_check; \
    \
    name##_platform_check<true> _check_##name(); \
    \
    type name(__VA_ARGS__)

// Simple.
#define M_GUBASH_WINDOWS_FUNC(ret, name, ...) \
    M_GUBASH_FOR_PLATFORMS__("windows", ret, name, __VA_ARGS__)

#define M_GUBASH_LINUX_FUNC(ret, name, ...) \
    M_GUBASH_FOR_PLATFORMS__("linux", ret, name, __VA_ARGS__)

#define M_GUBASH_MACOS_FUNC(ret, name, ...) \
    M_GUBASH_FOR_PLATFORMS__("macos", ret, name, __VA_ARGS__)

// Compiler attributes.
#if defined(__GNUC__) || defined(__clang__)
	#define M_GUBASH_NORETURN__ __attribute__((noreturn))
	#define M_GUBASH_ALWAYS_INLINE__ __attribute__((always_inline))
	#define M_GUBASH_NOINLINE__ __attribute__((noinline))
	#define M_GUBASH_PACKED__ __attribute__((packed))
#elif defined(_MSC_VER)
	#define M_GUBASH_NORETURN__ __declspec(noreturn)
	#define M_GUBASH_ALWAYS_INLINE__ __forceinline
	#define M_GUBASH_NOINLINE__ __declspec(noinline)
	#define M_GUBASH_PACKED__
#else
	#define M_GUBASH_NORETURN__
	#define M_GUBASH_ALWAYS_INLINE__ inline
	#define M_GUBASH_NOINLINE__
	#define M_GUBASH_PACKED__
#endif