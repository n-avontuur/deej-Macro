package deej

import (
	"fmt"
	"strconv"
)

type (
	Encoder struct {
		function     EncoderFunc
		functionName string
		target       int
	}

	EncoderFunc func(deej *Deej, index int, value float32)

	FuncInfo struct {
		ID       int
		Func     EncoderFunc
		FuncName string
	}
)

var (
	Encoders      []Encoder
	infoFunctions = []FuncInfo{
		{1, controlVolume, "controlVolume"},
		{2, actAsScrollWheel, "actAsScrollWheel"},
		{3, actAsArrowKeys, "actAsArrowKeys"},
		{4, doNothing, "doNothing"},
	}
)

func setupEncoderAmount(encoderAmount int) {
	currentLength := len(Encoders)
	if encoderAmount > currentLength {
		newEncoders := make([]Encoder, encoderAmount)
		copy(newEncoders, Encoders)
		for i := currentLength; i < encoderAmount; i++ {
			newEncoders[i] = Encoder{
				target:       0,
				function:     doNothing,
				functionName: "doNothing",
			}
		}
		Encoders = newEncoders
		fmt.Printf("Setup Encoders[] : %v \n", Encoders)
	} else if encoderAmount <= currentLength {
		Encoders = Encoders[:encoderAmount]
	}
}

func (deej *Deej) assignFunctionToEncoder(encoderNumber string, funcName string, targetName string) {
	fmt.Println("Assign function to encoder")

	// Convert encoder number and check for errors
	encoderNumberInt, err := strconv.Atoi(encoderNumber)
	if err != nil {
		fmt.Println("Could not transform encoderNumber to int:", err)
		return
	}

	// Validate encoder number
	if encoderNumberInt < 0 || encoderNumberInt > len(Encoders) {
		fmt.Printf("Encoder number out of range: number is %d and range is %d\n", encoderNumberInt, len(Encoders))
		return
	}

	// Check if infoFunctions is not empty
	if len(infoFunctions) == 0 {
		fmt.Println("infoFunctions is empty or nil")
		return
	}

	// Find and assign the function
	var functionFound bool
	for _, function := range infoFunctions {
		if function.FuncName == funcName {
			// Check for target name in slider mappings
			if deej.config.SliderMapping == nil {
				fmt.Println("SliderMapping is nil")
				return
			}

			found := false
			deej.config.SliderMapping.iterate(func(sliderIdx int, target []string) {
				fmt.Printf("Target value %d. \n", sliderIdx)
				if target[0] == targetName {
					Encoders[encoderNumberInt].functionName = function.FuncName
					Encoders[encoderNumberInt].function = function.Func
					Encoders[encoderNumberInt].target = sliderIdx
					found = true
					return
				}
			})

			if !found {
				fmt.Println("Target name not found in slider mappings")
			}
			functionFound = true
			break
		}
	}

	if !functionFound {
		fmt.Println("Function name does not match")
	}
}

func controlVolume(deej *Deej, index int, value float32) {
	encoder := Encoders[index]
	moveEvents := []SliderMoveEvent{}
	deej.serial.currentSliderPercentValues[encoder.target] = value
	moveEvents = append(moveEvents, SliderMoveEvent{
		SliderID:     encoder.target,
		PercentValue: value,
	})
	//fmt.Printf("moveEvents : %v", moveEvents)
	if deej.Verbose() {
		deej.logger.Debugw("Slider moved", "event", moveEvents[len(moveEvents)-1])
	}
	// deliver move events if there are any, towards all potential consumers
	if len(moveEvents) > 0 {
		for _, consumer := range deej.serial.sliderMoveConsumers {
			for _, moveEvent := range moveEvents {
				consumer <- moveEvent
			}
		}
	}
}

func actAsScrollWheel(deej *Deej, index int, value float32) {
	fmt.Printf("Acting as scroll wheel with value: %f. \n", value)
}

func actAsArrowKeys(deej *Deej, index int, value float32) {
	fmt.Printf("Acting as arrow keys with value: %f.\n", value)
}

func doNothing(deej *Deej, index int, value float32) {
	fmt.Println("No action assigned")
}
