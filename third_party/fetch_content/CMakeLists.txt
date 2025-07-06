include(FetchContent)

# --------------------------------------------------------------------

# Offline mode (uncomment next line to enable)
# set(FETCHCONTENT_FULLY_DISCONNECTED ON)

# set(FETCHCONTENT_QUIET OFF)

# --------------------------------------------------------------------

cmake_policy(SET CMP0135 NEW)

# --------------------------------------------------------------------

# Libraries

# --------------------------------------------------------------------

# fmt with println

project_log("FetchContent: fmt")

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 10.2.1
)
FetchContent_MakeAvailable(fmt)

# --------------------------------------------------------------------

# Unique Function

project_log("FetchContent: function2")

FetchContent_Declare(
        function2
        GIT_REPOSITORY https://github.com/Naios/function2.git
        GIT_TAG 4.2.2
)
FetchContent_MakeAvailable(function2)

# --------------------------------------------------------------------

FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)

FetchContent_MakeAvailable(json)

# --------------------------------------------------------------------

project_log("FetchContent: wheels")

FetchContent_Declare(
        wheels
        GIT_REPOSITORY https://gitlab.com/Lipovsky/wheels.git
        GIT_TAG 97de8bf57c2b0c8e6d590a0c7458d1731fe0b8fe
)
FetchContent_MakeAvailable(wheels)

# --------------------------------------------------------------------

project_log("FetchContent: sure-stack")

FetchContent_Declare(
        sure-stack
        GIT_REPOSITORY https://gitlab.com/Lipovsky/sure-stack.git
        GIT_TAG 9b719cadb2b87d9cb15a5f6f6291903154bad6d8
)
FetchContent_MakeAvailable(sure-stack)

# --------------------------------------------------------------------

project_log("FetchContent: sure")

FetchContent_Declare(
        sure
        GIT_REPOSITORY https://gitlab.com/Lipovsky/sure.git
        GIT_TAG 3deee6d66d40909fe1f468d9b75cd8ff8c0d57db
)
FetchContent_MakeAvailable(sure)

# --------------------------------------------------------------------

project_log("FetchContent: futex_like")

FetchContent_Declare(
        futex_like
        GIT_REPOSITORY https://gitlab.com/Lipovsky/futex_like.git
        GIT_TAG 55810cd99c551fe98e2a835b1bec51ea383dad98
)
FetchContent_MakeAvailable(futex_like)

# --------------------------------------------------------------------

project_log("FetchContent: spin_wait")

FetchContent_Declare(
        spin_wait
        GIT_REPOSITORY https://gitlab.com/Lipovsky/spin_wait.git
        GIT_TAG 1c558bec396264c031213c37a48bca0e9dca16c5
)
FetchContent_MakeAvailable(spin_wait)

# --------------------------------------------------------------------

project_log("FetchContent: twist")

FetchContent_Declare(
        twist
        GIT_REPOSITORY https://gitlab.com/Lipovsky/twist.git
        GIT_TAG e4fd73e5a12077880f7af46984b232548de0bd27
)
FetchContent_MakeAvailable(twist)

# --------------------------------------------------------------------

project_log("FetchContent: vvv")

FetchContent_Declare(
        vvv
        GIT_REPOSITORY https://gitlab.com/Lipovsky/vvv.git
        GIT_TAG 9889f40c587b9498ccfcdcf6c4e305173fffb50b
)
FetchContent_MakeAvailable(vvv)


# --------------------------------------------------------------------

project_log("FetchContent: tinyfiber")

FetchContent_Declare(
        tinyfiber
        GIT_REPOSITORY https://gitlab.com/Lipovsky/tinyfiber.git
        GIT_TAG ce3d8ee6d943f4100490d2131e3b46afbdbfc3c9
)
FetchContent_MakeAvailable(tinyfiber)

# --------------------------------------------------------------------

# Memory allocation

if((CMAKE_BUILD_TYPE MATCHES Release) AND NOT TWIST_FAULTY)
    project_log("FetchContent: mimalloc")

    FetchContent_Declare(
            mimalloc
            GIT_REPOSITORY https://github.com/microsoft/mimalloc
            GIT_TAG v2.2.3
    )
    FetchContent_MakeAvailable(mimalloc)

endif()
