hunter_config(CURL VERSION ${HUNTER_CURL_VERSION} CMAKE_ARGS HTTP_ONLY=ON CMAKE_USE_OPENSSL=OFF CMAKE_USE_LIBSSH2=OFF CURL_CA_PATH=none)
hunter_config(Boost VERSION 1.66.0)

hunter_config(vapash VERSION 0.4.3
    URL https://github.com/marlonhanks/vapash/archive/v0.4.3.tar.gz
    SHA1 c4afb2cc6f56931ed8e433e80aae9553c6fc4662
)