/*
   Project: Native Meson Build Application
   Description: This source file is part of the Trilobite Coder Lab project and is authored by Michael Gene Brockus (Dreamer).
   
   Contact Information:
   - Email: michaelbrockus@gmail.com
   - Website: https://trilobite.code.blog

   License: This software is released under the Apache License 2.0. Please refer to the LICENSE file for more details.

   This Meson build file defines the build configuration for the Native Meson Build Application.
   It contains instructions and settings to build the project, including dependencies, compiler options,
   and other build-related settings. Make sure to review and modify this file as needed for your specific project requirements.

   For more information on Meson build system:
   - Official website: https://mesonbuild.com/
   - Meson documentation: https://meson.readthedocs.io/en/stable/
   - GitHub repository: https://github.com/mesonbuild/meson

   Trilobite Coder Lab:
   - Trilobite Coder Lab is a development and research initiative by Michael Gene Brockus (Dreamer).
     It focuses on various aspects of software development, including programming, open-source projects, and code-related articles.
     Visit the lab's website for more information and resources.

   Author:
   - Name: Michael Gene Brockus (Dreamer)
   - Email: michaelbrockus@gmail.com
   - Website: https://trilobite.code.blog

   License:
   - This project is licensed under the Apache License 2.0.
     For detailed licensing information, please refer to the LICENSE file in the project directory.

   For any questions, concerns, or contributions, feel free to contact the author via email or visit the Trilobite Coder Lab website.
*/
#ifndef APP_H
#define APP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
/* 
   File: bool.h
   Description: This header file provides support for the C99 standard boolean data type and related macros.
   It allows the use of 'bool', 'true', and 'false' in the code for boolean operations.
   For more information on the C99 boolean type, refer to the C standard documentation.
*/

#include <stdio.h>
/* 
   File: stdio.h
   Description: This header file is part of the C Standard Library and provides functions and macros for standard input and output operations.
   It is essential for performing input and output in C programs and includes functions like 'printf' and 'scanf.'
   For more information on the functions and macros provided by 'stdio.h,' refer to the C Standard Library documentation.
*/

#include <stdlib.h>
/* 
   File: stdlib.h
   Description: This header file is part of the C Standard Library and provides functions and macros for general-purpose programming tasks.
   It includes functions like memory allocation, random number generation, and system utilities.
   For more information on the functions and macros provided by 'stdlib.h,' refer to the C Standard Library documentation.
*/

#include <trilobite/xcore.h>
/* 
   File: xcore.h
   Description: This header file is part of the Trilobite library and provides core functionality for the Trilobite framework.
   It includes essential functions and data structures required for working with the Trilobite framework.
   For more information on the Trilobite framework and 'xcore.h,' refer to the Trilobite documentation.
*/

#include <trilobite/xdata.h>
/* 
   File: xdata.h
   Description: This header file is part of the Trilobite library and provides data-related functionality for the Trilobite framework.
   It includes data structures and functions related to data management within the Trilobite framework.
   For more information on the Trilobite framework and 'xdata.h,' refer to the Trilobite documentation.
*/

#ifdef __cplusplus
}
#endif

#endif