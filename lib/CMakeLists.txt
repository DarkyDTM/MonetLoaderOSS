target_sources(${PROJECT_NAME} PRIVATE
    lib/imgui/imgui.cpp
    lib/imgui/imgui_draw.cpp
    lib/imgui/imgui_widgets.cpp
    lib/imgui/imgui_demo.cpp
    lib/imgui/imgui_stdlib.cpp

    lib/imgui_fonts/arial_bold.cpp

    lib/raknet/BitStream.cpp
    lib/raknet/DS_HuffmanEncodingTree.cpp
    lib/raknet/StringCompressor.cpp

    lib/stb_image.cpp
    )