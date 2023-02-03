/**
 * @file parser_circuit.hpp
 *
 * @brief Functions and structures related to parsing the circuit file
 */

#pragma once

#include <cstddef>
#include <vector>
#include <string>
#include "gate.hpp"

/**
 * @brief Contains information about a specific gate/input (intermediate struct between text and struct Gate)
 */
struct ParsedGate
{
	/// Number of line that the gate was read from
	size_t lineNumber;
	/// Gate type (defined in gate.hpp)
	GateType type = GateType::UNDEFINED;
	/// Inputs and outputs for normal gates or input/output nodes when the type is GateType::INPUT or GateType::OUTPUT
	std::vector<size_t> nodes;
};

/**
 * @brief Extract nodes from the circuit file
 *
 * @param[in]	filename	Path to the file containing the circuit
 *
 * @return		Vector of unprocessed logic gates, inputs and outputs
 */
std::vector<ParsedGate> get_circuit(const std::string& filename);