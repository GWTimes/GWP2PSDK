//
//  GWP2PLogger.h
//  Yoosee
//
//  Created by JonorZhang on 2019/5/28.
//  Copyright © 2019 Gwell. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifndef __GWP2PLogger_H__
#define __GWP2PLogger_H__

typedef NS_ENUM(NSUInteger, GWLogLevel) {
    GWLogLevelOff,
    GWLogLevelFatal,
    GWLogLevelError,
    GWLogLevelWarning,
    GWLogLevelInfo,
    GWLogLevelDebug,
    GWLogLevelVerbose,
};

/// 打印函数
/// @param level 等级
/// @param file 文件路径
/// @param func 函数名
/// @param line 行号
/// @param repeatedly 是否频繁打印
/// @param fmt 消息格式
extern void _logger_(GWLogLevel level, const char *file, const char *func, int line, bool repeatedly, const char *fmt, ...);

#define logCustom(level, file, func, line, fmt, ...) _logger_(level, file, func, line, NO, fmt, ##__VA_ARGS__);
#define logLevel(level, fmt, ...)   logCustom(level, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)

// 日志输出
#define logError(fmt, ...) _logger_(GWLogLevelError, __FILE__, __FUNCTION__, __LINE__, NO, fmt, ##__VA_ARGS__);
#define logWarning(fmt, ...) _logger_(GWLogLevelWarning, __FILE__, __FUNCTION__, __LINE__, NO, fmt, ##__VA_ARGS__);
#define logInfo(fmt, ...) _logger_(GWLogLevelInfo, __FILE__, __FUNCTION__, __LINE__, NO, fmt, ##__VA_ARGS__);
#define logDebug(fmt, ...) _logger_(GWLogLevelDebug, __FILE__, __FUNCTION__, __LINE__, NO, fmt, ##__VA_ARGS__);
#define logVerbose(fmt, ...) _logger_(GWLogLevelVerbose, __FILE__, __FUNCTION__, __LINE__, NO, fmt, ##__VA_ARGS__);

// 用于高频打印，输出应按1秒折叠
#define logErrorRepeat(fmt, ...) _logger_(GWLogLevelError, __FILE__, __FUNCTION__, __LINE__, YES, fmt, ##__VA_ARGS__);
#define logWarningRepeat(fmt, ...) _logger_(GWLogLevelWarning, __FILE__, __FUNCTION__, __LINE__, YES, fmt, ##__VA_ARGS__);
#define logInfoRepeat(fmt, ...) _logger_(GWLogLevelInfo, __FILE__, __FUNCTION__, __LINE__, YES, fmt, ##__VA_ARGS__);
#define logDebugRepeat(fmt, ...) _logger_(GWLogLevelDebug, __FILE__, __FUNCTION__, __LINE__, YES, fmt, ##__VA_ARGS__);
#define logVerboseRepeat(fmt, ...) _logger_(GWLogLevelDebug, __FILE__, __FUNCTION__, __LINE__, YES, fmt, ##__VA_ARGS__);

#endif
