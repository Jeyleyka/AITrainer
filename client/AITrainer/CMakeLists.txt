cmake_minimum_required(VERSION 3.16)

project(AITrainer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Test Widgets Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test Widgets Core Network)

# ВСЕ исходники проекта + хедеры с Q_OBJECT
set(PROJECT_SOURCES
    main.cpp
    UI/MainWindow/MainWindow.cpp
    UI/MainWindow/MainWindow.h
    UI/Components/Header/Header.cpp
    UI/Components/Header/Header.h
    Core/AIModelManager/AIModelManager.cpp
    Core/AIModelManager/AIModelManager.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(AITrainer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        UI/Components/NavBar/NavBar.h UI/Components/NavBar/NavBar.cpp
        icons.qrc
        UI/Components/NavBarItem/NavBarItem.h UI/Components/NavBarItem/NavBarItem.cpp
        UI/Components/PrSettingUp/PrSettingUp.h UI/Components/PrSettingUp/PrSettingUp.cpp
        UI/Components/Gender/Gender.h UI/Components/Gender/Gender.cpp
        UI/Components/ClickableWidget/ClickableWidget.h UI/Components/ClickableWidget/ClickableWidget.cpp
        UI/Components/Weigh/Weigh.h UI/Components/Weigh/Weigh.cpp
        UI/Components/Aim/Aim.h UI/Components/Aim/Aim.cpp
        UI/Components/StepPage/StepPage.h UI/Components/StepPage/StepPage.cpp
        UI/Components/Age/Age.h UI/Components/Age/Age.cpp
        UI/Components/HeightAndWeight/HeightAndWeight.h UI/Components/HeightAndWeight/HeightAndWeight.cpp
        UI/Components/HeightWeight.h
        UI/Components/TrainingFormat/TrainingFormat.h UI/Components/TrainingFormat/TrainingFormat.cpp
        UI/Components/TrainingFrequency/TrainingFrequency.h UI/Components/TrainingFrequency/TrainingFrequency.cpp
        UI/Components/EatingType/EatingType.h UI/Components/EatingType/EatingType.cpp

        # UnitTests/AIResponseTest/AIResponseTest.h UnitTests/AIResponseTest/AIResponseTest.cpp
    )
else()
    add_executable(AITrainer ${PROJECT_SOURCES})
endif()

# Подключаем Qt модули
target_link_libraries(AITrainer PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

add_executable(Tests
    UnitTests/AIResponseTest/AIResponseTest.cpp  UnitTests/AIResponseTest/AIResponseTest.h
    Core/AIModelManager/AIModelManager.cpp Core/AIModelManager/AIModelManager.h
)

find_package(Qt6 REQUIRED COMPONENTS Test)

target_link_libraries(Tests Qt6::Test Qt6::Widgets Qt6::Core Qt6::Network)

# Финализируем для Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(AITrainer)
endif()
