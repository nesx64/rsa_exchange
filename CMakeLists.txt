cmake_minimum_required(VERSION 3.16)
project(RSA_Simulator)

# Utilisation de Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(OpenSSL REQUIRED)


set(CMAKE_AUTOMOC ON)  # Active la génération automatique de moc (Qt Meta-Object Compiler)
set(CMAKE_AUTOUIC ON)  # Active la génération automatique des fichiers .ui
set(CMAKE_AUTORCC ON)  # Active la génération automatique des fichiers .qrc

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
        RSA_controller/Generator.cpp)

target_link_libraries(RSA_Simulator
        Qt6::Widgets
        OpenSSL::SSL     # Ajouter ces deux lignes
        OpenSSL::Crypto)  # Remplace par Qt5::Widgets si Qt5 est utilisé
