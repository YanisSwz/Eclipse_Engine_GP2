include(FetchContent)

if (NOT TARGET googletest)
	FetchContent_Declare(
		googletest
		GIT_REPOSITORY https://github.com/google/googletest
		GIT_TAG v1.16.0
		SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/googletest
	)

	if (MSVC)
		# For Windows: Prevent overriding the parent project's compiler/linker settings
		set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	endif()

	FetchContent_MakeAvailable(googletest)
endif()


if (NOT TARGET glm)
	FetchContent_Declare(
		glm
		GIT_REPOSITORY	https://github.com/g-truc/glm.git
		GIT_TAG 1.0.1
		SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glm
	)

	FetchContent_MakeAvailable(glm)
endif()

target_link_libraries(MATH_LIB_UT PRIVATE gtest_main)
target_link_libraries(MATH_LIB_UT PRIVATE glm::glm)