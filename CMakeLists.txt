cmake_minimum_required(VERSION 3.16)
project(RSA_Simulator)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(OpenSSL REQUIRED)

qt_wrap_ui(UI_HEADERS ${CMAKE_SOURCE_DIR}/dev_rsa-ex.ui)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(RSA_Simulator main.cpp
        RSA_model/keys/KeyModel.cpp
        RSA_model/keys/KeyModel.h
        RSA_model/keys/PublicKeyModel.cpp
        RSA_model/keys/PublicKeyModel.h
        RSA_model/keys/PrivateKeyModel.cpp
        RSA_model/keys/PrivateKeyModel.h
        RSA_model/UserModel.cpp
        RSA_model/RSAModel.cpp
        RSA_model/RSAModel.h
        RSA_controller/RSAController.cpp
        RSA_controller/RSAController.h
        RSA_model/CAModel.cpp
        RSA_model/CAModel.h
        RSA_model/Certificate.cpp
        RSA_model/Certificate.h
        RSA_controller/Generator.cpp
        RSA_view/RSAWindow.hpp
        RSA_view/RSAWindow.cpp
        RSA_view/RSAClient.cpp
        RSA_view/RSAClient.h
        RSA_model/Message.cpp
        RSA_model/Message.h
        ${UI_HEADERS}
)

target_link_libraries(RSA_Simulator
        Qt6::Widgets
        OpenSSL::SSL
        OpenSSL::Crypto)