#ifdef __cplusplus
extern "C" {
#endif//_cplusplus


#include <native-export/native-export.h>
#include <assert.h>

#ifdef _MSC_VER
#pragma warning (disable: 4996)
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
		buffers
	};


	char* dst_file;
	nativeExport(export_info, &dst_file);

	printf("c header file:\n\n\n%s\n\n\n", dst_file);

	{//WRITE HEADER FILE
		FILE* dst_stream = fopen("../sample/native-export-output.h", "w");
		assert(dst_stream != NULL);
		fwrite(dst_file, 1, strlen(dst_file), dst_stream);
		fclose(dst_stream);
	}//WRITE HEADER FILE


	free(dst_file);

	return 0;
}


#ifdef __cplusplus
}
#endif//_cplusplus

