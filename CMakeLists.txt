cmake_minimum_required(VERSION 3.12)

project(ENVELOPE_APP VERSION 0.0.1)

add_subdirectory(JUCE)                    

juce_add_gui_app(EnvelopeApp
    PRODUCT_NAME "CodeTest_Anderson")    


target_sources(EnvelopeApp
    PRIVATE
        Source/Main.cpp
        Source/MainComponent.cpp
        Source/Envelope.cpp
        Source/EnvelopeComponent.cpp)

target_compile_definitions(EnvelopeApp
    PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:EnvelopeApp,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:EnvelopeApp,JUCE_VERSION>")

target_link_libraries(EnvelopeApp
    PRIVATE
        # GuiAppData            # If we'd created a binary data target, we'd link to it here
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
