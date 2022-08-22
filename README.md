# native-export

---

Supported languages:
 - C/C++

Samples:
 * Currently used to [store shaders](https://github.com/MrSinho/shgui/tree/main/shaders/include/shgui) in a [header file](https://github.com/MrSinho/shgui/blob/main/shaders/export-shaders.c) and [font data](https://github.com/MrSinho/shgui/blob/main/fonts/include/fonts/consolas.h) for an immediate mode gui library

A simple library for exporting a structure or some array data to a c-header like output.

---
# Chapters
- [Clone](#clone)
- [C](#c)
    - [Usage example](#usage-example)
    - [Header output](#header-output)
---

## Clone

```bash
git clone --recursive https://github.com/mrsinho/native-export.git
cd native-export/c
mkdir build
cd build
cmake -DNATIVE_EXPORT_BUILD_SAMPLE=ON ..
cmake --build .
```

## C

# [Usage example](c/sample/src/native-export-sample.c)

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

## [Header outputs](c/sample/)

Output with [header file definitions](c/sample/native-export-outputs.h):
```c
#pragma once

#define _NATIVE_EXPORT_SAMPLE_OUTPUT_H

```

Output header file with the [specified data](c/sample/native-export-sample-output.h):
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

---

