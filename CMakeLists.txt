cmake_minimum_required(VERSION 3.22)
project(karse C)

set(CMAKE_C_STANDARD 11)

# OpenSSL-START
find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
    message(STATUS "OpenSSL ${OPENSSL_VERSION} was found!")
    message(
            STATUS "OpenSSL info:
    OpenSSL Include Dir: ${OPENSSL_INCLUDE_DIR}
    OpenSSL libs:
      OpenSSL(SSL): ${OPENSSL_SSL_LIBRARY}
      OpenSSL(Crypto): ${OPENSSL_CRYPTO_LIBRARY}"
    )
else(OPENSSL_FOUND)
    message(FATAL_ERROR "OpenSSL Not Found!")
endif(OPENSSL_FOUND)

link_libraries(crypto ssl)
# OpenSSL-END

add_executable(karse src/core/main.c src/core/core.h src/io/io.h src/io/web/http.c src/io/web/http.h src/io/web/socket/linux.c src/io/web/socket/linux.h src/io/web/web.h src/stdafx.h src/crypto/crypto.h src/crypto/key.c src/crypto/key.h src/io/file/file.c src/io/file/file.h src/crypto/x509.c src/crypto/x509.h src/io/web/socket/windows.c src/io/web/socket/windows.h)
