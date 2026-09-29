include(ExternalProject)

set(OPENSSL_VERSION "openssl-3.5.3")

set(OPENSSL_SOURCE_DIR
    "${CMAKE_BINARY_DIR}/_deps/openssl-src"
)

set(OPENSSL_BINARY_DIR
    "${CMAKE_BINARY_DIR}/_deps/openssl-build"
)

set(OPENSSL_INSTALL_DIR
    "${CMAKE_BINARY_DIR}/_deps/openssl-install"
)

set(OPENSSL_INCLUDE_DIR
    "${OPENSSL_INSTALL_DIR}/include"
)

if(WIN32)

    if(NOT MSVC)
        message(FATAL_ERROR
            "Windows builds currently require MSVC."
        )
    endif()

    find_program(PERL_EXECUTABLE perl REQUIRED)
    find_program(NMAKE_EXECUTABLE nmake REQUIRED)

    set(OPENSSL_SSL_LIBRARY
        "${OPENSSL_INSTALL_DIR}/lib/libssl.lib"
    )

    set(OPENSSL_CRYPTO_LIBRARY
        "${OPENSSL_INSTALL_DIR}/lib/libcrypto.lib"
    )

    set(OPENSSL_CONFIGURE_COMMAND
        "${PERL_EXECUTABLE}"
        "${OPENSSL_SOURCE_DIR}/Configure"
    )

    set(OPENSSL_CONFIGURE_ARGS
        VC-WIN64A
        no-shared
        no-tests
        "--prefix=${OPENSSL_INSTALL_DIR}"
        "--openssldir=${OPENSSL_INSTALL_DIR}"
    )

    set(OPENSSL_BUILD_COMMAND
        "${NMAKE_EXECUTABLE}"
    )

    set(OPENSSL_INSTALL_COMMAND
        "${NMAKE_EXECUTABLE}"
        install_sw
    )

elseif(UNIX AND NOT APPLE)

    set(OPENSSL_SSL_LIBRARY
        "${OPENSSL_INSTALL_DIR}/lib64/libssl.a"
    )

    set(OPENSSL_CRYPTO_LIBRARY
        "${OPENSSL_INSTALL_DIR}/lib64/libcrypto.a"
    )

    set(OPENSSL_CONFIGURE_COMMAND
        "${OPENSSL_SOURCE_DIR}/Configure"
    )

    set(OPENSSL_CONFIGURE_ARGS
        linux-x86_64
        no-shared
        no-tests
        "--prefix=${OPENSSL_INSTALL_DIR}"
        "--openssldir=${OPENSSL_INSTALL_DIR}"
    )

    set(OPENSSL_BUILD_COMMAND
        make
    )

    set(OPENSSL_INSTALL_COMMAND
        make install_sw
    )

else()

    message(FATAL_ERROR
        "Unsupported platform: ${CMAKE_SYSTEM_NAME}"
    )

endif()


ExternalProject_Add(OpenSSLExternal

    PREFIX
        "${CMAKE_BINARY_DIR}/_deps/openssl"

    SOURCE_DIR
        "${OPENSSL_SOURCE_DIR}"

    BINARY_DIR
        "${OPENSSL_BINARY_DIR}"

    GIT_REPOSITORY
        https://github.com/openssl/openssl.git

    GIT_TAG
        ${OPENSSL_VERSION}

    GIT_SHALLOW
        TRUE

    CONFIGURE_COMMAND
        ${OPENSSL_CONFIGURE_COMMAND}
        ${OPENSSL_CONFIGURE_ARGS}

    BUILD_COMMAND
        ${OPENSSL_BUILD_COMMAND}

    INSTALL_COMMAND
        ${OPENSSL_INSTALL_COMMAND}

    TEST_COMMAND
        ""

    USES_TERMINAL_DOWNLOAD
        TRUE

    USES_TERMINAL_CONFIGURE
        TRUE

    USES_TERMINAL_BUILD
        TRUE

    USES_TERMINAL_INSTALL
        TRUE
)

# ExternalProject builds the libraries during the build phase, so create
# the include directory now; this allows CMake to validate the imported
# target's INTERFACE_INCLUDE_DIRECTORIES during configuration

file(MAKE_DIRECTORY
    "${OPENSSL_INCLUDE_DIR}"
)

add_library(OpenSSL::Crypto STATIC IMPORTED GLOBAL)

set_target_properties(OpenSSL::Crypto PROPERTIES
    IMPORTED_LOCATION
        "${OPENSSL_CRYPTO_LIBRARY}"

    INTERFACE_INCLUDE_DIRECTORIES
        "${OPENSSL_INCLUDE_DIR}"
)

add_dependencies(
    OpenSSL::Crypto
    OpenSSLExternal
)

add_library(OpenSSL::SSL STATIC IMPORTED GLOBAL)

set_target_properties(OpenSSL::SSL PROPERTIES
    IMPORTED_LOCATION
        "${OPENSSL_SSL_LIBRARY}"

    INTERFACE_INCLUDE_DIRECTORIES
        "${OPENSSL_INCLUDE_DIR}"

    INTERFACE_LINK_LIBRARIES
        OpenSSL::Crypto
)

add_dependencies(
    OpenSSL::SSL
    OpenSSL::Crypto
)
