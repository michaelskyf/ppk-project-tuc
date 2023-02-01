#pragma once

#include <vector>
#include <cstddef>
#include <map>

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

enum class GateValue
{
	ZERO = 0,
	ONE = 1,
	UNDEFINED,
};

struct Gate
{
	GateType type = GateType::UNDEFINED;
	std::vector<size_t> inputs;
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
 *			- ZERO or ONE on success
 *			- UNDEFINED on failure
 */
GateValue get_gate_value(Gate& gate, std::map<size_t, Gate>& nodes);