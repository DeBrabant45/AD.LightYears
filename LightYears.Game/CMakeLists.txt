add_executable(${LIGHT_YEARS_GAME_TARGET_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/include/gameframework/GameApplication.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gameframework/GameApplication.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/spaceships/Spaceship.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/spaceships/Spaceship.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/player/PlayerSpaceship.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/player/PlayerSpaceship.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/weapons/Shooter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/weapons/Shooter.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/weapons/BulletShooter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/weapons/BulletShooter.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/weapons/projectiles/Bullet.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/weapons/projectiles/Bullet.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/gameplay/HealthComponent.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gameplay/HealthComponent.cpp
)

target_include_directories(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC ${LIGHT_YEARS_ENGINE_TARGET_NAME})

function(CopyLibDirectoryToTarget LIB_NAME TARGET_NAME)
   add_custom_command(TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND
        ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:${LIB_NAME}>
        $<TARGET_FILE_DIR:${TARGET_NAME}>
    ) 
endfunction()
CopyLibDirectoryToTarget(${LIGHT_YEARS_ENGINE_TARGET_NAME} ${LIGHT_YEARS_GAME_TARGET_NAME})

set(RESOURCE_FOLDER_NAME "assets")
set(RESOURCE_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_FOLDER_NAME}")

add_custom_command(
    TARGET ${LIGHT_YEARS_GAME_TARGET_NAME}
    POST_BUILD
    COMMAND
    ${CMAKE_COMMAND} -E copy_directory
    ${RESOURCE_SRC_DIR}
    $<TARGET_FILE_DIR:${LIGHT_YEARS_GAME_TARGET_NAME}>/${RESOURCE_FOLDER_NAME}
)

configure_file(
    "config.h.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/config.h" ESCAPE_QUOTES
)