//go:build linux
// +build linux

package deej

import (
	"fmt"
)

type LinuxSessionCommandHandler struct {
	// Add any necessary fields
}

func (lsch *LinuxSessionCommandHandler) HandleCommand(command string) {
	// Implement the logic to handle the command on Linux
	fmt.Printf("Handling command on Linux: %s\n", command)
	// Add your specific logic here
}

func handleKeyCommand(deej Deej, page string, key int) {
	// Access the CommandPages field from the CanonicalConfig
	commandPages := deej.config.CommandPages

	// Check if the requested page exists in the CommandPages map
	pageCommands, ok := commandPages[page]
	if !ok {
		// Handle the case where the page doesn't exist
		fmt.Printf("Page '%s' not found in CommandPages\n", page)
		return
	}

	// Check if the requested key exists in the page's command map
	command, ok := pageCommands[key]
	if !ok {
		// Handle the case where the key doesn't exist
		fmt.Printf("Key '%d' not found in page '%s'\n", key, page)
		return
	}

	// Execute the command
	executeCommand(command.Type, command.Command)
}

func executeCommand(commandType, commandValue string) {
	switch commandType {
	case "ConnectBluetooth":
		// Implement the logic to connect Bluetooth
		fmt.Printf("Connecting Bluetooth on Linux\n")
	case "StartApplication":
		// Implement the logic to start an application
		fmt.Printf("Starting application '%s' on Linux\n", commandValue)
	default:
		// Handle unknown command types
		fmt.Printf("Unknown command type '%s' with value '%s' on Linux\n", commandType, commandValue)
	}
}
