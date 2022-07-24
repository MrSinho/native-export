#ifndef NATIVE_EXPORT_H
#define NATIVE_EXPORT_H



#ifdef __cplusplus
extern "C" {
#endif//__cplusplus



#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>



typedef enum NativeExportFormat {
    NATIVE_EXPORT_FORMAT_UNSPECIFIED   = 0,
    NATIVE_EXPORT_FORMAT_INT8          = 1,
    NATIVE_EXPORT_FORMAT_UINT8         = 2,
    NATIVE_EXPORT_FORMAT_INT16         = 3,
    NATIVE_EXPORT_FORMAT_UINT16        = 4,
    NATIVE_EXPORT_FORMAT_INT32         = 5,
    NATIVE_EXPORT_FORMAT_UINT32        = 6,
    NATIVE_EXPORT_FORMAT_INT64         = 7,
    NATIVE_EXPORT_FORMAT_UINT64        = 8,
    NATIVE_EXPORT_FORMAT_FLOAT32       = 9,
    NATIVE_EXPORT_FORMAT_UFLOAT32      = 10,
    NATIVE_EXPORT_FORMAT_DOUBLE64      = 11,
    NATIVE_EXPORT_FORMAT_UDOUBLE64     = 12,
    NATIVE_EXPORT_FORMAT_MAX_ENUM      = 13,
} NativeExportFormat;



typedef enum NativeExportResult {
    NATIVE_EXPORT_SUCCESS                   = 1,
    NATIVE_EXPORT_INVALID_MEMORY            =-2,
    NATIVE_EXPORT_INVALID_FORMAT            =-3,
    NATIVE_EXPORT_INVALID_BUFFER_COUNT      =-4,
    NATIVE_EXPORT_INVALID_SIZE              =-5,
    NATIVE_EXPORT_INVALID_STREAM            =-6
} NativeExportResult;



typedef struct NativeExportBuffer {
    NativeExportFormat  format;
    void*               p_src;
    uint32_t            size;
    char*               name;
} NativeExportBuffer;



typedef struct NativeExportInfo {
    uint32_t            buffer_count;
    NativeExportBuffer* p_buffers;
    char*               header_macro_name;
} NativeExportInfo;



#define nativeExportError(condition, error_msg, failure_expression)\
    if ((int)(condition)) {\
        printf("native export error: %s\n", error_msg);\
        failure_expression;\
    }



extern NativeExportResult nativeExportDescription(void* p_src, const uint32_t src_size, const NativeExportFormat format, const char* description_name, char** pp_dst_description);

extern NativeExportResult nativeExport(NativeExportInfo export_info, char** pp_dst_file_data);

extern NativeExportResult nativeExportWriteHeader(NativeExportInfo export_info, const char* dst_path);

extern NativeExportResult nativeExportGenerateHeaderDefinitions(NativeExportInfo* p_export_infos, const uint32_t export_info_count, const char* dst_path);

static void nativeExportRelease(NativeExportInfo* p_export_info) {
    free(p_export_info->p_buffers);
}



#ifdef __cplusplus
}
#endif//_cplusplus

#endif//NATIVE_EXPORT_H