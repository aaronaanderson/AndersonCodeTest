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
        JUCE_WEB_BROWSER=0  
        JUCE_USE_CURL=0 
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:EnvelopeApp,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:EnvelopeApp,JUCE_VERSION>")

target_link_libraries(EnvelopeApp
    PRIVATE
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
