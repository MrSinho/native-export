#ifdef __cplusplus
extern "C" {
#endif//_cplusplus


#include <native-export/native-export.h>//to export

#include "../native-export-outputs.h"//to check macro definitions

#ifdef _NATIVE_EXPORT_SAMPLE_OUTPUT_H
#include "../native-export-sample-output.h"//generated header
#endif//_NATIVE_EXPORT_SAMPLE_OUTPUT_H

#include <assert.h>

#ifdef _MSC_VER
#pragma warning (disable: 4996 6386 6001)
#endif//_MSC_VER


int main(void) {

	float src_0[3] = {
		165.0f, 1613.0f, 7891.0f
	};

	uint8_t src_1[10] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	NativeExportBuffer buffer_0 = {
		NATIVE_EXPORT_FORMAT_FLOAT32,
		src_0,
		sizeof(src_0),
		"src_buffer"
	};

	NativeExportBuffer buffer_1 = {
		NATIVE_EXPORT_FORMAT_UINT8,
		src_1,
		sizeof(src_1),
		"src_buffer_1"
	};


	NativeExportBuffer buffers[2] = { buffer_0, buffer_1 };

	NativeExportInfo export_info = {
		2,
		buffers,
		"NATIVE_EXPORT_SAMPLE_OUTPUT_H"
	};

	{//Get file data
		char* dst_file;
		nativeExport(export_info, &dst_file);
		printf("c header file:\n\n\n%s\n\n\n", dst_file);
	}

	{
		nativeExportWriteHeader(export_info, "../sample/native-export-sample-output.h");
	}

	nativeExportGenerateHeaderDefinitions(&export_info, 1, "../sample/native-export-outputs.h");

#ifdef _NATIVE_EXPORT_SAMPLE_OUTPUT_H
		puts("READING HEADER VALUES");
		float* p_values = (float*)src_buffer;//defined at generated header "../native-export-sample-output.h"
		printf("buffer 0 values: %f, %f, %f\n", p_values[0], p_values[1], p_values[2]);
#endif//_NATIVE_EXPORT_SAMPLE_OUTPUT_H

	return 0;
}


#ifdef __cplusplus
}
#endif//_cplusplus

