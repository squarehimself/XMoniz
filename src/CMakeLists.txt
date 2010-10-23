include (CompizBcop)

compiz_add_bcop_targets (
    core
    ${compiz_BINARY_DIR}/generated/core.xml.in
    _bcop_sources
)

include_directories (
    ${compiz_SOURCE_DIR}/include
    ${compiz_BINARY_DIR}
    ${compiz_BINARY_DIR}/generated
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${COMPIZ_INCLUDE_DIRS}
)

add_definitions (
    -DHAVE_CONFIG_H
    -DPLUGINDIR=\\\"${compiz_plugindir}\\\"
    -DIMAGEDIR=\\\"${compiz_imagedir}\\\"
    -DMETADATADIR=\\\"${compiz_metadatadir}\\\"
)

link_directories (
    ${COMPIZ_LINK_DIRS}
)

add_executable (compiz
    region.cpp
    atoms.cpp
    timer.cpp
    main.cpp
    actions.cpp
    screen.cpp
    window.cpp
    action.cpp
    option.cpp
    string.cpp
    match.cpp
    pluginclasses.cpp
    event.cpp
    plugin.cpp
    session.cpp
    output.cpp
    rect.cpp
    size.cpp
    point.cpp
    windowgeometry.cpp
    icon.cpp
    modifierhandler.cpp
    ${_bcop_sources}
)

target_link_libraries (
    compiz ${COMPIZ_LIBRARIES} m pthread dl
)

install (
    TARGETS compiz
    DESTINATION ${exec_prefix}
)
