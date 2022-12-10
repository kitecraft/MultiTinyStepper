#pragma once

//This is a shortened version of https://github.com/blemasle/arduino-mcp23017
//Original author: blemasle

#include <Arduino.h>
#include <Wire.h>

enum class MCP23017Port : uint8_t
{
	A = 0,
	B = 1
};
/**
 * Registers addresses.
 * The library use addresses for IOCON.BANK = 0.
 * See "3.2.1 Byte mode and Sequential mode".
 */
enum class MCP23017Register : uint8_t
{
	IODIR_A		= 0x00, 		///< Controls the direction of the data I/O for port A.
	IODIR_B		= 0x01,			///< Controls the direction of the data I/O for port B.
	IPOL_A		= 0x02,			///< Configures the polarity on the corresponding GPIO_ port bits for port A.
	IPOL_B		= 0x03,			///< Configures the polarity on the corresponding GPIO_ port bits for port B.
	GPINTEN_A	= 0x04,			///< Controls the interrupt-on-change for each pin of port A.
	GPINTEN_B	= 0x05,			///< Controls the interrupt-on-change for each pin of port B.
	DEFVAL_A	= 0x06,			///< Controls the default comparaison value for interrupt-on-change for port A.
	DEFVAL_B	= 0x07,			///< Controls the default comparaison value for interrupt-on-change for port B.
	INTCON_A	= 0x08,			///< Controls how the associated pin value is compared for the interrupt-on-change for port A.
	INTCON_B	= 0x09,			///< Controls how the associated pin value is compared for the interrupt-on-change for port B.
	IOCON		= 0x0A,			///< Controls the device.
	GPPU_A		= 0x0C,			///< Controls the pull-up resistors for the port A pins.
	GPPU_B		= 0x0D,			///< Controls the pull-up resistors for the port B pins.
	INTF_A		= 0x0E,			///< Reflects the interrupt condition on the port A pins.
	INTF_B		= 0x0F,			///< Reflects the interrupt condition on the port B pins.
	INTCAP_A	= 0x10,			///< Captures the port A value at the time the interrupt occured.
	INTCAP_B	= 0x11,			///< Captures the port B value at the time the interrupt occured.
	GPIO_A		= 0x12,			///< Reflects the value on the port A.
	GPIO_B		= 0x13,			///< Reflects the value on the port B.
	OLAT_A		= 0x14,			///< Provides access to the port A output latches.
	OLAT_B		= 0x15,			///< Provides access to the port B output latches.
};

inline MCP23017Register operator+(MCP23017Register a, MCP23017Port b) {
	return static_cast<MCP23017Register>(static_cast<uint8_t>(a) + static_cast<uint8_t>(b));
};

class MCP23017
{
private:
	TwoWire* _bus;
	uint8_t _deviceAddr;
	
public:

	/**
	 * Initializes the chip with the default configuration.
	 * Enables Byte mode (IOCON.BANK = 0 and IOCON.SEQOP = 1).
	 * Enables pull-up resistors for all pins. This will only be effective for input pins.
	 * 
	 * See "3.2.1 Byte mode and Sequential mode".
	 */
	void init(uint8_t address, TwoWire& bus = Wire);

	/**
	 * Controls the pins direction on a whole port at once.
	 * 
	 * 1 = Pin is configured as an input.
	 * 0 = Pin is configured as an output.
	 * 
	 * See "3.5.1 I/O Direction register".
	 */
	void portMode(MCP23017Port port, uint8_t directions, uint8_t pullups = 0xFF, uint8_t inverted = 0x00);


	/**
	 * Writes pins state to a whole port.
	 * 
	 * 1 = Logic-high
	 * 0 = Logic-low
	 * 
	 * See "3.5.10 Port register".
	 */
	void writePort(MCP23017Port port, uint8_t value);

	/**
	 * Writes a single register value.
	 */
	void writeRegister(MCP23017Register reg, uint8_t value);
	/**
	 * Writes values to a register pair.
	 * 
	 * For portA and portB variable to effectively match the desired port,
	 * you have to supply a portA register address to reg. Otherwise, values
	 * will be reversed due to the way the MCP23017 works in Byte mode.
	 */
	void writeRegister(MCP23017Register reg, uint8_t portA, uint8_t portB);

};