#ifndef SMC_H
#define SMC_H

#include <stdio.h>  // For basic error reporting (can be customized)
#include <stdlib.h> // For memory management

// ----------------------------------------------------------------------------
// Module Definition Macros
// ----------------------------------------------------------------------------

// SMC_MODULE_BEGIN(module_name) - Starts the definition of a module.
#define SMC_MODULE_BEGIN(module_name) \
    typedef struct { \
        void* private_data;  // Pointer for encapsulating module-specific data

// SMC_MODULE_DATA(data_type, data_name) - Declares a member in the module's data struct.
#define SMC_MODULE_DATA(data_type, data_name) \
        data_type data_name;

// SMC_MODULE_END(module_name) - Ends the module definition.
#define SMC_MODULE_END(module_name) \
    } module_name##_t; \
    extern module_name##_t module_name; \
    void module_name##_init();  // Initialization function for the module

// ----------------------------------------------------------------------------
// Interface Function Declaration Macro
// ----------------------------------------------------------------------------
#define SMC_API(return_type, function_name, arg_list) \
    return_type module_name##_##function_name arg_list

// ----------------------------------------------------------------------------
// Dependency Declaration Macro
// ----------------------------------------------------------------------------
#define SMC_DEPENDS_ON(module_name, function_name, arg_list) \
    extern return_type module_name##_##function_name arg_list

// ----------------------------------------------------------------------------
// Error Handling Macros
// ----------------------------------------------------------------------------
#define SMC_ERROR(error_code, message) \
    fprintf(stderr, "ERROR: [%s:%d] (%d) - %s\n", __FILE__, __LINE__, error_code, message)

// ----------------------------------------------------------------------------
// Logging Macros
// ----------------------------------------------------------------------------
#define SMC_LOG(level, message) \
    fprintf(stdout, "[%s] %s: %s\n", level, __func__, message)

// ----------------------------------------------------------------------------
// Memory Management Macros
// ----------------------------------------------------------------------------
#define SMC_ALLOC(size) malloc(size)
#define SMC_FREE(ptr) free(ptr)

// ----------------------------------------------------------------------------
// Example Usage (Conceptual)
// ----------------------------------------------------------------------------

// Example module for handling network connections
SMC_MODULE_BEGIN(network)
    SMC_MODULE_DATA(int, socket_fd);
    SMC_MODULE_DATA(char*, host);
    SMC_MODULE_DATA(int, port);
SMC_MODULE_END(network)

// Function prototypes
SMC_API(int, connect, (const char* host, int port));
SMC_API(void, disconnect, (void));

// Implementation of the network module
void network_init() {
    network.private_data = SMC_ALLOC(sizeof(int)); // Example of allocating private data
    network.socket_fd = -1; // Initialize socket_fd
    network.host = NULL; // Initialize host
    network.port = 0; // Initialize port
}

int network_connect(const char* host, int port) {
    // Simulate a connection attempt
    SMC_LOG("INFO", "Attempting to connect...");
    // Here you would implement actual connection logic
    return 0; // Return success for this example
}

void network_disconnect() {
    // Simulate disconnection logic
    SMC_LOG("INFO", "Disconnecting...");
}

// Example of using the network module
void my_function() {
    network_init(); // Initialize the network module
    if (network_connect("example.com", 80) == 0) {
        SMC_LOG("INFO", "Connected to network successfully");
    } else {
        SMC_ERROR(1, "Failed to connect to network");
    }
    network_disconnect(); // Clean up
}

#endif // SMC_H
