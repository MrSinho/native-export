# native-export

Supported languages:
 - C/C++

A simple library for exporting a structure or some array data to a c-header like output.

## Clone and build

```bash
git clone --recursive https://github.com/mrsinho/native-export.git
cd native-export/c
mkdir build
cd build
cmake -DNATIVE_EXPORT_BUILD_SAMPLE=ON ..
cmake --build .
```

## [Usage example](c/sample/src/native-export-sample.c)

```c
#include <native-export/native-export.h>
#include <assert.h>

int main(void) {

	float src[3] = {
		165.0f, 1613.0f, 7891.0f
	};

	NativeExportBuffer buffer_0 = {
		NATIVE_EXPORT_FORMAT_FLOAT32,
		src,
		sizeof(src),
		"src_buffer"
	};

	NativeExportInfo export_info = {
	    1,
		&buffer_0
	};

	char* dst_file;
	nativeExport(export_info, &dst_file);

	printf("c header file:\n\n\n%s\n\n\n", dst_file);

	free(dst_file);

	return 0;
}
```

## [Header output](c/sample/native-export-output.h)

```c
#pragma once
#ifdef __cplusplus
extern "C" {
#endif//__cplusplus


#include <stdint.h>


static const int32_t src_buffer[3] = {
	0x43250000,
	0x44c9a000,
	0x45f69800
};


#ifdef __cplusplus
}
#endif//cplusplus
```

To reinterpret the `src_buffer` data as floating point values, do:

```c
float* as_floats = (float*)src_buffer;
    
printf("%f, %f, %f\n", as_floats[0], as_floats[1], as_floats[2]);
```