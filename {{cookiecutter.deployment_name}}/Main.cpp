// ======================================================================
// \title  Main.cpp
// \brief main program for the F' application. Intended for Arduino-based systems
//
// ======================================================================
// Used to access topology functions
#include <{{cookiecutter.deployment_name}}/Top/{{cookiecutter.deployment_name}}TopologyAc.hpp>
#include <{{cookiecutter.deployment_name}}/Top/{{cookiecutter.deployment_name}}Topology.hpp>

#include <FreeRTOS.h>
#include <task.h>

// Used for logging
#include <Arduino/Os/Console.hpp>

void RateLoop(void *params) {
    while (1) {
        rateDriver.cycle();
    }
}

/**
 * \brief setup the program
 *
 * This is an extraction of the Arduino setup() function.
 * 
 */
void setup() {
    // Initialize OSAL
    Os::init();

    // Setup Serial and Logging
    Serial.begin(115200);
    static_cast<Os::Arduino::StreamConsoleHandle*>(Os::Console::getSingleton().getHandle())->setStreamHandler(Serial);

    // Object for communicating state to the reference topology
    {{cookiecutter.deployment_name}}::TopologyState inputs;
    inputs.uartNumber = 0;
    inputs.uartBaud = 115200;

    // Setup topology
    {{cookiecutter.deployment_name}}::setupTopology(inputs);
    xTaskCreate(RateLoop, "RateLoop", 1600, NULL, 1, NULL);

    Fw::Logger::log("Program Started\n");
    vTaskStartScheduler();
}

/**
 * \brief run the program
 *
 * This is an extraction of the Arduino loop() function.
 * 
 */
void loop() {
}