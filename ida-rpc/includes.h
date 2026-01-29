#pragma once

#define _CRT_SECURE_NO_WARNINGS 1
#define __IDP__                 1

// Platform detection
#if defined(_WIN32) || defined(_WIN64)
#define __NT__                  1
#else
#define __LINUX__               1
#endif

#define __X64__                 1

#define plugin_name "IDA RPC"

#include <ida.hpp>
#include <idp.hpp>
#include <frame.hpp>
#include <expr.hpp>
#include <name.hpp>
#include <segment.hpp>
#include <bytes.hpp>
#include <loader.hpp>
#include <kernwin.hpp>
#include <auto.hpp>
#include <entry.hpp>
#include <bytes.hpp>
#include <typeinf.hpp>
#include <demangle.hpp>
#include <allins.hpp>
#include <search.hpp>
#include <ua.hpp>
#include <fpro.h>
#include <diskio.hpp>