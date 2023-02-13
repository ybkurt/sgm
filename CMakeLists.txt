cmake_minimum_required(VERSION 3.0.0)
project(sgm VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(OpenCV REQUIRED)
find_package(CUDA REQUIRED)


if(CUDA_FOUND)
	set(CUDA_NVCC_FLAGS 
	${CUDA_NVCC_FLAGS};
        -O3 -lineinfo
        -gencode=arch=compute_35,code=sm_35
        -gencode=arch=compute_50,code=sm_50
        -gencode=arch=compute_52,code=sm_52
        -gencode arch=compute_61,code=sm_61
        -gencode=arch=compute_75,code=sm_75)

        CUDA_INCLUDE_DIRECTORIES(include)
        include_directories(include)

	if(OpenCV_FOUND)
		CUDA_INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
		include_directories(${OpenCV_INCLUDE_DIRS})

		CUDA_ADD_EXECUTABLE(${PROJECT_NAME} 
    src/main.cpp src/median_filter.cu src/hamming_cost.cu src/disparity_method.cu src/debug.cu src/costs.cu)

		target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
	endif(OpenCV_FOUND)
endif(CUDA_FOUND)
