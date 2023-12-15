#ifdef __cplusplus
extern "C" {
#endif//__cplusplus



#include <native-export/native-export.h>



#ifdef _MSC_VER
#pragma warning (disable: 4996)
#endif//_MSC_VER



NativeExportResult nativeExportDescription(void* p_src, const uint32_t src_size, const NativeExportFormat format, const char* description_name, char** pp_dst_description) {
    nativeExportError(p_src == NULL, "invalid src buffer", return NATIVE_EXPORT_INVALID_MEMORY);
    nativeExportError(src_size == 0, "invalid src size", return NATIVE_EXPORT_INVALID_SIZE);
    nativeExportError(format >= NATIVE_EXPORT_FORMAT_MAX_ENUM, "invalid format", return NATIVE_EXPORT_INVALID_FORMAT);
    nativeExportError(description_name == NULL, "invalid description name", return NATIVE_EXPORT_INVALID_MEMORY);
    nativeExportError(pp_dst_description == NULL, "invalid description memory", return NATIVE_EXPORT_INVALID_MEMORY);

    uint32_t item_max_char_count = 0;
    uint32_t item_size = 0;
    
    char description_start[64] = "static const ";

    switch (format) {
    case NATIVE_EXPORT_FORMAT_UNSPECIFIED:
        item_size = 1;
        item_max_char_count = 16;
        strcat(description_start, "int8_t ");
        break;
    case NATIVE_EXPORT_FORMAT_INT8:
        item_size = 1;
        item_max_char_count = 3;
        strcat(description_start, "int8_t ");
        break;   
    case NATIVE_EXPORT_FORMAT_UINT8:
        item_size = 1;
        item_max_char_count = 3;
        strcat(description_start, "uint8_t ");
        break;
    case NATIVE_EXPORT_FORMAT_INT16:
        item_size = 2;
        item_max_char_count = 5;
        strcat(description_start, "int16_t ");
        break;  
    case NATIVE_EXPORT_FORMAT_UINT16:
        item_size = 2;
        item_max_char_count = 5;
        strcat(description_start, "uint16_t ");
        break; 
    case NATIVE_EXPORT_FORMAT_INT32:
        item_size = 4;
        item_max_char_count = 10;
        strcat(description_start, "int32_t ");
        break;  
    case NATIVE_EXPORT_FORMAT_UINT32:
        item_size = 4;
        item_max_char_count = 10;
        strcat(description_start, "uint32_t ");
        break; 
    case NATIVE_EXPORT_FORMAT_INT64:
        item_size = 8;
        item_max_char_count = 19;
        strcat(description_start, "int64_t ");
        break;
    case NATIVE_EXPORT_FORMAT_UINT64:
        item_size = 8;
        item_max_char_count = 16;
        strcat(description_start, "uint64_t ");
        break; 
    case NATIVE_EXPORT_FORMAT_FLOAT32:
        item_size = 4;
        item_max_char_count = 16;
        strcat(description_start, "int32_t ");
        break; 
    case NATIVE_EXPORT_FORMAT_UFLOAT32:
        item_size = 4;
        item_max_char_count = 16;
        strcat(description_start, "uint32_t ");
        break;
    case NATIVE_EXPORT_FORMAT_DOUBLE64:
        item_size = 8;
        item_max_char_count = 16;
        strcat(description_start, "int64_t ");
        break; 
    case NATIVE_EXPORT_FORMAT_UDOUBLE64:
        item_size = 8;
        item_max_char_count = 16;
        strcat(description_start, "uint64_t ");
        break;
    default:
        return NATIVE_EXPORT_INVALID_FORMAT;
    }


    const uint32_t item_count = src_size / item_size;


    strcat(description_start, description_name);
    char s_arr_size[256];
    sprintf(s_arr_size, "[%" PRIu32 "] = {\n", item_count);
    strcat(description_start, s_arr_size);

    //                                          representing values             +   commas, line endings and tabs
    char* description_body = (char*)calloc(1, (item_max_char_count * item_count) + (item_count * 3));
    nativeExportError(description_body == NULL, "invalid description body memory", return NATIVE_EXPORT_INVALID_MEMORY);

    for (uint32_t item_idx = 0; item_idx < item_count; item_idx++) {
        char s_value[24] = ""; 

        void* p_value = (void*)&((int8_t*)p_src)[item_idx * item_size];
        
        int8_t      val_i8       = *(int8_t*)p_value;
        uint8_t     val_ui8      = *(uint8_t*)p_value;
        int16_t     val_i16      = *(int16_t*)p_value;
        uint16_t    val_ui16     = *(uint16_t*)p_value;
        int32_t     val_i32      = *(int32_t*)p_value;
        uint32_t    val_ui32     = *(uint32_t*)p_value;
        int64_t     val_i64      = *(int64_t*)p_value;
        uint64_t    val_ui64     = *(uint64_t*)p_value;
        float       val_f32      = *(float*)p_value;
        double      val_d64      = *(double*)p_value;

        switch (format) {
        case NATIVE_EXPORT_FORMAT_UNSPECIFIED:
            sprintf(s_value, "0x%" PRIx8, val_i8);
            break;
        case NATIVE_EXPORT_FORMAT_INT8:
            sprintf(s_value, "%" PRId8, val_i8);
            break;   
        case NATIVE_EXPORT_FORMAT_UINT8:
            sprintf(s_value, "%" PRIu8, val_ui8);
            break;
        case NATIVE_EXPORT_FORMAT_INT16:
            sprintf(s_value, "%" PRIi16, val_i16);
            break;  
        case NATIVE_EXPORT_FORMAT_UINT16:
            sprintf(s_value, "%" PRIu16, val_ui16);
            break; 
        case NATIVE_EXPORT_FORMAT_INT32:
            sprintf(s_value, "%" PRIi32, val_i32);
            break;  
        case NATIVE_EXPORT_FORMAT_UINT32:
            sprintf(s_value, "%" PRIu32, val_ui32);
            break; 
        case NATIVE_EXPORT_FORMAT_INT64:
            sprintf(s_value, "%" PRId64, val_i64);
            break;
        case NATIVE_EXPORT_FORMAT_UINT64:
            sprintf(s_value, "%" PRIu64, val_ui64);
            break; 
        case NATIVE_EXPORT_FORMAT_FLOAT32:
            sprintf(s_value, "0x%" PRIx32, val_i32);
            break; 
        case NATIVE_EXPORT_FORMAT_UFLOAT32:
            sprintf(s_value, "0x%" PRIx32, val_i32);
            break;
        case NATIVE_EXPORT_FORMAT_DOUBLE64:
            sprintf(s_value, "0x%" PRIx64, val_i64);
            break;
        case NATIVE_EXPORT_FORMAT_UDOUBLE64:
            sprintf(s_value, "0x%" PRIx64, val_i64);
            break;
        default:
            return NATIVE_EXPORT_INVALID_FORMAT;
        }

        strcat(description_body, "\t");
        strcat(description_body, s_value);

        if (item_idx == (item_count - 1)) {
            strcat(description_body, "\n");
        }
        else {
            strcat(description_body, ",\n");
        }
    }

    const char* description_end = "};\n\n";

    //create mega string
    char* description = (char*)calloc(1,
        strlen(description_start) + 
        strlen(description_body) + 
        strlen(description_end) + 1
    );
    nativeExportError(description == NULL, "invalid description memory", return NATIVE_EXPORT_INVALID_MEMORY);

    strcpy(description, description_start);
    strcat(description, description_body);
    strcat(description, description_end);

    free(description_body);

    (*pp_dst_description) = description;

    return NATIVE_EXPORT_SUCCESS;
}



NativeExportResult nativeExport(NativeExportInfo export_info, char** pp_dst_file_data) {
    nativeExportError(export_info.buffer_count == 0, "invalid buffer count", return NATIVE_EXPORT_INVALID_BUFFER_COUNT);
    nativeExportError(export_info.p_buffers == NULL, "invalid buffers memory", return NATIVE_EXPORT_INVALID_MEMORY);
    nativeExportError(pp_dst_file_data == NULL, "invalid destination file memory", return NATIVE_EXPORT_INVALID_MEMORY);
    
    char start[1024];
    if (export_info.header_macro_name == NULL) {
        strcpy(start, "#pragma once\n");
    }
    else {
        strcpy(start, "#ifndef ");
        strcat(start, export_info.header_macro_name);
        strcat(start, "\n\
#define ");
        strcat(start, export_info.header_macro_name);
        strcat(start, "\n\n");
    }
    strcat(start, "\
#ifdef __cplusplus\n\
extern \"C\" {\n\
#endif//__cplusplus\n\n\n\
#include <stdint.h>\n\n\n");

    char** pp_descriptions = calloc(export_info.buffer_count, sizeof(char*));
    nativeExportError(pp_descriptions == NULL, "invalid descriptions memory", return NATIVE_EXPORT_INVALID_MEMORY);

    uint32_t descriptions_size = 0;
    for (uint32_t buffer_idx = 0; buffer_idx < export_info.buffer_count; buffer_idx++) {
        char* description = NULL;
        NativeExportResult r = nativeExportDescription(
            export_info.p_buffers[buffer_idx].p_src, 
            export_info.p_buffers[buffer_idx].size, 
            export_info.p_buffers[buffer_idx].format, 
            export_info.p_buffers[buffer_idx].name, 
            &description
        );

        nativeExportError(
            r != NATIVE_EXPORT_SUCCESS,
            "failed exporting description",
            free(pp_descriptions);  return 0
        );

        pp_descriptions[buffer_idx] = description;
        descriptions_size += (uint32_t)strlen(description);
    }

    char end[1024];
    strcpy(end, "\n\
#ifdef __cplusplus\n\
}\n\
#endif//cplusplus");
    if (export_info.header_macro_name != NULL) {
        strcat(end, "\n#endif//");
        strcat(end, export_info.header_macro_name);
    }


    char* file_data = calloc(1, strlen(start) + descriptions_size + strlen(end) + 1);
    nativeExportError(file_data == NULL, "invalid file data", return NATIVE_EXPORT_INVALID_MEMORY);

    strcpy(file_data, start);

    for (uint32_t buffer_idx = 0; buffer_idx < export_info.buffer_count; buffer_idx++) {
        strcat(file_data, pp_descriptions[buffer_idx]);
        free(pp_descriptions[buffer_idx]);
    }
    free(pp_descriptions);

    strcat(file_data, end);

    (*pp_dst_file_data) = file_data;

    return NATIVE_EXPORT_SUCCESS;
}

NativeExportResult nativeExportWriteHeader(NativeExportInfo export_info, const char* dst_path) {
    nativeExportError(dst_path == NULL, "invalid destination path", return NATIVE_EXPORT_INVALID_MEMORY);

    NativeExportResult r = NATIVE_EXPORT_SUCCESS;

    char* dst_file_data = NULL;
    r = nativeExport(export_info, &dst_file_data);

    if (r != NATIVE_EXPORT_SUCCESS) {
        return r;
    }

    FILE* dst_stream = fopen(dst_path, "w");
    nativeExportError(dst_stream == NULL, "invalid destination file stream", return NATIVE_EXPORT_INVALID_STREAM);
    fwrite(dst_file_data, 1, strlen(dst_file_data), dst_stream);
    fclose(dst_stream);

    return NATIVE_EXPORT_SUCCESS;
}

NativeExportResult nativeExportGenerateHeaderDefinitions(NativeExportInfo* p_export_infos, const uint32_t export_info_count, const char* dst_path) {

    uint32_t additional_size = 0;
    for (uint32_t export_idx = 0; export_idx < export_info_count; export_idx++) {
        additional_size += 1 + (uint32_t)strlen(p_export_infos[export_idx].header_macro_name) + (uint32_t)strlen("#define ") + 1;
    }

    const char* common = "#pragma once\n\n";

    uint32_t file_size = (uint32_t)strlen(common) + additional_size;
    char* dst_file_data = calloc(1, file_size);
    nativeExportError(dst_file_data == NULL, "invalid destination file data", return NATIVE_EXPORT_INVALID_MEMORY);

    strcpy(dst_file_data, common);
    for (uint32_t export_idx = 0; export_idx < export_info_count; export_idx++) {
        strcat(dst_file_data, "#define _");
        strcat(dst_file_data, p_export_infos[export_idx].header_macro_name);
        strcat(dst_file_data, "\n");
    }

    FILE* dst_stream = fopen(dst_path, "w");
    nativeExportError(dst_stream == NULL, "invalid destination file stream", return NATIVE_EXPORT_INVALID_STREAM);
    fwrite(dst_file_data, file_size, 1, dst_stream);
    fclose(dst_stream);

    return NATIVE_EXPORT_SUCCESS;
}

#ifdef __cplusplus
}
#endif//__cplusplus