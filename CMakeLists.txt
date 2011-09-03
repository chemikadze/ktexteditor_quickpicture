project(ktexteditor_quickpicture)

find_package(Qt4 REQUIRED)
include_directories(${QT_INCLUDE_DIR})

find_package(KDE4 4.2.0 REQUIRED)
include(KDE4Defaults)

set(quickpicture_PART_SRCS 
	quickpicture.cpp
	simple_controller.cpp
	controller.cpp
)

kde4_add_plugin(ktexteditor_quickpicture ${quickpicture_PART_SRCS} )

target_link_libraries(ktexteditor_quickpicture ${KDE4_KDECORE_LIBS} ${KDE4_KTEXTEDITOR_LIBS} )

install(TARGETS ktexteditor_quickpicture DESTINATION ${PLUGIN_INSTALL_DIR} )

install(FILES ktexteditor_quickpicture.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
install(FILES ktexteditor_quickpicture.rc  DESTINATION  ${DATA_INSTALL_DIR}/ktexteditor_quickpicture )
