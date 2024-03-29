/**
 * @file gate.hpp
 *
 * @brief Structures, enums and functions related to the gate representation
 */

#pragma once

#include <vector>
#include <cstddef>
#include <map>

/**
 * @brief Enumerator containing valid gate types
 */
enum class GateType
{
	UNDEFINED,
	INPUT,
	OUTPUT,
	AND,
	NAND,
	OR,
	NOR,
	XOR,
	XNOR,
	NEG,
};

/**
 * @brief Enumerator containing valid values that a gate can have
 */
enum class GateValue
{
	ZERO = 0,
	ONE = 1,
	UNDEFINED,
};

/**
 * @brief Structure used for simulating a single gate
 */
struct Gate
{
	/// Gate type
	GateType type = GateType::UNDEFINED;
	/// Inputs (other nodes that the gate needs to generate output)
	std::vector<size_t> inputs;
	/// Output value
	GateValue value = GateValue::UNDEFINED;
};

/**
 * @brief Recursively get the value of the gate
 *
 * @param[in,out]	gate	Current gate
 *
 * @param[in,out]	nodes	Map of all nodes in the circuit
 *
 * @return
 *			- GateValue::ZERO or GateValue::ONE on success
 *			- GateValue::UNDEFINED on failure
 */
GateValue get_gate_value(Gate& gate, std::map<size_t, Gate>& nodes);